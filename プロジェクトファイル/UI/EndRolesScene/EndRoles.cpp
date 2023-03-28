#include "EndRoles.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Time.h"

//定数
namespace
{
	static const float RETURN_IMAGE_X_POS = 0.6f;  //戻る画像の初期X位置
	static const float RETURN_IMAGE_Y_POS = -0.7f; //戻る画像の初期Y位置
	static const float MOVE_RANGE = 13.6f;         //移動できる範囲
	static const float START_Y_POS = -12.0f;	   //初期
	static const float MOVE_ADD_VALUE = 0.005f;    //移動するときの加算量
	static const float START_TIME = 3.0f;          //開始する時間
}

//コンストラクタ
EndRoles::EndRoles(GameObject* parent, std::string modelPath, std::string name)
	: ImageBase(parent, modelPath, name),hReturnImage_((int)ZERO), hTime_((int)ZERO), isMove_(false)
{
}

//更新の前に一度だけ呼ばれる
void EndRoles::ChildStartUpdate()
{
	//画像ロード
	hReturnImage_ = Image::Load("Image/EndRole/ReturnTitle.png");
	assert(hReturnImage_ >= ZERO);

	//タイマー追加
	ARGUMENT_INITIALIZE(hTime_,Time::Add());

	//タイマースタート
	Time::UnLock(hTime_);

	//トランスフォーム設定
	ARGUMENT_INITIALIZE(tReturnImage_.position_.x,RETURN_IMAGE_X_POS);
	ARGUMENT_INITIALIZE(tReturnImage_.position_.y,RETURN_IMAGE_Y_POS);

	//初期位置
	ARGUMENT_INITIALIZE(transform_.position_.y,START_Y_POS);
}

//更新
void EndRoles::ChildUpdate()
{
	//定数秒以上たっていたら動かす
	if (Time::GetTimef(hTime_) >= START_TIME) ARGUMENT_INITIALIZE(isMove_, true);

	//動くのなら
	if (isMove_)
	{
		//移動範囲内なら移動
		if (transform_.position_.y < MOVE_RANGE) transform_.position_.y += MOVE_ADD_VALUE;

		//移動範囲外にAButton押したならタイトルに戻る
		if (transform_.position_.y >= MOVE_RANGE && Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
		{
			//ロードを描画しない
			GameManager::GetpSceneManager()->SetLoadDrawFlag(false);

			//シーン変更
			GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TITLE);
		}
	}
	
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