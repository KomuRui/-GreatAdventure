#include "EndRolesScene.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../UI/EndRolesScene/EndRoles.h"


//�R���X�g���N�^
EndRolesScene::EndRolesScene(GameObject* parent)
	: GameObject(parent, "EndRolesScene")
{

}

//������
void EndRolesScene::Initialize()
{
	//�G���h���[���\��
	Instantiate<EndRoles>(this,"Image/EndRole/EndRoleImage.png","EndRoles");

	//�t�F�[�h�A�E�g
	Fade::SetFadeStatus(FADE_NORMAL_OUT);
}

//�X�V
void EndRolesScene::Update()
{
}

//�`��
void EndRolesScene::Draw()
{
}

//�J��
void EndRolesScene::Release()
{
}

void EndRolesScene::StartUpdate()
{
}