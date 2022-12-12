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
	Model::SetAnimFrame(hModel_, ANIM_START_FREAM, ANIM_END_FREAM, ANIM_SPEED);
}

//�X�V
void BulletPigEnemy::ChildUpdate()
{
	//�����A�j���[�V�����̃t���[�����I���t���[���Ȃ狅���˂���
	if (Model::GetAnimFrame(hModel_) == ANIM_END_FREAM)
		ShotBullet();
}

//������
void BulletPigEnemy::ShotBullet()
{
	//������(���̓������������߂�̂�)
	Bullet *pBullet = Instantiate<Bullet>(this);

	//���̕��������߂�
	XMVECTOR dir = XMLoadFloat3(new XMFLOAT3(Model::GetBonePosition(hModel_, "Base"))) - XMLoadFloat3(&transform_.position_);

	//���̕������Z�b�g
	pBullet->SetFront(dir);
}

//�����蔻��
void BulletPigEnemy::OnCollision(GameObject* pTarget)
{
}

