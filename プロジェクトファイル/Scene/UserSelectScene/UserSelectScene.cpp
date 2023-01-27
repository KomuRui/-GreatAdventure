#include "UserSelectScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Engine/Model.h"
#include "../../Engine/CreateStage.h"
#include "../../OtherObject/SelectPlanetController.h"
#include "../../OtherObject/UserSelectSceneUI.h"
#include "../../Manager/GameManager/GameManager.h"

//�R���X�g���N�^
UserSelectScene::UserSelectScene(GameObject* parent)
	: GameObject(parent, "UserSelectScene"), hModel_(-1)
{
}

//������
void UserSelectScene::Initialize()
{
	///////////////�摜�f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Stage/UserSelect/Model/BackGroundModel.fbx");
	assert(hModel_ >= ZERO);

	//�w�i�̃��f�����������点��
	Model::SetBrightness(hModel_, BRIGHTNESS);

	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	CreateStage* pCreateStage = new CreateStage;
	pCreateStage->LoadFileCreateStage(GetParent(), "Stage/UserSelect/StageInformation/UserSelectScene1.txt");

	////////////////////UI�\��//////////////////////

	Instantiate<UserSelectSceneUI>(GetParent());

	///////////////�J����///////////////////

	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
	Camera::SetFieldAngle(45);
}

//�X�V�̑O�Ɉ�x�����Ă΂��X�V
void UserSelectScene::StartUpdate()
{
}

//�X�V
void UserSelectScene::Update()
{
	//�w�i��]
	transform_.rotate_.y += RATATION_SPEED;

	//���[�U�[���̊Ǘ����Ă��閼�O��Ԃ̍X�V���Ă�
	SelectPlanetController::Update();

	//��
	if (Input::IsPadButton(XINPUT_GAMEPAD_A))
	{
		//�{���͊e���[�U�[�̏����m�F���ăX�^�[�g�V�[�������߂�
		GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TUTORIAL1);
	}
}

//�`��
void UserSelectScene::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void UserSelectScene::Release()
{
}

