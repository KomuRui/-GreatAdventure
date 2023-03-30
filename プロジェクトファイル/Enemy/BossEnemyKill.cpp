#include "BossEnemyKill.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/ResourceManager/Image.h"
#include "../Engine/GameObject/Camera.h"
#include "../Manager/EffectManager/OtherEffectManager/OtherEffectManager.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/AudioManager/OtherAudioManager/OtherAudioManager.h"
#include "../Engine/ResourceManager/Fade.h"

//定数
namespace
{
	static const float ROTATION_ADD_VALUE = 5.0f;      //回転の加算する時の値    
	static const float COLOR_R_ADD_VALUE = 0.002f;     //色のR値を加算する時の値
	static const float SCALE_X_ADD_VALUE = 0.002f;     //Xの拡大率を加算する時の値
	static const float CAM_TAR_Y_ADD_VALUE = 10.0f;	   //カメラのターゲットYに加算する時の値
	static const float EFFECT_POS_Y_ADD_VALUE = 9.0f;  //エフェクトポジションYに加算する時の値
	static const float CALL_TIME_METHOD = 0.5f;        //タイムメソッドを呼ぶ時間
	static const float FADE_ADD_ALPHA = 0.01f;		   //フェードするときの加算する透明度
	static const XMFLOAT3 CAM_POS = { ZERO,11,10 };    //カメラのポジション
}

//コンストラクタ
BossEnemyKill::BossEnemyKill(GameObject* parent)
	: GameObject(parent), hModel_(-1), sign_(1), imageAlpha_(ZERO), isModelDraw_(true),
	colorR_(ZERO), isExplosion_(false), hImage_(-1), isFadeIn_(false)
{
}

//初期化
void BossEnemyKill::Initialize()
{
	///////////////モデルデータのロード///////////////////

	ARGUMENT_INITIALIZE(pathName_, "Enemy/Model/MainBoss.fbx");
	hModel_ = Model::Load(pathName_);
	assert(hModel_ >= ZERO);

	///////////////画像データのロード///////////////////

	hImage_ = Image::Load("Image/World2/BlackImage.png");
	Image::SetAlpha(hImage_, imageAlpha_);
	assert(hImage_ >= ZERO);

	/////////////////明るさ設定/////////////////

	Model::SetBrightness(hModel_, 1.0f);

	///////////////カメラの設定///////////////////

	ARGUMENT_INITIALIZE(camTar_,XMFLOAT3(transform_.position_.x, transform_.position_.y + CAM_TAR_Y_ADD_VALUE, transform_.position_.z));
	Camera::SetPosition(CAM_POS);
	Camera::SetUpDirection(UP_VECTOR);
	Camera::SetTarget(camTar_);

	///////////////音///////////////////

	OtherAudioManager::BossCharge();
}

//更新
void BossEnemyKill::Update()
{
	//もしcolorR_が1以上かつ爆発していないのなら
	if (colorR_ >= 1 && !isExplosion_)
	{
		//爆発音
		OtherAudioManager::BossExplosion();

		//爆発したに変更
		ARGUMENT_INITIALIZE(isExplosion_, true);

		//エフェクトの発生ポジションを求める
		XMFLOAT3 effectPos = transform_.position_;
		effectPos.y += EFFECT_POS_Y_ADD_VALUE;

		//爆発エフェクト
		OtherEffectManager::ExplosionEffect(effectPos);

		//モデル描画しない
		ARGUMENT_INITIALIZE(isModelDraw_, false);

		//定数秒後にタイムメソッドを呼ぶ
		SetTimeMethod(CALL_TIME_METHOD);

		return;
	}

	//フェードが最後まで終わっていかつ爆発しているのならLastSceneへ移行
	if (Fade::isNormalFadeNotTransparency() && isExplosion_)
	{

		//ロード画面を描画しない
		GameManager::GetpSceneManager()->SetLoadDrawFlag(false);

		//ラストシーンへ
		GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_LAST);

		//フェードアウト
		Fade::SetFadeStatus(FADE_NORMAL_OUT, "Image/World2/AfterImage.png");

		return;
	}

	//もしアルファ値が最大値以上かつフェードインしていなければ
	if (imageAlpha_ >= 1.0f && Fade::GetFadeStatus() != FADE_NORMAL_IN) Fade::SetFadeStatus(FADE_NORMAL_IN,"Image/World2/AfterImage.png");

	//アンビエント値設定
	Model::SetAmbient(hModel_, XMFLOAT4(colorR_, ZERO, ZERO, 1.0f));
	colorR_ += COLOR_R_ADD_VALUE;

	//びくびく震わせる
	ARGUMENT_INITIALIZE(transform_.rotate_.y,ROTATION_ADD_VALUE * sign_);
	sign_ *= -1;

	//太らせる
	transform_.scale_.x += SCALE_X_ADD_VALUE;

	//常にボス見るように
	Camera::SetPosition(CAM_POS);
	Camera::SetUpDirection(UP_VECTOR);
	Camera::SetTarget(camTar_);
}

//描画
void BossEnemyKill::Draw()
{
	//モデル
	{
		if (isModelDraw_)
		{
			Model::SetTransform(hModel_, transform_);
			Model::Draw(hModel_);
		}
	}

	//画像
	{
		Transform t;

		//フェードインするなら透明度を下げる
		if (isFadeIn_) imageAlpha_ += FADE_ADD_ALPHA;

		//描画
		Image::SetAlpha(hImage_, imageAlpha_);
		Image::SetTransform(hImage_, t);
		Image::SetUi(hImage_);
	}
}

//指定した時間で呼ばれるメソッド
void BossEnemyKill::TimeMethod()
{
	//フェードインするように
	ARGUMENT_INITIALIZE(isFadeIn_, true);
}
