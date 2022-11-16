#include "PigEnemy.h"
#include "../Engine/Model.h"

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
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, XMVectorGetY(XMVector3Normalize(vNormal)) * 1, 0), 1.7f);
	AddCollider(collision);

	///////////////�A�j���[�V����///////////////////

	//�J�n
	Model::SetAnimFrame(hModel_, 1, 60, 2);
}

//�X�V
void PigEnemy::EnemyChildUpdate()
{
	//�R���C�_�[�̃|�W�V�����ύX
	SetPosCollider(XMFLOAT3(0, XMVectorGetY(XMVector3Normalize(vNormal)) * 1, 0));
}

//�m�b�N�o�b�N���Ď��S
void PigEnemy::KnockBackDie()
{
	//�m�b�N�o�b�N���Ă��Ȃ��̂Ȃ�
	if (!knockBackFlag_)
	{
		//Player�̃|�W�V�����Q�b�g
		XMFLOAT3 playerPos = pPlayer_->GetPosition();

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

	//�m�b�N�o�b�N�����������m�b�N�o�b�N�̑z�苗����1�ȓ��̋����Ȃ�
	if (Transform::RangeCalculation(transform_.position_, knockBackPos) < 1)
	{
		knockBackFlag_ = !knockBackFlag_;
		aiState_ = WAIT;
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
		//����Player����]���Ă�����
		if (pPlayer_->GetRotationFlag())
		{
			//�q�b�g�X�g�b�v���o(��������������)
			Leave();
			pTarget->Leave();

			//Player���G��1.0�b��ɓ����o��
			SetTimeMethod(0.1f);
			pTarget->SetTimeMethod(0.1f);

			//�m�b�N�o�b�N���Ď��S������
			aiState_ = KNOCKBACK_DIE;

		}
	}
}
