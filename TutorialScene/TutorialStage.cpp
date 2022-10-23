#include "TutorialStage.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"

//コンストラクタ
TutorialStage::TutorialStage(GameObject* parent)
	: GameObject(parent, "TutorialStage"), status_(first)
{
	for (int i = 0; i < MAX; i++)
	{
		hModel_[i] = -1;
		pos_[i] = { 0,0,0 };
	}
}

//初期化
void TutorialStage::Initialize()
{

	///////////////モデルデータのロード///////////////////

	std::string fileName[] = {
		"Stage/First/first_1.fbx",
		"first_Stage.fbx"
	};

	for (int i = 0; i < MAX; i++)
	{
		hModel_[i] = Model::Load(fileName[i]);
		assert(hModel_[i] >= 0);
	}


	////////////////Circleflag_の初期化//////////////////

	//3Dの動きをさせたいならflagをtrueにしておく(2Dならfalse)
	threeDflag_[first] = false;
	threeDflag_[Two] = true;

	///////////////transform///////////////////

	//ステージごとにPlayerの初期位置設定

	//1
	pos_[first] = { 2,2,0 };

	//2
	pos_[Two] = { 20,15,0 };

}

//更新
void TutorialStage::Update()
{
}

//描画
void TutorialStage::Draw()
{
	Model::SetTransform(hModel_[status_], transform_);
	Model::Draw(hModel_[status_]);
}

//開放
void TutorialStage::Release()
{
}

void TutorialStage::StartUpdate()
{
}
