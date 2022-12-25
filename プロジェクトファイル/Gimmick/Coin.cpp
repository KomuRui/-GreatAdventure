#include "Coin.h"

//�萔
namespace
{
	static const float ADD_ROTATION_ANGLE = 0.08f; //��]����Ƃ��̉��Z����p�x
	static const float COLLIDER_POS_Y = 1.0f;      //�R���C�_�[��Y���̃|�W�V����
	static const float COLLIDER_RADIUS = 1.0f;     //�R���C�_�[�̔��a
}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void Coin::ChildStartUpdate()
{
	//�R���C�_�[�ǉ�
	SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)) * COLLIDER_POS_Y * transform_.scale_.y, ZERO), COLLIDER_RADIUS * transform_.scale_.y);
	AddCollider(collision);
}

void Coin::ChildUpdate()
{
	//��]
	angle_ += ADD_ROTATION_ANGLE;

	//Angle��360�܂ł�������0�ɖ߂�
	if (angle_ > TWOPI_DEGREES)
		angle_ = ZEROPI_DEGREES;
}

//�����蔻��
void Coin::OnCollision(GameObject* pTarget)
{
	//Player�ȊO�Ȃ牽�����Ȃ�
	if (pTarget->GetObjectName() != "Player")
		return;

	//���g�̍폜
	KillMe();
}
