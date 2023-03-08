#include "ShootingStarCreate.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/ResourceManager/VFX.h"
#include "../Engine/ResourceManager/Time.h"

//�萔
namespace
{
	static const int GENERATION_TIME = 2.0f;     //��������
	static const float GENERATION_POS_Y = 20.0f; //�����|�W�V����Y
}

//�R���X�g���N�^
ShootingStarCreate::ShootingStarCreate(GameObject* parent)
	:GameObject(parent, "ShootingStarCreate"), hTime_(ZERO)
{
}

//������
void ShootingStarCreate::Initialize()
{
	//�^�C�}�[�ǉ�
	ARGUMENT_INITIALIZE(hTime_,Time::Add());

	//�^�C�}�[�X�^�[�g
	Time::UnLock(hTime_);
}

//�X�V
void ShootingStarCreate::Update()
{
	//�������Ԃ������琶��
	if (Time::GetTimei(hTime_) >= GENERATION_TIME) Generation();
}

//����
void ShootingStarCreate::Generation()
{

}