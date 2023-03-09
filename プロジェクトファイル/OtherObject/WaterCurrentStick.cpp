#include "WaterCurrentStick.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/ResourceManager/VFX.h"
#include "../Manager/EffectManager/OtherEffectManager/OtherEffectManager.h"

//�R���X�g���N�^
WaterCurrentStick::WaterCurrentStick(GameObject* parent, std::string modelFilePath_, std::string name)
	:GameObject(parent, name), hModel_(-1), filePath_(modelFilePath_), front_(STRAIGHT_VECTOR),hEffect_(ZERO)
{
}

//������
void WaterCurrentStick::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load(filePath_);
	assert(hModel_ >= ZERO);

	//�O�x�N�g���X�V
	front_ = XMVector3Normalize(XMVector3TransformCoord(front_, XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y))));

	//�����̃G�t�F�N�g�\��
	hEffect_ = OtherEffectManager::WaterCurrentEffect(transform_.position_,VectorToFloat3(front_));
}

//�X�V
void WaterCurrentStick::Update()
{
	////�O�x�N�g���X�V
	//front_ = XMVector3Normalize(XMVector3TransformCoord(front_, XMMatrixRotationY(XMConvertToRadians(10))));

	////�G�t�F�N�g�̕����ς���
	//VFX::GetEmitter(hEffect_)->data.direction = VectorToFloat3(front_);
}

//�`��
void WaterCurrentStick::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void WaterCurrentStick::Release()
{
}
