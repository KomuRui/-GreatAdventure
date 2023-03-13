#include "UserPlanetBase.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/DirectX/Input.h"
#include "../Engine/ResourceManager/Easing.h"
#include "../Engine/ResourceManager/VFX.h"
#include "../UI/UserSelectScene/UserGameStartUI.h"
#include "../Manager/ButtonManager/ButtonManager.h"

////定数
namespace
{
	static const float ROTATION_SPEED = 0.3f;			 //回転速度
	static const float STATUS_CHANGE_DISTANCE = 0.05f;   //状態が変更するときの距離
	static const float INTERPOLATION_COEFFICIENT = 0.1f; //補間係数
	static const float FALL_SPEED = 0.4f;                //落ちる速度の値
	static const float KILL_VALUE = -40.0f;              //削除するときの値
}

//コンストラクタ
UserPlanetBase::UserPlanetBase(GameObject* parent, std::string modelPath, std::string name)
	:GameObject(parent, name), hModel_(-1), ModelNamePath_(modelPath), status_(PlanetStatus::Stop), isSelect_(false)
{
}

/////////////////////オーバーライドする関数//////////////////////

//初期化
void UserPlanetBase::Initialize()
{
	//モデルデータロード
	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= ZERO);

	//回転初期化
	ARGUMENT_INITIALIZE(transform_.rotate_, XMFLOAT3(ZERO, ZERO, ZERO));

	//イージング設定
	ARGUMENT_INITIALIZE(pEasing_,new EasingMove(&transform_.rotate_,XMFLOAT3(0,0,0), XMFLOAT3(0,360,0),2.0f,Easing::OutCubic));

	//継承先用
	ChildInitialize();
}

//更新の前に一回呼ばれる関数
void UserPlanetBase::StartUpdate()
{
}

//更新
void UserPlanetBase::Update()
{
	//選択されていたら少し回転させる
	if (isSelect_)
		pEasing_->Move();

	//状態によって呼ぶ関数分ける
	switch (status_)
	{
	//移動
	case PlanetStatus::Move:

		NextPositionToMove();
		break;

	//落ちる
	case PlanetStatus::Fall:

		Fall();
		break;

	//爆発
	case PlanetStatus::Explosion:

		Explosion();
		break;

	default:
		break;
	}


	//継承先用
	ChildUpdate();
}

//描画
void UserPlanetBase::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//解放
void UserPlanetBase::Release()
{
}

/////////////////////関数//////////////////////

//次の位置へ移動
void UserPlanetBase::NextPositionToMove()
{
	//補間しながら目的のポジションまで変更していく
	transform_.position_ = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&nextPos_), INTERPOLATION_COEFFICIENT));
	
	//距離が0.05より小さいならStop状態に設定
	if (RangeCalculation(transform_.position_, nextPos_) < STATUS_CHANGE_DISTANCE)
	{
		//自身のポジションを次の位置に設定
		ARGUMENT_INITIALIZE(transform_.position_, nextPos_);
		ARGUMENT_INITIALIZE(status_, PlanetStatus::Stop);
	}

}

//次のポジションセット
void UserPlanetBase::SetNextPosition(const XMFLOAT3& nextPos)
{
	ARGUMENT_INITIALIZE(nextPos_, nextPos);           //次の位置設定
	ARGUMENT_INITIALIZE(status_, PlanetStatus::Move); //状態設定
}

//選択されていないのなら落ちる
void UserPlanetBase::Fall()
{
	//落とす
	transform_.position_.y -= FALL_SPEED;

	//もし削除する値より下なら削除
	if (transform_.position_.y < KILL_VALUE) KillMe();
}

//爆発してモデル変更
void UserPlanetBase::Explosion()
{
	//爆発エフェクト
	ExplosionEffect();
	SetTimeMethod(0.5f);

	//停止状態に
	ARGUMENT_INITIALIZE(status_, PlanetStatus::Stop);
}

//新規作成
void UserPlanetBase::CreateNewFile()
{
	UserCreateNewFile(ModelNamePath_); 
}

//指定した時間で呼ばれるメソッド
void UserPlanetBase::TimeMethod()
{
	//モデル変更
	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= ZERO);

	//ボタンリセット
	ButtonManager::Reset();

	//ゲームスタートUI作成
	Instantiate<UserGameStartUI>(GetParent());

}

//選択されているかどうか
bool UserPlanetBase::IsSelect()
{
	//もし選択されているのなら
	if (isSelect_)
	{
		//選択解除
		ARGUMENT_INITIALIZE(isSelect_, false);

		//回転元に
		ARGUMENT_INITIALIZE(transform_.rotate_.y, ZERO);

		return true;
	}

	return false;
}

//状態をセット
void UserPlanetBase::SetStatus(PlanetStatus status, std::string iconModelPath)
{
	//状態変更
	ARGUMENT_INITIALIZE(status_, status);

	//もし爆発に変更ならモデルパス保存
	if (status_ == PlanetStatus::Explosion) ARGUMENT_INITIALIZE(ModelNamePath_, iconModelPath);
	
}

//落ちる状態に変更
bool UserPlanetBase::SetFallStatus()
{
	//もし選択されていないのなら
	if (!isSelect_)
	{
		//状態変更
		ARGUMENT_INITIALIZE(status_, PlanetStatus::Fall);
		return true;
	}

	return false;
}

//選択されているかどうかセット
void UserPlanetBase::SetIsSelect(const bool& flag)
{
	 ARGUMENT_INITIALIZE(isSelect_, flag);

	 //もし選択されていたらリセット
	 if (isSelect_)pEasing_->Reset(&transform_.rotate_, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 360, 0), 2.0f, Easing::OutCubic);
}

//既存ファイルかどうか
bool UserPlanetBase::IsExisting()
{
	return (ModelNamePath_ != "Stage/Home/Home.fbx");
}

//爆発エフェクト
void UserPlanetBase::ExplosionEffect()
{
	EmitterData data;
	data.textureFileName = "Cloud.png";
	data.position = { 0,0,0 };
	data.delay = 0;
	data.number = 60;
	data.lifeTime = 150;
	data.direction = XMFLOAT3(0, 1, 0);
	data.directionRnd = XMFLOAT3(90, 90, 90);
	data.speed = 0.05f;
	data.speedRnd = 0.8;
	data.size = XMFLOAT2(5, 5);
	data.sizeRnd = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1.05, 1.05);
	data.color = XMFLOAT4(1, 1, 1, 1);
	data.deltaColor = XMFLOAT4(-0.02, -0.02, 0, -1.0 / 50);
	VFX::Start(data);
}