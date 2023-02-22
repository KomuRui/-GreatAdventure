#include "HomeScene.h"
#include "../../Engine/SceneManager.h"
#include "../../Player/Player3D.h"
#include "../../Manager/GameManager/GameManager.h"
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
	GameManager::SetpPlayer(Instantiate<Player3D>(this));
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");

	//���[�v�̃|�W�V�����ƈړ���̐ݒ�
	pWarp->SetPosition(GameManager::GetpStage()->GetPos());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetWarpType(MoveToPurpose);

	//�t�F�[�h�C��
	GameManager::SetFadeStatus(FADE_CIRCLE_IN);
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
