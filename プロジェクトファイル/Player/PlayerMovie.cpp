#include "PlayerMovie.h"
#include "../Engine/GameObject/Camera.h"
#include "../Engine/GameObject/Light.h"
#include "../Engine/ResourceManager/Time.h"
#include "../Manager/CoinManager/CoinManager.h"
#include "../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../Gimmick/Movie/MovieCoin.h"
#include "../Enemy/BossEnemyMovie.h"
#include "../Engine/ResourceManager/VFX.h"

//コンストラクタ
PlayerMovie::PlayerMovie(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, "MainCharacter/Star_Main_Character.fbx", "Player"), vMovieCam_(XMVectorSet(-4, 6, 2, ZERO)), hTime_((int)ZERO)
{
}

//デストラクタ
PlayerMovie::~PlayerMovie()
{
    //解放
    VFX::Release();
}

//初期化
void PlayerMovie::ChildInitialize()
{
    //タイマーを追加
    ARGUMENT_INITIALIZE(hTime_, Time::Add());

    //ボスへの方向を求めて吸い取られるエフェクト表示
    XMFLOAT3 pBossPos = ((BossEnemyMovie*)FindObject("BossEnemyMovie"))->GetPosition();
    XMVECTOR dir = (XMLoadFloat3(&pBossPos) - XMLoadFloat3(&transform_.position_)) + UP_VECTOR * 2;
    PlayerEffectManager::AbsorptionEffect(transform_.position_, dir,vNormal_);
}

//更新
void PlayerMovie::ChildUpdate()
{
    //コイン放出
    CoinRelease();

    //カメラ
    CameraBehavior();
}

//カメラの処理
void PlayerMovie::CameraBehavior()
{

    XMFLOAT3 camPos;                                         //最終的なカメラの位置を入れる変数
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);     //transform_.position_のVector型
    XMVECTOR vCam_ = vMovieCam_;                             //Playerからカメラのベクトルを作成
    vCam_ = XMVector3TransformCoord(vCam_, totalMx_);        //vCamを回す

    vPos += vCam_;                   //PlayerのPosにPlayerからカメラのベクトルをたす
    XMStoreFloat3(&camPos, vPos);    //camPosにvPosをXMFLOAT3に変えていれる

    XMFLOAT3 camTar = Float3Add(transform_.position_, XMFLOAT3(ZERO, ZERO, -4));

    //カメラのいろいろ設定
    Camera::SetUpDirection(vNormal_);
    Camera::SetPosition(camPos);
    Camera::SetTarget(camTar);

    //ライトの位置設定
    XMFLOAT3 lightPos;
    XMStoreFloat3(&lightPos, vNormal_ + XMLoadFloat3(&transform_.position_));
    Light::SetPlayerPosition(XMFLOAT4(lightPos.x, lightPos.y, lightPos.z, ZERO));
}

//コイン放出
void PlayerMovie::CoinRelease()
{
    //もしタイマーをロックしているならアンロック
    if (Time::isLock(hTime_))Time::UnLock(hTime_);

    //もしコインが1枚でもあるかつ0.5秒たっていれば
    if (CoinManager::GetCoinNum() > ZERO && Time::GetTimef(hTime_) > 0.25f)
    {
        //コイン表示
        Instantiate<MovieCoin>(GetParent());

        //リセット
        Time::Reset(hTime_);

        //コイン減少
        CoinManager::DecrementCoin(1);
    }
}