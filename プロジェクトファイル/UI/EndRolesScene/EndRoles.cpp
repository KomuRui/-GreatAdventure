#include "EndRoles.h"
#include "../../Engine/ResourceManager/Image.h"

//定数
namespace
{
	static const float MOVE_RANGE = 13.6f;      //移動できる範囲
	static const float START_Y_POS = -13.0f;	//初期
	static const float MOVE_ADD_VALUE = 0.015f; //移動するときの加算量
}

//コンストラクタ
EndRoles::EndRoles(GameObject* parent, std::string modelPath, std::string name)
	: ImageBase(parent, modelPath, name),hReturnImage_(ZERO)
{
}

//更新の前に一度だけ呼ばれる
void EndRoles::ChildStartUpdate()
{
	//画像ロード
	hReturnImage_ = Image::Load("Image/EndRole/ReturnTitle.png");
	assert(hReturnImage_ >= ZERO);

	//トランスフォーム設定
	tReturnImage_.position_.x = 0.6f;
	tReturnImage_.position_.y = -0.7f;

	//初期位置
	ARGUMENT_INITIALIZE(transform_.position_.y,START_Y_POS);
}

//更新
void EndRoles::ChildUpdate()
{
	//移動範囲内なら移動
	if(transform_.position_.y < MOVE_RANGE) transform_.position_.y += MOVE_ADD_VALUE;
}

//描画
void EndRoles::ChildDraw()
{
	//移動範囲外なら描画
	if (transform_.position_.y >= MOVE_RANGE)
	{
		Image::SetTransform(hReturnImage_, tReturnImage_);
		Image::Draw(hReturnImage_);
	}
}