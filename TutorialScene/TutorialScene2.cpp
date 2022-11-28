#include "TutorialScene2.h"
#include "../Engine/SceneManager.h"
#include "../Player.h"
#include "../TutorialScene/TutorialStage2.h"
#include "../Engine/GameManager.h"
#include "../Gimmick/Warp.h"

//�R���X�g���N�^
TutorialScene2::TutorialScene2(GameObject* parent)
	: GameObject(parent, "TutorialScene2")
{

}

//������
void TutorialScene2::Initialize()
{
	//���ꂩ��g���X�e�[�W�̃|�C���^��GameManager�ɃZ�b�g
	GameManager::SetpStage(Instantiate<TutorialStage2>(this));

	//Player�ƃ��[�v�̕\��
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");
	GameManager::SetpPlayer(Instantiate<Player>(this));

	//���[�v�̃|�W�V�����ƈړ���̐ݒ�
	pWarp->SetPosition(GameManager::GetpPlayer()->GetPosition());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetNumber(2);
}

//�X�V
void TutorialScene2::Update()
{
	/*if (Input::IsKeyDown(DIK_R))
	{
		SceneManager* pScene = (SceneManager*)FindObject("SceneManager");
		pScene->ChangeScene(SCENE_ID_TUTORIAL1);
	}*/
}

//�`��
void TutorialScene2::Draw()
{
}

//�J��
void TutorialScene2::Release()
{
}

void TutorialScene2::StartUpdate()
{
}
