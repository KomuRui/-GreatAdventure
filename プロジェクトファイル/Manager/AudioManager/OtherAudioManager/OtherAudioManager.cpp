#include "OtherAudioManager.h"
#include "../../../Engine/ResourceManager/Audio.h"

// 様々な音を管理する
namespace OtherAudioManager
{
	
	int hClickAudio_;    //クリック音
	int hWarpHitAudio_;  //ワープヒット音
	int hWarpShootAudio_;//ワープショット音
	int hGameOverAudio_; //ゲームオーバー音

	/// <summary>
	/// 初期化
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

	/// <summary>
	/// ワープヒット音
	/// </summary>
	void WarpHitAudio() { Audio::Play(hWarpHitAudio_); }

	/// <summary>
	/// ワープショット音
	/// </summary>
	void WarpShootAudio() { Audio::Play(hWarpShootAudio_); }

	/// <summary>
	/// ゲームオーバー音
	/// </summary>
	void GameOverAudio() { Audio::Play(hGameOverAudio_); }
}