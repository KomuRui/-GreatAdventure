#include "MiniGamePigEnemy.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/MiniGameManager/MiniGameManager.h"
#include "../Manager/EffectManager/EnemyEffectManager/EnemyEffectManager.h"
#include "../Engine/GameObject/Camera.h"

//�萔
namespace
{

	//////////////////////�L�����̕K�v�ȏ��//////////////////////

	static const int RAY_DISTANCE = 1;                        //���C�̋���
	static const int KNOCKBACK_ASSUMPTION_DISTANCE = 10;	  //�m�b�N�o�b�N�z�苗��
	static const float KNOCKBACK_DIFFERENCIAL_DISTANCE = 5.0f;//�m�b�N�o�b�N�̍�������
	static const float INTERPOLATION_COEFFICIENT = 0.08f;     //��ԌW��
	static const float HIT_STOP_TIME = 0.15f;                 //�q�b�g�X�g�b�v���o�̎���
	static const float FLY_VECTOR_SIZE = 1.0f;				  //FLY�x�N�g���̑傫��
	static const float FLY_VECTOR_DOWN = 0.015f;			  //FLY�x�N�g�������������Ă����Ƃ��̒l
	static const float DIE_TIME = 1.0f;                       //���ʂ܂ł̎���

	//////////////////////�J����//////////////////////

	static const float VIBRATION_INTENSITY = 0.4f; //�U���̋���
}

//�R���X�g���N�^
MiniGamePigEnemy::MiniGamePigEnemy(GameObject* parent)
	:PigEnemy(parent,"MiniGamePigEnemy")
{}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void MiniGamePigEnemy::ChildPigEnemyStartUpdate()
{
	///////////////���邳///////////////////

	Model::SetBrightness(hModel_, 1.0f);


	///////////////�p�x���]///////////////////

	angle_ += XMConvertToRadians(180);
}

//�X�V
void MiniGamePigEnemy::ChildPigEnemyUpdate()
{
	//Player�����ɍs�����玀�S
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z - 5)
		KillMe();

	//�m�b�N�o�b�N���ĂȂ�����ł��Ȃ��̂Ȃ�
	if (pState_ != EnemyStateList::GetEnemyKnockBackState() && pState_ != EnemyStateList::GetEnemyDieState())
		ChangeEnemyState(EnemyStateList::GetEnemyWaitState());
}

//�m�b�N�o�b�N���Ď��S
void MiniGamePigEnemy::KnockBackDie()
{
	//�m�b�N�o�b�N���Ă��Ȃ��̂Ȃ�
	if (!isKnockBack_)
	{
		//�m�b�N�o�b�N�ǂ��܂ł��邩�ݒ�(�P�ʃx�N�g���ɂ��Ē萔���{�ɂ���)
		knockBackDir_ = (XMVectorSet(0, 0, 10, 0) * KNOCKBACK_ASSUMPTION_DISTANCE) + XMLoadFloat3(&transform_.position_);

		//�ǂ̂��炢���Ԃ��ݒ�
		ARGUMENT_INITIALIZE(vFly_, GameManager::GetpPlayer()->GetNormal() * FLY_VECTOR_SIZE);

		//��ƂȂ�Fly�x�N�g����ۑ����Ă���
		ARGUMENT_INITIALIZE(keepFly_, vFly_);

		//�m�b�N�o�b�N����
		ARGUMENT_INITIALIZE(isKnockBack_, !isKnockBack_);
	}

	//�m�b�N�o�b�N(�w��̏ꏊ�܂ŕ�Ԃ��Ă������s���悤��)
	XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), knockBackDir_, INTERPOLATION_COEFFICIENT));

	//����
	float dist = RangeCalculation(transform_.position_, VectorToFloat3(knockBackDir_));

	//�ǂɖ��܂�Ȃ��悤�ɂ��邽�߂Ƀm�b�N�o�b�N�����Ƀ��C���΂�
	RayCastData data;
	data.start = transform_.position_;
	XMStoreFloat3(&data.dir, -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)));
	Model::RayCast(hGroundModel_, &data);

	//���܂������߂�
	if (data.dist <= RAY_DISTANCE)
	{
		//���S��ԂɕύX
		ChangeEnemyState(EnemyStateList::GetEnemyDieState());
	}

	//�m�b�N�o�b�N���Ă���Ȃ�
	if (isKnockBack_)
	{
		//��ƂȂ�W�����v�x�N�g���ƕ����������Ȃ�
		if (signbit(XMVectorGetY(vFly_)) == signbit(XMVectorGetY(keepFly_)))
		{
			//�x�N�g���̒������ׂ�
			float len = sqrtf(XMVectorGetX(vFly_) * XMVectorGetX(vFly_) + XMVectorGetY(vFly_) * XMVectorGetY(vFly_) + XMVectorGetZ(vFly_) * XMVectorGetZ(vFly_));

			//�t���C�x�N�g�����L�����̏㎲�ɒ���
			ARGUMENT_INITIALIZE(vFly_, vNormal_ * len);

			//���΂���
			ARGUMENT_INITIALIZE(transform_.position_, Float3Add(transform_.position_, VectorToFloat3(vFly_ - (vNormal_ * FLY_VECTOR_DOWN))));

			//�ǂ�ǂ�W�����v�x�N�g�������������Ă���
			ARGUMENT_INITIALIZE(vFly_, vFly_ - (vNormal_ * FLY_VECTOR_DOWN));
		}

		Model::SetAnimFrame(hModel_, 80, 80, ZERO);
	}

	//�m�b�N�o�b�N�����������m�b�N�o�b�N�̑z�苗����1�ȓ��̋����Ȃ�
	if (dist < KNOCKBACK_DIFFERENCIAL_DISTANCE)
	{
		//�m�b�N�o�b�N���ĂȂ���Ԃ�
		ARGUMENT_INITIALIZE(isKnockBack_, !isKnockBack_);

		//���S��ԂɕύX
		ChangeEnemyState(EnemyStateList::GetEnemyDieState());
	}
}

//���S
void MiniGamePigEnemy::Die()
{
	//�ҋ@��ԂɕύX
	ChangeEnemyState(EnemyStateList::GetEnemyWaitState());

	//������΂����A�j���[�V������
	Model::SetAnimFrame(hModel_, 80, 80, ZERO);

	//���ʃG�t�F�N�g
	EnemyEffectManager::DieEffect(transform_.position_, up_);

	//�R���C�_�[���폜
	KillCollider(collision);

	//�폜
	KillMe();
}

//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
void MiniGamePigEnemy::OnCollision(GameObject* pTarget)
{
	//����Player�Ɠ���������
	if (pTarget->GetObjectName() == "Player")
	{
		
		//����Player����]���Ă����炩���g������ł��Ȃ��Ȃ�
		if (GameManager::GetpPlayer()->IsRotation() && pState_ != EnemyStateList::GetEnemyKnockBackState() && pState_ != EnemyStateList::GetEnemyDieState())
		{
			MiniGameManager::SetRunSpeed(8.0f);
			MiniGameManager::SetRunMode(true);
			MiniGameManager::AddCombo();
			MiniGameManager::SetComboTextScale(1.3f);

			//���������ʒu�𒲂ׂ�
			XMFLOAT3 hitPos = VectorToFloat3(XMLoadFloat3(&transform_.position_) + (XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) * GetColliderRadius()));

			//�G�t�F�N�g�\��
			EnemyEffectManager::HitEffect(hitPos, transform_.position_);

			//�J�����U��
			Camera::SetCameraVibration(VIBRATION_INTENSITY, 0.02f);

			//�m�b�N�o�b�N���Ď��S������
			ChangeEnemyState(EnemyStateList::GetEnemyKnockBackState());

			//�I��
			return;

		}
	}
}