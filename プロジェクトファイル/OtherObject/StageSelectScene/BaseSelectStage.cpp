#include "BaseSelectStage.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Engine/ResourceManager/Easing.h"

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
	pCreateStage_->LoadFileCreateStage(this, "Stage/StageSelect/StageInformation/StageSelectStage.txt");
	pCreateStage_->LoadFileCreateStage(GetParent(), "Stage/StageSelect/StageInformation/StageSelectUI.txt");

	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Stage/StageSelect/Base.fbx");
	assert(hModel_ >= ZERO);

	/////////////////�C�[�W���O������/////////////////

	ARGUMENT_INITIALIZE(pEasing_, new EasingMove(&transform_.rotate_, transform_.rotate_, transform_.rotate_,0.0f,Easing::InQuint));

	/////////////////���邳�ݒ�/////////////////

	Model::SetBrightness(hModel_, 1.0f);

	///////////////�J�����̐ݒ�///////////////////

	Camera::SetPosition(XMFLOAT3(0,20,70));
	Camera::SetTarget(XMFLOAT3(0,-10,0));
}

//�X�V
void BaseSelectStage::Update()
{
	//�������I����Ă��邩�ǂ���
	bool isFinish = pEasing_->Move();

	//�������I����Ă��邩�X�e�B�b�N���X�����̂Ȃ��]������
	if (Input::IsPadStickRightL() && isFinish)
	{
		XMFLOAT3 afterRotate = transform_.rotate_;
		afterRotate.y += ROTATION_ANGLE_VALUE;
		pEasing_->Reset(&transform_.rotate_,transform_.rotate_, afterRotate,1.0f, Easing::OutCubic);
	}
	else if (Input::IsPadStickLeftL() && isFinish)
	{
		XMFLOAT3 afterRotate = transform_.rotate_;
		afterRotate.y -= ROTATION_ANGLE_VALUE;
		pEasing_->Reset(&transform_.rotate_, transform_.rotate_, afterRotate, 1.0f, Easing::OutCubic);
	}
}

//�`��
void BaseSelectStage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

