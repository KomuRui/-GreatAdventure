#include "ShineLight.h"
#include "../Engine/GameObject/Light.h"
#include "../Engine/ResourceManager/Model.h"

//定数
namespace
{
	static const int LIGHT_INTENSITY = 2;							 //ライトの強さ
	static const int REACTION_DISTANCE = 4;							 //反応距離
	static const float SHINE_PERMIT_CALLING_TIME = 1.0f;			 //光るのを許可するメソッドを呼ぶ時間
	static const XMFLOAT4 HIGHLIGHT_COLOR = { 1.0f,1.0f,1.0f,1.0f }; //ハイライトの色
}

//コンストラクタ
ShineLight::ShineLight(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath, name), shineFlag_(false),lightNum_((int)ZERO),shinePermitFlag_(true)
{
}

//更新の前に一回だけ呼ばれる更新
void ShineLight::ChildStartUpdate()
{
	//レイの判定にいれたいのでtrueにしておく
	Model::SetRayFlag(hModel_, true);
}

//更新
void ShineLight::ChildUpdate()
{
	//もし光るのを許可するなら
	if (shinePermitFlag_)
	{
		//プレイヤーとの距離が反応距離より小さいかつ光っていないのなら
		if (RangeCalculation(GameManager::GetpPlayer()->GetPosition(), transform_.position_) < REACTION_DISTANCE && !shineFlag_)
		{
			//ライト設置
			XMFLOAT4 lightPos = { transform_.position_.x,transform_.position_.y, transform_.position_.z,ZERO };
			lightNum_ = Light::CreateLight(lightPos, LIGHT_INTENSITY);

			//ハイライト
			Model::SetSpeculer(hModel_, HIGHLIGHT_COLOR);

			//光っているように設定
			ARGUMENT_INITIALIZE(shineFlag_, true);
		}
	}
}

//光らないようにセット
void ShineLight::SetNotShineLight()
{
	//光らないように
	Light::DeleteLight(lightNum_);

	//光っていないに設定
	ARGUMENT_INITIALIZE(shineFlag_, false);
	ARGUMENT_INITIALIZE(shinePermitFlag_, false);

	//ハイライト削除
	Model::SetSpeculer(hModel_, XMFLOAT4(ZERO, ZERO, ZERO, ZERO));

	//消してからすぐに光るようにしたくないので
	//1.0秒後に光らせられるようにする
	SetTimeMethod(SHINE_PERMIT_CALLING_TIME);
}

//指定した時間で呼ばれるメソッド
void ShineLight::TimeMethod()
{
	//光るのを許可
	ARGUMENT_INITIALIZE(shinePermitFlag_, true);
}