#include "TitleScene.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Player/PlayerBase.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../OtherObject/TitleModel.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Manager/MiniGameManager/MiniGameManager.h"

//�萔
namespace
{
	static const float RATATION_SPEED = 0.5f;    //��]���x
	static const float BRIGHTNESS = 1.5f;		 //�w�i���f���̖��邳
	static const XMFLOAT3 CAM_POS = { 0, 0, 5 }; //�J�����̈ʒu
	static const XMFLOAT3 CAM_TAR = { 0, 0, 0 }; //�J�����̃^�[�Q�b�g
	static const int FIELD_ANGLE = 45;           //�J�����̉�p
}

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hModel_(-1)
{
}

//������
void TitleScene::Initialize()
{
	///////////////�摜�f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Stage/Title/Model/BackGroundModel.fbx");
	assert(hModel_ >= ZERO);

	//�w�i�̃��f�����������点��
	Model::SetBrightness(hModel_, BRIGHTNESS);


	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	CreateStage* pCreateStage = new CreateStage;
	pCreateStage->LoadFileCreateStage(GetParent(), "Stage/Title/StageInformation/TitleScene1.txt");

	///////////////�J����///////////////////

	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
	Camera::SetFieldAngle(FIELD_ANGLE);

	/////////////////�t�F�[�h�C��/////////////////////

	//�����O��̃V�[�����^�C�g������Ȃ��̂Ȃ�t�F�[�h�C��
	if (GameManager::GetpSceneManager()->GetBeforeSceneId() != SCENE_ID_TITLE)
		Fade::SetFadeStatus(FADE_CIRCLE_IN);
}

//�X�V�̑O�Ɉ�x�����Ă΂��X�V
void TitleScene::StartUpdate()
{
}

//�X�V
void TitleScene::Update()
{
	//�w�i��]������
	transform_.rotate_.y += RATATION_SPEED;

	//A��R�g���K�[���������ŃV�[���ړ�(�^�C�����\�b�h���g���Ă��Ȃ��̂Ȃ�)
	if (Input::IsPadButton(XINPUT_GAMEPAD_A) && Input::GetPadTrrigerR() && !GetTimeMethod())
	{
		//�V�[���ړ��̍ۂ̃G�t�F�N�g�\��
		TitleModel* pTitleModel = (TitleModel*)FindObject("TitleModel");

		//nullptr����Ȃ����
		if(pTitleModel !=nullptr)
			pTitleModel->SceneChangeEffect();

		//�G�t�F�N�g���L�������Ƃ��ɃV�[���ڍs�������̂Ń^�C�����\�b�h���g���Ďw�肵�����Ԃ�����������ɌĂ�
		SetTimeMethod(0.5f);
	}
}

//�`��
void TitleScene::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void TitleScene::Release()
{
}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void TitleScene::TimeMethod()
{
	//���[�h�̎��̕`���ݒ肵�Ȃ�
	GameManager::GetpSceneManager()->SetLoadDrawFlag(false);
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_USER_SELECT);
}