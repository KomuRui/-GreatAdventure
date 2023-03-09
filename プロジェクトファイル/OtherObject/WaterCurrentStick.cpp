#include "WaterCurrentStick.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/ResourceManager/VFX.h"
#include "../Manager/EffectManager/OtherEffectManager/OtherEffectManager.h"

//�萔
namespace
{
	static const int ROTATION_ANGLE = 10; //��]�p�x

	/// <summary>
	/// �֐��̃|�C���^�z��
	/// </summary>
	static void (WaterCurrentStick::* InstantiateArray[])() = { &WaterCurrentStick::Normal, &WaterCurrentStick::Rotation };

}

//�R���X�g���N�^
WaterCurrentStick::WaterCurrentStick(GameObject* parent, std::string modelFilePath_, std::string name)
	:GameObject(parent, name), hModel_(-1), filePath_(modelFilePath_), front_(STRAIGHT_VECTOR),hEffect_(ZERO),
	type_(WaterCurrentStickType::NORMAL)
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
	//�^�ɂ���ČĂԊ֐��𕪂���
	(this->*InstantiateArray[static_cast<int>(type_)])();
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

//��]
void WaterCurrentStick::Rotation()
{
	//�O�x�N�g���X�V
	front_ = XMVector3Normalize(XMVector3TransformCoord(front_, XMMatrixRotationY(XMConvertToRadians(ROTATION_ANGLE))));

	//�G�t�F�N�g�̕����ς���
	VFX::GetEmitter(hEffect_)->data.direction = VectorToFloat3(front_);
}