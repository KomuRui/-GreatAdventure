#include "UserGameStartUI.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Engine/ResourceManager/Easing.h"
#include "../../Engine/ResourceManager/Text.h"
#include "../../Engine/Component/EasingMove.h"
#include "../../Manager/ButtonManager/ButtonManager.h"
#include "IconSelectUI.h"

//�R���X�g���N�^
UserGameStartUI::UserGameStartUI(GameObject* parent)
	: GameObject(parent, "UserGameStartUI"), pCreateStage_(new CreateStage)
{}

//������
void UserGameStartUI::Initialize()
{
	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	pCreateStage_->LoadFileCreateStage(this, "Stage/UserSelect/StageInformation/UserGameStartUI.txt");
}


//�X�V
void UserGameStartUI::Update()
{
}
