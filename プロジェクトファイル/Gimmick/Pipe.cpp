#include "Pipe.h"
#include "../Manager/GameManager/GameManager.h"

//�萔
namespace
{
	//���S���鎞��Player�Ƃ�Z�̋���
	static const int KILLME_PLAYER_Z_DIS = -5;
}

//�R���X�g���N�^
Pipe::Pipe(GameObject* parent)
	:Mob(parent, "Stage/Gimmick/Pipe.fbx", "Pipe")
{
}

//�X�V�̑O�Ɉ�x������΂��֐�
void Pipe::ChildStartUpdate()
{
	///////////////���邳///////////////////

	Model::SetBrightness(hModel_, 1.0f);
}

//�X�V
void Pipe::ChildUpdate()
{
	//Player�����ɍs�����玀�S
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z + KILLME_PLAYER_Z_DIS)
		KillMe();
}
