#include "sceneManager.h"
#include "Model.h"
#include "Image.h"
#include "Audio.h"
#include "Light.h"
#include "Time.h"
#include "../Scene/TitleScene/TitleScene.h"
#include "../Scene/TutorialScene/TutorialScene1.h"
#include "../Scene/TutorialScene/TutorialScene2.h"
#include "../Scene/HomeScene/HomeScene.h"
#include "../Scene/WorldScene/World1/WorldScene1.h"
#include "../Scene/WorldScene/World2/WorldScene2.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Scene/UserSelectScene/UserSelectScene.h"
#include "../Manager/CoinManager/CoinManager.h"
#include "../Manager/LifeManager/LifeManager.h"
#include "../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../Manager/EffectManager/EnemyEffectManager/EnemyEffectManager.h"
#include "../Manager/EffectManager/CoinEffectManager/CoinEffectManager.h"
#include "../Scene/MiniGameScene/MiniGameScene.h"
#include "../Manager/MiniGameManager/MiniGameManager.h"
#include "../Scene/MiniGameLevelSelectScene/MiniGameLevelSelectScene.h"
#include "../Manager/ButtonManager/ButtonManager.h"

//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager"), loadDrawFlag_(true)
{
}

//������
void SceneManager::Initialize()
{
	//���g��ǉ�
	GameManager::SetpSceneManager(this);

	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_TUTORIAL2;
	nextSceneID_ = currentSceneID_;
	Instantiate<TutorialScene2>(this);
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
		ButtonManager::Reset();
		Audio::AllRelease();
		Model::AllRelease();
		Image::AllRelease();
		Time::AllRelease();

		//�V�[���J�ڎ��̏�����
		GameManager::SceneTransitionInitialize();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_TITLE:				 Instantiate<TitleScene>(this); break;
		case SCENE_ID_USER_SELECT:			 Instantiate<UserSelectScene>(this); break;
		case SCENE_ID_TUTORIAL1:		     Instantiate<TutorialScene1>(this); break;
		case SCENE_ID_TUTORIAL2:		     Instantiate<TutorialScene2>(this); break;
		case SCENE_ID_HOME:     		     Instantiate<HomeScene>(this); break;
		case SCENE_ID_MINIGAME:              Instantiate<MiniGameScene>(this); break;
		case SCENE_ID_MINIGAME_LEVEL_SELECT: Instantiate<MiniGameLevelSelectScene>(this); break;
		case SCENE_ID_WORLD1:                Instantiate<WorldScene1>(this); break;
		case SCENE_ID_WORLD2:                Instantiate<WorldScene2>(this); break;
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