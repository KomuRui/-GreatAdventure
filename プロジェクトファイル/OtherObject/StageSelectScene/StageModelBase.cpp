#include "StageModelBase.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"


//�R���X�g���N�^
StageModelBase::StageModelBase(GameObject* parent, std::string ModelPath, std::string name)
	:GameObject(parent, name), hModel_(-1),modelPathName_(ModelPath), isSelect_(false), 
	isStageRelease_(false), hPict_(-1)
{
}

//������
void StageModelBase::Initialize()
{

	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load(modelPathName_);
	assert(hModel_ >= ZERO);

	///////////////�摜�f�[�^�̃��[�h///////////////////

	hPict_ = Image::Load("Image/StageSelect/NotRelease.png");
	assert(hPict_ >= ZERO);

	/////////////////���邳�ݒ�/////////////////

	Model::SetBrightness(hModel_, 1.0f);


	//�p����p
	ChildInitialize();
}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void StageModelBase::StartUpdate()
{
	//�p����p
	ChildStartUpdate();
}

//�X�V
void StageModelBase::Update()
{
	//�����I������Ă��Ă��X�e�[�W���������Ă��ă{�^�����������̂Ȃ�
	if (isSelect_ && isStageRelease_ && Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
		SelectButtonPush();
	//�X�e�[�W���������Ă��Ȃ������ꍇ
	else if (isSelect_ && !isStageRelease_ && Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
		NotStageReleaseButtonPush();

	//�p����p
	ChildUpdate();
}

//�`��
void StageModelBase::Draw()
{
	//���f��
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	//�I������Ă��Ă��������Ă��Ȃ��̂Ȃ�摜�`��
	if (isSelect_ && !isStageRelease_)
	{
		Image::SetTransform(hPict_, tPict_);
		Image::Draw(hPict_);
	}

	//�p����p
	ChildDraw();
}

//���
void StageModelBase::Release()
{
	//�p����p
	ChildRelease();
}

//�������Ă��Ȃ��X�e�[�W�̎��Ƀ{�^�������������̏��u
void StageModelBase::NotStageReleaseButtonPush()
{

}
