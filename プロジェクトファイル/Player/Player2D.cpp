#include "Player2D.h"
#include "../Engine/GameObject/Camera.h"
#include "../Engine/GameObject/Light.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/AudioManager/PlayerAudioManager/PlayerAudioManager.h"
#include "../Engine/ResourceManager/Audio.h"

//定数
namespace
{
    //Playerのパラメータを保存してあるパス
    LPCTSTR parameterPath = "Parameter/Player/PlayerParameter.ini";

    ///////////////キャラの必要な情報///////////////////

    static const float GRAVITY_ADDITION = 0.03f;    //重力の加算値
    static const float PLAYER_MODEL_SIZE_X = 1.0f;  //PlayerのXのモデルサイズ
    static const float PLAYER_MODEL_SIZE_Y = 2.0f;  //PlayerのYのモデルサイズ

    ////////////////ライト///////////////////

    static const float LIGHT_POS_Z = GetPrivateProfilefloat("LIGHT", "LightZPos", "2", parameterPath);  //ライトのZのポジション

    ////////////////カメラ///////////////////

    static const float CAMERA_INTERPOLATION_FACTOR = GetPrivateProfilefloat("CAMERA", "CamFactor", "0.08", parameterPath);  //カメラの移動を補間するときの補間係数
    static const float CAM_POS_2D_Z = GetPrivateProfilefloat("CAMERA", "CamPos2DZ", "20", parameterPath);                   //2Dの時のカメラのZの位置
}

//コンストラクタ
Player2D::Player2D(GameObject* parent)
    :PlayerBase(parent)
{
}

//更新
void Player2D::ChildPlayerUpdate()
{
    RotationInStage();       //ステージに合わせて回転
    MovingOperation();       //Player操作
    StageRayCast();          //ステージとの当たり判定
}

//プレイヤー操作
void Player2D::MovingOperation()
{
    //今の状態の動き
    pState_->Update2D(this);
}

//ステージに合わせて回転
void Player2D::RotationInStage()
{
    //Playerの向きの角度分軸ベクトルを回転させる
    ARGUMENT_INITIALIZE(transform_.mmRotate_,XMMatrixRotationAxis(UP_VECTOR, angle_));

    //Playerが回転しているなら
    if (IsRotation()) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(UP_VECTOR, jampRotationPreviousAngle_));
}

//Playerのカメラの処理
void Player2D::PlayerCameraBehavior(XMFLOAT3* pos, XMFLOAT3* tar)
{
    //最終的な位置とターゲット
    XMFLOAT3 camTar2 = { transform_.position_.x,transform_.position_.y,transform_.position_.z };
    XMFLOAT3 camPos2 = { transform_.position_.x, transform_.position_.y, CAM_POS_2D_Z };

    //flagがtrueなら位置動かす
    if (isMoveCamPos_)
        XMStoreFloat3(pos, XMVectorLerp(XMLoadFloat3(pos), XMLoadFloat3(&camPos2), CAMERA_INTERPOLATION_FACTOR));

    XMStoreFloat3(tar, XMVectorLerp(XMLoadFloat3(tar), XMLoadFloat3(&camTar2), CAMERA_INTERPOLATION_FACTOR));

    //カメラのいろいろ設定
    Camera::SetPosition(*pos);
    Camera::SetTarget(*tar);

    //Playerについてるライトの位置調整
    Light::SetPlayerPosition(XMFLOAT4(transform_.position_.x, transform_.position_.y, LIGHT_POS_Z, ZERO));
}

//レイで当たり判定
void Player2D::StageRayCast()
{
    //ブロックとの当たり判定をするためにトランスフォームを保存
    XMFLOAT3 Colpos = transform_.position_;
    Colpos.x -= (PLAYER_MODEL_SIZE_X / 2);

    //右
    if (GameManager::GetpStage()->IsBlock(&Colpos, Right))
    {
        ARGUMENT_INITIALIZE(transform_.position_, Colpos);
    }

    ARGUMENT_INITIALIZE(Colpos, transform_.position_);
    Colpos.x += (PLAYER_MODEL_SIZE_X / 2);

    //左
    if (pstage_->IsBlock(&Colpos, Left))
    {
        ARGUMENT_INITIALIZE(transform_.position_, Colpos);
    }

    ARGUMENT_INITIALIZE(Colpos, transform_.position_);
    Colpos.y -= (PLAYER_MODEL_SIZE_Y / 2);

    //下
    if (pstage_->IsBlock(&Colpos, Under))
    {
        //ポジション設定
        ARGUMENT_INITIALIZE(transform_.position_, Colpos);

        //もし前回着地していなかったら音鳴らす
        if (!isBeforeLand_)
        {
            ARGUMENT_INITIALIZE(isBeforeLand_, true);
            PlayerAudioManager::JumpLandAudio();
        }

        //回転じゃないなら
        if (PlayerStateManager::playerState_ != PlayerStateManager::playerRotationning_)
        {
            //状態変更
            ARGUMENT_INITIALIZE(PlayerStateManager::playerState_, PlayerStateManager::playerStanding_);
            PlayerStateManager::playerState_->Enter(this);
        }

        ARGUMENT_INITIALIZE(acceleration_, 1);
    }
    else
        ARGUMENT_INITIALIZE(isBeforeLand_, false);

    ARGUMENT_INITIALIZE(Colpos, transform_.position_);
    Colpos.y += (PLAYER_MODEL_SIZE_Y / 2);

    //上
    if (pstage_->IsBlock(&Colpos, Top))
    {
        ARGUMENT_INITIALIZE(transform_.position_, Colpos);

        //状態変更
        ARGUMENT_INITIALIZE(PlayerStateManager::playerState_, PlayerStateManager::playerStanding_);
        PlayerStateManager::playerState_->Enter(this);

        ARGUMENT_INITIALIZE(acceleration_, 1);
    }

    //各方向
    RayCastData rightData;
    RayCastData leftData;
    RayCastData upData;
    RayCastData downData;

    //当たってるか確認
    HitTest(&rightData, RIGHT_VECTOR);
    HitTest(&leftData, LEFT_VECTOR);
    HitTest(&upData, UP_VECTOR);
    HitTest(&downData, DOWN_VECTOR);

    //////////////////////////////はみ出した分下げる//////////////////////////////////////

    if (rightData.dist <= 1)
    {
        XMVECTOR dis = { rightData.dist,ZERO,ZERO };
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (RIGHT_VECTOR - dis));
    }
    if (leftData.dist <= 1)
    {
        XMVECTOR dis = { -leftData.dist,ZERO,ZERO };
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (LEFT_VECTOR - dis));
    }

    if (upData.dist <= 1)
    {
        XMVECTOR dis = { ZERO,upData.dist,ZERO };
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (UP_VECTOR - dis));
    }

    if (downData.dist >= 0.9)
    {
        transform_.position_ = Float3Add(transform_.position_, VectorToFloat3((DOWN_VECTOR / 10) * acceleration_));
        acceleration_ += GRAVITY_ADDITION;
    }
    else
    {
        //回転じゃないなら
        if (PlayerStateManager::playerState_ != PlayerStateManager::playerRotationning_)
        {
            PlayerAudioManager::JumpLandAudio();

            //状態変更
            PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
            PlayerStateManager::playerState_->Enter(this);
        }

        ARGUMENT_INITIALIZE(acceleration_, 1);
    }

}

//当たり判定
void Player2D::HitTest(RayCastData* data, const XMVECTOR& dir)
{
    data->start = transform_.position_;       //レイの発射位置  
    XMStoreFloat3(&data->dir, dir);           //レイの方向
    Model::RayCast(hGroundModel_, data);      //レイを発射                                      
}

