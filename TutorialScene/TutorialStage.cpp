#include "TutorialStage.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"
#include "../Engine/ImGuiSet.h"


//コンストラクタ
TutorialStage::TutorialStage(GameObject* parent)
	: GameObject(parent, "TutorialStage"), status_(first), spaceModel_(-1)
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
	ImGuiSet* a = Instantiate<ImGuiSet>(this);

	a->CreateStage("Stage/Tutorial/StageInformation/TutorialStage1.txt");

	tBlock_ = a->GetTransformBlock();

	///////////////モデルデータのロード///////////////////

	std::string fileName[] = {
		"Stage/Tutorial/first_1.fbx",
		"Stage/Tutorial/first_Stage.fbx"
	};

	for (int i = 0; i < MAX; i++)
	{
		hModel_[i] = Model::Load(fileName[i]);
		assert(hModel_[i] >= 0);
	}

	spaceModel_ = Model::Load("Stage/SpaceModel/Space2.fbx");
	Model::SetRayFlag(hModel_[Two], false);
	Model::SetRayFlag(spaceModel_, false);

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

	Model::SetTransform(spaceModel_, transform_);
	Model::Draw(spaceModel_);
}

//開放
void TutorialStage::Release()
{
}

//更新の前に一回だけ呼ばれる
void TutorialStage::StartUpdate()
{
}

//そこにブロックがあるかどうか,もしあったら重なっている分ずらす
bool TutorialStage::IsBlock(XMFLOAT3 *pos, int status)
{
	for (auto i = tBlock_.begin(); i != tBlock_.end(); i++)
	{
		if ((*i).position_.x + 1 > pos->x &&
			(*i).position_.x - 1 < pos->x &&
			(*i).position_.y - 1 < pos->y &&
			(*i).position_.y + 1 > pos->y &&
			(*i).position_.z - 1 < pos->z &&
			(*i).position_.z + 1 > pos->z)
		{
			switch (status)
			{
			case 0:
				pos->x = ((*i).position_.x + 1.5);
				break;
			case 1:
				pos->x = ((*i).position_.x - 1.5);
				break;
			case 2:
				pos->y = ((*i).position_.y + 2);
				break;
			case 3:
				pos->y = ((*i).position_.y - 2);
				break;
			}
			
			return true;
		}
	}

	return false;
}
