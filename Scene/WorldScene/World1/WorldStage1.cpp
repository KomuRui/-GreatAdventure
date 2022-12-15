#include "WorldStage1.h"
#include "../../../Engine/Model.h"
#include "../../../Engine/ImGuiSet.h"
#include "../../../Engine/Light.h"
#include "../../../Engine/Camera.h"
#include "../../../Gimmick/Warp.h"
#include "../../../Engine/CreateStage.h"

//�R���X�g���N�^
WorldStage1::WorldStage1(GameObject* parent)
	:Stage(parent, "WorldStage1")
{
	//��p
	fieldAngle_ = 100;

	//���C�g�̋���
	lightIntensity_ = 2;
}

//������
void WorldStage1::Initialize()
{
	/////////////////�X�e�[�W�ݒu���邽�߂ɕK�v��GUI///////////////////

	Instantiate<ImGuiSet>(this);

	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	//////�X�e�[�W�쐬
	CreateStage* pCreateStage = new CreateStage;
	pCreateStage->LoadFile(this,"Stage/World/World1/StageInformation/WorldStage1.txt");

	////���[�v�̃V�[���J�ڐ�����߂Ă���
	//Warp* pWarp = (Warp*)FindObject("Warp");
	//pWarp->SetSceneId(SCENE_ID_TUTORIAL1);


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
	Model::SetAlpha(hModel_[PolyModel], 0);

	//��p
	Camera::SetFieldAngle(fieldAngle_);

	//�J�����̏�x�N�g��
	Camera::SetUpDirection(XMVectorSet(0, 1, 0, 0));

	//���C�g�̋���
	Light::SetPlayerIntensity(lightIntensity_);

	//Warp�̈ړ���
	warpPos_ = { -70.5, 4.5, 76 };

	//Player�̏����ʒu
	pos_ = { -70.5,204.5,76 };

	//3D�Ȃ̂�true�ɂ���
	threeDflag_ = true;

	//���̎g�p���Ă��Ȃ��̂�false
	circleFlag_ = false;

	//����Maya�Őݒ肵���̂ō���������
	tRotation_.position_.x = -30;
	tRotation_.position_.z = 42;
}

//�X�V
void WorldStage1::Update()
{
	//���f����]
	tRotation_.rotate_.y += 0.2;
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
