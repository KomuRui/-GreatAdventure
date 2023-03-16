#pragma once
#include "../../Engine/ResourceManager/Global.h"
#include "../../Engine/GameObject/GameObject.h"

//�Q�[���ɓo�ꂷ��V�[��
enum SCENE_ID
{
	SCENE_ID_TITLE = 0,
	SCENE_ID_USER_SELECT,
	SCENE_ID_TUTORIAL1,
	SCENE_ID_TUTORIAL2,
	SCENE_ID_STAGE_SELECT,
	SCENE_ID_MINIGAME,
	SCENE_ID_MINIGAME_LEVEL_SELECT,
	SCENE_ID_HOME,
	SCENE_ID_WORLD1,
	SCENE_ID_WORLD2,
	SCENE_ID_LAST,
	SCENE_ID_ENDROLES,
	SCENE_ID_MAX
};

//-----------------------------------------------------------
//�V�[���؂�ւ���S������I�u�W�F�N�g
//-----------------------------------------------------------
class SceneManager : public GameObject
{
private:

	SCENE_ID currentSceneID_;	//���݂̃V�[��
	SCENE_ID nextSceneID_;		//���̃V�[��;

	bool     isLoadDraw_;       //���[�h�����Ă鎞�ɉ摜�\�����邩

public:

	//�R���X�g���N�^
	//�����Fparent	�e�I�u�W�F�N�g
	SceneManager(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override {};
	void Release() override {};
	void StartUpdate() override {};

	//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
	//�����Fnext	���̃V�[����ID
	void ChangeScene(SCENE_ID next);

	//�V�[�����X�V
	void SceneUpdate();

	//�����V�[������������Ԃɂ���
	void SameSceneInitializ(SCENE_ID next);

	//���[�h�����Ă鎞�ɉ摜�\�����邩�Z�b�g����
	void SetLoadDrawFlag(bool flag);

	//���݂̃V�[��ID�Q�b�g
	SCENE_ID GetSceneId();
};