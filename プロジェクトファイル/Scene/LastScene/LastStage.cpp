#include "LastStage.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//�R���X�g���N�^
LastStage::LastStage(GameObject* parent)
	:Stage(parent, "LastStage")
{
	//��p
	ARGUMENT_INITIALIZE(fieldAngle_,100);

	//���C�g�̋���
	ARGUMENT_INITIALIZE(lightIntensity_,3);
}

//������
void LastStage::Initialize()
{

	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	////�X�e�[�W�쐬
	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/Last/StageInformation/LastStage.txt");

	/////////////////////���f���f�[�^�̃��[�h///////////////////////

	hModel_[Base] = Model::Load("Stage/Last/LastStage.fbx");
	hModel_[Space] = Model::Load("Stage/SpaceModel/Space.fbx");
	hModel_[PolyModel] = Model::Load("Stage/Last/LastStage_Polygon.fbx");

	///////////////////////////�e��ݒ�/////////////////////////////

	//���C�̔����Base�����ꂽ���̂�true�ɂ��Ă���
	Model::SetRayFlag(hModel_[Base], true);

	//Space���f���̖��邳�ݒ�
	Model::SetBrightness(hModel_[Space],1.0f);

	//PolyModel�𓧖��ɐݒ�(�����m�F���邽�߂����Ɏg������)
	Model::SetAlpha(hModel_[PolyModel], ZERO);

	//��p
	Camera::SetFieldAngle(fieldAngle_);

	//�J�����̏�x�N�g��
	Camera::SetUpDirection(UP_VECTOR);

	//���C�g�̋���
	Light::SetPlayerIntensity((float)lightIntensity_);

	//Player�̏����ʒu
	ARGUMENT_INITIALIZE(pos_,XMFLOAT3(-3,2,-5));

	//3D�Ȃ̂�true�ɂ���
	ARGUMENT_INITIALIZE(threeDflag_,true);

}

//�X�V
void LastStage::Update()
{
}

//�`��
void LastStage::Draw()
{
	Model::SetTransform(hModel_[Base], transform_);
	Model::Draw(hModel_[Base]);

	Model::SetTransform(hModel_[Space], tSpace_);
	Model::Draw(hModel_[Space]);
}

//���
void LastStage::Release()
{
}
