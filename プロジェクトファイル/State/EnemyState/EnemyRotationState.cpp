#include "EnemyRotationState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Enemy/Enemy.h"

//�X�V
void EnemyRotationState::Update2D(Enemy* enemy)
{
	//���͏���
	HandleInput(enemy);
}

//3D�p�X�V
void EnemyRotationState::Update3D(Enemy* enemy)
{
	//��]
	enemy->Rotation();

	//���͏���
	HandleInput(enemy);
}

//���͂ɂ���ď�ԕω�����
void EnemyRotationState::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void EnemyRotationState::Enter(Enemy* enemy)
{
	//�����{�X�Ȃ�
	if (enemy->GetObjectName().find("Boss") != string::npos)
	{
		//Player�̃|�W�V�����Q�b�g(Y�𓯂��ɂ���)
		XMFLOAT3 playerPos = GameManager::GetpPlayer()->GetPosition();
		ARGUMENT_INITIALIZE(playerPos.y, enemy->GetPosition().y);

		//���g����Player�ւ̃x�N�g��
		XMVECTOR vToPlayer = XMVector3Normalize(XMLoadFloat3(&playerPos) - XMLoadFloat3(new XMFLOAT3(enemy->GetPosition())));

		//�x�N�g����Y�𓯂��ɂ���(�Q�����̂悤��)
		XMFLOAT3 dir = VectorToFloat3(XMVector3TransformCoord(STRAIGHT_VECTOR, enemy->GetmmRotate()));
		ARGUMENT_INITIALIZE(dir.y, VectorToFloat3(vToPlayer).y);

		//���g����Player�ւ̃x�N�g���Ǝ��g�̑O�x�N�g���Ƃ̓��ς𒲂ׂ�
		float dotX =  GetDotRadians(XMLoadFloat3(&dir), vToPlayer);

		//�ǂ��������ɉ�]�����邩���߂邽�߂ɊO�ς����߂�
		XMVECTOR cross = XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&dir), vToPlayer));

		//����
		int sign = 1;

		//�������Ⴄ�Ȃ�
		if (signbit(XMVectorGetY(cross)) != signbit(XMVectorGetY(enemy->GetNormal())))
			sign *= -1;

		//��]��������ݒ�
		enemy->SetRotationSign(sign);

		//��]�p�x�ݒ�
		enemy->SetRotationAngle(dotX);

		//�ǂ̂��炢��]��������������
		enemy->SetRotationTotal(ZERO);
	}
	else
	{
		//��]��������ݒ�
		enemy->SetRotationSign(rand() % 2 == 1 ? 1 : -1);

		//��]�p�x�ݒ�
		enemy->SetRotationAngle(XMConvertToRadians((rand() % 141) + 40));

		//�ǂ̂��炢��]��������������
		enemy->SetRotationTotal(ZERO);
	}
}