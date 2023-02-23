#include "ScalingImage.h"
#include "../Engine/ResourceManager/Image.h"

//定数
namespace
{
	static const XMVECTOR MIN_SCALE = { 0.0f,0.0f,0.0f };  //最低拡大率
	static const XMVECTOR MAX_SCALE = { 0.1f,0.1f,0.0f };  //最高拡大率
	static const float INTERPOLATION_FACTOR = 0.05f;       //補間係数
	static const float CHANGE_TARGET_DISTANCE = 0.01f;     //ターゲット変更するときの距離
}

//コンストラクタ
ScalingImage::ScalingImage(GameObject* parent, std::string modelPath, std::string name)
	: ImageBase(parent, modelPath, name)
{
}

//更新の前に一度だけ呼ばれる
void ScalingImage::ChildStartUpdate()
{
	//補間する前の拡大率保存
	ARGUMENT_INITIALIZE(beforeScale_, (XMLoadFloat3(&transform_.scale_) + MIN_SCALE));

	//次の目標とする拡大率の保存
	ARGUMENT_INITIALIZE(targetScale_, (XMLoadFloat3(&transform_.scale_) + MAX_SCALE));
}

//更新
void ScalingImage::ChildUpdate()
{
	//拡大率を補間しながら変えていく
	XMStoreFloat3(&transform_.scale_, XMVectorLerp(XMLoadFloat3(&transform_.scale_), targetScale_, INTERPOLATION_FACTOR));

	//距離が0.01より短いのなら
	if (RangeCalculation(transform_.scale_, VectorToFloat3(targetScale_)) < CHANGE_TARGET_DISTANCE)
	{
		//ターゲット交換
		std::swap(beforeScale_, targetScale_);
	}
}