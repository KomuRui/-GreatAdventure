#pragma once

/// <summary>
/// Player�̎����Ă�R�C���Ǘ�
/// </summary>
namespace CoinManager
{
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �V�[���J�ڂ̎��̏�����
	/// </summary>
	void SceneTransitionInitialize();

	/// <summary>
	/// �R�C�����������Ă��邩�`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �R�C���̒ǉ�
	/// </summary>
	/// <param name="num">�ǉ��������R�C���̐�</param>
	void AddCoin(int num);

	/// <summary>
	/// �R�C���̌���
	/// </summary>
	/// <param name="num">�������������R�C���̐�</param>
	void DecrementCoin(int num);

	/// <summary>
	/// �R�C���̐��擾
	/// </summary>
	/// <returns>�R�C���̐�</returns>
	int GetCoinNum();

	/// <summary>
	/// �R�C���̐����Z�b�g
	/// </summary>
	/// <param name="num">�Z�b�g�������R�C���̐�</param>
	void SetCoinNum(int num);
}

