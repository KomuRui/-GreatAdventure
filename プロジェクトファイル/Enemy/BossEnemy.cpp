#include "BossEnemy.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/GameObject/Camera.h"
#include "../Manager/EffectManager/EnemyEffectManager/EnemyEffectManager.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Gimmick/FlyBall.h"

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
	static const int KNOCKBACK_ASSUMPTION_DISTANCE = 25;	           //�m�b�N�o�b�N�z�苗��
	static const int KNOCKBACK_DIFFERENCIAL_DISTANCE = 1;			   //�m�b�N�o�b�N�̍�������
	static const float INTERPOLATION_COEFFICIENT = 0.08f;			   //��ԌW��
	static const float HIT_STOP_TIME = 0.15f;						   //�q�b�g�X�g�b�v���o�̎���
	static const float COLLIDER_SIZE = 8.0f;                           //�R���C�_�[�T�C�Y
	static const float DIE_TIME = 2.0f;                                //���ʂ܂ł̎���

	//////////////////////�J����//////////////////////

	static const float VIBRATION_INTENSITY = 0.2f; //�U���̋���
}

//�R���X�g���N�^
BossEnemy::BossEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Enemy(parent, modelPath, name), isKnockBack_(false), hp_(MAX_HP)
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

	//�m�b�N�o�b�N�����������m�b�N�o�b�N�̑z�苗����1�ȓ��̋����Ȃ�
	if (dist < KNOCKBACK_DIFFERENCIAL_DISTANCE)
	{
		//�m�b�N�o�b�N���Ă��Ȃ���Ԃɂ���
		ARGUMENT_INITIALIZE(isKnockBack_, !isKnockBack_);

		//����ł�����
		if (hp_ <= ZERO)
		{
			//���S��ԂɕύX
			ChangeEnemyState(EnemyStateList::GetEnemyDieState());
		}
		else
			//�ҋ@��ԂɕύX
			ChangeEnemyState(EnemyStateList::GetEnemyWaitState());
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
	//��ԃ{�[���Ɠ����������m�b�N�o�b�N���ĂȂ����{�[�������ł����Ȃ�
	if (pTarget->GetObjectName() == "FlyBall" && EnemyStateList::GetEnemyKnockBackState() != pState_ && ((FlyBall*)pTarget)->IsFly())
	{
		//�̗͌���
		hp_ -= 1;

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
