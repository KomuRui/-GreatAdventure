#include "ShineLight.h"
#include "../Engine/Light.h"
#include "../Engine/Model.h"

//�R���X�g���N�^
ShineLight::ShineLight(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath, name), shineFlag_(false),lightNum_(0),num_(1)
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
	//�v���C���[�Ƃ̋���������������菬�����������Ă��Ȃ��̂Ȃ�
	if (Transform::RangeCalculation(GameManager::GetpPlayer()->GetPosition(), transform_.position_) < REACTION_DISTANCE && !shineFlag_)
	{
		//���C�g�ݒu
		XMFLOAT4 lightPos = { transform_.position_.x,transform_.position_.y, transform_.position_.z,ZERO };
		lightNum_ = Light::SetPositionAndIntensity(lightPos, -LIGHT_INTENSITY);

		//�����Ă���悤�ɐݒ�
		ARGUMENT_INITIALIZE(shineFlag_, true);
	}

}
