#include "FlyBall.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/EffectManager/EnemyEffectManager/EnemyEffectManager.h"
#include "../Engine/ResourceManager/Easing.h"

//�萔
namespace
{
	static const float ADD_ROTATION_VALUE = 0.05f;   //��]����Ƃ��̉��Z�l
	static const float MAX_ROTATION_VALUE = 100.0f;  //�ő��]�l
	static const float HIT_STOP_TIME = 0.15f;		 //�q�b�g�X�g�b�v���o�̎���
	static const float COLLIDER_POS_Y = 1.0f;        //�R���C�_�[��Y���̃|�W�V����
	static const float COLLIDER_RADIUS = 1.0f;       //�R���C�_�[�̔��a
}

//�R���X�g���N�^
FlyBall::FlyBall(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent,modelPath,name), rotateAngle_(ZERO),isFly_(false), pEasing_(new EasingMove),
	beforePos_(ZERO,ZERO,ZERO), isReturnPos(false), hStickModel_(ZERO), basePos_(ZERO, ZERO, ZERO), baseUp_(XMVectorSet(ZERO, ZERO, ZERO, ZERO))
{}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void FlyBall::ChildStartUpdate()
{
	//���f���f�[�^�̃��[�h
	hStickModel_ = Model::Load("Stage/Gimmick/FlyBall_Stick.fbx");
	assert(hStickModel_ >= ZERO);

	//�x�[�X�̃|�W�V�����Ə�x�N�g���ݒ�
	ARGUMENT_INITIALIZE(basePos_, transform_.position_);
	ARGUMENT_INITIALIZE(baseUp_, vNormal_);

	//�_�̃g�����X�t�H�[���ݒ�
	ARGUMENT_INITIALIZE(tStick_.position_,transform_.position_);
	ARGUMENT_INITIALIZE(tStick_.scale_, tStick_.scale_);
	ARGUMENT_INITIALIZE(tStick_.mFlag_, true);

	//�R���C�_�[�ǉ�
	SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)) * COLLIDER_POS_Y * transform_.scale_.y, ZERO), COLLIDER_RADIUS);
	AddCollider(collision);

	//���邳
	Model::SetBrightness(hModel_, 1.0f);
	Model::SetBrightness(hStickModel_, 1.0f);
}

//�X�V
void FlyBall::ChildUpdate()
{
	//��]
	Rotation();

	//�������ł���̂Ȃ�
	if (isFly_) Fly();

	//�_�̃g�����X�t�H�[���̌v�Z
	StickCalculation();
}

//�`��
void FlyBall::ChildDraw()
{
	Model::SetTransform(hStickModel_, tStick_);
	Model::Draw(hStickModel_);
}

//���
void FlyBall::Fly()
{
	//������
	if (pEasing_->Move())
	{
		//�߂��Ă��Ȃ��̂Ȃ�
		if (!isReturnPos)
		{
			//���ɖ߂�
			ARGUMENT_INITIALIZE(isReturnPos, true);

			//�ړ��O�̃|�W�V�����ɖ߂�悤�ɐݒ�
			pEasing_->Reset(&transform_.position_,transform_.position_, beforePos_, 0.5f, Easing::OutQuad);
		}
		else
		{
			ARGUMENT_INITIALIZE(isFly_,false);
			ARGUMENT_INITIALIZE(isReturnPos,false);
		}
	}
}

//��]
void FlyBall::Rotation()
{
	//�M�~�b�N�̏㎲�ŉ�]������
	transform_.mmRotate_ *= XMMatrixRotationAxis(up_, rotateAngle_);

	//��]�̒l�𑝂₷
	rotateAngle_ += ADD_ROTATION_VALUE;

	//�萔�ȏ�ɂȂ����珉����
	if (rotateAngle_ >= MAX_ROTATION_VALUE) ARGUMENT_INITIALIZE(rotateAngle_, ZERO);
}

//�_�̃g�����X�t�H�[���̌v�Z
void FlyBall::StickCalculation()
{
	//�_�̉�]�s��ݒ�
	ARGUMENT_INITIALIZE(tStick_.mmRotate_, transform_.mmRotate_);

	//�_�̊g��k���v�Z
	ARGUMENT_INITIALIZE(tStick_.scale_.y, RangeCalculation(basePos_, transform_.position_) - 0.3f);

	//Ball�̃x�[�X�|�W�V�������猻�݂�Ball�̃|�W�V�����Ɍ����Ẵx�N�g�����쐬
	XMVECTOR toBall = XMLoadFloat3(&transform_.position_) - XMLoadFloat3(&basePos_);

	//�x�[�X��x�N�g����toBall�Ƃ̓��ς𒲂ׂ�
	float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(baseUp_), XMVector3Normalize(toBall)));

	//�O�ϋ��߂�
	XMVECTOR cross = XMVector3Cross(baseUp_, toBall);

	//�l�͈̔͊O����Ȃ���ΊO�ώ��ŉ�]������
	if (dotX != ZERO && dotX <= 1 && dotX >= -1) tStick_.mmRotate_ *= XMMatrixRotationAxis(cross, acos(dotX));
}

//�����蔻��
void FlyBall::OnCollision(GameObject* pTarget)
{
	//�����������肪Player����Ȃ��̂Ȃ炱�̐�̏��������Ȃ�
	if (pTarget->GetObjectName() != "Player") return;

	//����Player����]���Ă�����
	if (GameManager::GetpPlayer()->IsRotation() && !isFly_)
	{
		//��΂�
		ARGUMENT_INITIALIZE(isFly_, true);

		//���ł����������v�Z
		XMVECTOR dir_ = XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(SubTract(transform_.position_, pTarget->GetPosition()))));

		//��������
		dir_ += GameManager::GetpPlayer()->GetDown() * 0.5f;

		//��ԃ|�W�V������ݒ�
		XMFLOAT3 afterPos = Float3Add(VectorToFloat3(dir_ * 15.0f),transform_.position_);

		//���X�����|�W�V�����ݒ�
		ARGUMENT_INITIALIZE(beforePos_, transform_.position_);

		//�����ݒ�
		pEasing_->Reset(&transform_.position_, transform_.position_, afterPos, 0.5f, Easing::OutQuad);

		//�����������̃G�t�F�N�g�\��
		EnemyEffectManager::HitEffect(Float3Add(GameManager::GetpPlayer()->GetPosition(), VectorToFloat3(dir_ * 0.5f)), transform_.position_);

		//�q�b�g�X�g�b�v���o(�������~�߂�)
		Leave();
		pTarget->Leave();

		//Player���G��0.15�b��ɓ����o��
		SetTimeMethod(HIT_STOP_TIME);
		pTarget->SetTimeMethod(HIT_STOP_TIME);
	}
}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void FlyBall::TimeMethod()
{
	Enter();
}