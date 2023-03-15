#include "UserPlanetBase.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/ResourceManager/Image.h"
#include "../Engine/DirectX/Input.h"
#include "../Engine/ResourceManager/Easing.h"
#include "../Engine/ResourceManager/VFX.h"
#include "../UI/UserSelectScene/UserGameStartUI.h"
#include "../Manager/ButtonManager/ButtonManager.h"
#include "SelectPlanetController.h"
#include "UserInfomation.h"

////�萔
namespace
{
	static const float STATUS_CHANGE_DISTANCE = 0.05f;        //��Ԃ��ύX����Ƃ��̋���
	static const float INTERPOLATION_COEFFICIENT = 0.1f;      //��ԌW��
	static const float FALL_SPEED = 0.4f;                     //�����鑬�x�̒l
	static const float KILL_VALUE = -40.0f;                   //�폜����Ƃ��̒l
	static const XMFLOAT3 FALL_POSITION = { ZERO,-40,ZERO };  //������ʒu
	static const XMFLOAT3 RETURN_POSITION = { ZERO,40,ZERO }; //�߂�ʒu

	//�C�[�W���O
	static const float EASING_TIME = 2.0f;                    //�C�[�W���O�ɂ����鎞��
	static const XMFLOAT3 BEFORE_ROTATE = { ZERO,ZERO,ZERO }; //��]�O
	static const XMFLOAT3 AFTER_ROTATE = { ZERO,360,ZERO };   //��]��

}

//�R���X�g���N�^
UserPlanetBase::UserPlanetBase(GameObject* parent, std::string modelPath, std::string name)
	:GameObject(parent, name), hModel_(-1), ModelNamePath_(modelPath), status_(PlanetStatus::Stop)
	, isSelect_(false), hNewFilePict_(-1), hCoinPict_(-1),hStagePict_(-1), hCrossPict_(-1)
{
}

/////////////////////�I�[�o�[���C�h����֐�//////////////////////

//������
void UserPlanetBase::Initialize()
{
	//���f���f�[�^���[�h
	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= ZERO);

	//�摜�f�[�^�̃��[�h
	hNewFilePict_ = Image::Load("Image/UserSelect/NewFileText.png");
	assert(hNewFilePict_ >= ZERO);
	hCoinPict_ = Image::Load("Image/Coin/Coin.png");
	assert(hCoinPict_ >= ZERO);
	hStagePict_ = Image::Load("Image/UserSelect/Stage.png");
	assert(hStagePict_ >= ZERO);
	hCrossPict_ = Image::Load("Image/Coin/Cross.png");
	assert(hCrossPict_ >= ZERO);

	//�e�L�X�g�̏�����
	ARGUMENT_INITIALIZE(pText_, new Text);
	pText_->Initialize("Text/NumberFont.png", 128, 256, 10);

	//��]������
	ARGUMENT_INITIALIZE(transform_.rotate_, XMFLOAT3(ZERO, ZERO, ZERO));

	//�C�[�W���O�ݒ�
	ARGUMENT_INITIALIZE(pEasingRotate_,new EasingMove(&transform_.rotate_, BEFORE_ROTATE, AFTER_ROTATE, EASING_TIME,Easing::OutCubic));

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
		pEasingRotate_->Move();

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

	//���̈ʒu�ɖ߂�
	case PlanetStatus::ReturnPosition:

		ReturnPosition();
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
	//���f���`��
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	//�摜�`��(�I������Ă��ď�Ԃ��I�𒆂������t�@�C������Ȃ��̂Ȃ�)
	if (isSelect_ && SelectPlanetController::GetStatus() == SelectPlanetStatus::Selecting && !IsExisting())
	{
		Transform t;
		ARGUMENT_INITIALIZE(t.position_.y,0.2f);
		Image::SetTransform(hNewFilePict_, t);
		Image::Draw(hNewFilePict_);
	}
	//�����t�@�C���̎�
	else if((isSelect_ && SelectPlanetController::GetStatus() == SelectPlanetStatus::Selecting && IsExisting()))
	{
		//�R�C��
		Transform t;
		ARGUMENT_INITIALIZE(t.scale_.x, 0.8f);
		ARGUMENT_INITIALIZE(t.scale_.y, 0.8f);
		ARGUMENT_INITIALIZE(t.position_.x, -0.85f);
		ARGUMENT_INITIALIZE(t.position_.y, -0.7f);
		Image::SetTransform(hCoinPict_, t);
		Image::Draw(hCoinPict_);

		//�X�e�[�W
		ARGUMENT_INITIALIZE(t.position_.x, -0.85f);
		ARGUMENT_INITIALIZE(t.position_.y, -0.3f);
		Image::SetTransform(hStagePict_, t);
		Image::Draw(hStagePict_);

		//�N���X
		ARGUMENT_INITIALIZE(t.position_.x, -0.65f);
		ARGUMENT_INITIALIZE(t.position_.y, -0.7f);
		Image::SetTransform(hCrossPict_, t);
		Image::Draw(hCrossPict_);
		ARGUMENT_INITIALIZE(t.position_.x, -0.65f);
		ARGUMENT_INITIALIZE(t.position_.y, -0.3f);
		Image::SetTransform(hCrossPict_, t);
		Image::Draw(hCrossPict_);

		//�e�L�X�g
		pText_->NumberDraw(500,910, UserInfomation::GetCoinNum(),1.0f,0.02f);
		pText_->NumberDraw(500,700, UserInfomation::GetStageReleaseNum(),1.0f,0.01f);
	}
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
	pEasingMove_->Move();
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

//���̈ʒu�ɖ߂�
void UserPlanetBase::ReturnPosition()
{
	//�ړ����I������̂Ȃ�X�g�b�v��Ԃ�
	if(pEasingMove_->Move())SetStatus(PlanetStatus::Stop);
}

//�C�[�W���O�ړ����Z�b�g
void UserPlanetBase::SetEasingMove()
{
	//�C�[�W���O�ݒ�
	ARGUMENT_INITIALIZE(pEasingMove_, new EasingMove(&transform_.position_, transform_.position_,Float3Add(transform_.position_,FALL_POSITION), EASING_TIME, Easing::OutCubic));
}

//�߂�C�[�W���O�ړ����Z�b�g
void UserPlanetBase::SetReturnEasingMove()
{
	//�C�[�W���O�ݒ�
	ARGUMENT_INITIALIZE(pEasingMove_, new EasingMove(&transform_.position_, transform_.position_, Float3Add(transform_.position_, RETURN_POSITION), EASING_TIME, Easing::OutCubic));
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
bool UserPlanetBase::IsSelectToChange()
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

//�I������Ă��邩�ǂ���
bool UserPlanetBase::IsSelect() { return isSelect_; }

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

		//�C�[�W���O�Z�b�g
		SetEasingMove();

		return true;
	}

	return false;
}

//�I������Ă��邩�ǂ����Z�b�g
void UserPlanetBase::SetIsSelect(const bool& flag)
{
	 ARGUMENT_INITIALIZE(isSelect_, flag);

	 //�����I������Ă����烊�Z�b�g
	 if (isSelect_)pEasingRotate_->Reset(&transform_.rotate_, BEFORE_ROTATE, AFTER_ROTATE, EASING_TIME, Easing::OutCubic);
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