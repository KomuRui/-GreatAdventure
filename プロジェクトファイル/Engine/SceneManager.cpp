#include "sceneManager.h"
#include "Model.h"
#include "Image.h"
#include "Audio.h"
#include "Light.h"
#include "../Scene/TitleScene/TitleScene.h"
#include "../Scene/TutorialScene/TutorialScene1.h"
#include "../Scene/TutorialScene/TutorialScene2.h"
#include "../Scene/HomeScene/HomeScene.h"
#include "../Scene/WorldScene/World1/WorldScene1.h"
#include "../Engine/GameManager.h"
#include "../Scene/UserSelectScene/UserSelectScene.h"

//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager"), loadDrawFlag_(true)
{
}

//������
void SceneManager::Initialize()
{
	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_WORLD1;
	nextSceneID_ = currentSceneID_;
	Instantiate<WorldScene1>(this);
}

//�X�V
void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���[�h���ɕ`�悷��Ȃ�
		if (loadDrawFlag_)
		{
			//���[�h���Ă���Ƃ��p�̉摜�\��(�����\���������̂ŕ`��I�����Ă�)
			GameManager::SetStatus(DRAW);
			Direct3D::EndDraw();
		}

		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();

		//���[�h�����f�[�^��S�폜
		Audio::AllRelease();
		Model::AllRelease();
		Image::AllRelease();

		//���C�g����������Ԃɂ��Ă���
		Light::Initialize();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_TITLE:				 Instantiate<TitleScene>(this); break;
		case SCENE_ID_USER_SELECT:			 Instantiate<UserSelectScene>(this); break;
		case SCENE_ID_TUTORIAL1:		     Instantiate<TutorialScene1>(this); break;
		case SCENE_ID_TUTORIAL2:		     Instantiate<TutorialScene2>(this); break;
		case SCENE_ID_HOME:     		     Instantiate<HomeScene>(this); break;
		case SCENE_ID_WORLD1:                Instantiate<WorldScene1>(this); break;
		}
		currentSceneID_ = nextSceneID_;

		//���[�h���ɕ`�悷��ɏ��������Ă���
		ARGUMENT_INITIALIZE(loadDrawFlag_, true);
	}

}

//�`��
void SceneManager::Draw()
{
}

//�J��
void SceneManager::Release()
{
}

void SceneManager::StartUpdate()
{
}

//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;

}

//���݂̃V�[��ID�Q�b�g
SCENE_ID SceneManager::GetSceneId()
{
	return nextSceneID_;
}

//���[�h�����Ă鎞�ɉ摜�\�����邩�Z�b�g����
void SceneManager::SetLoadDrawFlag(bool flag)
{
	ARGUMENT_INITIALIZE(loadDrawFlag_, flag);
}