#include "PlayerAudioMAnager.h"
#include "../../../Engine/ResourceManager/Audio.h"

// Playerの音を管理する
namespace PlayerAudioManager
{
	//当たった時の音番号
	int hAttackHitAudio_;//攻撃音
	int hDamageAudio_;   //ダメージ音
	int hJumpAudio_;     //ジャンプ音
	int hJumpLandAudio_; //着地音


	/// <summary>
	/// 初期化
	///</summary>
	void Initialize()
	{
		hAttackHitAudio_ = Audio::Load("Audio/SE/Player/Hit.wav");
		assert(hAttackHitAudio_ >= ZERO);
		hDamageAudio_ = Audio::Load("Audio/SE/Player/damage.wav");
		assert(hDamageAudio_ >= ZERO);
		hJumpAudio_ = Audio::Load("Audio/SE/Player/Jump.wav");
		assert(hJumpAudio_ >= ZERO);
		hJumpLandAudio_ = Audio::Load("Audio/SE/Player/JumpLanding.wav");
		assert(hJumpLandAudio_ >= ZERO);
	}

	/// <summary>
	/// シーン遷移の時の初期化
	/// </summary>
	void SceneTransitionInitialize()
	{
		Initialize();
	}

	//攻撃当たった時の音
	void AttackHitAudio() { Audio::Play(hAttackHitAudio_); }
	
	//ダメージくらった時の音
	void DamageAudio() { Audio::Play(hDamageAudio_); }

	//ジャンプ音
	void JumpAudio() { Audio::Play(hJumpAudio_); }

	//着地音
	void JumpLandAudio() { Audio::Play(hJumpLandAudio_); }
}