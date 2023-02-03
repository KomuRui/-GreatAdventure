#include "ButtonBase.h"

//コンストラクタ
ButtonBase::ButtonBase(GameObject* parent, std::string modelPath, std::string name)
	:ImageBase(parent,modelPath,name), isSelect_(false), isPush_(false)
{}


//更新
void ButtonBase::ChildUpdate()
{
	//もし選択されているのなら
	if (isSelect_)
	{
		//設定されている関数を呼び出す
		IsButtonSelecting();
	}

	//もし選択されているかつAボタンを押したのなら
	if (isSelect_ && Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//一回でも押したに設定
		ARGUMENT_INITIALIZE(isPush_, true);

		//設定されている関数を呼び出す
		IsButtonPush();
	}
}

//選択されているかをセット 
void ButtonBase::SetSelect(bool flag)
{
	//もし選択されていないかつ設定されるflagがtrueなら
	if (!isSelect_ && flag) IsButtonSelect();

	//もし選択されていて設定されるflagがfalseなら
	if (isSelect_ && !flag) IsButtonSelectRelease();

	//設定
	ARGUMENT_INITIALIZE(isSelect_, flag);
}