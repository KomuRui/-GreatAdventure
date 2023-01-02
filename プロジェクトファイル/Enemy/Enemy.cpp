#include "Enemy.h"
#include "../Engine/Model.h"

////定数
namespace
{
    static const float NORMAL_INTERPOLATION_FACTOR = 0.045; //法線を補間するときの補間係数
    static const int MAX_NORMAL_RADIANS = 50;               //法線との最大角度
    static const float RAY_HIT_DISTANCE = 1.0f;             //レイの当たった距離
    static const float MOVE_RAY_HIT_DISTANCE = 0.9f;        //動いているときのレイの当たった距離
    static const float GRAVITY_STRENGTH = 0.083f;           //重力の強さ
    static const float ADD_ROTATION_ANGLE = 0.02f;          //回転するときの加算する角度
    static const float MOVE_SPEED = 0.1f;                   //移動スピード
    static const int SIGN_CHANGE = -1;                      //符号チェンジするために必要
    static const int FEED_BACK_ANGLE = 50;					//反応角度
    static const float FEED_BACK_DISTANCE = 15.0f;			//反応距離
    static const float MIN_PLAYER_DISTANCE = 3.0f;          //Playerとの最小距離
}

//コンストラクタ
Enemy::Enemy(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath,name),acceleration(1), operationTime_(ZERO), hGroundModel_(-1), stateCount_(ZERO),
    rotationAngle_(ZERO), rotationTotal_(ZERO), front_(XMVectorSet(ZERO, ZERO,1, ZERO)), dotX_(ZERO), rotationSign_(1),
    pState_(new EnemyState), isUseGravity_(true), basePos_(ZERO,ZERO,ZERO)
{
}

//初期化
void Enemy::ChildInitialize()
{
    EnemyChildInitialize();
}

//更新の前に一回呼ばれる関数
void Enemy::ChildStartUpdate()
{
    ///////////////初期状態設定///////////////////
    
    //待機状態
    ChangeEnemyState(EnemyStateList::GetEnemyWaitState());

    //探索するときのベースポジション設定
    ARGUMENT_INITIALIZE(basePos_, transform_.position_);

    ///////////////Stageのデータ取得///////////////////

    //モデル番号取得
    hGroundModel_ = pstage_->GethModel();

    ///////////////継承先用の初期化///////////////////

    EnemyChildStartUpdate();

}

//更新
void Enemy::ChildUpdate()
{

    //複数個所で使うので先に宣言しておく
    RayCastData downData;
    downData.start = transform_.position_;         //レイのスタート位置
    downData.dir = VectorToFloat3(down_);          //レイの方向
    Model::AllRayCast(hGroundModel_, &downData);   //レイを発射(All)

    //真下の法線を調べてキャラの上軸を決定する
    CheckUnderNormal(downData);

    //Playerが視角内,指定距離内にいるかどうか調べる
    PlayerNearWithIsCheck();

    //キャラの動き
    MovingOperation();

    //継承先用のアップデート
    EnemyChildUpdate();

    //ステージとの当たり判定
    StageRayCast(downData);
}

//描画
void Enemy::ChildDraw()
{
    //継承先用の描画
    EnemyChildDraw();
}

//真下の法線を調べてキャラの上軸を決定する
void Enemy::CheckUnderNormal(const RayCastData& data)
{
    if (data.hit && (XMVectorGetX(vNormal_) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetY(-vNormal_) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetZ(-vNormal_) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&data.normal)))))
    {
        //元のキャラの上ベクトルvNormalと下の法線の内積を求める
        float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&data.normal)), XMVector3Normalize(vNormal_)));

        //角度が50度以内に収まっていたら(壁とかに上らせないため)
        if (acos(dotX) < XMConvertToRadians(MAX_NORMAL_RADIANS) && acos(dotX) > XMConvertToRadians(-MAX_NORMAL_RADIANS))
        {
            //ちょっと補間
            vNormal_ = XMVector3Normalize((XMVectorLerp(XMVector3Normalize(vNormal_), XMLoadFloat3(&data.normal), NORMAL_INTERPOLATION_FACTOR)));
            down_ = -vNormal_;
        }
    }
}

//レイ(円用)
void Enemy::StageRayCast(const RayCastData& data)
{
    //前
    RayCastData straightData;
    straightData.start = transform_.position_;                                                          //レイのスタート位置
    straightData.dir = VectorToFloat3(XMVector3TransformCoord(STRAIGHT_VECTOR, transform_.mmRotate_));  //レイの方向
    Model::AllRayCast(hGroundModel_, &straightData);                                                    //レイを発射

    //////////////////////////////はみ出した分下げる//////////////////////////////////////

    //前の距離が1.0以下なら
    if (straightData.dist <= RAY_HIT_DISTANCE)
    {
        XMVECTOR dis = { ZERO,ZERO,straightData.dist };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVector3TransformCoord(STRAIGHT_VECTOR, transform_.mmRotate_) - dis));

        //0に初期化
        ZERO_INITIALIZE(operationTime_);
        ZERO_INITIALIZE(rotationTotal_);
        ZERO_INITIALIZE(rotationAngle_);
        ZERO_INITIALIZE(stateCount_);

        //状態を回転に変更
        ChangeEnemyState(EnemyStateList::GetEnemyRotationState());

        //アニメーション停止
        Model::SetAnimFlag(hModel_, false);
    }

    //下の距離が1.0以上かつ重力適用するなら
    if (data.dist >= RAY_HIT_DISTANCE && isUseGravity_)
    {
        transform_.position_ = Float3Add(transform_.position_, VectorToFloat3((-vNormal_) * GRAVITY_STRENGTH));
    }

}

//キャラの動き
void Enemy::MovingOperation()
{
    //状態の更新を呼ぶ
    pState_->Update3D(this);
}

//探索範囲内にいるかどうか
bool Enemy::IsInSearchRange()
{
    //探索範囲内にいる
    if (RangeCalculation(basePos_, transform_.position_) < 8)
        return true;
    else
    {
        //Playerのポジションゲット
        XMFLOAT3 playerPos = GameManager::GetpPlayer()->GetPosition();

        //ベースポジションからPlayerへのベクトル
        XMVECTOR vToPlayer = XMLoadFloat3(&basePos_) - XMLoadFloat3(&transform_.position_);

        //自身からPlayerへのベクトルと自身の前ベクトルとの内積を調べる
        dotX_ = acos(XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)), XMVector3Normalize(vToPlayer))));

        //もしEnemyが向いている方向とベースポジションまでの方向の角度がFEED_BACK_ANGLEいないなら
        if (dotX_ < XMConvertToRadians(FEED_BACK_ANGLE) && dotX_ > XMConvertToRadians(-FEED_BACK_ANGLE))
            return true;
        else
            return false;
    }
}

///////////////////AI行動関数////////////////////

//待機
void Enemy::Wait()
{
    //状態が状態変化の時間より大きくなったら
    if (stateCount_ > operationTime_)
    {
        //0に初期化
        ZERO_INITIALIZE(operationTime_);

        //状態をMoveに変更
        ChangeEnemyState(EnemyStateList::GetEnemyMoveState());
    }
}

//行動
void Enemy::Move()
{
    //もし探索範囲にいないのなら
    if (!IsInSearchRange())
    {
        //回転状態に
        ChangeEnemyState(EnemyStateList::GetEnemyRotationState());

        //回転状態の回転角度をベースポジションに動くように設定する
        ARGUMENT_INITIALIZE(rotationAngle_,dotX_);
    }

    //アニメーション開始
    Model::SetAnimFlag(hModel_, true);

    //移動して自身のtransformに反映
    transform_.position_ = Float3Add(transform_.position_, VectorToFloat3(XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)) * MOVE_SPEED));

    //高さ合わせるためにレイを飛ばす
    RayCastData downData;
    downData.start = transform_.position_;         //レイのスタート位置
    downData.dir = VectorToFloat3(down_);          //レイの方向
    Model::AllRayCast(hGroundModel_, &downData);   //レイを発射(All)

    //地形の高さに合わせる
    //当たった距離が0.9fより小さいなら
    if (downData.dist < MOVE_RAY_HIT_DISTANCE)
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&downData.pos) + vNormal_);

    //状態が状態変化の時間より大きくなったら
    if (stateCount_ > operationTime_)
    {
        //0に初期化
        ZERO_INITIALIZE(operationTime_);
        ZERO_INITIALIZE(stateCount_);

        //状態を回転に設定
        ChangeEnemyState(EnemyStateList::GetEnemyRotationState());

        //アニメーション停止
        Model::SetAnimFlag(hModel_, false);
    }
}

//回転
void Enemy::Rotation()
{
    //アニメーション停止
    Model::SetAnimFlag(hModel_, false);

    //回転
    angle_ += ADD_ROTATION_ANGLE * rotationSign_;
    rotationTotal_ += ADD_ROTATION_ANGLE;

    //回転角度より回転総数が多くなったら
    if (rotationTotal_ > rotationAngle_)
    {
        //0に初期化
        ZERO_INITIALIZE(operationTime_);
        ZERO_INITIALIZE(rotationTotal_);
        ZERO_INITIALIZE(rotationAngle_);

        //状態を待機に設定
        ChangeEnemyState(EnemyStateList::GetEnemyWaitState());
    }
}

//Playerが視角内,指定距離内にいるかどうか調べる
void Enemy::PlayerNearWithIsCheck()
{
    //もしPlayerのポインタがNullになっていたら処理をしない
    if (GameManager::GetpPlayer() == nullptr) return;

    //Playerのポジションゲット
    XMFLOAT3 playerPos = GameManager::GetpPlayer()->GetPosition();

    //自身からPlayerへのベクトル
    XMVECTOR vToPlayer = XMLoadFloat3(&playerPos) - XMLoadFloat3(&transform_.position_);

    //自身からPlayerへのベクトルと自身の前ベクトルとの内積を調べる
    dotX_ = acos(XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)), XMVector3Normalize(vToPlayer))));

    //どっち方向に回転させるか決めるために外積を求める
    XMVECTOR cross = XMVector3Cross(XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)), XMVector3Normalize(vToPlayer));

    //符号が違うなら
    if (signbit(XMVectorGetY(cross)) != signbit(XMVectorGetY(vNormal_)))
        dotX_ *= SIGN_CHANGE;


    //視角内,指定距離内にいるなら
    if (dotX_ < XMConvertToRadians(FEED_BACK_ANGLE) && dotX_ > XMConvertToRadians(-FEED_BACK_ANGLE) &&
        RangeCalculation(playerPos, transform_.position_) < FEED_BACK_DISTANCE)
    {
        //死んでないならPlayerの方向を向く
        if(pState_ != EnemyStateList::GetEnemyDieState())
            angle_ += dotX_;

        //死んでいないのなら移動状態に
        if(pState_ != EnemyStateList::GetEnemyKnockBackState() && pState_ != EnemyStateList::GetEnemyDieState())
            ChangeEnemyState(EnemyStateList::GetEnemyMoveState());

        //Playerとの距離が最小距離以内かつ死んでないのなら待機状態に
        if (RangeCalculation(transform_.position_, GameManager::GetpPlayer()->GetPosition()) < MIN_PLAYER_DISTANCE && pState_ != EnemyStateList::GetEnemyKnockBackState() && EnemyStateList::GetEnemyDieState())
            ChangeEnemyState(EnemyStateList::GetEnemyWaitState());

        //継承先用の関数(視角内、射程内にPlayerがいるなら)
        PlayerWithIf();
    }
    else
        //継承先用の関数(視角内、射程内にPlayerがないなら)
        NotPlayerWithIf();
}

//状態チェンジ
void Enemy::ChangeEnemyState(EnemyState* state)
{
    //同じ状態じゃないのなら
    if (pState_ != state)
    {
        //状態変更
        ARGUMENT_INITIALIZE(pState_, state);
        pState_->Enter(this);
    }
}

