#include "TutorialScene2.h"
#include "../../Engine/SceneManager.h"
#include "../../Player.h"
#include "../../Scene/TutorialScene/TutorialStage2.h"
#include "../../Engine/GameManager.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/Camera.h"

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
	GameManager::SetpPlayer(Instantiate<Player>(this));
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");

	//���[�v�̃|�W�V�����ƈړ���̐ݒ�
	pWarp->SetPosition(GameManager::GetpPlayer()->GetPosition());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetNumber(2);

	GameManager::SetStatus(FADE_IN);
}

//�X�V
void TutorialScene2::Update()
{
	if (Input::IsKeyDown(DIK_R))
	{
		SceneManager* pScene = (SceneManager*)FindObject("SceneManager");
		pScene->ChangeScene(SCENE_ID_HOME);
	}
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
