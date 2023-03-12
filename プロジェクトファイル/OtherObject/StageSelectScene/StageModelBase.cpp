#include "StageModelBase.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"


//コンストラクタ
StageModelBase::StageModelBase(GameObject* parent, std::string ModelPath, std::string name)
	:GameObject(parent, name), hModel_(-1),modelPathName_(ModelPath), isSelect_(false), 
	isStageRelease_(false), hPict_(-1)
{
}

//初期化
void StageModelBase::Initialize()
{

	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load(modelPathName_);
	assert(hModel_ >= ZERO);

	///////////////画像データのロード///////////////////

	hPict_ = Image::Load("Image/StageSelect/NotRelease.png");
	assert(hPict_ >= ZERO);

	/////////////////明るさ設定/////////////////

	Model::SetBrightness(hModel_, 1.0f);


	//継承先用
	ChildInitialize();
}

//更新の前に一度だけ呼ばれる関数
void StageModelBase::StartUpdate()
{
	//継承先用
	ChildStartUpdate();
}

//更新
void StageModelBase::Update()
{
	//もし選択されていてかつステージが解放されていてボタンを押したのなら
	if (isSelect_ && isStageRelease_ && Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
		SelectButtonPush();
	//ステージが解放されていなかった場合
	else if (isSelect_ && !isStageRelease_ && Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
		NotStageReleaseButtonPush();

	//継承先用
	ChildUpdate();
}

//描画
void StageModelBase::Draw()
{
	//モデル
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	//選択されていてかつ解放されていないのなら画像描画
	if (isSelect_ && !isStageRelease_)
	{
		Image::SetTransform(hPict_, tPict_);
		Image::Draw(hPict_);
	}

	//継承先用
	ChildDraw();
}

//解放
void StageModelBase::Release()
{
	//継承先用
	ChildRelease();
}

//解放されていないステージの時にボタンを押した時の処置
void StageModelBase::NotStageReleaseButtonPush()
{

}
