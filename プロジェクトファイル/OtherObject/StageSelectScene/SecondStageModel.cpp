#include "SecondStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//�萔
namespace
{
	static const XMFLOAT3 ROTATION_MODEL_POSITION = { -39.5f, ZERO, 1.2f }; //��]���f���̃|�W�V����
	static const float ROTATION_ADD_VALUE = 0.30f;	//��]���鎞�̉��Z����l
}

//�R���X�g���N�^
SecondStageModel::SecondStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent,ModelPath,name), hRotationModel_(-1)
{
}

//������
void SecondStageModel::ChildInitialize()
{
	///////////////���f���f�[�^�̃��[�h///////////////////

	hRotationModel_ = Model::Load("Stage/StageSelect/second/secondStageModel2.fbx");
	assert(hRotationModel_ >= ZERO);

	/////////////////���邳�ݒ�/////////////////

	Model::SetBrightness(hRotationModel_, 1.0f);

	//////////////////�g�����X�t�H�[��������/////////////////////

	ARGUMENT_INITIALIZE(tRotation_.position_, ROTATION_MODEL_POSITION);
	ARGUMENT_INITIALIZE(tRotation_.pParent_, transform_.pParent_);
}

//�X�V
void SecondStageModel::ChildUpdate()
{
	//��]
	tRotation_.rotate_.y += ROTATION_ADD_VALUE;
}

//�`��
void SecondStageModel::ChildDraw()
{
	Model::SetTransform(hRotationModel_, tRotation_);
	Model::Draw(hRotationModel_);
}