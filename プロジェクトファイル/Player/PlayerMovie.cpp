#include "PlayerMovie.h"
#include "../Engine/GameObject/Camera.h"
#include "../Engine/GameObject/Light.h"

//コンストラクタ
PlayerMovie::PlayerMovie(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, "Star_Main_Character.fbx", "Player"), vMovieCam_(XMVectorSet(-4, 6, 2, ZERO))
{
}

//初期化
void PlayerMovie::ChildInitialize()
{
}

//更新
void PlayerMovie::ChildUpdate()
{
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
