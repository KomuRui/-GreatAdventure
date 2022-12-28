#include "LifeManager.h"
#include "../../Engine/Global.h"
#include "../GameManager/GameManager.h"
#include "../../Engine/Image.h"

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
	/// <summary>
	/// ���C�t���Ƃɉ摜�𕪂������̂ŗ񋓂���
	/// </summary>
	enum Life
	{
		Zero,		//HP0
		One,		//HP1
		Two,		//HP2
		Three,		//HP3
		MAX_LIFE_IMAGE
	};

	///////////////////////////////�ϐ�//////////////////////////////////

	//Player�̌��݂̃��C�t�̑���
	int playerLife_;

	//���C�t���Ƃ̉摜�ԍ�
	int lifeImage[MAX_LIFE_IMAGE];

	///////////////////////////////�֐�//////////////////////////////////

	//������
	void LifeManager::Initialize()
	{
		//�e���C�t�̉摜���[�h
		lifeImage[Zero] = Image::Load("Image/Player/PlayerHP0.png");
		lifeImage[One] = Image::Load("Image/Player/PlayerHP1.png");
		lifeImage[Two] = Image::Load("Image/Player/PlayerHP2.png");
		lifeImage[Three] = Image::Load("Image/Player/PlayerHP3.png");
		

		//Playre�̃��C�t������
		ARGUMENT_INITIALIZE(playerLife_, NORMAL_PLAYER_LIFE);
	}

	//�_���[�W�H��������ɌĂԃ��\�b�h
	void LifeManager::Damage(int damage)
	{
		//���C�t�����
		playerLife_ -= damage;

		//��������ł�����GameManager�Ɏ��񂾂��Ɠ`����
		if(IsDie()){ GameManager::PlayerDie(); }
	}

	//HPUI�`��
	void LifeManager::Draw()
	{

	}

	//���񂾂ǂ���
	bool LifeManager::IsDie() { return (playerLife_ <= ZERO); }
}