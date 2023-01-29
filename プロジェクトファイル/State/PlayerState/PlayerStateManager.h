#pragma once
#include "../../Engine/Input.h"
#include "PlayerState.h"
#include "../../Engine/Global.h"
#include "JumpingState.h"
#include "JumpRotationningState.h"
#include "RotationningState.h"
#include "RunningState.h"
#include "StandingState.h"
#include "WalkingState.h"
#include "DieState.h"

//��`
class PlayerBase;

/// <summary>
/// Player�̏�Ԃ��Ǘ����Ă���N���X
/// </summary>
class PlayerStateManager : public PlayerState
{
private:

	//�L�����̑O�����̃x�N�g��
	XMVECTOR front_;                        

public:

	//��Ԃ������ϐ�
	static PlayerState* playerState_;

	//�e��ԕϐ�
	static JumpingState*          playerJumping_;             //�W�����v
	static JumpRotationningState* playerJumpRotationning_;    //�W�����v��]
	static RotationningState*     playerRotationning_;		  //��]
	static RunningState*          playerRunning_;		      //����
	static StandingState*		  playerStanding_;			  //�����Ă�
	static WalkingState* 		  playerWalking_;			  //����
	static DieState*              playerDieing_;              //���S

    //�R���X�g���N�^
	PlayerStateManager();

	//2D�p�X�V
	virtual void Update2D(PlayerBase* player)override;

	//3D�p�X�V
	virtual void Update3D(PlayerBase* player)override;

	//�~�j�Q�[���p�X�V
	virtual void UpdateMiniGame(PlayerBase* player)override;

	//���͂ɂ���ď�ԕω�����
	virtual void HandleInput(PlayerBase* player)override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	virtual void Enter(PlayerBase* player)override;

	//��ԃ`�F���W�p
	void ChangeState(PlayerState* change, PlayerBase* player);

};



