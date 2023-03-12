#include "StageSelectStage.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//�R���X�g���N�^
StageSelectStage::StageSelectStage(GameObject* parent)
	:Stage(parent, "StageSelectStage")
{
	//��p
	ARGUMENT_INITIALIZE(fieldAngle_,45);
}

//������
void StageSelectStage::Initialize()
{

	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	//////�X�e�[�W�쐬
	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/Home/StageInformation/StageSelectStage.txt");

	/////////////////////���f���f�[�^�̃��[�h///////////////////////

	hModel_[Space] = Model::Load("Stage/SpaceModel/Space.fbx");

	///////////////////////////�e��ݒ�/////////////////////////////

	//Space���f���̖��邳�ݒ�
	Model::SetBrightness(hModel_[Space], 0.5f);

	//��p
	Camera::SetFieldAngle(fieldAngle_);

	//�J�����̏�x�N�g��
	Camera::SetUpDirection(UP_VECTOR);
}

//�X�V
void StageSelectStage::Update()
{
}

//�`��
void StageSelectStage::Draw()
{
	Model::SetTransform(hModel_[Space], tSpace_);
	Model::Draw(hModel_[Space]);
}

//���
void StageSelectStage::Release()
{
}
