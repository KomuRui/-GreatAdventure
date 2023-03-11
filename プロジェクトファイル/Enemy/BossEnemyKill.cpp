#include "BossEnemyKill.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/GameObject/Camera.h"

//�萔
namespace
{
	static const XMFLOAT3 CAM_POS = { ZERO,10,ZERO }; //�J�����̃|�W�V����
}

//�R���X�g���N�^
BossEnemyKill::BossEnemyKill(GameObject* parent)
	: GameObject(parent), hModel_(-1)
{
}

//������
void BossEnemyKill::Initialize()
{
	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Enemy/Model/MainBoss.fbx");
	assert(hModel_ >= ZERO);

	///////////////�J�����̐ݒ�///////////////////

	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(transform_.position_);
}

//�X�V
void BossEnemyKill::Update()
{


	//��Ƀ{�X����悤��
	Camera::SetTarget(transform_.position_);
}

//�`��
void BossEnemyKill::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

