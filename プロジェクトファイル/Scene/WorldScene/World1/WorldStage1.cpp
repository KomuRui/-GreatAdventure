#include "WorldStage1.h"
#include "../../../Engine/ResourceManager/Model.h"
#include "../../../Engine/GameObject/Light.h"
#include "../../../Engine/GameObject/Camera.h"
#include "../../../Gimmick/Warp.h"
#include "../../../Engine/ResourceManager/CreateStage.h"

//�R���X�g���N�^
WorldStage1::WorldStage1(GameObject* parent)
	:Stage(parent, "WorldStage1")
{
	//��p
	ARGUMENT_INITIALIZE(fieldAngle_,100);

	//���C�g�̋���
	ARGUMENT_INITIALIZE(lightIntensity_, 2);
}

//������
void WorldStage1::Initialize()
{

	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	//�X�e�[�W�쐬
	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this,"Stage/World/World1/StageInformation/WorldStage1.txt");

	//���[�v�̃V�[���J�ڐ�����߂Ă���
	Warp* pWarp = (Warp*)FindObject("Warp");
	pWarp->SetSceneId(SCENE_ID_HOME);
	pWarp->SetStageRelease(3); //���̃X�e�[�W���N���A���������X�e�[�W����3�ɂȂ�悤�ɂ���

	/////////////////////���f���f�[�^�̃��[�h///////////////////////

	hModel_[Base] = Model::Load("Stage/World/World1/Stage_Main.fbx");
	hModel_[Space] = Model::Load("Stage/SpaceModel/Space1.fbx");
	hModel_[PolyModel] = Model::Load("Stage/World/World1/Stage_Hit_Test.fbx");
	Model_[Rotation] = Model::Load("Stage/World/World1/Stage_Rotation.fbx");

	///////////////////////////�e��ݒ�/////////////////////////////

	//���C�̔����Base��Rotation�����ꂽ���̂�true�ɂ��Ă���
	Model::SetRayFlag(hModel_[Base], true);
	Model::SetRayFlag(Model_[Rotation], true);

	//Space���f���̖��邳�ݒ�
	Model::SetBrightness(hModel_[Space], 0.5f);

	//PolyModel�𓧖��ɐݒ�(�����m�F���邽�߂����Ɏg������)
	Model::SetAlpha(hModel_[PolyModel], ZERO);

	//��p
	Camera::SetFieldAngle(fieldAngle_);

	//�J�����̏�x�N�g��
	Camera::SetUpDirection(UP_VECTOR);

	//���C�g�̋���
	Light::SetPlayerIntensity((float)lightIntensity_);

	//Warp�̈ړ���
	ARGUMENT_INITIALIZE(warpPos_,XMFLOAT3(-70.5, 4.5, 76));

	//Player�̏����ʒu
	ARGUMENT_INITIALIZE(pos_, XMFLOAT3(-70.5,204.5,76));

	//3D�Ȃ̂�true�ɂ���
	ARGUMENT_INITIALIZE(threeDflag_,true);

	//���̎g�p���Ă��Ȃ��̂�false
	ARGUMENT_INITIALIZE(circleFlag_,false);

	//����Maya�Őݒ肵���̂ō���������
	ARGUMENT_INITIALIZE(tRotation_.position_.x, -30);
	ARGUMENT_INITIALIZE(tRotation_.position_.z, 42);
}

//�X�V
void WorldStage1::Update()
{
	//���f����]
	tRotation_.rotate_.y += 0.2f;
}

//�`��
void WorldStage1::Draw()
{
	Model::SetTransform(hModel_[Base], transform_);
	Model::Draw(hModel_[Base]);

	Model::SetTransform(Model_[Rotation], tRotation_);
	Model::Draw(Model_[Rotation]);

	Model::SetTransform(hModel_[Space], tSpace_);
	Model::Draw(hModel_[Space]);
}

//���
void WorldStage1::Release()
{
}
