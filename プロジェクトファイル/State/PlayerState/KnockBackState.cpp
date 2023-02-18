#include "KnockBackState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/Global.h"
#include "../../Player/PlayerBase.h"
#include "PlayerStateManager.h"

//�萔
namespace
{
	static const int RAY_DISTANCE = 1;                          //���C�̋���
	static const int KNOCKBACK_ASSUMPTION_DISTANCE = 10;	    //�m�b�N�o�b�N�z�苗��
	static const int KNOCKBACK_DIFFERENCIAL_DISTANCE = 1;		//�m�b�N�o�b�N�̍�������
	static const float INTERPOLATION_COEFFICIENT = 0.08f;		//��ԌW��
	static const float FLY_VECTOR_SIZE = 0.5f;					//FLY�x�N�g���̑傫��
	static const float FLY_VECTOR_DOWN = 0.015f;				//FLY�x�N�g�������������Ă����Ƃ��̒l
}

//�X�V
void KnockBackState::Update2D(PlayerBase* player)
{

	HandleInput(player);
}

//3D�p�X�V
void KnockBackState::Update3D(PlayerBase* player)
{

	//�m�b�N�o�b�N(�w��̏ꏊ�܂ŕ�Ԃ��Ă������s���悤��)
	player->SetPosition(VectorToFloat3(XMVectorLerp(XMLoadFloat3(new XMFLOAT3(player->GetPosition())), knockBackDir_, INTERPOLATION_COEFFICIENT)));

	//����
	float dist = RangeCalculation(player->GetPosition(), VectorToFloat3(knockBackDir_));

	//�ǂɖ��܂�Ȃ��悤�ɂ��邽�߂Ƀ��C���΂�
	RayCastData data;
	data.start = player->GetPosition();     
	XMStoreFloat3(&data.dir, -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(player->GetPosition())) - XMLoadFloat3(new XMFLOAT3(player->GetPosition()))));
	Model::RayCast(GameManager::GetpStage()->GethModel(), &data); 

	//���܂������߂�
	if (data.dist <= RAY_DISTANCE)
	{
		//�����Ă����Ԃ�
		PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
	}

	//��ƂȂ�W�����v�x�N�g���ƕ����������Ȃ�
	if (signbit(XMVectorGetY(vFly_)) == signbit(XMVectorGetY(keepFly_)))
	{
		//�x�N�g���̒������ׂ�
		float len = sqrtf(XMVectorGetX(vFly_) * XMVectorGetX(vFly_) + XMVectorGetY(vFly_) * XMVectorGetY(vFly_) + XMVectorGetZ(vFly_) * XMVectorGetZ(vFly_));

		//�t���C�x�N�g�����L�����̏㎲�ɒ���
		ARGUMENT_INITIALIZE(vFly_, player->GetNormal() * len);

		//���΂���
		player->SetPosition(Float3Add(player->GetPosition(), VectorToFloat3(vFly_ - (player->GetNormal() * FLY_VECTOR_DOWN))));

		//�ǂ�ǂ�W�����v�x�N�g�������������Ă���
		ARGUMENT_INITIALIZE(vFly_, vFly_ - (player->GetNormal() * FLY_VECTOR_DOWN));
	}

	//�m�b�N�o�b�N�����������m�b�N�o�b�N�̑z�苗����1�ȓ��̋����Ȃ�
	if (dist < KNOCKBACK_DIFFERENCIAL_DISTANCE)
	{
		//�����Ă����Ԃ�
		PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
	}

	HandleInput(player);
}

//���͂ɂ���ď�ԕω�����
void KnockBackState::HandleInput(PlayerBase* player)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void KnockBackState::Enter(PlayerBase* player)
{
	//�m�b�N�o�b�N�ǂ��܂ł��邩�ݒ�(�P�ʃx�N�g���ɂ��Ē萔���{�ɂ���)
	knockBackDir_ = (XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(player->GetPosition())) - XMLoadFloat3(&hitEnemyPos_)) * KNOCKBACK_ASSUMPTION_DISTANCE) + XMLoadFloat3(new XMFLOAT3(player->GetPosition()));

	//�ǂ̂��炢���Ԃ��ݒ�
	ARGUMENT_INITIALIZE(vFly_, player->GetNormal() * FLY_VECTOR_SIZE);

	//��ƂȂ�Fly�x�N�g����ۑ����Ă���
	ARGUMENT_INITIALIZE(keepFly_, vFly_);


	//3D��2D�ŌĂԊ֐��ς���
	if (GameManager::GetpStage()->GetthreeDflag())
		Update3D(player);
	else
		Update2D(player);
}