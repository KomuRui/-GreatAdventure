#include "CoinAudioMAnager.h"
#include "../../../Engine/ResourceManager/Audio.h"

// Coin�̉����Ǘ�����
namespace CoinAudioManager
{
	//�����������̉��ԍ�
	int hHitAudio_;

	/// <summary>
	/// ������
	///</summary>
	void Initialize()
	{
		//�����[�h
		hHitAudio_ = Audio::Load("Audio/SE/Coin/Coin.wav");
		assert(hHitAudio_ >= ZERO);
	}

	/// <summary>
	/// �V�[���J�ڂ̎��̏�����
	/// </summary>
	void SceneTransitionInitialize()
	{
		Initialize();
	}

	//�����������̉�
	void HitAudio()
	{
		Audio::Play(hHitAudio_);
	}

}