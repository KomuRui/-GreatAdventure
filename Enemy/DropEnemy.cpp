#include "DropEnemy.h"
#include "../Engine/Model.h"

//�R���X�g���N�^
DropEnemy::DropEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Enemy(parent, modelPath, name), knockBackFlag_(false)
{
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void DropEnemy::EnemyChildStartUpdate()
{
	///////////////���f���f�[�^�̃��[�h///////////////////

	//��
	hHedModel_ = Model::Load("Enemy/Model/DropEnemyHed.fbx");
	assert(hHedModel_ >= 0);

	//���̕����̐F��ύX
	Model::SetSpeculer(hHedModel_, XMFLOAT4(0,0,1,1));

	///////////////�����蔻��ݒ�///////////////////

	//��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, XMVectorGetY(XMVector3Normalize(vNormal)) * 1, 0), 1.7f);
	AddCollider(collision);

	///////////////�A�j���[�V����///////////////////

	//�J�n
	Model::SetAnimFrame(hModel_, 1, 60, 3);

}

//�X�V
void DropEnemy::EnemyChildUpdate()
{
	//�R���C�_�[�̃|�W�V�����ύX
	SetPosCollider(XMFLOAT3(0, XMVectorGetY(XMVector3Normalize(vNormal)) * 1, 0));
}

//�`��
void DropEnemy::EnemyChildDraw()
{
	Model::SetTransform(hHedModel_, transform_);
	Model::Draw(hHedModel_);
}

//Player�����p���A�w�苗�����ɂ��鎞�̏���
void DropEnemy::PlayerWithIf()
{
	//���̕����̐F��ύX
	Model::SetSpeculer(hHedModel_, XMFLOAT4(1, 0, 0, 1));
}

//Player�����p���A�w�苗�����ɂ��Ȃ����̏���
void DropEnemy::NotPlayerWithIf()
{
	//���̕����̐F��ύX
	Model::SetSpeculer(hHedModel_, XMFLOAT4(0, 0, 1, 1));
}

//�m�b�N�o�b�N���Ď��S
void DropEnemy::KnockBackDie()
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
void DropEnemy::Die()
{
}

//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
void DropEnemy::TimeMethod()
{
	Enter();
}

//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
void DropEnemy::OnCollision(GameObject* pTarget)
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

			//Player���G��0.15�b��ɓ����o��
			SetTimeMethod(0.15f);
			pTarget->SetTimeMethod(0.15f);

			//�m�b�N�o�b�N���Ď��S������
			aiState_ = KNOCKBACK_DIE;

		}
	}
}
