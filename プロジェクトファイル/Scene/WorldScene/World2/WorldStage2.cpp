#include "WorldStage2.h"
#include "../../../Engine/ResourceManager/Model.h"
#include "../../../Engine/GameObject/Light.h"
#include "../../../Engine/GameObject/Camera.h"
#include "../../../Gimmick/Warp.h"
#include "../../../Engine/ResourceManager/CreateStage.h"

//�R���X�g���N�^
WorldStage2::WorldStage2(GameObject* parent)
	:Stage(parent, "WorldStage2"), isStageDraw_(true)
{
	//��p
	ARGUMENT_INITIALIZE(fieldAngle_, 100);

	//���C�g�̋���
	ARGUMENT_INITIALIZE(lightIntensity_, 2);
}

//������
void WorldStage2::Initialize()
{

	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	//�X�e�[�W�쐬
	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/World/World2/StageInformation/WorldStage2.txt");

	/////////////////////���f���f�[�^�̃��[�h///////////////////////

	hModel_[Base] = Model::Load("Stage/World/World2/Stage.fbx");
	hModel_[Space] = Model::Load("Stage/SpaceModel/Space.fbx");
	hModel_[PolyModel] = Model::Load("Stage/World/World2/Stage.fbx");

	///////////////////////////�e��ݒ�/////////////////////////////

	//���C�̔����Base��Rotation�����ꂽ���̂�true�ɂ��Ă���
	Model::SetRayFlag(hModel_[Base], true);

	//Space���f���̖��邳�ݒ�
	Model::SetBrightness(hModel_[Space], 1.0f);

	//PolyModel�𓧖��ɐݒ�(�����m�F���邽�߂����Ɏg������)
	Model::SetAlpha(hModel_[PolyModel], ZERO);

	//��p
	Camera::SetFieldAngle(fieldAngle_);

	//�J�����̏�x�N�g��
	Camera::SetUpDirection(UP_VECTOR);

	//���C�g�̋���
	Light::SetPlayerIntensity((float)lightIntensity_);

	//Warp�̈ړ���
	ARGUMENT_INITIALIZE(warpPos_,XMFLOAT3(ZERO, 15.0f, ZERO));

	//Player�̏����ʒu
	ARGUMENT_INITIALIZE(pos_, XMFLOAT3(ZERO,204.5f, ZERO));

	//3D�Ȃ̂�true�ɂ���
	ARGUMENT_INITIALIZE(threeDflag_,true);

	//���̎g�p���Ă���̂�true
	ARGUMENT_INITIALIZE(circleFlag_,true)
}

//�X�V
void WorldStage2::Update()
{
}

//�`��
void WorldStage2::Draw()
{
	//�X�e�[�W�`�悷��Ȃ�
	if (isStageDraw_)
	{
		Model::SetTransform(hModel_[Base], transform_);
		Model::Draw(hModel_[Base]);
	}

	Model::SetTransform(hModel_[Space], tSpace_);
	Model::Draw(hModel_[Space]);
}

//���
void WorldStage2::Release()
{
}

//���[�r�[�쐬
void WorldStage2::CreateMovie()
{
	pCreateStage_->LoadFileCreateStage(this, "Stage/World/World2/StageInformation/WorldStage2_Movie.txt");
}

//�{�X�X�e�[�W�쐬
void WorldStage2::CreateBossStage()
{
	pCreateStage_->LoadFileCreateStage(this, "Stage/World/World2/StageInformation/WorldStage2_Boss.txt");
}

//�{�X�|���V�[���쐬
void WorldStage2::CreateBossKill()
{
	pCreateStage_->LoadFileCreateStage(this, "Stage/World/World2/StageInformation/WorldStage2_BossKill.txt");
}