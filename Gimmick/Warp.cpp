#include "Warp.h"
#include "../Engine/Model.h"
#include "../Engine/SceneManager.h"

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
	BoxCollider* collision = new BoxCollider(COLLIDER_POS, COLLIDER_SIZE);
	AddCollider(collision);

	//���[�v��Player���悹��Ƃ���Player�̃|�W�V������ݒ�
	playerPos_ = Transform::Float3Add(transform_.position_, Transform::VectorToFloat3(XMVector3Normalize(-vNormal)));

	//���[�v�|�W�V�������ݒ肳��Ă��Ȃ��̂Ȃ�
	if(warpTarget.x == 0 && warpTarget.y == 0 && warpTarget.z == 0)
	//���[�v�̖ړI�n
	warpTarget = Transform::Float3Add(transform_.position_, Transform::VectorToFloat3(XMVector3Normalize(vNormal) * 800));

	/////////////////////////�G�t�F�N�g////////////////////////////

	//�|�����C��������
	pLine[0] = new PolyLine;
	pLine[1] = new PolyLine;
	pLine[2] = new PolyLine;

	//�e�N�X�`�����[�h
	pLine[0]->Load("tex.png");
	pLine[1]->Load("tex.png");
	pLine[2]->Load("tex.png");

	//�e�|�W�V����������
	pLine[0]->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLine[1]->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pLine[2]->AddPosition(Model::GetBonePosition(hModel_, "Base"));

	//�G�t�F�N�g�o�����߂ɕK�v�ȃN���X
	pParticle_ = Instantiate<Particle>(this);

	//��x�N�g����Player�Ɠ����̂ɐݒ�
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
	if (pLine[0] == nullptr)
		return;

	//�|�����C����`��
	pLine[0]->Draw();
	pLine[1]->Draw();
	pLine[2]->Draw();
}

//�p����p�̊J��
void Warp::ChildRelease()
{
	SAFE_RELEASE(pLine[0]);
	SAFE_RELEASE(pLine[1]);
	SAFE_RELEASE(pLine[2]);
	SAFE_DELETE_ARRAY(pLine[0]);
	SAFE_DELETE_ARRAY(pLine[1]);
	SAFE_DELETE_ARRAY(pLine[2]);
}

//���̖ړI�n�܂ňړ�
void Warp::MovingToPurpose()
{
	//��]���x�ō��ɐݒ�
	turnoverRate_ = MAX_TURNOVERRATE;

	//Player��null�Ȃ炱�̐�̏����͂��Ȃ�
	if (GameManager::GetpPlayer() == nullptr) return;

	//�ړI�n�܂Ői��
	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + XMVector3Normalize(XMLoadFloat3(&warpTarget) - XMLoadFloat3(&transform_.position_)) * 1.5);

	//���̃|�W�V�����ƖړI�n�̋��������߂�
	float dist = Transform::RangeCalculation(transform_.position_, warpTarget);

	//������50��菬�����Ȃ�|�����C���i�X������
	if (dist < 50)
	{
		pLine[0]->SetMoveAlphaFlag();
		pLine[1]->SetMoveAlphaFlag();
		pLine[2]->SetMoveAlphaFlag();

		//Player�@�����ׂ�悤��
		GameManager::GetpPlayer()->SetNormalFlag(true);
	}

	//������5��菬�����Ȃ�G�t�F�N�g�\���E���[�v�폜
	if (dist < 5)
	{
		//Player�̗����G�t�F�N�g�\��
		GameManager::GetpPlayer()->FallEffect();

		//�폜
		KillMe();
	}

	//null�Ȃ�
	if (pLine[0] == nullptr)
		return;

	//�e�G�t�F�N�g�̃|�W�V�����ݒ�
	pLine[0]->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLine[1]->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pLine[2]->AddPosition(Model::GetBonePosition(hModel_, "Base"));
}

//���̐��Ƀ��[�v
void Warp::MovingToStar()
{
	//Player��null�Ȃ炱�̐�̏����͂��Ȃ�
	if (GameManager::GetpPlayer() == nullptr) return;

	//�J�����̃|�W�V�����𓮂��Ȃ��悤�ɐݒ�
	GameManager::GetpPlayer()->SetCamPosFlag();

	//�ړI�n�܂ŕ�Ԃ��Ȃ���i��
	XMStoreFloat3(&transform_.position_,XMQuaternionSlerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&warpTarget), 0.003));

	//���̃|�W�V�����ƖړI�n�̋��������߂�
	float dist = Transform::RangeCalculation(transform_.position_, warpTarget);

	//������300��菬�����Ȃ玟�̃X�e�[�W�Ɉڍs
	if (dist < 300) 
	{
		SceneManager* pScene = (SceneManager*)FindObject("SceneManager");
		pScene->ChangeScene(SCENE_ID_TUTORIAL2);
	}


	//�e�G�t�F�N�g�̃|�W�V�����ݒ�
	pLine[0]->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLine[1]->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pLine[2]->AddPosition(Model::GetBonePosition(hModel_, "Base"));
}

//�����蔻��
void Warp::OnCollision(GameObject* pTarget)
{
	//Player�ƏՓ˂�����
	if (pTarget->GetObjectName() == "Player")
	{
		//���[�v��Player���悹��Ƃ���Player�̃|�W�V������ݒ�
		XMStoreFloat3(&playerPos_, XMVector3Normalize(-vNormal));
		playerPos_ = Transform::Float3Add(transform_.position_, playerPos_);
		
		//Player�|�W�V�������Z�b�g����
		pTarget->SetPosition(playerPos_);

		//number_��1�̏�ԂȂ�
		if (number_ == 1)
		{
			Player* pPlayer_ = (Player*)FindObject("Player");
			if (pPlayer_ == nullptr) return;

			pPlayer_->SetInverseNormalAndDown();
			number_ = 0;
		}

		//Player�Ɠ������Ă����ԂȂ��]�����ǂ�ǂ񑁂߂�
		//������]�����ő�܂ŒB�������Ԃ�Move�ɐݒ�
		number_ <= 1 ? (turnoverRate_ < MAX_TURNOVERRATE ? turnoverRate_ += ADDITION_TURNOVERRATE : status_ = MOVE)
			         :  status_ = MOVE;
	}
}
