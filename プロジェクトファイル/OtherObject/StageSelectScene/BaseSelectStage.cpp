#include "BaseSelectStage.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Engine/ResourceManager/Easing.h"
#include "../../UI/StageSelectScene/StageSelectTextUI.h"

//�萔
namespace
{
	static const XMFLOAT3 CAM_POS = { 0,20,70 }; //�J�����̃|�W�V����
	static const XMFLOAT3 CAM_TAR = { 0,-10,0 }; //�J�����̃^�[�Q�b�g
	static const int ROTATION_ANGLE_VALUE = 45;  //��]�p�x
	static const float EASING_TIME = 1.0f;       //�C�[�W���O�ɂ����鎞��
}

//�R���X�g���N�^
BaseSelectStage::BaseSelectStage(GameObject* parent)
	:GameObject(parent, "BaseSelectStage"), hModel_(-1), lookCheckPoint_(static_cast<int>(CheckPoint::FIRST))
{
}

//������
void BaseSelectStage::Initialize()
{
	///////////////////�e�X�e�[�W�쐬////////////////////////
	
	CreateStage* pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/StageSelect/StageInformation/StageSelectStage.txt");
	pCreateStage_->LoadFileCreateStage(GetParent(), "Stage/StageSelect/StageInformation/StageSelectUI.txt");
	Instantiate<StageSelectTextUI>(GetParent());

	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Stage/StageSelect/Base.fbx");
	assert(hModel_ >= ZERO);

	/////////////////�C�[�W���O������/////////////////

	ARGUMENT_INITIALIZE(pEasing_, new EasingMove(&transform_.rotate_, transform_.rotate_, transform_.rotate_,0.0f,Easing::InQuint));

	/////////////////���邳�ݒ�/////////////////

	Model::SetBrightness(hModel_, 1.0f);

	///////////////�J�����̐ݒ�///////////////////

	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
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
		pEasing_->Reset(&transform_.rotate_,transform_.rotate_, afterRotate, EASING_TIME, Easing::OutCubic);
	}
	else if (Input::IsPadStickLeftL() && isFinish)
	{
		XMFLOAT3 afterRotate = transform_.rotate_;
		afterRotate.y -= ROTATION_ANGLE_VALUE;
		pEasing_->Reset(&transform_.rotate_, transform_.rotate_, afterRotate, EASING_TIME,Easing::OutCubic);
	}
}

//�`��
void BaseSelectStage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}
