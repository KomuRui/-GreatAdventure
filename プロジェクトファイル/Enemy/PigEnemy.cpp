#include "PigEnemy.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"

//�萔
namespace
{
	//////////////////////�A�j���[�V����//////////////////////

	static const int ANIM_START_FRAME = 1; //�J�n�t���[��
	static const int ANIM_END_FRAME = 60;  //�I���t���[��
	static const int ANIM_DIE_FRAME = 70;  //���S�t���[��
	static const float ANIM_SPEED = 2.0f;  //�A�j���X�s�[�h

	//////////////////////�L�����̕K�v�ȏ��//////////////////////

	static const int FEED_BACK_ANGLE = 25;					//�����p�x
	static const int RAY_DISTANCE = 1;                      //���C�̋���
	static const int KNOCKBACK_ASSUMPTION_DISTANCE = 10;	//�m�b�N�o�b�N�z�苗��
	static const int KNOCKBACK_DIFFERENCIAL_DISTANCE = 1;   //�m�b�N�o�b�N�̍�������
	static const float INTERPOLATION_COEFFICIENT = 0.08f;   //��ԌW��
	static const float HIT_STOP_TIME = 0.15f;               //�q�b�g�X�g�b�v���o�̎���

	//////////////////////�J����//////////////////////

	static const float VIBRATION_INTENSITY = 0.2f; //�U���̋���
}

//�R���X�g���N�^
PigEnemy::PigEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Enemy(parent, modelPath, name), knockBackFlag_(false),knockBackDir_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),pParticle_(nullptr)
{
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void PigEnemy::EnemyChildStartUpdate()
{

	///////////////�����蔻��ݒ�///////////////////

	//��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)) * 1, ZERO), 1.7f);
	AddCollider(collision);

	///////////////�A�j���[�V����///////////////////

	//�J�n
	Model::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, ANIM_SPEED);

	///////////////�G�t�F�N�g///////////////////

	//�G�t�F�N�g�o�����߂ɕK�v�ȃN���X
	pParticle_ = Instantiate<Particle>(this);
}

//�X�V
void PigEnemy::EnemyChildUpdate()
{
	//�R���C�_�[�̃|�W�V�����ύX
	SetPosCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)), ZERO));
}

//Player�����g�̏�ɂ��邩�ǂ���
bool PigEnemy::IsPlayerTop()
{
	//���g�̏�x�N�g����Player�܂ł̃x�N�g���̓��ς����߂�
	float topAngle = acos(XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)), XMVector3Normalize(vNormal_))));

	//���p��,�w�苗�����ɂ���Ȃ�
	return (topAngle < XMConvertToRadians(FEED_BACK_ANGLE) && topAngle > XMConvertToRadians(-FEED_BACK_ANGLE)) ? true : false;
}

//�����������̃G�t�F�N�g
void PigEnemy::HitEffect(const XMFLOAT3& pos)
{
	EmitterData data;
	data.textureFileName = "Cloud.png";
	data.position = pos;
	data.delay = 0;
	data.number = 30;
	data.lifeTime = 20;
	XMStoreFloat3(&data.dir, -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)));
	data.dirErr = XMFLOAT3(90, 90, 90);
	data.speed = 0.1f;
	data.speedErr = 0.8;
	data.size = XMFLOAT2(1, 1);
	data.sizeErr = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1.05, 1.05);
	data.color = XMFLOAT4(1, 1, 0.1, 1);
	data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
	pParticle_->Start(data);
}

//�m�b�N�o�b�N���Ď��S
void PigEnemy::KnockBackDie()
{
	//�m�b�N�o�b�N���Ă��Ȃ��̂Ȃ�
	if (!knockBackFlag_)
	{
		//�m�b�N�o�b�N�ǂ��܂ł��邩�ݒ�(�P�ʃx�N�g���ɂ��Ē萔���{�ɂ���)
		knockBackDir_ = (-XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) * KNOCKBACK_ASSUMPTION_DISTANCE) + XMLoadFloat3(&transform_.position_);

		//�m�b�N�o�b�N����
		ARGUMENT_INITIALIZE(knockBackFlag_, !knockBackFlag_);
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
		XMVECTOR dis = -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) * data.dist;
		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (-XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) - dis));

		//�߂����狗����0�ɏ�����
		ZERO_INITIALIZE(dist);
	}

	//�m�b�N�o�b�N�����������m�b�N�o�b�N�̑z�苗����1�ȓ��̋����Ȃ�
	if (dist < KNOCKBACK_DIFFERENCIAL_DISTANCE)
	{
		//�m�b�N�o�b�N���ĂȂ���Ԃ�
		ARGUMENT_INITIALIZE(knockBackFlag_, !knockBackFlag_);

		//�ҋ@��ԂɕύX
		ChangeEnemyState(EnemyStateList::GetEnemyWaitState());
	}
}

//���S
void PigEnemy::Die()
{
		
}

//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
void PigEnemy::TimeMethod()
{
	Enter();
}

//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
void PigEnemy::OnCollision(GameObject* pTarget)
{
	//����Player�Ɠ���������
	if (pTarget->GetObjectName() == "Player")
	{
		
		//����������Player����ɂ��邩���g������ł��Ȃ��Ȃ�
		if (IsPlayerTop() && pState_ != EnemyStateList::GetEnemyKnockBackState() && pState_ != EnemyStateList::GetEnemyDieState())
		{
			//����ł�A�j���[�V�����ɂ���
			Model::SetAnimFrame(hModel_, ANIM_DIE_FRAME, ANIM_DIE_FRAME, ZERO);

			//���S������
			ChangeEnemyState(EnemyStateList::GetEnemyDieState());
		}

		//����Player����]���Ă����炩���g������ł��Ȃ��Ȃ�
		if (GameManager::GetpPlayer()->IsRotation() && pState_ != EnemyStateList::GetEnemyKnockBackState() && pState_ != EnemyStateList::GetEnemyDieState())
		{
			//�q�b�g�X�g�b�v���o(�������~�߂�)
			Leave();
			pTarget->Leave();

			//Player���G��0.15�b��ɓ����o��
			SetTimeMethod(HIT_STOP_TIME);
			pTarget->SetTimeMethod(HIT_STOP_TIME);

			//���������|�W�V������ۑ�����ϐ�
			XMFLOAT3 hitPos;

			//���������ʒu�𒲂ׂ�
			XMStoreFloat3(&hitPos, XMLoadFloat3(&transform_.position_) + (XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) * GetColliderRadius()));

			//�G�t�F�N�g�\��
			HitEffect(hitPos);

			//�J�����U��
			Camera::SetCameraVibration(VIBRATION_INTENSITY);

			//�m�b�N�o�b�N���Ď��S������
			ChangeEnemyState(EnemyStateList::GetEnemyKnockBackState());

			//�I��
			return;

		}
	}
}
