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

	//�L�����̑O�����̃x�N�g��
	XMVECTOR front_;                        

public:

	//��Ԃ������ϐ�
	static State* state_;

	//�e��ԕϐ�
	static JumpingState*          jumping_;             //�W�����v
	static JumpRotationningState* jumpRotationning_;    //�W�����v��]
	static RotationningState*     rotationning_;		//��]
	static RunningState*          running_;				//����
	static StandingState*		  standing_;			//�����Ă�
	static WalkingState* 		  walking_;				//����

    //�R���X�g���N�^
	PlayerState();

	//2D�p�X�V
	void Update2D() override;

	//3D�p�X�V
	void Update3D() override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput() override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	void Enter() override;

};


