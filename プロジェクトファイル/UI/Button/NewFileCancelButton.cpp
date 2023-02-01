#include "NewFileCancelButton.h"
#include "../../Engine/Global.h"
#include "../../Engine/Image.h"

//コンストラクタ
NewFileCancelButton::NewFileCancelButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath,name), hNotSelectPict_(-1)
{
	//ロード
	ARGUMENT_INITIALIZE(hNotSelectPict_, Image::Load("Image/UserSelect/Cancel_Select.png"));

	
}


//選択画像を設定
void NewFileCancelButton::SetSelectImage()
{

}

//選択されていないときの画像を設定
void NewFileCancelButton::SetNotSelectImage()
{

}

//戻る
void NewFileCancelButton::Back()
{

}

//アイコン選択へ
void NewFileCancelButton::GoIconSelect()
{

}