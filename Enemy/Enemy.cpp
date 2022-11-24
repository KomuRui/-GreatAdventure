#include "Enemy.h"
#include "../Engine/Model.h"

Enemy::Enemy(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath,name),acceleration(1), aiState_(MOVE), operationTime_(0), hGroundModel_(-1), stateCount_(0),
    rotationAngle_(0), rotationTotal_(0), front_(XMVectorSet(0,0,1,0)), dotX_(0), rotationSign_(1)
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

    ///////////////Player探す////////////////

    pPlayer_ = (Player*)FindObject("Player");

    ///////////////Stageのデータ取得///////////////////

    //モデル番号取得
    hGroundModel_ = pstage_->GethModel();

    ///////////////継承先用の初期化///////////////////

    EnemyChildStartUpdate();

}

//更新
void Enemy::ChildUpdate()
{
#pragma region キャラの下にレイを打ってそこの法線を求める

    RayCastData data[MAX_RAY_SIZE];                  //レイの個数分作成
    data[Under].start = transform_.position_;         //レイの発射位置
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, Down);//動かす値
    data[Under].dir = moveY2;
    Model::RayCast(hGroundModel_, &data[Under]);      //レイを発射(All)

    if (data[Under].hit && (XMVectorGetX(vNormal) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&data[Under].normal))) || XMVectorGetY(-vNormal) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&data[Under].normal))) || XMVectorGetZ(-vNormal) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&data[Under].normal)))))
    {
        //元のキャラの上ベクトルvNormalと下の法線の内積を求める
        float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&data[Under].normal)), XMVector3Normalize(vNormal)));

        //角度が60度以内に収まっていたら(壁とかに上らせないため)
        if (acos(dotX) < XMConvertToRadians(50) && acos(dotX) > XMConvertToRadians(-50))
        {
            //ちょっと補間
            vNormal = XMVector3Normalize((XMLoadFloat3(&data[Under].normal) + vNormal) + vNormal * 30);
            Down = -vNormal;
        }

    }
#pragma endregion

    //Playerが視角内,指定距離内にいるかどうか調べる
    PlayerNearWithIsCheck();

    //キャラの動き
    MovingOperation(data);

    //継承先用のアップデート
    EnemyChildUpdate();

    //ステージとの当たり判定
    StageRayCast(data);
}

//描画
void Enemy::ChildDraw()
{
    //継承先用の描画
    EnemyChildDraw();
}

//ステージに合わせてPlayerを回転
void Enemy::RotationInStage()
{
    //Xのベクトルを抜き取る
    float dotX = 0;

    //自キャラまでのベクトルと自キャラの真上のベクトルが少しでも違うなら
    if (XMVectorGetX(Up) != XMVectorGetX(vNormal) || XMVectorGetY(Up) != XMVectorGetY(vNormal) || XMVectorGetZ(Up) != XMVectorGetZ(vNormal))
    {
        //自キャラまでのベクトルと自キャラの真上のベクトルの内積を求める
        XMVECTOR vecDot = XMVector3Dot(XMVector3Normalize(Up), XMVector3Normalize(vNormal));

        //Xのベクトルを抜き取る
        dotX = XMVectorGetX(vecDot);
    }

    XMVECTOR cross = XMVector3Cross(Up, vNormal);

    if (!pstage_->GetthreeDflag())
    {
        XMVECTOR TwoDUp = { 0, 1, 0, 0 };

        TotalMx = XMMatrixIdentity();
        transform_.mmRotate_ = TotalMx;

        transform_.mmRotate_ *= XMMatrixRotationAxis(TwoDUp, Angle);

    }
    else
    {
        if (dotX != 0 && dotX <= 1 && dotX >= -1)
        {
            TotalMx *= XMMatrixRotationAxis(cross, acos(dotX));
            transform_.mmRotate_ = TotalMx;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal, Angle);
        }
        else
        {
            transform_.mmRotate_ = TotalMx;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal, Angle);

        }
    }

    //自キャラまでのベクトルと自キャラの真上のベクトルが少しでも違うなら
    if (XMVectorGetX(Up) != XMVectorGetX(vNormal) || XMVectorGetY(Up) != XMVectorGetY(vNormal) || XMVectorGetZ(Up) != XMVectorGetZ(vNormal))
    {
        Up = vNormal;
    }
}

//レイ(円用)
void Enemy::StageRayCast(RayCastData* data)
{
    //前
    data[Straight].start = transform_.position_;     //レイの発射位置
    XMVECTOR moveZ = { 0,0,1 };                      //動かす値
    moveZ = XMVector3TransformCoord(moveZ, transform_.mmRotate_);
    XMStoreFloat3(&data[Straight].dir, moveZ);
    Model::RayCast(hGroundModel_, &data[Straight]);  //レイを発射

    //////////////////////////////はみ出した分下げる//////////////////////////////////////

    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    if (data[Straight].dist <= 1)
    {
        XMVECTOR dis = { 0,0,data[Straight].dist };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveZ - dis));

        //0に初期化
        ZERO_INITIALIZE(operationTime_);
        ZERO_INITIALIZE(rotationTotal_);
        ZERO_INITIALIZE(rotationAngle_);
        ZERO_INITIALIZE(stateCount_);

        //状態を回転に変更
        aiState_ = ROTATION;

        //アニメーション停止
        Model::SetAnimFlag(hModel_, false);
    }

    if (data[Under].dist >= 1)//3
    {
        XMFLOAT3 moveL;

        XMStoreFloat3(&moveL, (-vNormal) / 12);

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
    }

}

//キャラの動き
void Enemy::MovingOperation(RayCastData* data)
{
    //状態によってEnemyの行動を変化させる
    switch (aiState_)
    {
    //待機
    case WAIT:

        //WAITから次の状態に変わるまでの時間を設定
        if (operationTime_ == ZERO)
        {
            operationTime_ = (rand() % 13 + 6) * 10;
            ZERO_INITIALIZE(stateCount_);
        }

        Wait();
        break;
    //移動
    case MOVE:

        //MOVEから次の状態に変わるまでの時間を設定
        if (operationTime_ == ZERO)
        {
            operationTime_ = (rand() % 19 + 12) * 10;
            ZERO_INITIALIZE(stateCount_);
        }

        Move(data);
        break;
    //回転
    case ROTATION:

        //回転する角度を設定
        if (rotationAngle_ == ZERO)
        {
            rotationSign_ = rand() % 2 == 1 ? 1 : -1;
            rotationAngle_ = XMConvertToRadians((rand() % 141) + 40);
            ZERO_INITIALIZE(stateCount_);
        }

        //回転は任意の角度まで回転したら状態が変わる
        Rotation();
        break;

    //ノックバックして死亡
    case KNOCKBACK_DIE:

        KnockBackDie();
        break;

    //死亡
    case DIE:

        Die();
        break;

    //どれでもない時
    default:

        //状態を待機に設定
        aiState_ = WAIT;

        //0に初期化
        ZERO_INITIALIZE(operationTime_);
        ZERO_INITIALIZE(stateCount_);

        break;
    }

    //状態秒数増やす
    stateCount_++;
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
        aiState_ = MOVE;
    }
}

//行動
void Enemy::Move(RayCastData* data)
{
    //アニメーション開始
    Model::SetAnimFlag(hModel_, true);

    //XMFLOAT3型の1Fream動く量を格納する変数
    XMFLOAT3 move = { 0,0,0 };

    //進行ベクトルを自身の回転行列で回転させてmoveに格納(1Fream動く量を0.1にしておく)
    XMStoreFloat3(&move,XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)) / 10);

    //自身のtransformに加算
    transform_.position_ = { transform_.position_.x + move.x,transform_.position_.y + move.y,transform_.position_.z + move.z };

    //地形の高さに合わせる
    //当たった距離が0.9fより小さいなら
    if (data[Under].dist < 0.9f)
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&data[Under].pos) + vNormal);

    //状態が状態変化の時間より大きくなったら
    if (stateCount_ > operationTime_)
    {
        //0に初期化
        ZERO_INITIALIZE(operationTime_);

        //状態を回転に設定
        aiState_ = ROTATION;

        //アニメーション停止
        Model::SetAnimFlag(hModel_, false);
    }
}

//回転
void Enemy::Rotation()
{
    //回転
    Angle += 0.02 * rotationSign_;
    rotationTotal_ += 0.02;

    if (Angle > XMConvertToRadians(TWOPI_DEGREES))
        Angle = XMConvertToRadians(ZEROPI_DEGREES);

    //回転角度より回転総数が多くなったら
    if (rotationTotal_ > rotationAngle_)
    {
        //0に初期化
        ZERO_INITIALIZE(operationTime_);
        ZERO_INITIALIZE(rotationTotal_);
        ZERO_INITIALIZE(rotationAngle_);

        //状態を待機に設定
        aiState_ = WAIT;
    }
}

//Playerが視角内,指定距離内にいるかどうか調べる
void Enemy::PlayerNearWithIsCheck()
{
    //もしPlayerのポインタがNullptrになっていたら処理をしない
    if (pPlayer_ == nullptr) return;

    //Playerのポジションゲット
    XMFLOAT3 playerPos = pPlayer_->GetPosition();

    //自身からPlayerへのベクトル
    XMVECTOR vToPlayer = XMLoadFloat3(&playerPos) - XMLoadFloat3(&transform_.position_);

    //自身からPlayerへのベクトルと自身の前ベクトルとの内積を調べる
    dotX_ = acos(XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)), XMVector3Normalize(vToPlayer))));

    //どっち方向に回転させるか決めるために外積を求める
    XMVECTOR cross = XMVector3Cross(XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)), XMVector3Normalize(vToPlayer));

    //符号が違うなら
    if (signbit(XMVectorGetY(cross)) != signbit(XMVectorGetY(vNormal)))
        dotX_ *= -1;


    //視角内,指定距離内にいるなら
    if (dotX_ < XMConvertToRadians(50) && dotX_ > XMConvertToRadians(-50) &&
        Transform::RangeCalculation(playerPos, transform_.position_) < 15.0f)
    {
        //死んでないなら
        if(aiState_ != DIE)
            //Playerの方を向くための角度を足す
            Angle += dotX_;

        //死んでいないのなら
        if(aiState_ != KNOCKBACK_DIE && aiState_ != DIE)
             aiState_ = MOVE;

        //Playerとの距離が１以内かつ死んでないのなら
        if (Transform::RangeCalculation(transform_.position_, pPlayer_->GetPosition()) < 3 && aiState_ != KNOCKBACK_DIE && aiState_ != DIE)
            aiState_ = WAIT;

        //継承先用の関数(視角内、射程内にPlayerがいるなら)
        PlayerWithIf();
    }
    else
        //継承先用の関数(視角内、射程内にPlayerがないなら)
        NotPlayerWithIf();
}

//Playerの方向へ移動
void Enemy::MovingLookPlayer()
{
    
}
