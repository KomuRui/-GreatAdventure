#include "PlayerBase.h"
#include "../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"

////定数
namespace
{
    //Playerのパラメータを保存してあるパス
    LPCTSTR parameterPath = "Parameter/Player/PlayerParameter.ini";

    ///////////////キャラの必要な情報///////////////////

    static const float NORMAL_INTERPOLATION_FACTOR = GetPrivateProfilefloat("PLAYER", "NormalFactor", "0.045", parameterPath); //法線を補間するときの補間係数
    static const float PLAYER_ANIM_SPEED = GetPrivateProfilefloat("PLAYER", "AnimSpeed", "1.0", parameterPath);                //アニメーションの再生速度
    static const int ANIM_START_FRAME = GetPrivateProfilefloat("PLAYER", "AnimStartFrame", "1", parameterPath);                //アニメーションの開始フレーム
    static const int ANIM_END_FRAME = GetPrivateProfilefloat("PLAYER", "AnimEndFrame", "60", parameterPath);			       //アニメーションの終了フレーム
    static const int MAX_NORMAL_RADIANS = GetPrivateProfilefloat("PLAYER", "MaxNormalRadians", "50", parameterPath);   	       //法線との最大角度			
    static const float PLAYER_MODEL_SIZE_X = 1.0f;  //PlayerのXのモデルサイズ
    static const float PLAYER_MODEL_SIZE_Y = 2.0f;  //PlayerのYのモデルサイズ
    static const float GRAVITY_ADDITION = 0.03f;    //重力の加算値

    ////////////////ライト///////////////////

    static const float LIGHT_POS_Z = GetPrivateProfilefloat("LIGHT", "LightZPos", "2", parameterPath);  //ライトのZのポジション

    ////////////////カメラ///////////////////

    static const float CAMERA_INTERPOLATION_FACTOR = GetPrivateProfilefloat("CAMERA", "CamFactor", "0.08", parameterPath);  //カメラの移動を補間するときの補間係数
    static const float CAM_POS_2D_Z = GetPrivateProfilefloat("CAMERA", "CamPos2DZ", "20", parameterPath);                   //2Dの時のカメラのZの位置
    static const float CAM_SHOULDER_ADD_VALUE = 0.5f; //ショルダーでカメラ操作する時の加算する値
    static const float CAM_STICR_ADD_VALUE = 0.03f;   //スティックRでカメラを操作するときの加算する値

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
    normalFlag_(true),

    //その他
    acceleration_(1),
    pState_(new PlayerStateManager),

    ///////////////////カメラ///////////////////////

    camMat_(XMMatrixIdentity()),
    camStatus_(LONG),
    camAngle_(1),
    camPosFlag_(true),
    camFlag_(true)

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

    ///////////////エフェクトとアニメーション設定///////////////////

    //エフェクト出すために必要
    PlayerEffectManager::Initialize(this);

    //アニメーション
    Model::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, PLAYER_ANIM_SPEED);
}

//更新の前に一回呼ばれる関数
void PlayerBase::ChildStartUpdate()
{
    //自身のポジションセット
    ARGUMENT_INITIALIZE(transform_.position_, pstage_->GetPos());
}

//更新
void PlayerBase::Update()
{
    //真下の法線を調べる
    CheckUnderNormal();

    //継承先用の更新
    ChildPlayerUpdate();

    //カメラの挙動
    CameraBehavior();
}


