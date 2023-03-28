#include "ShineLight.h"
#include "../Engine/GameObject/Light.h"
#include "../Engine/ResourceManager/Model.h"

//�萔
namespace
{
	static const int LIGHT_INTENSITY = 2;							 //���C�g�̋���
	static const int REACTION_DISTANCE = 4;							 //��������
	static const float SHINE_PERMIT_CALLING_TIME = 1.0f;			 //����̂������郁�\�b�h���ĂԎ���
	static const XMFLOAT4 HIGHLIGHT_COLOR = { 1.0f,1.0f,1.0f,1.0f }; //�n�C���C�g�̐F
}

//�R���X�g���N�^
ShineLight::ShineLight(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath, name), shineFlag_(false),lightNum_((int)ZERO),shinePermitFlag_(true)
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
			lightNum_ = Light::CreateLight(lightPos, LIGHT_INTENSITY);

			//�n�C���C�g
			Model::SetSpeculer(hModel_, HIGHLIGHT_COLOR);

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

	//�n�C���C�g�폜
	Model::SetSpeculer(hModel_, XMFLOAT4(ZERO, ZERO, ZERO, ZERO));

	//�����Ă��炷���Ɍ���悤�ɂ������Ȃ��̂�
	//1.0�b��Ɍ��点����悤�ɂ���
	SetTimeMethod(SHINE_PERMIT_CALLING_TIME);
}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void ShineLight::TimeMethod()
{
	//����̂�����
	ARGUMENT_INITIALIZE(shinePermitFlag_, true);
}