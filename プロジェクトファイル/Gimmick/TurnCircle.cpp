#include "TurnCircle.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Manager/GameManager/GameManager.h"

//�萔
namespace
{
	static const float RAY_HIT_DISTANCE = 1.0f;				//���C�̓�����������
	static const float GRAVITY_STRENGTH = 0.083f;           //�d�͂̋���
	static const float NORMAL_INTERPOLATION_FACTOR = 0.045f;//�@�����Ԃ���Ƃ��̕�ԌW��
	static const float ADD_ROTATION_VALUE = 0.05f;          //��]����Ƃ��̉��Z����p�x
	static const int MAX_NORMAL_RADIANS = 50;               //�@���Ƃ̍ő�p�x
	static const int KILLME_PLAYER_Z_DIS = -5;              //���S���鎞��Player�Ƃ�Z�̋���
}

//�R���X�g���N�^
TurnCircle::TurnCircle(GameObject* parent)
	:Mob(parent, "Stage/Gimmick/TurnCircle.fbx", "TurnCircle"), rotationAngle_(ZERO)
{
}

//�X�V�̑O�Ɉ�x������΂��֐�
void TurnCircle::ChildStartUpdate()
{
	///////////////���邳///////////////////

	Model::SetBrightness(hModel_, 1.0f);

	///////////��Q���Ƃ��Ēǉ�///////////

	Model::SetRayFlag(hModel_, true);
	Model::SetObstacleObj(hModel_, this);

	//////////////////////�R���|�[�l���g�̏����ݒ�////////////////////////////////

	ARGUMENT_INITIALIZE(posture_.transform_, &transform_);
	ARGUMENT_INITIALIZE(posture_.down_, &down_);
	ARGUMENT_INITIALIZE(posture_.vNormal_, &vNormal_);
	ARGUMENT_INITIALIZE(posture_.hGroundModel_, hGroundModel_);
}

//�X�V
void TurnCircle::ChildUpdate()
{
	//�R���|�[�l���g�̍X�V���Ă�
	posture_.Update();

	//��]
	Rotation();

	//Player�����ɍs�����玀�S
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z + KILLME_PLAYER_Z_DIS)
		KillMe();
}

//��]
void TurnCircle::Rotation()
{
	//��]
	transform_.mmRotate_ *= XMMatrixRotationAxis(STRAIGHT_VECTOR, rotationAngle_);

	//Angle��360�܂ł�������0�ɖ߂�
	if (rotationAngle_ > TWOPI_DEGREES)
		rotationAngle_ = ZEROPI_DEGREES;

	//���Z
	rotationAngle_ += ADD_ROTATION_VALUE;
}