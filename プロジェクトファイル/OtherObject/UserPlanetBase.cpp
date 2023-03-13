#include "UserPlanetBase.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/DirectX/Input.h"
#include "../Engine/ResourceManager/Easing.h"
#include "../Engine/ResourceManager/VFX.h"
#include "../UI/UserSelectScene/UserGameStartUI.h"
#include "../Manager/ButtonManager/ButtonManager.h"

////�萔
namespace
{
	static const float ROTATION_SPEED = 0.3f;			 //��]���x
	static const float STATUS_CHANGE_DISTANCE = 0.05f;   //��Ԃ��ύX����Ƃ��̋���
	static const float INTERPOLATION_COEFFICIENT = 0.1f; //��ԌW��
	static const float FALL_SPEED = 0.4f;                //�����鑬�x�̒l
	static const float KILL_VALUE = -40.0f;              //�폜����Ƃ��̒l
}

//�R���X�g���N�^
UserPlanetBase::UserPlanetBase(GameObject* parent, std::string modelPath, std::string name)
	:GameObject(parent, name), hModel_(-1), ModelNamePath_(modelPath), status_(PlanetStatus::Stop), isSelect_(false)
{
}

/////////////////////�I�[�o�[���C�h����֐�//////////////////////

//������
void UserPlanetBase::Initialize()
{
	//���f���f�[�^���[�h
	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= ZERO);

	//��]������
	ARGUMENT_INITIALIZE(transform_.rotate_, XMFLOAT3(ZERO, ZERO, ZERO));

	//�C�[�W���O�ݒ�
	ARGUMENT_INITIALIZE(pEasing_,new EasingMove(&transform_.rotate_,XMFLOAT3(0,0,0), XMFLOAT3(0,360,0),2.0f,Easing::OutCubic));

	//�p����p
	ChildInitialize();
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void UserPlanetBase::StartUpdate()
{
}

//�X�V
void UserPlanetBase::Update()
{
	//�I������Ă����班����]������
	if (isSelect_)
		pEasing_->Move();

	//��Ԃɂ���ČĂԊ֐�������
	switch (status_)
	{
	//�ړ�
	case PlanetStatus::Move:

		NextPositionToMove();
		break;

	//������
	case PlanetStatus::Fall:

		Fall();
		break;

	//����
	case PlanetStatus::Explosion:

		Explosion();
		break;

	default:
		break;
	}


	//�p����p
	ChildUpdate();
}

//�`��
void UserPlanetBase::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void UserPlanetBase::Release()
{
}

/////////////////////�֐�//////////////////////

//���̈ʒu�ֈړ�
void UserPlanetBase::NextPositionToMove()
{
	//��Ԃ��Ȃ���ړI�̃|�W�V�����܂ŕύX���Ă���
	transform_.position_ = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&nextPos_), INTERPOLATION_COEFFICIENT));
	
	//������0.05��菬�����Ȃ�Stop��Ԃɐݒ�
	if (RangeCalculation(transform_.position_, nextPos_) < STATUS_CHANGE_DISTANCE)
	{
		//���g�̃|�W�V���������̈ʒu�ɐݒ�
		ARGUMENT_INITIALIZE(transform_.position_, nextPos_);
		ARGUMENT_INITIALIZE(status_, PlanetStatus::Stop);
	}

}

//���̃|�W�V�����Z�b�g
void UserPlanetBase::SetNextPosition(const XMFLOAT3& nextPos)
{
	ARGUMENT_INITIALIZE(nextPos_, nextPos);           //���̈ʒu�ݒ�
	ARGUMENT_INITIALIZE(status_, PlanetStatus::Move); //��Ԑݒ�
}

//�I������Ă��Ȃ��̂Ȃ痎����
void UserPlanetBase::Fall()
{
	//���Ƃ�
	transform_.position_.y -= FALL_SPEED;

	//�����폜����l��艺�Ȃ�폜
	if (transform_.position_.y < KILL_VALUE) KillMe();
}

//�������ă��f���ύX
void UserPlanetBase::Explosion()
{
	//�����G�t�F�N�g
	ExplosionEffect();
	SetTimeMethod(0.5f);

	//��~��Ԃ�
	ARGUMENT_INITIALIZE(status_, PlanetStatus::Stop);
}

//�V�K�쐬
void UserPlanetBase::CreateNewFile()
{
	UserCreateNewFile(ModelNamePath_); 
}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void UserPlanetBase::TimeMethod()
{
	//���f���ύX
	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= ZERO);

	//�{�^�����Z�b�g
	ButtonManager::Reset();

	//�Q�[���X�^�[�gUI�쐬
	Instantiate<UserGameStartUI>(GetParent());

}

//�I������Ă��邩�ǂ���
bool UserPlanetBase::IsSelect()
{
	//�����I������Ă���̂Ȃ�
	if (isSelect_)
	{
		//�I������
		ARGUMENT_INITIALIZE(isSelect_, false);

		//��]����
		ARGUMENT_INITIALIZE(transform_.rotate_.y, ZERO);

		return true;
	}

	return false;
}

//��Ԃ��Z�b�g
void UserPlanetBase::SetStatus(PlanetStatus status, std::string iconModelPath)
{
	//��ԕύX
	ARGUMENT_INITIALIZE(status_, status);

	//���������ɕύX�Ȃ烂�f���p�X�ۑ�
	if (status_ == PlanetStatus::Explosion) ARGUMENT_INITIALIZE(ModelNamePath_, iconModelPath);
	
}

//�������ԂɕύX
bool UserPlanetBase::SetFallStatus()
{
	//�����I������Ă��Ȃ��̂Ȃ�
	if (!isSelect_)
	{
		//��ԕύX
		ARGUMENT_INITIALIZE(status_, PlanetStatus::Fall);
		return true;
	}

	return false;
}

//�I������Ă��邩�ǂ����Z�b�g
void UserPlanetBase::SetIsSelect(const bool& flag)
{
	 ARGUMENT_INITIALIZE(isSelect_, flag);

	 //�����I������Ă����烊�Z�b�g
	 if (isSelect_)pEasing_->Reset(&transform_.rotate_, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 360, 0), 2.0f, Easing::OutCubic);
}

//�����t�@�C�����ǂ���
bool UserPlanetBase::IsExisting()
{
	return (ModelNamePath_ != "Stage/Home/Home.fbx");
}

//�����G�t�F�N�g
void UserPlanetBase::ExplosionEffect()
{
	EmitterData data;
	data.textureFileName = "Cloud.png";
	data.position = { 0,0,0 };
	data.delay = 0;
	data.number = 60;
	data.lifeTime = 150;
	data.direction = XMFLOAT3(0, 1, 0);
	data.directionRnd = XMFLOAT3(90, 90, 90);
	data.speed = 0.05f;
	data.speedRnd = 0.8;
	data.size = XMFLOAT2(5, 5);
	data.sizeRnd = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1.05, 1.05);
	data.color = XMFLOAT4(1, 1, 1, 1);
	data.deltaColor = XMFLOAT4(-0.02, -0.02, 0, -1.0 / 50);
	VFX::Start(data);
}