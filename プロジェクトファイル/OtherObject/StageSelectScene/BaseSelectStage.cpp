#include "BaseSelectStage.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//�萔
namespace
{
	static const int ROTATION_ANGLE_VALUE = 45; //��]�p�x
}

//�R���X�g���N�^
BaseSelectStage::BaseSelectStage(GameObject* parent)
	:GameObject(parent, "BaseSelectStage"), hModel_(-1)
{
}

//������
void BaseSelectStage::Initialize()
{
	///////////////////�e�X�e�[�W�쐬////////////////////////
	
	CreateStage* pCreateStage_ = new CreateStage;
	//pCreateStage_->LoadFileCreateStage(this, "Stage/StageSelect/StageInformation/StageSelectStage.txt");

	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Stage/StageSelect/Base.fbx");
	assert(hModel_ >= ZERO);

	/////////////////���邳�ݒ�/////////////////

	Model::SetBrightness(hModel_, 1.0f);

	///////////////�J�����̐ݒ�///////////////////

	Camera::SetPosition(XMFLOAT3(0,50,80));
	//Camera::SetTarget(XMFLOAT3(0,0,0));

	transform_.scale_ = { 1,1,1 };
}

//�X�V
void BaseSelectStage::Update()
{
	if (Input::IsPadStickRightL()) transform_.rotate_.y += ROTATION_ANGLE_VALUE;
	if (Input::IsPadStickLeftL()) transform_.rotate_.y -= ROTATION_ANGLE_VALUE;
}

//�`��
void BaseSelectStage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

