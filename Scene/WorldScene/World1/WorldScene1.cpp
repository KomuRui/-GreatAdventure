#include "WorldScene1.h"
#include "../../../Engine/SceneManager.h"
#include "../../../Player.h"
#include "../../../Engine/GameManager.h"
#include "../../../Engine/Input.h"
#include "../../../Engine/Camera.h"
#include "../../../Gimmick/Warp.h"
#include "WorldStage1.h"

//�R���X�g���N�^
WorldScene1::WorldScene1(GameObject* parent)
	: GameObject(parent, "WorldScene1")
{

}

//������
void WorldScene1::Initialize()
{
	//�X�e�[�W�̕\��
	GameManager::SetpStage(Instantiate<WorldStage1>(this));

	//Player�ƃ��[�v�̕\��
	GameManager::SetpPlayer(Instantiate<Player>(this));
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");

	//���[�v�̃|�W�V�����ƈړ���̐ݒ�
	pWarp->SetPosition(GameManager::GetpPlayer()->GetPosition());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetNumber(2);
}

//�X�V
void WorldScene1::Update()
{
}

//�`��
void WorldScene1::Draw()
{
}

//�J��
void WorldScene1::Release()
{
}

void WorldScene1::StartUpdate()
{
}