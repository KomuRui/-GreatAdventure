#include "WorldStage2.h"
#include "../../../Engine/Model.h"
#include "../../../Engine/Light.h"
#include "../../../Engine/Camera.h"
#include "../../../Gimmick/Warp.h"
#include "../../../Engine/CreateStage.h"

//�R���X�g���N�^
WorldStage2::WorldStage2(GameObject* parent)
	:Stage(parent, "WorldStage2")
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
	pCreateStage_->LoadFileCreateStage(this, "Stage/World/World2/StageInformation/WorldStage2_Boss.txt");

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
	Light::SetPlayerIntensity(lightIntensity_);

	//Warp�̈ړ���
	ARGUMENT_INITIALIZE(warpPos_,XMFLOAT3(ZERO, 15, ZERO));

	//Player�̏����ʒu
	ARGUMENT_INITIALIZE(pos_, XMFLOAT3(ZERO,204.5, ZERO));

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
	Model::SetTransform(hModel_[Base], transform_);
	Model::Draw(hModel_[Base]);

	Model::SetTransform(hModel_[Space], tSpace_);
	Model::Draw(hModel_[Space]);
}

//���
void WorldStage2::Release()
{
}
