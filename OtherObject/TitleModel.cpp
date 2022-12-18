#include "TitleModel.h"
#include "../Engine/Model.h"

//�R���X�g���N�^
TitleModel::TitleModel(GameObject* parent)
	:GameObject(parent,"TitleModel"),hModel_(-1), beforeScale_(XMVectorSet(0,0,0,0))
{
}

//������
void TitleModel::Initialize()
{
	//���f���f�[�^���[�h
	hModel_ = Model::Load("Stage/Title/Model/TitleModel.fbx");
	assert(hModel_ >= ZERO);

}

//�X�V�̑O�Ɉ��Ă΂��֐�
void TitleModel::StartUpdate()
{
	//��Ԃ���O�̊g�嗦�ۑ�
	ARGUMENT_INITIALIZE(beforeScale_, MIN_SCALE);

	//���̖ڕW�Ƃ���g�嗦�̕ۑ�
	ARGUMENT_INITIALIZE(targetScale_, MAX_SCALE);
}

//�X�V
void TitleModel::Update()
{
	//�g�嗦���Ԃ��Ȃ���ς��Ă���
	XMStoreFloat3(&transform_.scale_,XMVectorLerp(XMLoadFloat3(&transform_.scale_), targetScale_, INTERPOLATION_FACTOR));

	//������0.01���Z���̂Ȃ�
	if (Transform::RangeCalculation(transform_.scale_, Transform::VectorToFloat3(targetScale_)) < CHANGE_TARGET_DISTANCE)
	{
		//�^�[�Q�b�g����
		std::swap(beforeScale_, targetScale_);
	}
}

//�`��
void TitleModel::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void TitleModel::Release()
{
}
