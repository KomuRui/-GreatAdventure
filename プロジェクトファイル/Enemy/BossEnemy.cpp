#include "BossEnemy.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/GameObject/Camera.h"
#include "../Manager/EffectManager/EnemyEffectManager/EnemyEffectManager.h"
#include "../Manager/GameManager/GameManager.h"

//�萔
namespace
{
	//////////////////////�A�j���[�V����//////////////////////

	static const int ANIM_START_FRAME = 1; //�J�n�t���[��
	static const int ANIM_END_FRAME = 60;  //�I���t���[��
	static const int ANIM_DIE_FRAME = 70;  //���S�t���[��
	static const float ANIM_SPEED = 3.0f;  //�A�j���X�s�[�h

	//////////////////////�L�����̕K�v�ȏ��//////////////////////

	static const int MAX_HP = 10;                                      //�ő�̗�
	static const int RAY_DISTANCE = 1;                                 //���C�̋���
	static const int KNOCKBACK_ASSUMPTION_DISTANCE = 10;	           //�m�b�N�o�b�N�z�苗��
	static const int KNOCKBACK_DIFFERENCIAL_DISTANCE = 1;			   //�m�b�N�o�b�N�̍�������
	static const float INTERPOLATION_COEFFICIENT = 0.08f;			   //��ԌW��
	static const float HIT_STOP_TIME = 0.15f;						   //�q�b�g�X�g�b�v���o�̎���
	static const XMFLOAT4 HED_NORMAL_COLOR = { ZERO,ZERO,1.0f,1.0f };  //�m�[�}����Ԃ̓��̐F
	static const XMFLOAT4 HED_FOUND_COLOR = { 1.0f,ZERO,ZERO,1.0f };   //���������̓��̐F
	static const float FLY_VECTOR_SIZE = 0.5f;						   //FLY�x�N�g���̑傫��
	static const float FLY_VECTOR_DOWN = 0.015f;					   //FLY�x�N�g�������������Ă����Ƃ��̒l
	static const float COLLIDER_SIZE = 8.0f;                           //�R���C�_�[�T�C�Y
	static const float DIE_TIME = 2.0f;                                //���ʂ܂ł̎���

	//////////////////////�J����//////////////////////

	static const float VIBRATION_INTENSITY = 0.2f; //�U���̋���
}

//�R���X�g���N�^
BossEnemy::BossEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Enemy(parent, modelPath, name), isKnockBack_(false), hp_
{
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void BossEnemy::EnemyChildStartUpdate()
{
	/////////////////���邳�ݒ�/////////////////

    Model::SetBrightness(hModel_, 1.0f);

	///////////////�����蔻��ݒ�///////////////////

	//��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)) * 5, ZERO), COLLIDER_SIZE);
	AddCollider(collision);

	///////////////�A�j���[�V����///////////////////

	//�J�n
	Model::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, ANIM_SPEED);

}

//�X�V
void BossEnemy::EnemyChildUpdate()
{
	//�R���C�_�[�̃|�W�V�����ύX
	SetPosCollider(VectorToFloat3((XMVector3Normalize(vNormal_) * 7)));
}

//Player�����p���A�w�苗�����ɂ��鎞�̏���
void BossEnemy::PlayerWithIf()
{
}

//Player�����p���A�w�苗�����ɂ��Ȃ����̏���
void BossEnemy::NotPlayerWithIf()
{
}

//�m�b�N�o�b�N���Ď��S
void BossEnemy::KnockBackDie()
{
	//�m�b�N�o�b�N���Ă��Ȃ��̂Ȃ�
	if (!isKnockBack_)
	{
		//�m�b�N�o�b�N�ǂ��܂ł��邩�ݒ�(�P�ʃx�N�g���ɂ��Ē萔���{�ɂ���)
		knockBackDir_ = (-XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) * KNOCKBACK_ASSUMPTION_DISTANCE) + XMLoadFloat3(&transform_.position_);

		//�ǂ̂��炢���Ԃ��ݒ�
		ARGUMENT_INITIALIZE(vFly_, vNormal_ * FLY_VECTOR_SIZE);

		//��ƂȂ�Fly�x�N�g����ۑ����Ă���
		ARGUMENT_INITIALIZE(keepFly_, vFly_);

		//�m�b�N�o�b�N����
		ARGUMENT_INITIALIZE(isKnockBack_, !isKnockBack_);
	}

	//�m�b�N�o�b�N(�w��̏ꏊ�܂ŕ�Ԃ��Ă������s���悤��)
	XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), knockBackDir_, INTERPOLATION_COEFFICIENT));

	//����
	float dist = RangeCalculation(transform_.position_, VectorToFloat3(knockBackDir_));

	//�ǂɖ��܂�Ȃ��悤�ɂ��邽�߂Ƀ��C���΂�
	RayCastData data;
	data.start = transform_.position_;     //���C�̔��ˈʒu
	XMStoreFloat3(&data.dir, -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)));
	Model::RayCast(hGroundModel_, &data);  //���C�𔭎�

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

		if (XMVectorGetX(up_) != XMVectorGetX(vNormal_) || XMVectorGetY(up_) != XMVectorGetY(vNormal_) || XMVectorGetZ(up_) != XMVectorGetZ(vNormal_))
		{
			//�O�ϋ��߂�
			XMVECTOR cross = XMVector3Cross(up_, vNormal_);

			//�]�΂���
			transform_.mmRotate_ *= XMMatrixRotationAxis(cross, 2);
		}
	}

	//�m�b�N�o�b�N�����������m�b�N�o�b�N�̑z�苗����1�ȓ��̋����Ȃ�
	if (dist < KNOCKBACK_DIFFERENCIAL_DISTANCE)
	{
		//�m�b�N�o�b�N���Ă��Ȃ���Ԃɂ���
		ARGUMENT_INITIALIZE(isKnockBack_, !isKnockBack_);

		//���S��ԂɕύX
		ChangeEnemyState(EnemyStateList::GetEnemyDieState());
	}
}

//���S
void BossEnemy::Die()
{
	//�ҋ@��ԂɕύX
	ChangeEnemyState(EnemyStateList::GetEnemyWaitState());

	//���ʃG�t�F�N�g
	EnemyEffectManager::DieEffect(transform_.position_, up_);

	//�폜
	KillMe();
}

//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
void BossEnemy::TimeMethod()
{
	Enter();
}

//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
void BossEnemy::OnCollision(GameObject* pTarget)
{
	//����Player�Ɠ���������
	if (pTarget->GetObjectName() == "Player")
	{
		//����Player����]���Ă����炩���g������ł��Ȃ��Ȃ�
		if (GameManager::GetpPlayer()->IsRotation() && pState_ != EnemyStateList::GetEnemyKnockBackState() && pState_ != EnemyStateList::GetEnemyDieState())
		{
			//�q�b�g�X�g�b�v���o(��������������)
			Leave();
			pTarget->Leave();

			//Player���G��0.15�b��ɓ����o��
			SetTimeMethod(HIT_STOP_TIME);
			pTarget->SetTimeMethod(HIT_STOP_TIME);

			//���������ʒu�𒲂ׂ�
			XMFLOAT3 hitPos = VectorToFloat3(XMLoadFloat3(&transform_.position_) + (XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) * GetColliderRadius()));

			//�G�t�F�N�g�\��
			EnemyEffectManager::HitEffect(hitPos, transform_.position_);

			//�J�����U��
			Camera::SetCameraVibration(VIBRATION_INTENSITY);

			//�m�b�N�o�b�N���Ď��S������
			ChangeEnemyState(EnemyStateList::GetEnemyKnockBackState());

			//�I��
			return;
		}
	}
}
