#include "PlayerAudioMAnager.h"
#include "../../../Engine/ResourceManager/Audio.h"

// Playerの音を管理する
namespace PlayerAudioManager
{
	//当たった時の音番号
	int hRotationAudio_; //回転音
	int hAttackHitAudio_;//攻撃音
	int hDamageAudio_;   //ダメージ音
	int hJumpAudio_;     //ジャンプ音
	int hJumpLandAudio_; //着地音
	int hFootStepAudio_; //足音音
	int hBlockHitAudio_; //ブロックヒット音

	//フラグ
	bool IsStopFootStep; //足音音止まっているかどうか

	/// <summary>
	/// 初期化
	///</summary>
	void Initialize()
	{
		hRotationAudio_ = Audio::Load("Audio/SE/Player/Rotation.wav");
		assert(hRotationAudio_ >= ZERO);

		hAttackHitAudio_ = Audio::Load("Audio/SE/Player/Hit.wav");
		assert(hAttackHitAudio_ >= ZERO);

		hDamageAudio_ = Audio::Load("Audio/SE/Player/Damage.wav");
		assert(hDamageAudio_ >= ZERO);

		hJumpAudio_ = Audio::Load("Audio/SE/Player/Jump.wav");
		assert(hJumpAudio_ >= ZERO);

		hJumpLandAudio_ = Audio::Load("Audio/SE/Player/JumpLanding.wav");
		assert(hJumpLandAudio_ >= ZERO);

		hFootStepAudio_ = Audio::Load("Audio/SE/Player/FootStep.wav");
		assert(hFootStepAudio_ >= ZERO);

		hBlockHitAudio_ = Audio::Load("Audio/SE/Player/BlockHit.wav");
		assert(hBlockHitAudio_ >= ZERO);

		ARGUMENT_INITIALIZE(IsStopFootStep, true);
	}

	/// <summary>
	/// シーン遷移の時の初期化
	/// </summary>
	void SceneTransitionInitialize()
	{
		Initialize();
	}

	//回転音
	void RotationAudio() { Audio::Play(hRotationAudio_); }

	//攻撃当たった時の音
	void AttackHitAudio() { Audio::Play(hAttackHitAudio_); }
	
	//ダメージくらった時の音
	void DamageAudio() { Audio::Play(hDamageAudio_); }

	//ジャンプ音
	void JumpAudio() { Audio::Play(hJumpAudio_); }

	//着地音
	void JumpLandAudio() { Audio::Play(hJumpLandAudio_); }

	//足音音
	void FootStepAudio() 
	{
		//まだ足音音鳴らしていないのなら
		if (IsStopFootStep)
		{
			Audio::PlayLoop(hFootStepAudio_);
			ARGUMENT_INITIALIZE(IsStopFootStep, false);
		}
	}

	//ブロックヒット音
	void BlockHitAudio() { Audio::Play(hBlockHitAudio_); }

	//足音ストップ
	void StopFootStep() 
	{
		Audio::Stop(hFootStepAudio_);
		ARGUMENT_INITIALIZE(IsStopFootStep, true);
	}

	//足音音が止まっているのかどうか
	bool IsStopFootStepAudio() { return IsStopFootStep; }
}