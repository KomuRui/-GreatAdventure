#include "Warp.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"

//�R���X�g���N�^
Warp::Warp(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name), status_(STOP)
, turnoverRate_(1), playerPos_(0, 0, 0), number_(0)
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
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, XMVectorGetY(XMVector3Normalize(vNormal)) * -2 * transform_.scale_.y, 0), 3.5f * transform_.scale_.y);
	AddCollider(collision);

	//���[�v��Player���悹��Ƃ���Player�̃|�W�V������ݒ�
	playerPos_ = Float3Add(transform_.position_, VectorToFloat3(XMVector3Normalize(-vNormal)));

	//���[�v�|�W�V�������ݒ肳��Ă��Ȃ��̂Ȃ�
	if(warpTarget_.x == 0 && warpTarget_.y == 0 && warpTarget_.z == 0)
	    //���[�v�̖ړI�n
		warpTarget_ = Float3Add(transform_.position_, VectorToFloat3(XMVector3Normalize(vNormal) * 800));

	/////////////////////////�G�t�F�N�g////////////////////////////

	//�|�����C��������
	pLine[RIGHT] = new PolyLine;
	pLine[LEFT] = new PolyLine;
	pLine[BASE] = new PolyLine;

	//�e�N�X�`�����[�h
	pLine[RIGHT]->Load("tex.png");
	pLine[LEFT]->Load("tex.png");
	pLine[BASE]->Load("tex.png");

	//�e�|�W�V����������
	pLine[RIGHT]->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLine[LEFT]->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pLine[BASE]->AddPosition(Model::GetBonePosition(hModel_, "Base"));

	//��x�N�g����Player�Ɠ����̂ɐݒ�
	if(number_ == 2)
		vNormal = GameManager::GetpPlayer()->GetNormal();
}

//�X�V
void Warp::ChildUpdate()
{
	//Y����]������
	Angle += ROTATION_QUANTITY * turnoverRate_;

	//Y���̊p�x��360���傫���Ȃ�0�ɖ߂�
	if (Angle > TWOPI_DEGREES) Angle = ZEROPI_DEGREES;

	//�}�b�N�X�X�s�[�h�ɒB�����玟�̐��Ƀ��[�v����(��Ԃɂ���Ĉړ��̎d����ς���)
	if (status_ == MOVE) number_ == 2 ? MovingToPurpose() : MovingToStar();

}

//�p����p�̕`��
void Warp::ChildDraw()
{
	//null�Ȃ�
	if (pLine[BASE] == nullptr)
		return;

	//�|�����C����`��
	pLine[RIGHT]->Draw();
	pLine[LEFT]->Draw();
	pLine[BASE]->Draw();
}

//�p����p�̊J��
void Warp::ChildRelease()
{
	//������
	for (int i = 0; i < MAX_POLY_LINE; i++)
	{
		SAFE_RELEASE(pLine[i]);
		SAFE_DELETE_ARRAY(pLine[i]);
	}
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
	if (dist < 5)
	{
		//Player�̗����G�t�F�N�g�\��
		GameManager::GetpPlayer()->FallEffect();

		//Player�@�����ׂ邩���X�e�[�W���݂ĕς���
		GameManager::GetpPlayer()->SetNormalFlag(GameManager::GetpStage()->GetCircleflag());

		//�J�����U��
		Camera::SetCameraVibration(0.5f);

		//�폜
		KillMe();
	}

	//null�Ȃ�
	if (pLine[BASE] == nullptr)
		return;

	//�e�G�t�F�N�g�̃|�W�V�����ݒ�
	pLine[RIGHT]->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLine[LEFT]->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pLine[BASE]->AddPosition(Model::GetBonePosition(hModel_, "Base"));
}

//���̐��Ƀ��[�v
void Warp::MovingToStar()
{
	//Player��null�Ȃ炱�̐�̏����͂��Ȃ�
	if (GameManager::GetpPlayer() == nullptr) return;

	//�J�����̃|�W�V�����𓮂��Ȃ��悤�ɐݒ�
	GameManager::GetpPlayer()->SetCamPosFlag();

	//�ړI�n�܂ŕ�Ԃ��Ȃ���i��
	XMStoreFloat3(&transform_.position_,XMQuaternionSlerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&warpTarget_), 0.003));

	//���̃|�W�V�����ƖړI�n�̋��������߂�
	float dist = RangeCalculation(transform_.position_, warpTarget_);

	//������600��菬�����Ȃ玟�̃X�e�[�W�Ɉڍs
	if (dist < FADE_OUT_DISTANCE)
	{
		//�t�F�[�h�̃X�e�[�^�X��FADE_OUT��Ԃ���Ȃ�������
		if (GameManager::GetStatus() != FADE_OUT)
			GameManager::SetStatus(FADE_OUT);
	}

	//������300��菬�����Ȃ玟�̃X�e�[�W�Ɉڍs
	if (dist < SCENE_MOVE_DISTANCE)
	{
		SceneManager* pScene = (SceneManager*)FindObject("SceneManager");
		pScene->ChangeScene(id_);
	}

	//�e�G�t�F�N�g�̃|�W�V�����ݒ�
	pLine[RIGHT]->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLine[LEFT]->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pLine[BASE]->AddPosition(Model::GetBonePosition(hModel_, "Base"));
}

//�����蔻��
void Warp::OnCollision(GameObject* pTarget)
{
	//Player�����Փ˔���
	if (pTarget->GetObjectName() != "Player")
		return;

	//���[�v��Player���悹��Ƃ���Player�̃|�W�V������ݒ�
	XMStoreFloat3(&playerPos_, XMVector3Normalize(-vNormal));
	playerPos_ = Float3Add(transform_.position_, playerPos_);
		
	//Player�|�W�V�������Z�b�g����
	pTarget->SetPosition(playerPos_);

	//Player�@���X�V���Ȃ��悤�ɂ���
	GameManager::GetpPlayer()->SetNormalFlag(false);

	//number_��1�̏�ԂȂ�
	if (number_ == 1)
	{
		GameManager::GetpPlayer()->SetInverseNormalAndDown();
		ZERO_INITIALIZE(number_);
	}

	//Player�Ɠ������Ă����ԂȂ��]�����ǂ�ǂ񑁂߂�
	//������]�����ő�܂ŒB�������Ԃ�Move�ɐݒ�
	if (number_ <= 1)
	{
		if (turnoverRate_ < MAX_TURNOVERRATE)
			turnoverRate_ += ADDITION_TURNOVERRATE;
		else
			ARGUMENT_INITIALIZE(status_, MOVE);
	}
	else
		ARGUMENT_INITIALIZE(status_, MOVE);
}
