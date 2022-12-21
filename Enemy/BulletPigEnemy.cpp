#include "BulletPigEnemy.h"
#include "../Gimmick/Bullet.h"

//�R���X�g���N�^
BulletPigEnemy::BulletPigEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent,modelPath,name)
{
}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void BulletPigEnemy::ChildStartUpdate()
{
	//�A�j���[�V�����ݒ�
	Model::SetAnimFlag(hModel_, true);
	Model::SetAnimFrame(hModel_, PIG_ENEMY_ANIM_START_FREAM, PIG_ENEMY_ANIM_END_FREAM, PIG_ENEMY_ANIM_SPEED);

	//���f���̖��邳�ݒ�
	Model::SetBrightness(hModel_, 0.7f);
}

//�X�V
void BulletPigEnemy::ChildUpdate()
{
	//�����A�j���[�V�����̃t���[�����I���t���[���Ȃ狅���˂���
	if (Model::GetAnimFrame(hModel_) == 40)
		ShotBullet();
}

//������
void BulletPigEnemy::ShotBullet()
{
	//������(���̓������������߂�̂�)
	Bullet *pBullet = Instantiate<Bullet>(this);

	//���̃|�W�V�����Z�b�g
	pBullet->SetPosition(Float3Add(pBullet->GetPosition(), XMFLOAT3(0,0,0)));
}

//�����蔻��
void BulletPigEnemy::OnCollision(GameObject* pTarget)
{
}

