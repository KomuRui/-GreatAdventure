#include "OtherAudioManager.h"
#include "../../../Engine/ResourceManager/Audio.h"

// �l�X�ȉ����Ǘ�����
namespace OtherAudioManager
{
	
	int hClickAudio_;//�N���b�N��

	/// <summary>
	/// ������
	///</summary>
	void Initialize()
	{
		hClickAudio_ = Audio::Load("Audio/SE/Click/NormalClick.wav");
		assert(hClickAudio_ >= ZERO);
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
}