#include "Bullet.h"
#include "../Engine/Model.h"

//�萔
namespace
{
	static const int LIFE_TIME = 180;						 //��������
	static const float ADD_ROTATION_ANGLE = 5.0f;            //��]����Ƃ��ɉ��Z����p�x
	static const float SPEED = 1.0f;                         //���̃X�s�[�h
	static const float    COLLIDER_SIZE = 2.0f;				 //�R���C�_�[�̃T�C�Y
	static const XMFLOAT3 COLLIDER_POS = { ZERO,ZERO,ZERO }; //�R���C�_�[�̈ʒu
	static const XMFLOAT3 BULLET_SCALE = { 4,4,4 };          //���̊g�嗦
}

//�R���X�g���N�^
Bullet::Bullet(GameObject* parent)
	:GameObject(parent,"Bullet"), hModel_(-1), front_(XMVectorSet(ZERO, ZERO,1, ZERO)),lifeTimeCount_(ZERO)
{
}

//������
void Bullet::Initialize()
{
	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Stage/Gimmick/Bullet.fbx");
	assert(hModel_ >= ZERO);

	//////////////////�����蔻��ݒ�//////////////////////

	SphereCollider* collision = new SphereCollider(COLLIDER_POS, COLLIDER_SIZE);
	AddCollider(collision);

	///////////////////transform////////////////////

	ARGUMENT_INITIALIZE(transform_.scale_, BULLET_SCALE);
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void Bullet::StartUpdate()
{
}

//�X�V
void Bullet::Update()
{
	//��]
	transform_.rotate_.y += ADD_ROTATION_ANGLE;

	//�ړ�
	transform_.position_ = VectorToFloat3(XMLoadFloat3(&transform_.position_) + (front_ * SPEED));

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
