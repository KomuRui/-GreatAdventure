#include "UserSelectStage.h"
#include "../../Engine/Model.h"
#include "../../Engine/Light.h"
#include "../../Engine/Camera.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/CreateStage.h"
#include "../../OtherObject/SelectPlanetController.h"
#include "../../UI/UserSelectScene/UserSelectSceneUI.h"

//�萔
namespace
{
	static const float RATATION_SPEED = 0.1f;    //��]���x
	static const float BRIGHTNESS = 1.5f;		 //�w�i���f���̖��邳
	static const XMFLOAT3 CAM_POS = { 0, 0, 5 }; //�J�����̈ʒu
	static const XMFLOAT3 CAM_TAR = { 0, 0, 0 }; //�J�����̃^�[�Q�b�g
}

//�R���X�g���N�^
UserSelectStage::UserSelectStage(GameObject* parent)
	:Stage(parent, "UserSelectStage")
{
	//��p
	ARGUMENT_INITIALIZE(fieldAngle_,45);
}

//������
void UserSelectStage::Initialize()
{
	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/UserSelect/StageInformation/UserSelectScene1.txt");

	/////////////////////���f���f�[�^�̃��[�h///////////////////////

	hModel_[Space] = Model::Load("Stage/UserSelect/Model/BackGroundModel.fbx");

	///////////////////////////�e��ݒ�/////////////////////////////

	//Space���f���̖��邳�ݒ�
	Model::SetBrightness(hModel_[Space], BRIGHTNESS);

	////////////////////UI�\��//////////////////////

	Instantiate<UserSelectSceneUI>(GetParent());

	///////////////�J����///////////////////

	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
	Camera::SetFieldAngle(fieldAngle_);
}

//�X�V
void UserSelectStage::Update()
{
	//�w�i��]������
	tSpace_.rotate_.y += RATATION_SPEED;

	//���[�U�[���̊Ǘ����Ă��閼�O��Ԃ̍X�V���Ă�
	SelectPlanetController::Update();
}

//�`��
void UserSelectStage::Draw()
{
	Model::SetTransform(hModel_[Space], tSpace_);
	Model::Draw(hModel_[Space]);
}

//���
void UserSelectStage::Release()
{
}
