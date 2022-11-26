#include "Mob.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Engine/GameManager.h"

//コンストラクタ
Mob::Mob(GameObject* parent, std::string modelPath,std::string name)
	: GameObject(parent, name), hModel_(-1), ModelNamePath_(modelPath), hGroundModel_(0), Angle(0),

    ///////////////////カメラ///////////////////////
    TotalMx(XMMatrixIdentity()),
    vNormal(XMVectorSet(0, -1, 0, 0)),
    Up(XMVectorSet(0, 1, 0, 0)),
    Down(XMVectorSet(0, -1, 0, 0))
{
}

//初期化
void Mob::Initialize()
{
	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= 0);

	////////////////////継承先で新たに初期化の内容追加する用///////////////////////

	ChildInitialize();

}

//更新の前に一回だけ呼ばれる関数
void Mob::StartUpdate()
{

    ///////////////Stageのデータ取得///////////////////

    //モデル番号取得
    pstage_ = GameManager::GetpStage();
    int polyModel = pstage_->GetPolyModell();

    //3Dなら
    if (pstage_->GetthreeDflag())
    {
        //近くのポリゴンを調べる
        NearPolyData dataNormal;
        dataNormal.start = transform_.position_;
        Model::NearPolyNormal(polyModel, &dataNormal);

        //法線を追加
        vNormal = XMLoadFloat3(&dataNormal.normal);
    }
    else
        vNormal = { 0,1,0,0 };

    ///////////////元々あるTransform.Rotateを使わないためFlagをTrueにする///////////////////

    transform_.mFlag_ = true;

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
        Up = vNormal;
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




