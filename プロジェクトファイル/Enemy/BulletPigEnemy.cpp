#include "BulletPigEnemy.h"
#include "../Gimmick/Bullet.h"

//�萔
namespace
{
	//////////////////////�A�j���[�V����/////////////////////////

	static const int ANIM_START_FREAM = 0; //�A�j���[�V�����̊J�n�t���[��
	static const int ANIM_END_FREAM = 90;  //�A�j���[�V�����̏I���t���[��
	static const int SHOT_ANIM_FREAM = 40; //�A�j���[�V�����̋��V���b�g�t���[��
	static const float ANIM_SPEED = 1.0f;  //�A�j���[�V�����̃X�s�[�h

	//////////////////////�L�����̕K�v�ȏ��/////////////////////////

	static const float MODEL_BRIGHTNESS = 0.7f; //���f���̖��邳

}

//�R���X�g���N�^
BulletPigEnemy::BulletPigEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Enemy(parent,modelPath,name)
{
}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void BulletPigEnemy::EnemyChildStartUpdate()
{
	//�A�j���[�V�����ݒ�
	Model::SetAnimFlag(hModel_, true);
	Model::SetAnimFrame(hModel_, ANIM_START_FREAM, ANIM_END_FREAM, ANIM_SPEED);

	//���f���̖��邳�ݒ�
	Model::SetBrightness(hModel_, MODEL_BRIGHTNESS);

	//�d�͓K�p�����Ȃ�
	ARGUMENT_INITIALIZE(isUseGravity_, false);

	//�I�C���[�p��]
	ARGUMENT_INITIALIZE(transform_.mFlag_,false);

	//��]�����ݒ�
	ARGUMENT_INITIALIZE(transform_.rotate_.y,XMConvertToDegrees(angle_));

	//�����Ɠ����Ă����Ԃɂ������̂ŏ�Ԃ�Move�ɕύX
	ChangeEnemyState(EnemyStateList::GetEnemyMoveState());
}

//����
void BulletPigEnemy::Move()
{
	//�i���ɓ����Ă������̂ŏ�ԃJ�E���g�����������Ă���
	ARGUMENT_INITIALIZE(stateCount_, ZERO);

	//�����A�j���[�V�����̃t���[�������˃t���[���Ȃ狅���˂���
	if (Model::GetAnimFrame(hModel_) == SHOT_ANIM_FREAM)
		ShotBullet();
	
}

//������
void BulletPigEnemy::ShotBullet()
{
	//���̔��˕���
	XMVECTOR dir =  XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(Model::GetBonePosition(hModel_, "Base"))) - XMLoadFloat3(&transform_.position_));

	//������
	Bullet *p = Instantiate<Bullet>(GetParent());
	p->SetFront(dir);
	p->SetPosition(transform_.position_);
}

//�����蔻��
void BulletPigEnemy::OnCollision(GameObject* pTarget)
{
}

