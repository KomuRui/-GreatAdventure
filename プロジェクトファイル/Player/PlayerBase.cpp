#include "PlayerBase.h"
#include "../Engine/Camera.h"
#include "../Engine/Light.h"
#include "../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/LifeManager/LifeManager.h"

////定数
namespace
{
    //Playerのパラメータを保存してあるパス
    LPCTSTR parameterPath = "Parameter/Player/PlayerParameter.ini";

    ///////////////キャラの必要な情報///////////////////

    static const float PLAYER_ANIM_SPEED = GetPrivateProfilefloat("PLAYER", "AnimSpeed", "1.0", parameterPath);                //アニメーションの再生速度
    static const int ANIM_START_FRAME = GetPrivateProfilefloat("PLAYER", "AnimStartFrame", "1", parameterPath);                //アニメーションの開始フレーム
    static const int ANIM_END_FRAME = GetPrivateProfilefloat("PLAYER", "AnimEndFrame", "60", parameterPath);			       //アニメーションの終了フレーム
    static const int MAX_NORMAL_RADIANS = GetPrivateProfilefloat("PLAYER", "MaxNormalRadians", "50", parameterPath);   	       //法線との最大角度			

    ////////////////コライダー///////////////////

    static const XMFLOAT3 COLLIDER_POS = { ZERO,ZERO,ZERO };  //コライダーの位置
    static const float    COLLIDER_SIZE = 1.0f;               //コライダーのサイズ
}

//コンストラクタ
PlayerBase::PlayerBase(GameObject* parent)
    :Mob(parent, "Star_Main_Character.fbx", "Player"),

    ///////////////キャラの必要な情報///////////////////

    //キャラの軸回転に必要な変数
    jampRotationPreviousAngle_(ZERO),
    mPreviousAngle_(XMMatrixIdentity()),
    normalInterpolation_(0.045f),
    isCheckNormal_(true),

    //その他
    acceleration_(1),
    pState_(new PlayerStateManager),

    ///////////////////カメラ///////////////////////

    camMat_(XMMatrixIdentity()),
    vCam_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
    camStatus_(LONG),
    camAngle_(1),
    isMoveCamPos_(true),
    isLockcam_(false)

{
    camVec_[LONG] = XMVectorSet(ZERO, 15, -15, ZERO);
    camVec_[SHORT] = XMVectorSet(ZERO, 4, -4, ZERO);
}

/////////////////////オーバーライドする関数//////////////////////

//初期化
void PlayerBase::ChildInitialize()
{
    ///////////////////初期化///////////////////////

    //状態
    ARGUMENT_INITIALIZE(PlayerStateManager::playerState_ ,PlayerStateManager::playerStanding_);

    //回転する時回転行列を使うようにする
    ARGUMENT_INITIALIZE(transform_.mFlag_,true);

    //当たり判定
    SphereCollider* collision = new SphereCollider(COLLIDER_POS, COLLIDER_SIZE);
    AddCollider(collision);

    //自身のポジションセット
    ARGUMENT_INITIALIZE(transform_.position_, GameManager::GetpStage()->GetPos());

    ///////////////アニメーション設定///////////////////

    //アニメーション
    Model::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, PLAYER_ANIM_SPEED);

    //継承先用の初期化
    ChildPlayerInitialize();
}

//更新の前に一回呼ばれる関数
void PlayerBase::ChildStartUpdate()
{
    //自身の法線を上に
    ARGUMENT_INITIALIZE(vNormal_, UP_VECTOR);

    //継承先用
    ChildPlayerStartUpdate();
}

//更新
void PlayerBase::Update()
{
    //nullならreturn
    if (pstage_ == nullptr) return;

    //真下の法線を調べる
    CheckUnderNormal();

    //継承先用の更新
    ChildPlayerUpdate();

    //カメラの挙動
    CameraBehavior();
}

//真下の法線を調べてキャラの上軸を決定する
void PlayerBase::CheckUnderNormal()
{
    //レイを真下に打つ
    RayCastData data;
    ARGUMENT_INITIALIZE(data.start,transform_.position_);
    ARGUMENT_INITIALIZE(data.dir,VectorToFloat3(down_));
    Model::AllRayCast(hGroundModel_, &data);

    //法線を調べるかどうかのFlagがtrueなら
    if (isCheckNormal_)
    {
        //レイが当たっていてかつ少しでも上ベクトルとvNormal_の値が違うのなら
        if (data.hit && (XMVectorGetX(vNormal_) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetY(-vNormal_) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetZ(-vNormal_) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&data.normal)))))
        {
            //元のキャラの上ベクトルvNormalと下の法線の内積を求める
            float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&data.normal)), XMVector3Normalize(vNormal_)));

            //角度が50度以内に収まっていたら(壁とかに上らせないため)
            if (acos(dotX) < XMConvertToRadians(MAX_NORMAL_RADIANS) && acos(dotX) > XMConvertToRadians(-MAX_NORMAL_RADIANS))
            {
                //ちょっと補間
                vNormal_ = XMVector3Normalize((XMVectorLerp(XMVector3Normalize(vNormal_), XMLoadFloat3(&data.normal), normalInterpolation_)));
                ARGUMENT_INITIALIZE(down_,-vNormal_);
            }

        }
    }
}

//カメラの処理
void PlayerBase::CameraBehavior()
{
    //カメラを補間して移動させたいのでPlayerのポジションを覚えておく
    static XMFLOAT3 camTar = transform_.position_;
    static XMFLOAT3 campos = transform_.position_;

    //カメラ固定されているのなら
    if (isLockcam_) { CameraLockBehavior(&campos, &camTar); return; }

    //Playerのカメラの処理(2Dと3Dでカメラの動きが違う)
    PlayerCameraBehavior(&campos,&camTar);
}


/// <summary>
/// カメラがロックされていた時のカメラの処理
/// </summary>
void PlayerBase::CameraLockBehavior(XMFLOAT3 *pos, XMFLOAT3 *tar)
{
    //カメラのポジションをyだけPlayerと同じにする(同じ高さで計算したいため)
    XMFLOAT3 camPos = Camera::GetPosition();
    ARGUMENT_INITIALIZE(camPos.y, transform_.position_.y);

    //カメラからPlayerへの方向ベクトル
    XMVECTOR dir = XMLoadFloat3(&transform_.position_) - XMLoadFloat3(&camPos);

    //角度求める
    float dotX = acos(XMVectorGetX(XMVector3Dot(XMVector3Normalize(dir), pState_->GetFrontVec())));

    //求めた角度分軸を回転
    transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, dotX);

    //Playerが回転しているなら
    if (IsRotation()) mPreviousAngle_ *= XMMatrixRotationAxis(vNormal_, dotX);

    ARGUMENT_INITIALIZE(camAngle_, ZERO);
    ARGUMENT_INITIALIZE(*pos, Camera::GetPosition());
    ARGUMENT_INITIALIZE(*tar, Camera::GetTarget());

    //ライト設定
    XMFLOAT3 lightPos;
    XMStoreFloat3(&lightPos, vNormal_ + XMLoadFloat3(&transform_.position_));
    Light::SetPlayerPosition(XMFLOAT4(lightPos.x, lightPos.y, lightPos.z, ZERO));

}

//指定した時間で呼ばれるメソッド
void PlayerBase::TimeMethod()
{
    Enter();
}

//当たり判定
void PlayerBase::OnCollision(GameObject* pTarget)
{
    //Warpと当たったなら
    if (pTarget->GetObjectName() == "Warp")
    {
        //状態変更
        pState_->ChangeState(PlayerStateManager::playerStanding_, this);

        //重力初期化
        ARGUMENT_INITIALIZE(acceleration_, 1);
    }

    //敵か球に当たったかつ回転していないのなら
    if ((pTarget->GetObjectName().find("Enemy") != string::npos || pTarget->GetObjectName().find("Bullet") != string::npos) && !IsRotation())
    {
        //ダメージ
        LifeManager::Damage();

        //状態変更
        if (!LifeManager::IsDie())
        {
            ARGUMENT_INITIALIZE(PlayerStateManager::playerState_, PlayerStateManager::playerKnockBacking_);
            PlayerStateManager::playerKnockBacking_->SetHitEnemyPos(pTarget->GetPosition());
            PlayerStateManager::playerState_->Enter(this);
        }
        else if(PlayerStateManager::playerState_ != PlayerStateManager::playerDieing_)
            pState_->ChangeState(PlayerStateManager::playerDieing_, this);
    }
}
