#pragma once
#include "../Engine/Input.h"
#include "State.h"
#include "JumpingState.h"
#include "JumpRotationningState.h"
#include "RotationningState.h"
#include "RunningState.h"
#include "StandingState.h"
#include "WalkingState.h"
#include "../Engine/Global.h"

//Player�̏�Ԃ̊��N���X
class PlayerState : public State
{
private:

	//��Ԃ������ϐ�
	State* state_;

public:

	//�e��ԕϐ�
	static JumpingState*          jumping_;             //�W�����v
	static JumpRotationningState* jumpRotationning_;    //�W�����v��]
	static RotationningState*     rotationning_;		//��]
	static RunningState*          running_;				//����
	static StandingState*		  standing_;			//�����Ă�
	static WalkingState* 		  walking_;				//����

    //�R���X�g���N�^
	PlayerState();

	//�X�V
	void Update() override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput() override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	void Enter() override;
};



