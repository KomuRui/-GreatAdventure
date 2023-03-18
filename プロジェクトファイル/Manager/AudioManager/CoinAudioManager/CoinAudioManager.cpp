#include "CoinAudioMAnager.h"
#include "../../../Engine/ResourceManager/Audio.h"

// Coinの音を管理する
namespace CoinAudioManager
{
	//当たった時の音番号
	int hHitAudio_;

	/// <summary>
	/// 初期化
	///</summary>
	void Initialize()
	{
		//音ロード
		hHitAudio_ = Audio::Load("Audio/SE/Coin/Coin.wav");
		assert(hHitAudio_ >= ZERO);
	}

	/// <summary>
	/// シーン遷移の時の初期化
	/// </summary>
	void SceneTransitionInitialize()
	{
		Initialize();
	}

	//当たった時の音
	void HitAudio()
	{
		Audio::Play(hHitAudio_);
	}

}