#include "Mob.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/DirectX/Input.h"
#include "../Manager/SceneManager/SceneManager.h"
#include "../Player/PlayerBase.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Engine/GUI/ImGuiSet.h"

//コンストラクタ
Mob::Mob(GameObject* parent, std::string modelPath,std::string name)
	: GameObject(parent, name), hModel_(-1), modelNamePath_(modelPath), hGroundModel_((int)ZERO), angle_(ZERO),

    ///////////////////カメラ///////////////////////
    totalMx_(XMMatrixIdentity()),
    vNormal_(XMVectorSet(ZERO, -1, ZERO, ZERO)),
    up_(XMVectorSet(ZERO, 1, ZERO, ZERO)),
    down_(XMVectorSet(ZERO, -1, ZERO, ZERO))
{
}

//初期化
void Mob::Initialize()
{
	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load(modelNamePath_);
    ARGUMENT_INITIALIZE(pathName_, modelNamePath_);
	assert(hModel_ >= ZERO);

	////////////////////継承先で新たに初期化の内容追加する用///////////////////////

	ChildInitialize();
}

//更新の前に一回だけ呼ばれる関数
void Mob::StartUpdate()
{
    if (GameManager::GetpStage() == nullptr) return;

    ///////////////Stageのデータ取得///////////////////

    //モデル番号取得
    ARGUMENT_INITIALIZE(pstage_,GameManager::GetpStage());
    ARGUMENT_INITIALIZE(hGroundModel_, pstage_->GethModel());
    int polyModel = pstage_->GetPolyModell();

    //3Dなら
    if (pstage_->GetthreeDflag())
    {
        //近くのポリゴンを調べる
        NearPolyData dataNormal;
        dataNormal.start = transform_.position_;
        Model::NearPolyNormal(polyModel, &dataNormal);

        //法線を追加
        ARGUMENT_INITIALIZE(vNormal_,XMLoadFloat3(&dataNormal.normal));
    }
    else
        ARGUMENT_INITIALIZE(vNormal_,UP_VECTOR);

    ///////////////元々あるTransform.Rotateを使わないためFlagをTrueにする///////////////////

    ARGUMENT_INITIALIZE(transform_.mFlag_,true);

    //継承先のStartUpdate
	ChildStartUpdate();
}

//更新
void Mob::Update()
{
    //nullなら処理をしない
    if (pstage_ == nullptr) return;

    //ステージに合わせてMobを回転させる
    RotationInStage();

    //継承先ごとに動きを変えれる
    ChildUpdate();
}

//ステージに合わせてMobを回転
void Mob::RotationInStage()
{
    //Xのベクトルを抜き取る
    float dotX = ZERO;

    //自キャラまでのベクトルと自キャラの真上のベクトルが少しでも違うなら
    if (TwoVectorNotValue(up_, vNormal_))
    {
        //自キャラまでのベクトルと自キャラの真上のベクトルの内積を求める
        XMVECTOR vecDot = XMVector3Dot(XMVector3Normalize(up_), XMVector3Normalize(vNormal_));

        //Xのベクトルを抜き取る
        dotX = XMVectorGetX(vecDot);
    }

    //外積求める
    ARGUMENT_INITIALIZE(horizontal_,XMVector3Cross(up_, vNormal_));

    //2D
    if (!pstage_->GetthreeDflag())
    {
        totalMx_ = XMMatrixIdentity();
        transform_.mmRotate_ = totalMx_;
        transform_.mmRotate_ *= XMMatrixRotationAxis(UP_VECTOR, angle_);
    }
    //3D
    else
    {

        if (dotX != ZERO && dotX <= 1 && dotX >= -1)
        {
            totalMx_ *= XMMatrixRotationAxis(horizontal_, acos(dotX));
            transform_.mmRotate_ = totalMx_;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);
        }
        else
        {
            transform_.mmRotate_ = totalMx_;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);
        }
    }

   //キャラの上軸更新
   ARGUMENT_INITIALIZE(up_,vNormal_);
}

//描画
void Mob::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	ChildDraw();
}

//開放
void Mob::Release()
{
    ChildRelease();
}




