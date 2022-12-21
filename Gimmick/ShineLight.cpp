#include "ShineLight.h"
#include "../Engine/Light.h"
#include "../Engine/Model.h"

//�R���X�g���N�^
ShineLight::ShineLight(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath, name), shineFlag_(false),lightNum_(0),num_(1), shinePermitFlag_(true)
{
}

//�X�V�̑O�Ɉ�񂾂��Ă΂��X�V
void ShineLight::ChildStartUpdate()
{
	//���C�̔���ɂ��ꂽ���̂�true�ɂ��Ă���
	Model::SetRayFlag(hModel_, true);
}

//�X�V
void ShineLight::ChildUpdate()
{
	//��������̂�������Ȃ�
	if (shinePermitFlag_)
	{
		//�v���C���[�Ƃ̋���������������菬�����������Ă��Ȃ��̂Ȃ�
		if (RangeCalculation(GameManager::GetpPlayer()->GetPosition(), transform_.position_) < REACTION_DISTANCE && !shineFlag_)
		{
			//���C�g�ݒu
			XMFLOAT4 lightPos = { transform_.position_.x,transform_.position_.y, transform_.position_.z,ZERO };
			lightNum_ = Light::SetPositionAndIntensity(lightPos, LIGHT_INTENSITY);

			//�����Ă���悤�ɐݒ�
			ARGUMENT_INITIALIZE(shineFlag_, true);
		}
	}
}

//����Ȃ��悤�ɃZ�b�g
void ShineLight::SetNotShineLight()
{
	//����Ȃ��悤��
	Light::DeleteLight(lightNum_);

	//�����Ă��Ȃ��ɐݒ�
	ARGUMENT_INITIALIZE(shineFlag_, false);
	ARGUMENT_INITIALIZE(shinePermitFlag_, false);

	//�����Ă��炷���Ɍ���悤�ɂ������Ȃ��̂�
	//1.0�b��Ɍ��点����悤�ɂ���
	SetTimeMethod(1.0f);
}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void ShineLight::TimeMethod()
{
	//����̂�����
	ARGUMENT_INITIALIZE(shinePermitFlag_, true);
}