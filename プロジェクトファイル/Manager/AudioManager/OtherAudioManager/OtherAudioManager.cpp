#include "OtherAudioManager.h"
#include "../../../Engine/ResourceManager/Audio.h"

// �l�X�ȉ����Ǘ�����
namespace OtherAudioManager
{
	
	int hClickAudio_;    //�N���b�N��
	int hWarpHitAudio_;  //���[�v�q�b�g��
	int hWarpShootAudio_;//���[�v�V���b�g��
	int hGameOverAudio_; //�Q�[���I�[�o�[��

	/// <summary>
	/// ������
	///</summary>
	void Initialize()
	{
		hClickAudio_ = Audio::Load("Audio/SE/Click/NormalClick.wav");
		assert(hClickAudio_ >= ZERO);

		hWarpHitAudio_ = Audio::Load("Audio/SE/Warp/Hit.wav");
		assert(hWarpHitAudio_ >= ZERO);

		hWarpShootAudio_ = Audio::Load("Audio/SE/Warp/Shoot.wav");
		assert(hWarpShootAudio_ >= ZERO);

		hGameOverAudio_ = Audio::Load("Audio/SE/Other/GameOver.wav");
		assert(hGameOverAudio_ >= ZERO);
	}

	/// <summary>
	/// �V�[���J�ڂ̎��̏�����
	/// </summary>
	void SceneTransitionInitialize()
	{
		Initialize();
	}

	/// <summary>
	/// �N���b�N��
	/// </summary>
	void ClickAudio() { Audio::Play(hClickAudio_); }

	/// <summary>
	/// ���[�v�q�b�g��
	/// </summary>
	void WarpHitAudio() { Audio::Play(hWarpHitAudio_); }

	/// <summary>
	/// ���[�v�V���b�g��
	/// </summary>
	void WarpShootAudio() { Audio::Play(hWarpShootAudio_); }

	/// <summary>
	/// �Q�[���I�[�o�[��
	/// </summary>
	void GameOverAudio() { Audio::Play(hGameOverAudio_); }
}