#include "OtherAudioManager.h"
#include "../../../Engine/ResourceManager/Audio.h"

// 様々な音を管理する
namespace OtherAudioManager
{
	
	int hClickAudio_;//クリック音

	/// <summary>
	/// 初期化
	///</summary>
	void Initialize()
	{
		hClickAudio_ = Audio::Load("Audio/SE/Click/NormalClick.wav");
		assert(hClickAudio_ >= ZERO);
	}

	/// <summary>
	/// シーン遷移の時の初期化
	/// </summary>
	void SceneTransitionInitialize()
	{
		Initialize();
	}

	/// <summary>
	/// クリック音
	/// </summary>
	void ClickAudio() { Audio::Play(hClickAudio_); }
}