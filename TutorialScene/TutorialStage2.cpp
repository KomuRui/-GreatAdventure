#include "TutorialStage2.h"
#include "../Engine/Model.h"
#include "../Engine/ImGuiSet.h"
#include "../Engine/Light.h"
#include "../Engine/Camera.h"

//�R���X�g���N�^
TutorialStage2::TutorialStage2(GameObject* parent)
	:Stage(parent, "TutorialStage2")
{
	//��p
	fieldAngle_ = 100;

	//���C�g�̋���
	lightIntensity_ = 5;
}

//������
void TutorialStage2::Initialize()
{
	/////////////////�X�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	//�X�e�[�W�쐬
	ImGuiSet* a = Instantiate<ImGuiSet>(this);
	a->CreateStage("Stage/Tutorial/StageInformation/TutorialStage2.txt");

	//�e�u���b�N�̔z�u���擾
	tBlock_ = a->GetTransformBlock();

	/////////////////////���f���f�[�^�̃��[�h///////////////////////

	hModel_[Base] = Model::Load("Stage/Tutorial/first_Stage1.fbx");
	hModel_[Space] = Model::Load("Stage/SpaceModel/Space.fbx");
	hModel_[PolyModel] = Model::Load("Stage/Tutorial/first_Stage_Polygon.fbx");

	///////////////////////////�e��ݒ�/////////////////////////////

	//���C�̔����Base�����ꂽ���̂�true�ɂ��Ă���
	Model::SetRayFlag(hModel_[Base], true);

	//Space���f���̖��邳�ݒ�
	Model::SetBrightness(hModel_[Space], 0.5);

	//PolyModel�𓧖��ɐݒ�(�����m�F���邽�߂����Ɏg������)
	Model::SetAlpha(hModel_[PolyModel], 0);

	//��p
	Camera::SetFieldAngle(fieldAngle_);

	//�J�����̏�x�N�g��
	Camera::SetUpDirection(XMVectorSet(0, 1, 0, 0));

	//���C�g�̋���
	Light::SetIntensity(lightIntensity_);

	//Player�̏����ʒu
	pos_ = { 20,15,0 };

	//3D�Ȃ̂�true�ɂ���
	threeDflag_ = true;

}

//�X�V
void TutorialStage2::Update()
{
	tSpace_.rotate_.y += 0.2;
}

//�`��
void TutorialStage2::Draw()
{
	Model::SetTransform(hModel_[Base], transform_);
	Model::Draw(hModel_[Base]);

	Model::SetTransform(hModel_[Space], tSpace_);
	Model::Draw(hModel_[Space]);
}

//���
void TutorialStage2::Release()
{
}
