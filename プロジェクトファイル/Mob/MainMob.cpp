#include "MainMob.h"
#include "../Engine/ImGuiSet.h"

//�萔
namespace
{
	////////////////////////////�A�j���[�V����////////////////////////////

	static const int START_FRAME = 0;	  //�J�n�t���[��
	static const int END_FRAME = 120;     //�I���t���[��
	static const float ANIM_SPEED = 1.0f; //�A�j���[�V�����̍Đ����x

	////////////////////////////���̑�////////////////////////////

	static const float PLAYER_LOOK_DISTANCE = 8; //Player�̕����������̋���
}

//�R���X�g���N�^
MainMob::MainMob(GameObject* parent, std::string modelPath, std::string name) 
	:Mob(parent, modelPath, name),isAnim_(true),toPlayer_(XMMatrixIdentity()), isLookPlayer_(false)
{}

//�X�V�̑O�Ɉ�x�����Ă΂��
void MainMob::ChildStartUpdate()
{
	//�����A�j���[�V��������Ȃ�
	if (isAnim_)
	{
		//�A�j���[�V����
		Model::SetAnimFrame(hModel_, START_FRAME, END_FRAME, ANIM_SPEED);
		Model::SetAnimFlag(hModel_, true);
	}
}

//�X�V
void MainMob::ChildUpdate()
{
	//�����A�j���[�V�������ĂȂ��Ȃ�Player�̕�������
	if (!isAnim_)
		LookPlayer();
}

//Player�̕�������
void MainMob::LookPlayer()
{
	//�������ł�Player�̕������Ă�����
	if(isLookPlayer_)
		transform_.mmRotate_ = XMMatrixInverse(nullptr, toPlayer_);

	//Player�Ƃ̋�����8�ȓ��Ȃ�Player�̕�������
	if (RangeCalculation(transform_.position_, GameManager::GetpPlayer()->GetPosition()) < PLAYER_LOOK_DISTANCE)
	{
		toPlayer_ = XMMatrixLookAtLH(XMVectorSet(ZERO, ZERO, ZERO, ZERO), XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_), up_);
		transform_.mmRotate_ = XMMatrixInverse(nullptr, toPlayer_);

		ARGUMENT_INITIALIZE(isLookPlayer_, true);
	}
}