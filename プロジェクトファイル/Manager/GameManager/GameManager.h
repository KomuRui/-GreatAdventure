#pragma once
#include "../../Stage.h"
#include "../../Player.h"
#include "../../Engine/SceneManager.h"

//�t�F�[�h�̏�Ԃ̗񋓌^
enum FadeStatus
{
	NOOP,     //�������Ȃ�
	DRAW,     //�摜�����\��
	FADE_IN,  //�t�F�[�h�C��
	FADE_OUT  //�t�F�[�h�A�E�g
};

//�Q�[���̂��낢��ȊǗ�������
namespace GameManager
{
	///////////////////////////////�֐�//////////////////////////////////
	
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// Player�����S��������LifeManager����Ă΂��
	/// </summary>
	void PlayerDie();

	///////////////////////////////�Z�b�g�Q�b�g�֐�//////////////////////////////////
	
	//�v���C���[�̃|�C���^�Z�b�g
	void SetpPlayer(Player* player);

	//�v���C���[�̃|�C���^�Q�b�g
	Player* GetpPlayer();

	//�X�e�[�W�̃|�C���^�Z�b�g
	void SetpStage(Stage* stage);

	//�X�e�[�W�̃|�C���^�Q�b�g
	Stage* GetpStage();

	//�V�[���}�l�[�W���[�̃|�C���^�Z�b�g
	void SetpSceneManager(SceneManager* scene);

	//�V�[���}�l�[�W���[�̃|�C���^�Q�b�g
	SceneManager* GetpSceneManager();

	///////////////////////////////�t�F�[�h�p�֐�////////////////////////////////////
	
	//�`��
	void Draw();

	//�t�F�[�h�`��
	void FadeDraw();

	//�t�F�[�h�C���`��
	void FadeInDraw();

	//�t�F�[�h�A�E�g�`��
	void FadeOutDraw();

	//��ԃZ�b�g
	void SetStatus(int status);

	//��ԃQ�b�g
	int GetStatus();
};

