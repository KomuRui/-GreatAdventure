#include "HomeScene.h"
#include "../../Engine/SceneManager.h"
#include "../../Player.h"
#include "../../Engine/GameManager.h"
#include "../../Engine/Input.h"
#include "../../Scene/HomeScene/HomeStage.h"
#include "../../Engine/Camera.h"
#include "../../Gimmick/Warp.h"

//�R���X�g���N�^
HomeScene::HomeScene(GameObject* parent)
	: GameObject(parent, "HomeScene")
{

}

//������
void HomeScene::Initialize()
{
	//�X�e�[�W�̕\��
	GameManager::SetpStage(Instantiate<HomeStage>(this));

	//Player�ƃ��[�v�̕\��
	GameManager::SetpPlayer(Instantiate<Player>(this));
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");

	//���[�v�̃|�W�V�����ƈړ���̐ݒ�
	pWarp->SetPosition(GameManager::GetpPlayer()->GetPosition());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetWarpType(MoveToPurpose);

	GameManager::SetStatus(FADE_IN);
}

//�X�V
void HomeScene::Update()
{
	if (Input::IsKeyDown(DIK_R))
	{
		SceneManager* pScene = (SceneManager*)FindObject("SceneManager");
		pScene->ChangeScene(SCENE_ID_WORLD1);
	}
}

//�`��
void HomeScene::Draw()
{
}

//�J��
void HomeScene::Release()
{
}

void HomeScene::StartUpdate()
{
}
