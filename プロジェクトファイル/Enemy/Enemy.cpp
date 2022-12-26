#include "Enemy.h"
#include "../Engine/Model.h"

////定数
namespace
{
    static const float NORMAL_INTERPOLATION_FACTOR = 0.045; //法線を補間するときの補間係数
    static const int MAX_NORMAL_RADIANS = 50;               //法線との最大角度
    static const float RAY_HIT_DISTANCE = 1.0f;             //レイの当たった距離
    static const float GRAVITY_STRENGTH = 0.083f;           //重力の強さ
}

//コンストラクタ
Enemy::Enemy(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath,name),acceleration(1), aiState_(MOVE), operationTime_(ZERO), hGroundModel_(-1), stateCount_(ZERO),
    rotationAngle_(ZERO), rotationTotal_(ZERO), front_(XMVectorSet(ZERO, ZERO,1, ZERO)), dotX_(ZERO), rotationSign_(1),
    pState_(new EnemyState)
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

    //初期状態の設定
    ChangeEnemyState(EnemyStateList::GetEnemyWaitState());

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

//ステージに合わせてPlayerを回転
void Enemy::RotationInStage()
{
    //Xのベクトルを抜き取る
    float dotX = 0;

    //自キャラまでのベクトルと自キャラの真上のベクトルが少しでも違うなら
    if (XMVectorGetX(up_) != XMVectorGetX(vNormal_) || XMVectorGetY(up_) != XMVectorGetY(vNormal_) || XMVectorGetZ(up_) != XMVectorGetZ(vNormal_))
    {
        //自キャラまでのベクトルと自キャラの真上のベクトルの内積を求める
        XMVECTOR vecDot = XMVector3Dot(XMVector3Normalize(up_), XMVector3Normalize(vNormal_));

        //Xのベクトルを抜き取る
        dotX = XMVectorGetX(vecDot);
    }

    XMVECTOR cross = XMVector3Cross(up_, vNormal_);

    if (!pstage_->GetthreeDflag())
    {

        totalMx_ = XMMatrixIdentity();
        transform_.mmRotate_ = totalMx_;

        transform_.mmRotate_ *= XMMatrixRotationAxis(UP_VECTOR, angle_);

    }
    else
    {
        if (dotX != 0 && dotX <= 1 && dotX >= -1)
        {
            totalMx_ *= XMMatrixRotationAxis(cross, acos(dotX));
            transform_.mmRotate_ = totalMx_;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);
        }
        else
        {
            transform_.mmRotate_ = totalMx_;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);

        }
    }

    //自キャラまでのベクトルと自キャラの真上のベクトルが少しでも違うなら
    if (XMVectorGetX(up_) != XMVectorGetX(vNormal_) || XMVectorGetY(up_) != XMVectorGetY(vNormal_) || XMVectorGetZ(up_) != XMVectorGetZ(vNormal_))
    {
        up_ = vNormal_;
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

    //下の距離が1.0以上なら
    if (data.dist >= RAY_HIT_DISTANCE)
    {
        transform_.position_ = Float3Add(transform_.position_, VectorToFloat3((-vNormal_) * GRAVITY_STRENGTH));
    }

}

//キャラの動き
void Enemy::MovingOperation()
{
    //状態の更新を呼ぶ
    pState_->Update3D(this);
    ////状態によってEnemyの行動を変化させる
    //switch (aiState_)
    //{
    ////待機
    //case WAIT:

    //    //WAITから次の状態に変わるまでの時間を設定
    //    if (operationTime_ == ZERO)
    //    {
    //        operationTime_ = (rand() % 13 + 6) * 10;
    //        ZERO_INITIALIZE(stateCount_);
    //    }

    //    Wait();
    //    break;
    ////移動
    //case MOVE:

    //    //MOVEから次の状態に変わるまでの時間を設定
    //    if (operationTime_ == ZERO)
    //    {
    //        operationTime_ = (rand() % 19 + 12) * 10;
    //        ZERO_INITIALIZE(stateCount_);
    //    }

    //    Move();
    //    break;
    ////回転
    //case ROTATION:

    //    //回転する角度を設定
    //    if (rotationAngle_ == ZERO)
    //    {
    //        rotationSign_ = rand() % 2 == 1 ? 1 : -1;
    //        rotationAngle_ = XMConvertToRadians((rand() % 141) + 40);
    //        ZERO_INITIALIZE(stateCount_);
    //    }

    //    //回転は任意の角度まで回転したら状態が変わる
    //    Rotation();
    //    break;

    ////ノックバックして死亡
    //case KNOCKBACK_DIE:

    //    KnockBackDie();
    //    break;

    ////死亡
    //case DIE:

    //    Die();
    //    break;

    ////どれでもない時
    //default:

    //    //状態を待機に設定
    //    aiState_ = WAIT;

    //    //0に初期化
    //    ZERO_INITIALIZE(operationTime_);
    //    ZERO_INITIALIZE(stateCount_);

    //    break;
    //}

    ////状態秒数増やす
    //stateCount_++;
}


///////////////////AI行動関数////////////////////

//待機
void Enemy::Wait()
{
    ////状態が状態変化の時間より大きくなったら
    //if (stateCount_ > operationTime_)
    //{
    //    //0に初期化
    //    ZERO_INITIALIZE(operationTime_);

    //    //状態をMoveに変更
    //    aiState_ = MOVE;
    //}
}

//行動
void Enemy::Move()
{
    //アニメーション開始
    Model::SetAnimFlag(hModel_, true);

    //XMFLOAT3型の1Fream動く量を格納する変数
    XMFLOAT3 move = { ZERO,ZERO,ZERO };

    //進行ベクトルを自身の回転行列で回転させてmoveに格納(1Fream動く量を0.1にしておく)
    XMStoreFloat3(&move,XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)) / 10);

    //自身のtransformに加算
    transform_.position_ = { transform_.position_.x + move.x,transform_.position_.y + move.y,transform_.position_.z + move.z };

    //高さ合わせるためにレイを飛ばす
    RayCastData downData;
    downData.start = transform_.position_;         //レイのスタート位置
    downData.dir = VectorToFloat3(down_);          //レイの方向
    Model::AllRayCast(hGroundModel_, &downData);   //レイを発射(All)

    //地形の高さに合わせる
    //当たった距離が0.9fより小さいなら
    if (downData.dist < 0.9f)
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&downData.pos) + vNormal_);

    ////状態が状態変化の時間より大きくなったら
    //if (stateCount_ > operationTime_)
    //{
    //    //0に初期化
    //    ZERO_INITIALIZE(operationTime_);

    //    //状態を回転に設定
    //    aiState_ = ROTATION;

    //    //アニメーション停止
    //    Model::SetAnimFlag(hModel_, false);
    //}
}

//回転
void Enemy::Rotation()
{
    ////回転
    //angle_ += 0.02 * rotationSign_;
    //rotationTotal_ += 0.02;


    ////回転角度より回転総数が多くなったら
    //if (rotationTotal_ > rotationAngle_)
    //{
    //    //0に初期化
    //    ZERO_INITIALIZE(operationTime_);
    //    ZERO_INITIALIZE(rotationTotal_);
    //    ZERO_INITIALIZE(rotationAngle_);

    //    //状態を待機に設定
    //    aiState_ = WAIT;
    //}
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
        dotX_ *= -1;


    //視角内,指定距離内にいるなら
    if (dotX_ < XMConvertToRadians(50) && dotX_ > XMConvertToRadians(-50) &&
        RangeCalculation(playerPos, transform_.position_) < 15.0f)
    {
        //死んでないなら
        if(EnemyStateList::GetEnemyDieState())
            //Playerの方を向くための角度を足す
            angle_ += dotX_;

        //死んでいないのなら
        if(pState_ != EnemyStateList::GetEnemyKnockBackState() && pState_ != EnemyStateList::GetEnemyDieState())
            ChangeEnemyState(EnemyStateList::GetEnemyMoveState());

        //Playerとの距離が3以内かつ死んでないのなら
        if (RangeCalculation(transform_.position_, GameManager::GetpPlayer()->GetPosition()) < 3 && pState_ != EnemyStateList::GetEnemyKnockBackState() && EnemyStateList::GetEnemyDieState())
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

