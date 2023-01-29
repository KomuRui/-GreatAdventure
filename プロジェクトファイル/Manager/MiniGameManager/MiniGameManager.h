#pragma once

//�~�j�Q�[���̏��
enum class MiniGameStatus
{
	NOT_START = 0, //�܂��J�n���Ă��Ȃ�
	PLAY,          //�v���C��
	END            //�~�j�Q�[���I��
};

/// <summary>
/// �~�j�Q�[���̊Ǘ�������
/// </summary>
namespace MiniGameManager
{
	///////////////////////////////�֐�//////////////////////////////////

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �`��(�R�C���̎擾����R���{��,�^�C���̕\��)
	/// </summary>
	void Draw();

	/// <summary>
	/// ���ʕ\��
	/// </summary>
	void ResultDraw();

	/// <summary>
	/// �J�n���Ă��邩
	/// </summary>
	/// <returns>true�Ȃ�J�n���Ă���</returns>
	bool IsPlay();

	/// <summary>
	/// �J�n���Ă��邩���Z�b�g
	/// </summary>
	void ChangeMiniGameStatus(MiniGameStatus status);

	/// <summary>
	/// �X�s�[�h�����Z�b�g
	/// </summary>
	void ResetRunSpeed();

	/// <summary>
	/// �R���{�����Z�b�g
	/// </summary>
	void ResetCombo();

	/// <summary>
	/// �R���{�����Z
	/// </summary>
	void AddCombo();

	/// <summary>
	/// �X�s�[�h���Z�b�g
	/// </summary>
	void SetRunSpeed(const float& speed);

	/// <summary>
	/// ���鑬�x���擾
	/// </summary>
	/// <returns>���鑬�x</returns>
	float GetRunSpeed();

	/// <summary>
	/// �~�j�Q�[���̏�Ԃ��Q�b�g
	/// </summary>
	/// <returns>�~�j�Q�[���̏��</returns>
	MiniGameStatus GetMiniGameStatus();

	/// <summary>
	/// ������ݒ�
	/// </summary>
	/// <param name="dis">�ݒ肵��������</param>
	void SetResultDis(const int& dis);

	/// <summary>
	/// Run���[�h���ǂ���
	/// </summary>
	/// <returns>true�Ȃ�RunMode</returns>
	bool IsRunMode();

	/// <summary>
	/// RunMode���ǂ����ݒ�
	/// </summary>
	void SetRunMode(const bool& flag);

	/// <summary>
	/// �R���{�̕����̊g�嗦���Z�b�g
	/// </summary>
	void SetComboTextScale(const float& scale);

};

