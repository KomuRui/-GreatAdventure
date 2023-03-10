#include "BossEnemy.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/GameObject/Camera.h"
#include "../Manager/EffectManager/EnemyEffectManager/EnemyEffectManager.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Gimmick/FlyBall.h"
#include "../Engine/ResourceManager/Time.h"
#include "BossEnemyChild.h"

//�萔
namespace
{
	//////////////////////�A�j���[�V����//////////////////////

	static const int ANIM_START_FRAME = 1; //�J�n�t���[��
	static const int ANIM_END_FRAME = 60;  //�I���t���[��
	static const int ANIM_DIE_FRAME = 70;  //���S�t���[��
	static const float ANIM_SPEED = 3.0f;  //�A�j���X�s�[�h

	//////////////////////�L�����̕K�v�ȏ��//////////////////////

	static const int MAX_HP = 10;                               //�ő�̗�
	static const int RAY_DISTANCE = 1;                          //���C�̋���
	static const int KNOCKBACK_ASSUMPTION_DISTANCE = 7;	        //�m�b�N�o�b�N�z�苗��
	static const int KNOCKBACK_DIFFERENCIAL_DISTANCE = 1;		//�m�b�N�o�b�N�̍�������
	static const float INTERPOLATION_COEFFICIENT = 0.08f;		//��ԌW��
	static const float ADD_ROTATION_ANGLE = 0.02f;				//��]����Ƃ��̉��Z����p�x
	static const float HIT_STOP_TIME = 0.15f;					//�q�b�g�X�g�b�v���o�̎���
	static const float COLLIDER_SIZE = 8.0f;                    //�R���C�_�[�T�C�Y
	static const float DIE_TIME = 2.0f;                         //���ʂ܂ł̎���
	static const float MOVE_RAY_HIT_DISTANCE = 0.9f;			//�����Ă���Ƃ��̃��C�̓�����������


	//////////////////////�J����//////////////////////

	static const float VIBRATION_INTENSITY = 0.2f; //�U���̋���
}

//�R���X�g���N�^
BossEnemy::BossEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Enemy(parent, modelPath, name), isKnockBack_(false), hp_(MAX_HP), hTime_(ZERO)
{
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void BossEnemy::EnemyChildStartUpdate()
{
	/////////////////�^�C�}�[�ǉ�/////////////////

	ARGUMENT_INITIALIZE(hTime_,Time::Add());

	/////////////////�ړ����x�ݒ�/////////////////

	ARGUMENT_INITIALIZE(moveRatio_,0.25f);

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

//�ړ�
void BossEnemy::Move()
{
	//�A�j���[�V�����J�n
	Model::SetAnimFlag(hModel_, true);

	//�ړ����Ď��g��transform�ɔ��f
	transform_.position_ = Float3Add(transform_.position_,
		VectorToFloat3(XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)) * moveRatio_));

	//�萔�b�ȏ�o�߂��Ă�����q������
	if (Time::GetTimef(hTime_) >= 1.5f)	Generation();

	//�������킹�邽�߂Ƀ��C���΂�
	RayCastData downData;
	downData.start = transform_.position_;         //���C�̃X�^�[�g�ʒu
	downData.dir = VectorToFloat3(down_);          //���C�̕���
	Model::AllRayCast(hGroundModel_, &downData);   //���C�𔭎�(All)

	//�n�`�̍����ɍ��킹��
	//��������������0.9f��菬�����Ȃ�
	if (downData.dist < MOVE_RAY_HIT_DISTANCE)
		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&downData.pos) + vNormal_);

	//��Ԃ���ԕω��̎��Ԃ��傫���Ȃ�����
	if (stateCount_ > operationTime_)
	{
		//0�ɏ�����
		ZERO_INITIALIZE(operationTime_);
		ZERO_INITIALIZE(stateCount_);

		//��Ԃ���]�ɐݒ�
		ChangeEnemyState(EnemyStateList::GetEnemyRotationState());

		//�^�C�}�[���Z�b�g
		Time::Reset(hTime_);
		Time::Lock(hTime_);

		//�A�j���[�V������~
		Model::SetAnimFlag(hModel_, false);
	}
}

//��]
void BossEnemy::Rotation()
{
	//�A�j���[�V������~
	Model::SetAnimFlag(hModel_, false);

	//��]
	angle_ += ADD_ROTATION_ANGLE * rotationSign_;
	rotationTotal_ += ADD_ROTATION_ANGLE;

	//��]�p�x����]�����������Ȃ�����
	if (abs(rotationTotal_) > abs(rotationAngle_))
	{
		//0�ɏ�����
		ZERO_INITIALIZE(operationTime_);
		ZERO_INITIALIZE(rotationTotal_);
		ZERO_INITIALIZE(rotationAngle_);

		//�^�C�}�[�X�^�[�g
		Time::UnLock(hTime_);

		//��Ԃ�ҋ@�ɐݒ�
		ChangeEnemyState(EnemyStateList::GetEnemyMoveState());
	}
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
			ChangeEnemyState(EnemyStateList::GetEnemyRotationState());
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

//����
void BossEnemy::Generation()
{
	//����
	Instantiate<BossEnemyChild>(GetParent())->SetPosition(Model::GetBonePosition(hModel_,"Base"));

	//�^�C�}�[���Z�b�g
	Time::Reset(hTime_);
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

		//�A�j���[�V������~
		Model::SetAnimFlag(hModel_, false);

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
