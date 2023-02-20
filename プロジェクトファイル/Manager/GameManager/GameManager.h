#pragma once
#include "../../Stage.h"
#include "../../Player/PlayerBase.h"
#include "../../Engine/SceneManager.h"

class Warp;

//�t�F�[�h�̏�Ԃ̗񋓌^
enum FadeStatus
{
	NOOP,     //�������Ȃ�
	DRAW,     //�摜�����\��
	FADE_IN,  //�t�F�[�h�C��
	FADE_OUT, //�t�F�[�h�A�E�g
	GAME_OVER //�Q�[���I�[�o�[ 
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
	/// �V�[���J�ڂ̎��̏�����
	/// </summary>
	void SceneTransitionInitialize();

	/// <summary>
	/// Player�����S��������LifeManager����Ă΂��
	/// </summary>
	void PlayerDie();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��(�R�C���̎擾����Player���C�t�̕\��)
	/// </summary>
	void Draw();

	///////////////////////////////�Z�b�g�Q�b�g�֐�//////////////////////////////////

	//�v���C���[�̃|�C���^�Z�b�g
	void SetpPlayer(PlayerBase* player);

	//�v���C���[�̃|�C���^�Q�b�g
	PlayerBase* GetpPlayer();

	//�X�e�[�W�̃|�C���^�Z�b�g
	void SetpStage(Stage* stage);

	//�X�e�[�W�̃|�C���^�Q�b�g
	Stage* GetpStage();

	//���[�v�̃|�C���^�Z�b�g
	void SetpWarp(Warp* warp);

	//���[�v�̃|�C���^�Q�b�g
	Warp* GetpWarp();

	//�V�[���}�l�[�W���[�̃|�C���^�Z�b�g
	void SetpSceneManager(SceneManager* scene);

	//�V�[���}�l�[�W���[�̃|�C���^�Q�b�g
	SceneManager* GetpSceneManager();

	///////////////////////////////�t�F�[�h�p�֐�////////////////////////////////////
	
	/// <summary>
	/// ���ʂ̉摜��\��
	/// </summary>
	void NormalDraw();

	/// <summary>
	/// ��Ԃɂ���ČĂԊ֐�������
	/// </summary>
	void FadeDraw();

	/// <summary>
	/// �t�F�[�h�C���`��
	/// </summary>
	void FadeInDraw();

	/// <summary>
	/// �t�F�[�h�A�E�g�`��
	/// </summary>
	void FadeOutDraw();

	/// <summary>
	/// �Q�[���I�[�o�[�`��
	/// </summary>
	void GameOverDraw();

	/// <summary>
	/// ��Ԃ��Z�b�g
	/// </summary>
	/// <param name="status">�Z�b�g���������</param>
	 
	/// <summary>
	/// ��Ԃ��Z�b�g
	/// </summary>
	/// <param name="status">�Z�b�g���������</param>
	/// <param name="filename"></param>
	void SetStatus(int status, std::string filename = "");

	/// <summary>
	/// ���݂̏�Ԃ��擾
	/// </summary>
	/// <returns>���݂̏��</returns>
	int GetStatus();
};

