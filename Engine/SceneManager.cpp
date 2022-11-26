#include "sceneManager.h"
#include "Model.h"
#include "Image.h"
#include "Audio.h"
#include "../TitleScene/TitleScene.h"
#include "../TutorialScene/TutorialScene1.h"
#include "../TutorialScene/TutorialScene2.h"

//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

//������
void SceneManager::Initialize()
{
	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_TUTORIAL1;
	nextSceneID_ = currentSceneID_;
	Instantiate<TutorialScene1>(this);
}

//�X�V
void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();

		//���[�h�����f�[�^��S�폜
		Audio::Release();
		Model::AllRelease();
		Image::AllRelease();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_TITLE:				 Instantiate<TitleScene>(this); break;
		case SCENE_ID_TUTORIAL1:		     Instantiate<TutorialScene1>(this); break;
		case SCENE_ID_TUTORIAL2:		     Instantiate<TutorialScene2>(this); break;
		}
		Audio::Initialize();
		currentSceneID_ = nextSceneID_;
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

	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();

		//���[�h�����f�[�^��S�폜
		Audio::Release();
		Model::AllRelease();
		Image::AllRelease();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_TITLE:				 Instantiate<TitleScene>(this); break;
		case SCENE_ID_TUTORIAL1:		     Instantiate<TutorialScene1>(this); break;
		case SCENE_ID_TUTORIAL2:		     Instantiate<TutorialScene2>(this); break;
		}
		Audio::Initialize();
		currentSceneID_ = nextSceneID_;
	}
}