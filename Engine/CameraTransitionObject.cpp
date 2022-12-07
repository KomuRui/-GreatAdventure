#include "CameraTransitionObject.h"
#include "BoxCollider.h"
#include "Camera.h"
#include "GameManager.h"

//�R���X�g���N�^
CameraTransitionObject::CameraTransitionObject(GameObject* parent, const StageCameraTransition& camInfo)
	:GameObject(parent,"CameraTransition"), hitFlag(false)
{
	//�e�ϐ�������
	ARGUMENT_INITIALIZE(info, camInfo);
}

//������
void CameraTransitionObject::Initialize()
{
	//���`�̓����蔻��쐬
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0,0,0), info.CollisionSize);
	AddCollider(collision);
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void CameraTransitionObject::StartUpdate()
{
}

//�X�V
void CameraTransitionObject::Update()
{
}

//�`��
void CameraTransitionObject::Draw()
{
}

//���
void CameraTransitionObject::Release()
{
}

//�����蔻��
void CameraTransitionObject::OnCollision(GameObject* pTarget)
{
	//�����������肪Player�ȊO�Ȃ�
	if (pTarget->GetObjectName() != "Player") return;

	//�܂��������Ă��Ȃ��̂Ȃ�
	if (!hitFlag)
	{
		//1.0�b��Ƀ��\�b�h���Ă�
		//�����ł�Player�����V���ɃZ�b�g�����J�������猩���ړ������������̂�...
		//�����؂�ւ���Ƒ��삵���炢�̂ŏ����Ԃ������Ă���...
		SetTimeMethod(1.0f);
		ARGUMENT_INITIALIZE(hitFlag, true);
	}

	//�J�����̃|�W�V�����ƃ^�[�Q�b�g�Z�b�g(��Ԃ��Ȃ���ύX)
	XMVECTOR vCamPos = XMVectorLerp(XMLoadFloat3(new XMFLOAT3(Camera::GetPosition())), XMLoadFloat3(&info.CameraPosition),0.1);
	XMVECTOR vCamTar = XMVectorLerp(XMLoadFloat3(new XMFLOAT3(Camera::GetTarget())), XMLoadFloat3(&info.CameraTarget), 0.1);
	Camera::SetPosition(Transform::VectorToFloat3(vCamPos));
	Camera::SetTarget(Transform::VectorToFloat3(vCamTar));
}

//�����蔻��(�N�Ƃ��������Ă��Ȃ���)
void CameraTransitionObject::OutCollision()
{
	//�������Ă����Ȃ�
	if (hitFlag)
	{
		//�J�������삷��悤��
		GameManager::GetpPlayer()->SetCamFlag(true);

		//�������Ă��Ȃ���Ԃ�
		ARGUMENT_INITIALIZE(hitFlag, false);
	}
}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void CameraTransitionObject::TimeMethod()
{
	//�J�������삵�Ȃ��悤�ɂ���
	GameManager::GetpPlayer()->SetCamFlag(false);
}