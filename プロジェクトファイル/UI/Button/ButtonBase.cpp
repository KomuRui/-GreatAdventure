#include "ButtonBase.h"

//コンストラクタ
ButtonBase::ButtonBase(GameObject* parent, std::string modelPath, std::string name)
	:ImageBase(parent,modelPath,name), isSelect_(false)
{}


//更新
void ButtonBase::ChildUpdate()
{
	//もし選択されているのなら
	if (isSelect_)
	{
		//設定されている関数を呼び出す
		IsButtonSelecting(ButtonSelectingFunc);
	}

	//もし選択されているかつAボタンを押したのなら
	if (isSelect_ && Input::IsPadButtonDown(Input::IsPadButton(XINPUT_GAMEPAD_A)))
	{
		//設定されている関数を呼び出す
		IsButtonPush(OnPushFunc);
	}
}

//選択されているかをセット 
void ButtonBase::SetSelect(bool flag)
{
	//もし選択されていないかつ設定されるflagがtrueなら
	if (!isSelect_ && flag) IsButtonPush(ButtonSelectFunc);

	//もし選択されていて設定されるflagがfalseなら
	if (isSelect_ && !flag) IsButtonSelectRelease(ButtonSelectReleaseFunc);

	//設定
	ARGUMENT_INITIALIZE(isSelect_, flag);
}