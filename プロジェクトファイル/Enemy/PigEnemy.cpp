#include "PigEnemy.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"

//�R���X�g���N�^
PigEnemy::PigEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Enemy(parent, modelPath, name), knockBackFlag_(false)
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
	Model::SetAnimFrame(hModel_, 1, 60, 2);

	///////////////�G�t�F�N�g///////////////////

	//�G�t�F�N�g�o�����߂ɕK�v�ȃN���X
	pParticle_ = Instantiate<Particle>(this);
}

//�X�V
void PigEnemy::EnemyChildUpdate()
{
	//�R���C�_�[�̃|�W�V�����ύX
	SetPosCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)) * 1, ZERO));
}

//Player�����g�̏�ɂ��邩�ǂ���
bool PigEnemy::IsPlayerTop()
{
	//���g�̏�x�N�g����Player�܂ł̃x�N�g���̓��ς����߂�
	float topAngle = acos(XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)), XMVector3Normalize(vNormal_))));

	//���p��,�w�苗�����ɂ���Ȃ�
	return (topAngle < XMConvertToRadians(25) && topAngle > XMConvertToRadians(-25)) ? true : false;
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
		//Player�̃|�W�V�����Q�b�g
		XMFLOAT3 playerPos = GameManager::GetpPlayer()->GetPosition();

		//�m�b�N�o�b�N�ǂ��܂ł��邩�ݒ�(�P�ʃx�N�g���ɂ��Ē萔���{�ɂ���)
		knockBackDir_ = (-XMVector3Normalize(XMLoadFloat3(&playerPos) - XMLoadFloat3(&transform_.position_)) * 10) + XMLoadFloat3(&transform_.position_);

		//�m�b�N�o�b�N����
		knockBackFlag_ = !knockBackFlag_;
	}

	//�m�b�N�o�b�N(�w��̏ꏊ�܂ŕ�Ԃ��Ă������s���悤��)
	XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), knockBackDir_, 0.08));

	//�ǂ��܂Ńm�b�N�o�b�N�����������ϐ�
	XMFLOAT3 knockBackPos;
	XMStoreFloat3(&knockBackPos, knockBackDir_);

	//����
	float dist = RangeCalculation(transform_.position_, knockBackPos);

	//�ǂɖ��܂�Ȃ��悤�ɂ��邽�߂Ƀ��C���΂�
	RayCastData data;
	data.start = transform_.position_;     //���C�̔��ˈʒu
	XMStoreFloat3(&data.dir, -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)));
	Model::RayCast(hGroundModel_, &data);  //���C�𔭎�

	//���܂������߂�
	if (data.dist <= 1)
	{
		XMVECTOR dis = -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) * data.dist;
		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (-XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) - dis));

		//�߂����狗����0�ɏ�����
		ZERO_INITIALIZE(dist);
	}

	//�m�b�N�o�b�N�����������m�b�N�o�b�N�̑z�苗����1�ȓ��̋����Ȃ�
	if (dist < 1)
	{
		knockBackFlag_ = !knockBackFlag_;
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
			Model::SetAnimFrame(hModel_, 70, 70, ZERO);

			//���S������
			ChangeEnemyState(EnemyStateList::GetEnemyDieState());
		}

		//����Player����]���Ă����炩���g������ł��Ȃ��Ȃ�
		if (GameManager::GetpPlayer()->IsRotation() && pState_ != EnemyStateList::GetEnemyKnockBackState() && pState_ != EnemyStateList::GetEnemyDieState())
		{
			//�q�b�g�X�g�b�v���o(��������������)
			Leave();
			pTarget->Leave();

			//Player���G��0.15�b��ɓ����o��
			SetTimeMethod(0.15f);
			pTarget->SetTimeMethod(0.15f);

			//���������|�W�V������ۑ�����ϐ�
			XMFLOAT3 hitPos;

			//���������ʒu�𒲂ׂ�
			XMStoreFloat3(&hitPos, XMLoadFloat3(&transform_.position_) + (XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) * GetColliderRadius()));

			//�G�t�F�N�g�\��
			HitEffect(hitPos);

			//�J�����U��
			Camera::SetCameraVibration(0.2f);

			//�m�b�N�o�b�N���Ď��S������
			ChangeEnemyState(EnemyStateList::GetEnemyKnockBackState());
			//aiState_ = KNOCKBACK_DIE;

			//�I��
			return;

		}
	}
}
