#pragma once

/// <summary>
/// �l�X�ȉ����Ǘ�����
/// </summary>
namespace OtherAudioManager
{
	/// <summary>
	/// ������
	///</summary>
	void Initialize();

	/// <summary>
	/// �V�[���J�ڂ̎��̏�����
	/// </summary>
	void SceneTransitionInitialize();

	/// <summary>
	/// �N���b�N��
	/// </summary>
	void ClickAudio();

	/// <summary>
	/// ���[�v�q�b�g��
	/// </summary>
	void WarpHitAudio();

	/// <summary>
	/// ���[�v�V���b�g��
	/// </summary>
	void WarpShootAudio();

	/// <summary>
	/// �Q�[���I�[�o�[��
	/// </summary>
	void GameOverAudio();
}