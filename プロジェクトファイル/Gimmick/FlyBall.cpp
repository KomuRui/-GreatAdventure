#include "FlyBall.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/EffectManager/EnemyEffectManager/EnemyEffectManager.h"
#include "../Engine/Easing.h"

//�萔
namespace
{
	static const float ADD_ROTATION_VALUE = 0.05f;   //��]����Ƃ��̉��Z�l
	static const float MAX_ROTATION_VALUE = 100.0f;  //�ő��]�l
	static const float COLLIDER_POS_Y = 1.0f;        //�R���C�_�[��Y���̃|�W�V����
	static const float COLLIDER_RADIUS = 1.0f;       //�R���C�_�[�̔��a
}

//�R���X�g���N�^
FlyBall::FlyBall(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent,modelPath,name), rotateAngle_(ZERO),isFly_(false), pEasing_(new EasingMove), basePos_(ZERO,ZERO,ZERO), isReturnPos(false)
{}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void FlyBall::ChildStartUpdate()
{
	//�R���C�_�[�ǉ�
	SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)) * COLLIDER_POS_Y * transform_.scale_.y, ZERO), COLLIDER_RADIUS);
	AddCollider(collision);

	//���邳
	Model::SetBrightness(hModel_, 1.0f);
}

//�X�V
void FlyBall::ChildUpdate()
{
	//�M�~�b�N�̏㎲�ŉ�]������
	transform_.mmRotate_ *= XMMatrixRotationAxis(up_, rotateAngle_);

	//��]������
	rotateAngle_ += ADD_ROTATION_VALUE;

	//�萔�ȏ�ɂȂ����珉����
	if (rotateAngle_ >= MAX_ROTATION_VALUE) ARGUMENT_INITIALIZE(rotateAngle_,ZERO);

	//�������ł���̂Ȃ�
	if (isFly_) Fly();
}

//���
void FlyBall::Fly()
{
	//������
	if (pEasing_->Move())
	{
		//�߂��Ă��Ȃ��̂Ȃ�
		if (!isReturnPos)
		{
			//���ɖ߂�
			ARGUMENT_INITIALIZE(isReturnPos, true);

			//�����ݒ�
			pEasing_->Reset(&transform_.position_,transform_.position_, basePos_, 0.5f, Easing::OutQuad);
		}
		else
		{
			ARGUMENT_INITIALIZE(isFly_,false);
			ARGUMENT_INITIALIZE(isReturnPos,false);
		}
	}
}

//�����蔻��
void FlyBall::OnCollision(GameObject* pTarget)
{
	//�����������肪Player����Ȃ��̂Ȃ炱�̐�̏��������Ȃ�
	if (pTarget->GetObjectName() != "Player") return;

	//����Player����]���Ă�����
	if (GameManager::GetpPlayer()->IsRotation() && !isFly_)
	{
		//��΂�
		ARGUMENT_INITIALIZE(isFly_, true);

		//���ł����������v�Z
		XMVECTOR dir_ = XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(SubTract(transform_.position_, pTarget->GetPosition()))));

		//��������
		dir_ += GameManager::GetpPlayer()->GetDown() * 0.5f;

		//��ԃ|�W�V������ݒ�
		XMFLOAT3 afterPos = Float3Add(VectorToFloat3(dir_ * 15.0f),transform_.position_);

		//���X�����|�W�V�����ݒ�
		ARGUMENT_INITIALIZE(basePos_, transform_.position_);

		//�����ݒ�
		pEasing_->Reset(&transform_.position_, transform_.position_, afterPos, 0.5f, Easing::OutQuad);

		//�����������̃G�t�F�N�g�\��
		EnemyEffectManager::HitEffect(Float3Add(GameManager::GetpPlayer()->GetPosition(), VectorToFloat3(dir_ * 0.5f)), transform_.position_);

	}
}