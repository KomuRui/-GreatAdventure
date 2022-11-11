#include "Enemy.h"
#include "../Engine/Model.h"

Enemy::Enemy(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath,name),acceleration(1), aiState_(MOVE), operationTime_(0), hGroundModel_(-1), stateCount_(0),
    moveDir_(XMVectorSet(0, 0, 1, 0)),rotationAngle_(0), rotationTotal_(0)
{
}

//初期化
void Enemy::ChildInitialize()
{
}

//更新の前に一回呼ばれる関数
void Enemy::ChildStartUpdate()
{
    ///////////////Stageの各データ取得///////////////////

    //モデル番号取得
    hGroundModel_ = pstage_->GethModel();
}

//更新
void Enemy::UpdateMove()
{
#pragma region キャラの下にレイを打ってそこの法線を求める

    RayCastData dataNormal;
    dataNormal.start = transform_.position_;         //レイの発射位置
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, Down);//動かす値
    dataNormal.dir = moveY2;
    Model::RayCast(hGroundModel_, &dataNormal);      //レイを発射(All)

    if (dataNormal.hit && (XMVectorGetX(vNormal) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&dataNormal.normal))) || XMVectorGetY(-vNormal) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&dataNormal.normal))) || XMVectorGetZ(-vNormal) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&dataNormal.normal)))))
    {
        //元のキャラの上ベクトルvNormalと下の法線の内積を求める
        float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&dataNormal.normal)), XMVector3Normalize(vNormal)));

        //角度が60度以内に収まっていたら(壁とかに上らせないため)
        if (acos(dotX) < XMConvertToRadians(60) && acos(dotX) > XMConvertToRadians(-60))
        {
            //ちょっと補間
            vNormal = XMVector3Normalize((XMLoadFloat3(&dataNormal.normal) + vNormal) + vNormal * 30);
            Down = -vNormal;
        }

    }
#pragma endregion

    //キャラの動き
    MovingOperation();

    //Playerをステージに合わせて回転
    RotationInStage();

    //ステージとの当たり判定
    StageRayCast();
}

//描画
void Enemy::ChildDraw()
{
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
void Enemy::StageRayCast()
{
    RayCastData data[MAX_RAY_SIZE];                  //レイの個数分作成

    //右
    data[Right].start = transform_.position_;        //レイの発射位置
    XMVECTOR moveX = { 1,0,0 };                      //動かす値
    moveX = XMVector3TransformCoord(moveX, transform_.mmRotate_);
    XMStoreFloat3(&data[Right].dir, moveX);
    Model::RayCast(hGroundModel_, &data[Right]);     //レイを発射

    //左
    data[Left].start = transform_.position_;         //レイの発射位置
    XMVECTOR moveX2 = { -1,0,0 };                    //動かす値
    moveX2 = XMVector3TransformCoord(moveX2, transform_.mmRotate_);
    XMStoreFloat3(&data[Left].dir, moveX2);
    Model::RayCast(hGroundModel_, &data[Left]);      //レイを発射

    //前
    data[Straight].start = transform_.position_;     //レイの発射位置
    XMVECTOR moveZ = { 0,0,1 };                      //動かす値
    moveZ = XMVector3TransformCoord(moveZ, transform_.mmRotate_);
    XMStoreFloat3(&data[Straight].dir, moveZ);
    Model::RayCast(hGroundModel_, &data[Straight]);  //レイを発射s

    //後
    data[Back].start = transform_.position_;         //レイの発射位置
    XMVECTOR moveZ2 = { 0,0,-1 };                    //動かす値
    moveZ2 = XMVector3TransformCoord(moveZ2, transform_.mmRotate_);
    XMStoreFloat3(&data[Back].dir, moveZ2);
    Model::RayCast(hGroundModel_, &data[Back]);      //レイを発射

    //上
    data[Top].start = transform_.position_;         //レイの発射位置]
    XMVECTOR moveY = { 0,1,0 };                    //動かす値
    moveY = XMVector3TransformCoord(moveY, transform_.mmRotate_);
    XMStoreFloat3(&data[Top].dir, moveY);
    Model::RayCast(hGroundModel_, &data[Top]);      //レイを発射

    //下
    data[Under].start = transform_.position_;         //レイの発射位置
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, -vNormal);//動かす値
    data[Under].dir = moveY2;
    Model::RayCast(hGroundModel_, &data[Under]);      //レイを発射

    //////////////////////////////はみ出した分下げる//////////////////////////////////////

    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    if (data[Right].dist <= 1)
    {
        XMVECTOR dis = { data[Right].dist,0,0 };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveX - dis));
    }
    if (data[Left].dist <= 1)
    {
        XMVECTOR dis = { -data[Left].dist,0,0 };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveX2 - dis));
    }
    if (data[Straight].dist <= 1)
    {
        XMVECTOR dis = { 0,0,data[Straight].dist };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveZ - dis));

        //状態を回転に変更
        aiState_ = ROTATION;
    }
    if (data[Back].dist <= 1)
    {
        XMVECTOR dis = { 0,0,-data[Back].dist };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveZ2 - dis));
    }

    if (data[Top].dist <= 1)
    {
        XMVECTOR dis = { 0,data[Top].dist,0 };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveY - dis));
    }

    if (data[Under].dist >= 1)//3
    {
        XMFLOAT3 moveL;

        XMStoreFloat3(&moveL, (-vNormal) / 10);

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
    }

}

//キャラの動き
void Enemy::MovingOperation()
{
    //状態によってEnemyの行動を変化させる
    switch (aiState_)
    {
    //待機
    case WAIT:

        //WAITから次の状態に変わるまでの時間を設定
        if (operationTime_ == 0)
        {
            operationTime_ = (rand() % 13 + 6) * 10;
            stateCount_ = 0;
        }

        Wait();
        break;
    //移動
    case MOVE:

        //MOVEから次の状態に変わるまでの時間を設定
        if (operationTime_ == 0)
        {
            operationTime_ = (rand() % 19 + 12) * 10;
            stateCount_ = 0;
        }

        Move();
        break;
    //回転
    case ROTATION:

        if (rotationAngle_ == 0)
        {
            rotationAngle_ = XMConvertToRadians((rand() % 141) + 40);
            stateCount_ = 0;
        }

        //回転は任意の角度まで回転したら状態が変わる
        Rotation();
        break;
    //どれでもない時
    default:
        aiState_ = WAIT;
        operationTime_ = 0;
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
        operationTime_ = 0;
        aiState_ = MOVE;
    }
}

//行動
void Enemy::Move()
{
    //XMFLOAT3型の1Fream動く量を格納する変数
    XMFLOAT3 move;

    //進行ベクトルを自身の回転行列で回転させてmoveに格納(1Fream動く量を0.1にしておく)
    XMStoreFloat3(&move,XMVector3Normalize(XMVector3TransformCoord(moveDir_, transform_.mmRotate_)) / 10);

    //自身のtransformに加算
    transform_.position_ = { transform_.position_.x + move.x,transform_.position_.y + move.y,transform_.position_.z + move.z };

    //状態が状態変化の時間より大きくなったら
    if (stateCount_ > operationTime_)
    {
        operationTime_ = 0;
        aiState_ = ROTATION;
    }
}

//回転
void Enemy::Rotation()
{
    //回転
    Angle += 0.01;

    if (Angle > XMConvertToRadians(TWOPI_DEGREES))
        Angle = XMConvertToRadians(ZEROPI_DEGREES);

    if (stateCount_ > rotationAngle_) operationTime_ = 0;
}
