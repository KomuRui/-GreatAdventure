#include "PlayerAudioMAnager.h"
#include "../../../Engine/ResourceManager/Audio.h"

// Player�̉����Ǘ�����
namespace PlayerAudioManager
{
	//�����������̉��ԍ�
	int hAttackHitAudio_;//�U����
	int hDamageAudio_;   //�_���[�W��
	int hJumpAudio_;     //�W�����v��
	int hJumpLandAudio_; //���n��


	/// <summary>
	/// ������
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
	/// �V�[���J�ڂ̎��̏�����
	/// </summary>
	void SceneTransitionInitialize()
	{
		Initialize();
	}

	//�U�������������̉�
	void AttackHitAudio() { Audio::Play(hAttackHitAudio_); }
	
	//�_���[�W����������̉�
	void DamageAudio() { Audio::Play(hDamageAudio_); }

	//�W�����v��
	void JumpAudio() { Audio::Play(hJumpAudio_); }

	//���n��
	void JumpLandAudio() { Audio::Play(hJumpLandAudio_); }
}