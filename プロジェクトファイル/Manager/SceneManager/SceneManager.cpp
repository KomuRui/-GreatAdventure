#include "sceneManager.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../../Engine/ResourceManager/Audio.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Scene/TitleScene/TitleScene.h"
#include "../../Scene/TutorialScene/TutorialScene1.h"
#include "../../Scene/TutorialScene/TutorialScene2.h"
#include "../../Scene/HomeScene/HomeScene.h"
#include "../../Scene/WorldScene/World1/WorldScene1.h"
#include "../../Scene/WorldScene/World2/WorldScene2.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Scene/UserSelectScene/UserSelectScene.h"
#include "../../Scene/LastScene/LastScene.h"
#include "../../Scene/EndRolesScene/EndRolesScene.h"
#include "../../Scene/StageSelectScene/StageSelectScene.h"
#include "../../Manager/CoinManager/CoinManager.h"
#include "../../Manager/LifeManager/LifeManager.h"
#include "../../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../../Manager/EffectManager/EnemyEffectManager/EnemyEffectManager.h"
#include "../../Manager/EffectManager/CoinEffectManager/CoinEffectManager.h"
#include "../../Scene/MiniGameScene/MiniGameScene.h"
#include "../../Manager/MiniGameManager/MiniGameManager.h"
#include "../../Scene/MiniGameLevelSelectScene/MiniGameLevelSelectScene.h"
#include "../../Manager/ButtonManager/ButtonManager.h"
#include "../../Engine/ResourceManager/VFX.h"
#include "../../OtherObject/UserInfomation.h"


//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager"), isLoadDraw_(true), isSameSceneInitialize_(false)
{
}

//������
void SceneManager::Initialize()
{
	//���g��ǉ�
	GameManager::SetpSceneManager(this);

	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

//�X�V
void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_ || isSameSceneInitialize_)
	{
		SceneUpdate();
	}
}

//�V�[�����X�V
void SceneManager::SceneUpdate()
{
	//���[�h���ɕ`�悷��Ȃ�
	if (isLoadDraw_)
	{
		//���[�h���Ă���Ƃ��p�̉摜�\��(�����\���������̂ŕ`��I�����Ă�)
		Fade::SetFadeStatus(DRAW);
		Direct3D::EndDraw();
	}

	//�Z�[�u���Ă���
	UserInfomation::CallSave();

	//���̃V�[���̃I�u�W�F�N�g��S�폜
	KillAllChildren();

	//���[�h�����f�[�^��S�폜
	ButtonManager::Reset();
	VFX::Release();
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
	case SCENE_ID_STAGE_SELECT:		     Instantiate<StageSelectScene>(this); break;
	case SCENE_ID_HOME:     		     Instantiate<HomeScene>(this); break;
	case SCENE_ID_MINIGAME:              Instantiate<MiniGameScene>(this); break;
	case SCENE_ID_MINIGAME_LEVEL_SELECT: Instantiate<MiniGameLevelSelectScene>(this); break;
	case SCENE_ID_WORLD1:                Instantiate<WorldScene1>(this); break;
	case SCENE_ID_WORLD2:                Instantiate<WorldScene2>(this); break;
	case SCENE_ID_LAST:					 Instantiate<LastScene>(this); break;
	case SCENE_ID_ENDROLES:              Instantiate<EndRolesScene>(this); break;
	}

	//�J�����g�V�[�����X�V
	ARGUMENT_INITIALIZE(currentSceneID_, nextSceneID_);

	//���[�h���ɕ`�悷��ɏ��������Ă���
	ARGUMENT_INITIALIZE(isLoadDraw_, true);

	//��������Ԃ�
	ARGUMENT_INITIALIZE(isSameSceneInitialize_, false);
}

//�����V�[������������Ԃɂ���
void SceneManager::SameSceneInitializ(SCENE_ID next)
{
	//���Ԏ~�߂Ă���Ή���
	Direct3D::SetTimeScale(false);

	//�V�[���؂�ւ�
	ChangeScene(next);

	//�����V�[��������������ɐݒ�
	ARGUMENT_INITIALIZE(isSameSceneInitialize_,true);
}

//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
void SceneManager::ChangeScene(SCENE_ID next){ 	Direct3D::SetTimeScale(false); ARGUMENT_INITIALIZE(nextSceneID_,next);}

//��O�̃V�[��ID���Q�b�g
SCENE_ID SceneManager::GetBeforeSceneId() { return currentSceneID_; }

//���݂̃V�[��ID�Q�b�g
SCENE_ID SceneManager::GetSceneId(){ return nextSceneID_;}

//���[�h�����Ă鎞�ɉ摜�\�����邩�Z�b�g����
void SceneManager::SetLoadDrawFlag(bool flag){ ARGUMENT_INITIALIZE(isLoadDraw_, flag);}