#include "Player3D.h"
#include "../Engine/Camera.h"
#include "../Engine/Light.h"
#include "../Block/Block.h"


//定数
namespace
{
    //Playerのパラメータを保存してあるパス
    LPCTSTR parameterPath = "Parameter/Player/PlayerParameter.ini";

    ///////////////キャラの必要な情報///////////////////

    static const float GRAVITY_ADDITION = 0.03f;    //重力の加算値

    ////////////////カメラ///////////////////

    static const float CAMERA_INTERPOLATION_FACTOR = GetPrivateProfilefloat("CAMERA", "CamFactor", "0.08", parameterPath);  //カメラの移動を補間するときの補間係数
    static const float CAM_SHOULDER_ADD_VALUE = 0.5f; //ショルダーでカメラ操作する時の加算する値
    static const float CAM_STICR_ADD_VALUE = 0.03f;   //スティックRでカメラを操作するときの加算する値
}

//コンストラクタ
Player3D::Player3D(GameObject* parent)
	:PlayerBase(parent)
{
}

//更新
void Player3D::ChildPlayerUpdate()
{
    MovingOperation();       //Player操作
    RotationInStage();       //ステージに合わせて回転
    StageRayCast();          //ステージとの当たり判定
}

//プレイヤー操作
void Player3D::MovingOperation()
{
    //今の状態の動き
    pState_->Update3D(this);

    //Bを押したらカメラの位置変更
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
    {
        //カメラの状態変更
        camStatus_ = (camStatus_ == LONG) ? SHORT
            : LONG;
    }

    //左ショルダーを押したら角度変更
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_LEFT_SHOULDER)) camAngle_ += CAM_SHOULDER_ADD_VALUE;

    //右ショルダーを押したら角度変更
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_RIGHT_SHOULDER)) camAngle_ -= CAM_SHOULDER_ADD_VALUE;

    //右スティックでカメラの角度かえる
    if (Input::GetPadStickR().x) camAngle_ += CAM_STICR_ADD_VALUE * Input::GetPadStickR().x;
}

//ステージに合わせて回転
void Player3D::RotationInStage()
{
    //Xのベクトルを抜き取る
    float dotX = ZERO;

    //自キャラまでのベクトルと自キャラの真上のベクトルが少しでも違うなら
    if (TwoVectorNotValue(up_,vNormal_))
    {
        //自キャラまでのベクトルと自キャラの真上のベクトルの内積を求める
        dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(up_), XMVector3Normalize(vNormal_)));
    }

    //エラーの範囲内ではなければ
    if (dotX != ZERO && dotX <= 1 && dotX >= -1)
    {
        //外積を求める(この結果の軸を横軸にする)
        XMVECTOR cross = XMVector3Cross(up_, vNormal_);

        //Playerを回転させるために二つの軸で回転させる
        totalMx_ *= XMMatrixRotationAxis(cross, acos(dotX));
        transform_.mmRotate_ = totalMx_;
        transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);

        //Playerが回転しているなら
        if (IsRotation()) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(cross, acos(dotX))) * XMMatrixRotationAxis(vNormal_, jampRotationPreviousAngle_);

        //カメラの行列用意
        ARGUMENT_INITIALIZE(camMat_,totalMx_);
    }
    else
    {
        //Playerを回転させるために軸で回転させる
        transform_.mmRotate_ = totalMx_;
        transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);

        //Playerが回転しているなら
        if (IsRotation()) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(vNormal_, jampRotationPreviousAngle_));
    }

    //自身の上ベクトル更新
    ARGUMENT_INITIALIZE(up_,vNormal_);
}

//Playerのカメラの処理
void Player3D::PlayerCameraBehavior(XMFLOAT3* pos, XMFLOAT3* tar)
{
    XMFLOAT3 camPos;                                         //最終的なカメラの位置を入れる変数
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);     //transform_.position_のVector型
    vCam_ = camVec_[camStatus_];                             //Playerからカメラのベクトルを作成
    vCam_ = XMVector3TransformCoord(vCam_, camMat_);         //vCamを回す
    vCam_ = XMVector3TransformCoord(vCam_, XMMatrixRotationAxis(vNormal_, camAngle_));

    vPos += vCam_;                   //PlayerのPosにPlayerからカメラのベクトルをたす
    XMStoreFloat3(&camPos, vPos);    //camPosにvPosをXMFLOAT3に変えていれる

    //補間移動
    XMStoreFloat3(tar, XMVectorLerp(XMLoadFloat3(tar), XMLoadFloat3(&transform_.position_), CAMERA_INTERPOLATION_FACTOR));

    //flagがtrueなら位置動かす
    if (isMoveCamPos_)
        XMStoreFloat3(pos, XMVectorLerp(XMLoadFloat3(pos), XMLoadFloat3(&camPos), CAMERA_INTERPOLATION_FACTOR));

    //カメラのいろいろ設定
    Camera::SetUpDirection(vNormal_);
    Camera::SetPosition(*pos);
    Camera::SetTarget(*tar);

    //ライトの位置設定
    XMFLOAT3 lightPos;
    XMStoreFloat3(&lightPos, vNormal_ + XMLoadFloat3(&transform_.position_));
    Light::SetPlayerPosition(XMFLOAT4(lightPos.x, lightPos.y, lightPos.z, ZERO));
}

//レイで当たり判定
void Player3D::StageRayCast()
{
    //各方向
    RayCastData rightData;
    RayCastData leftData;
    RayCastData straightData;
    RayCastData upData;
    RayCastData downData;

    //当たってるか確認
    HitTest(&rightData, RIGHT_VECTOR);
    HitTest(&leftData, LEFT_VECTOR);
    HitTest(&straightData, STRAIGHT_VECTOR);
    HitTest(&upData, UP_VECTOR);
    HitTest(&downData, DOWN_VECTOR);

    ////////////////////////////////はみ出した分下げる//////////////////////////////////////

    //先にベクトル型のポジションを作っておく
    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    //右
    if (rightData.dist <= 1.0)
    {
        XMVECTOR dis = { rightData.dist,ZERO,ZERO };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(RIGHT_VECTOR, transform_.mmRotate_) - dis));
    }

    //左
    if (leftData.dist <= 1.0)
    {
        XMVECTOR dis = { -leftData.dist,ZERO,ZERO };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(LEFT_VECTOR, transform_.mmRotate_) - dis));
    }

    //前
    if (straightData.dist <= 1.0)
    {
        XMVECTOR dis = { ZERO,ZERO,straightData.dist };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(STRAIGHT_VECTOR, transform_.mmRotate_) - dis));
    }

    //上
    if (upData.dist <= 1.0)
    {
        XMVECTOR dis = { ZERO,upData.dist,ZERO };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(UP_VECTOR, transform_.mmRotate_) - dis));

        //状態変更
        ARGUMENT_INITIALIZE(PlayerStateManager::playerState_, PlayerStateManager::playerStanding_);
        PlayerStateManager::playerState_->Enter(this);

        //ブロック情報がnullptrじゃないのなら
        if (upData.block != nullptr)
        {
            //ブロックを当たっている状態にする
            upData.block->SetIsHit(true);
        }
    }

    //下
    if (downData.dist >= 1.0)
    {
        transform_.position_ = Float3Add(transform_.position_, VectorToFloat3((down_ / 10) * acceleration_));
        acceleration_ += GRAVITY_ADDITION;
    }
    else
    {
        //回転じゃないなら
        if (PlayerStateManager::playerState_ != PlayerStateManager::playerRotationning_)
        {
            //状態変更
            PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
            PlayerStateManager::playerState_->Enter(this);
        }

        ARGUMENT_INITIALIZE(acceleration_, 1);
    }
}

//当たり判定
void Player3D::HitTest(RayCastData* data, const XMVECTOR& dir)
{
    data->start = transform_.position_;                                               //レイの発射位置  
    XMStoreFloat3(&data->dir, XMVector3TransformCoord(dir, transform_.mmRotate_));    //レイの方向
    Model::AllRayCast(hGroundModel_, data);                                           //レイを発射
}

