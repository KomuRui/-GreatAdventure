#include "Bullet.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/EffectManager/EnemyEffectManager/EnemyEffectManager.h"
#include "../Manager/AudioManager/PlayerAudioManager/PlayerAudioManager.h"

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
	:GameObject(parent,"Bullet"), hModel_(-1), front_(XMVectorSet(ZERO, ZERO,1, ZERO)),lifeTimeCount_((int)ZERO)
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

//�R���C�_�[�ɓ����������ɌĂ΂��֐�
void Bullet::OnCollision(GameObject* pTarget)
{
	//Player�ȊO�Ɠ��������炱�̐�̏����͂��Ȃ�
	if (pTarget->GetObjectName() != "Player")return;

	//����Player����]���Ă���̂Ȃ玩�g�̓��������ύX
	if (GameManager::GetpPlayer()->IsRotation())
	{
		//�t�����ɔ��ł����ɐݒ�
		front_ = XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(SubTract(transform_.position_, pTarget->GetPosition()))));

		//��
		PlayerAudioManager::AttackHitAudio();

		//�����������̃G�t�F�N�g�\��
		EnemyEffectManager::HitEffect(Float3Add(GameManager::GetpPlayer()->GetPosition(),VectorToFloat3(front_ * 0.5f)), transform_.position_);

		//������Ɍ�����
		front_ += GameManager::GetpPlayer()->GetNormal();
	}
	else
		KillMe();

}
