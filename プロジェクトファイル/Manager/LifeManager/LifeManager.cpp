#include "LifeManager.h"
#include "../../Engine/Global.h"

//�萔
namespace
{
	static const int NORMAL_PLAYER_LIFE = 3; //���ʂ�Player�̃��C�t�̐�
}

/// <summary>
/// Player�̃��C�t�Ǘ�
/// </summary>
namespace LifeManager
{
	///////////////////////////////�ϐ�//////////////////////////////////

	//Player�̌��݂̃��C�t�̑���
	int playerLife;

	///////////////////////////////�֐�//////////////////////////////////

	//������
	void LifeManager::Initialize()
	{
		ARGUMENT_INITIALIZE(playerLife, NORMAL_PLAYER_LIFE);
	}

	//�_���[�W�H��������ɌĂԃ��\�b�h
	void LifeManager::Damage(int damage)
	{
		//���C�t�����
		playerLife -= damage;

		//��������ł�����
		if(IsDie()){}
	}

	//���񂾂ǂ���
	bool LifeManager::IsDie() { return (playerLife <= ZERO); }
}