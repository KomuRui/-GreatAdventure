#include "Bullet.h"
#include "../Engine/Model.h"

//�R���X�g���N�^
Bullet::Bullet(GameObject* parent)
	:GameObject(parent,"Bullet"), hModel_(-1), front_(XMVectorSet(0,0,1,0)), speed_(1.0f), lifeTimeCount_(0)
{
}

//������
void Bullet::Initialize()
{
	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Stage/Gimmick/Bullet.fbx");
	assert(hModel_ >= 0);
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void Bullet::StartUpdate()
{
}

//�X�V
void Bullet::Update()
{
	//�ړ�
	transform_.position_ = Transform::VectorToFloat3(XMLoadFloat3(&transform_.position_) + (front_ * speed_));

	//�������Ԃ�萶���Ă�����
	if (lifeTimeCount_ > LIFE_TIME)
		KillMe();
	else
		lifeTimeCount_++;
}

//�`��
void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void Bullet::Release()
{
}
