#include "StageModelBase.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"


//�R���X�g���N�^
StageModelBase::StageModelBase(GameObject* parent, std::string ModelPath, std::string name)
	:GameObject(parent, name), hModel_(-1),modelPathName_(ModelPath), isSelect_(false)
{
}

//������
void StageModelBase::Initialize()
{

	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load(modelPathName_);
	assert(hModel_ >= ZERO);

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
	//�p����p
	ChildUpdate();
}

//�`��
void StageModelBase::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	//�p����p
	ChildDraw();
}

//���
void StageModelBase::Release()
{
	//�p����p
	ChildRelease();
}

