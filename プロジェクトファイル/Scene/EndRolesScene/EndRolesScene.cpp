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

	//�t�F�[�h�C��
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
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