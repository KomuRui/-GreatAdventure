#include "MainMob.h"

//�萔
namespace
{
	static const int START_FRAME = 0;	  //�J�n�t���[��
	static const int END_FRAME = 120;     //�I���t���[��
	static const float ANIM_SPEED = 1.0f; //�A�j���[�V�����̍Đ����x
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void MainMob::ChildStartUpdate()
{
	//�A�j���[�V����
	Model::SetAnimFrame(hModel_, START_FRAME, END_FRAME, ANIM_SPEED);
	Model::SetAnimFlag(hModel_, true);
}
