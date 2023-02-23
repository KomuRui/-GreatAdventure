#include "Warp.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/GameObject/Camera.h"
#include "../Engine/ResourceManager/Fade.h"
#include "../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../Manager/GameManager/GameManager.h"

//�萔
namespace
{
	////////////////���[�v�̈ړ��ɕK�v////////////////////

	static const int      FADE_OUT_DISTANCE = 600;          //�t�F�[�h�A�E�g���鎞�̋���
	static const int      SCENE_MOVE_DISTANCE = 300;        //�V�[���ڍs���鎞�̋���
	static const float    DESTINATION_DISTANCE = 800;       //�ړI�n�܂ł̋���
	static const float    WARP_KILL_DISTANCE = 5;           //���[�v���폜����Ƃ��̋���
	static const float    INTERPOLATION_COEFFICIENT = 0.003;//��ԌW��

	////////////////���[�v�̉�]�ɕK�v////////////////////

	static const float    ROTATION_QUANTITY = 0.02f;        //��]��
	static const float    ADDITION_TURNOVERRATE = 0.03f;    //��]�������Z�����
	static const float    MAX_TURNOVERRATE = 10.0f;         //�ő��]��
	
	////////////////////�����蔻��/////////////////////

	static const int      COLLIDER_POS_Y = -2;              //�R���C�_�[�|�W�V����
	static const float    COLLIDER_SIZE = 3.5f;             //�R���C�_�[�T�C�Y

	//////////////////////���̑�///////////////////////

	static const float    VIBRATION_INTENSITY = 0.5f;       //�J�����U���̋���
}

//�R���X�g���N�^
Warp::Warp(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name), status_(STOP)
, turnoverRate_(1), playerPos_(ZERO, ZERO, ZERO), type_(Normal),warpTarget_(ZERO, ZERO, ZERO), id_(SCENE_ID_HOME)
{
}

Warp::~Warp()
{
}

//������
void Warp::ChildInitialize()
{
}

//�X�^�[�g�A�b�v�f�[�g
void Warp::ChildStartUpdate()
{
	//���g�ɓ����蔻���ǉ�
	SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)) * COLLIDER_POS_Y * transform_.scale_.y, ZERO), COLLIDER_SIZE * transform_.scale_.y);
	AddCollider(collision);

	//���[�v��Player���悹��Ƃ���Player�̃|�W�V������ݒ�
	playerPos_ = Float3Add(transform_.position_, VectorToFloat3(XMVector3Normalize(-vNormal_)));

	//���[�v�|�W�V�������ݒ肳��Ă��Ȃ��̂Ȃ�
	if(warpTarget_.x == ZERO && warpTarget_.y == ZERO && warpTarget_.z == ZERO)
	    //���[�v�̖ړI�n
		warpTarget_ = Float3Add(transform_.position_, VectorToFloat3(XMVector3Normalize(vNormal_) * DESTINATION_DISTANCE));

	/////////////////////////�G�t�F�N�g////////////////////////////

	pRightLine_ = new PolyLine;
	pLeftLine_  = new PolyLine;
	pBaseLine_  = new PolyLine;

	//�e�N�X�`�����[�h
	pRightLine_->Load("tex.png");
	pLeftLine_->Load("tex.png");
	pBaseLine_->Load("tex.png");

	//�e�|�W�V����������
	pRightLine_->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLeftLine_->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pBaseLine_->AddPosition(Model::GetBonePosition(hModel_, "Base"));

	//��x�N�g����Player�Ɠ����̂ɐݒ�
	if(type_ == MoveToPurpose)
		vNormal_ = GameManager::GetpPlayer()->GetNormal();
}

//�X�V
void Warp::ChildUpdate()
{
	//Y����]������
	angle_ += ROTATION_QUANTITY * turnoverRate_;

	//Y���̊p�x��360���傫���Ȃ�0�ɖ߂�
	if (angle_ > TWOPI_DEGREES) angle_ = ZEROPI_DEGREES;

	//�}�b�N�X�X�s�[�h�ɒB�����玟�̐��Ƀ��[�v����(��Ԃɂ���Ĉړ��̎d����ς���)
	if (status_ == MOVE) type_ == MoveToPurpose ? MovingToPurpose() : MovingToStar();

}

//�p����p�̕`��
void Warp::ChildDraw()
{
	//null�Ȃ�
	if (pBaseLine_ == nullptr)
		return;

	//�|�����C����`��
	pBaseLine_->Draw();
	pRightLine_->Draw();
	pLeftLine_->Draw();
}

//�p����p�̊J��
void Warp::ChildRelease()
{
	SAFE_RELEASE(pBaseLine_);
	SAFE_DELETE_ARRAY(pBaseLine_);
	SAFE_RELEASE(pLeftLine_);
	SAFE_DELETE_ARRAY(pLeftLine_);
	SAFE_RELEASE(pRightLine_);
	SAFE_DELETE_ARRAY(pRightLine_);
}

//���̖ړI�n�܂ňړ�
void Warp::MovingToPurpose()
{
	//��]���x�ō��ɐݒ�
	turnoverRate_ = MAX_TURNOVERRATE;

	//Player��null�Ȃ炱�̐�̏����͂��Ȃ�
	if (GameManager::GetpPlayer() == nullptr) return;

	//�ړI�n�܂Ői��
	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + XMVector3Normalize(XMLoadFloat3(&warpTarget_) - XMLoadFloat3(&transform_.position_)) * 1.5);

	//���̃|�W�V�����ƖړI�n�̋��������߂�
	float dist = RangeCalculation(transform_.position_, warpTarget_);

	//������5��菬�����Ȃ�G�t�F�N�g�\���E���[�v�폜�@
	if (dist < WARP_KILL_DISTANCE)
	{
		//Player�̗����G�t�F�N�g�\��
		PlayerEffectManager::FallEffect(GameManager::GetpPlayer()->GetPosition());

		//Player�@�����ׂ邩���X�e�[�W���݂ĕς���
		GameManager::GetpPlayer()->SetCheckNormal(GameManager::GetpStage()->GetCircleflag());

		//�J�����U��
		Camera::SetCameraVibration(VIBRATION_INTENSITY);

		//�폜
		KillMe();
	}

	//null�Ȃ�
	if (pBaseLine_ == nullptr)
		return;

	//�e�G�t�F�N�g�̃|�W�V�����ݒ�
	pRightLine_->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLeftLine_->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pBaseLine_->AddPosition(Model::GetBonePosition(hModel_, "Base"));
}

//���̐��Ƀ��[�v
void Warp::MovingToStar()
{
	//Player��null�Ȃ炱�̐�̏����͂��Ȃ�
	if (GameManager::GetpPlayer() == nullptr) return;

	//�J�����̃|�W�V�����𓮂��Ȃ��悤�ɐݒ�
	GameManager::GetpPlayer()->SetCamPosNotMove();

	//�ړI�n�܂ŕ�Ԃ��Ȃ���i��
	XMStoreFloat3(&transform_.position_,XMQuaternionSlerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&warpTarget_), INTERPOLATION_COEFFICIENT));

	//���̃|�W�V�����ƖړI�n�̋��������߂�
	float dist = RangeCalculation(transform_.position_, warpTarget_);

	//������600��菬�����Ȃ玟�̃X�e�[�W�Ɉڍs
	if (dist < FADE_OUT_DISTANCE)
	{
		//�t�F�[�h�̃X�e�[�^�X��FADE_OUT��Ԃ���Ȃ�������
		if (Fade::GetFadeStatus() != FADE_CIRCLE_OUT)
			Fade::SetFadeStatus(FADE_CIRCLE_OUT);
	}

	//������300��菬�����Ȃ玟�̃X�e�[�W�Ɉڍs
	if (dist < SCENE_MOVE_DISTANCE)
	{
		GameManager::GetpSceneManager()->ChangeScene(id_);
	}

	//null�Ȃ�
	if (pBaseLine_ == nullptr)
		return;

	//�e�G�t�F�N�g�̃|�W�V�����ݒ�
	pRightLine_->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLeftLine_->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pBaseLine_->AddPosition(Model::GetBonePosition(hModel_, "Base"));
}

//�����蔻��
void Warp::OnCollision(GameObject* pTarget)
{
	//Player�����Փ˔���
	if (pTarget->GetObjectName() != "Player")
		return;

	//���[�v��Player���悹��Ƃ���Player�̃|�W�V������ݒ�
	XMStoreFloat3(&playerPos_, XMVector3Normalize(-vNormal_));
	playerPos_ = Float3Add(transform_.position_, playerPos_);
		
	//Player�|�W�V�������Z�b�g����
	pTarget->SetPosition(playerPos_);

	//Player�@���X�V���Ȃ��悤�ɂ���
	GameManager::GetpPlayer()->SetCheckNormal(false);

	//�^��InverseNormalAndDown�̏�ԂȂ�
	if (type_ == InverseNormalAndDown)
	{
		GameManager::GetpPlayer()->SetInverseNormalAndDown();
		ZERO_INITIALIZE(type_);
	}

	//Player�Ɠ������Ă����ԂȂ��]�����ǂ�ǂ񑁂߂�
	//������]�����ő�܂ŒB�������Ԃ�Move�ɐݒ�
	if (type_ <= InverseNormalAndDown)
	{
		if (turnoverRate_ < MAX_TURNOVERRATE)
			turnoverRate_ += ADDITION_TURNOVERRATE;
		else
			ARGUMENT_INITIALIZE(status_, MOVE);
	}
	else
		ARGUMENT_INITIALIZE(status_, MOVE);
}
