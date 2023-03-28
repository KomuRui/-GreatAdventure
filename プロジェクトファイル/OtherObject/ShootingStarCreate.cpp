#include "ShootingStarCreate.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/ResourceManager/VFX.h"
#include "../Engine/ResourceManager/Time.h"
#include "ShootingStar.h"

//�萔
namespace
{
	static const float GENERATION_TIME = 2.0f;     //��������
}

//�R���X�g���N�^
ShootingStarCreate::ShootingStarCreate(GameObject* parent)
	:GameObject(parent, "ShootingStarCreate"), hTime_((int)ZERO)
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
	//�^�C�}�[���Z�b�g
	Time::Reset(hTime_);

	//���ꐯ����
	for(int i = 0; i < 3; i++)
		Instantiate<ShootingStar>(this)->SetPosition(XMFLOAT3((float)Random(-20,90),(float)Random(40,70),(float)Random(-20, 90)));

}