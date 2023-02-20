#include "WorldScene2.h"
#include "../../../Engine/SceneManager.h"
#include "../../../Player/Player3D.h"
#include "../../../Manager/GameManager/GameManager.h"
#include "../../../Engine/Input.h"
#include "../../../Engine/Camera.h"
#include "../../../Gimmick/Warp.h"
#include "WorldStage2.h"

//�R���X�g���N�^
WorldScene2::WorldScene2(GameObject* parent)
	: GameObject(parent, "WorldScene2")
{

}

//������
void WorldScene2::Initialize()
{
	//�X�e�[�W�̕\��
	GameManager::SetpStage(Instantiate<WorldStage2>(this));

	//Player�ƃ��[�v�̕\��
	GameManager::SetpPlayer(Instantiate<Player3D>(this));
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");

	//���[�v�̃|�W�V�����ƈړ���̐ݒ�
	pWarp->SetPosition(GameManager::GetpStage()->GetPos());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetWarpType(MoveToPurpose);
	GameManager::SetpWarp(pWarp);

	//�t�F�[�h�C��
	GameManager::SetStatus(FADE_IN);
}

//�X�V
void WorldScene2::Update()
{
}

//�`��
void WorldScene2::Draw()
{
}

//�J��
void WorldScene2::Release()
{
}

void WorldScene2::StartUpdate()
{
}
