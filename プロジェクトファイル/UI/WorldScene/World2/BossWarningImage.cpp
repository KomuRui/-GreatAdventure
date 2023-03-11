#include "BossWarningImage.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/Component/EasingMove.h"
#include "../../../Engine/ResourceManager/Easing.h"
#include "../../../Engine/ResourceManager/Time.h"
#include "../../../Enemy/BossEnemy.h"

//�萔
namespace
{
	static const XMFLOAT3 EASING_ONE_BEFORE_POS = { 3,0,0 }; //�C�[�W���O1��ڂ̈ړ��O�|�W�V����
	static const XMFLOAT3 EASING_ONE_AFTER_POS = { 0,0,0 }; //�C�[�W���O1��ڂ̈ړ���|�W�V����
	static const XMFLOAT3 EASING_TWO_BEFORE_POS = { 0,0,0 }; //�C�[�W���O2��ڂ̈ړ��O�|�W�V����
	static const XMFLOAT3 EASING_TWO_AFTER_POS = { -3,0,0 }; //�C�[�W���O2��ڂ̈ړ���|�W�V����
	 
	static const float ALPHA_ADD_VALUE = 0.05f;    //�A���t�@�l�v�Z����Ƃ��ɉ��Z����l
	static const float NEXT_EASING_CHANGE = 3.0f;  //�A���t�@�l�v�Z����Ƃ��ɉ��Z����l
	static const float EASING_MOVE_TIME = 2.0f;	   //�C�[�W���O�̈ړ��ɂ����鎞��
}

//�R���X�g���N�^
BossWarningImage::BossWarningImage(GameObject* parent)
	: GameObject(parent), hWarningPict_(-1), hBackGround_(-1),isEasingChange_(false), isFinish_(false), 
	backGroundAlpha_(ZERO), sign_(1), hTime_(ZERO)
{
}

//������
void BossWarningImage::Initialize()
{
	///////////////�摜�f�[�^�̃��[�h///////////////////

	hWarningPict_ = Image::Load("Image/World2/BossWarning.png");
	assert(hWarningPict_ >= ZERO);

	hBackGround_ = Image::Load("Image/World2/Background.png");
	assert(hBackGround_ >= ZERO);

	///////////////�^�C�}�[�ǉ�///////////////////

	ARGUMENT_INITIALIZE(hTime_, Time::Add());
	Time::Lock(hTime_);

	////////////////////////////////�C�[�W���O�̏����ݒ�////////////////////////////////////

	ARGUMENT_INITIALIZE(pEasingMove_, new EasingMove(&transform_.position_, EASING_ONE_BEFORE_POS, EASING_ONE_AFTER_POS, EASING_MOVE_TIME, Easing::OutQuart))

}

//�X�V
void BossWarningImage::Update()
{
	//�C�[�W���O�̓������Ō�܂ŏI��������
	bool isEasingFinish = pEasingMove_->Move();

	//�C�[�W���O�̓������Ō�܂ŏI����Ă��邩�C�[�W���O�̏���ύX���Ă��Ȃ��̂Ȃ�
	if (isEasingFinish && !isEasingChange_)
	{
		//�^�C�������b�N����Ă���̂Ȃ�^�C�}�[�X�^�[�g
		if(Time::isLock(hTime_))Time::UnLock(hTime_);
	}

	//�C�[�W���O�̓������Ō�܂ŏI����Ă��邩�C�[�W���O�̏���ύX���Ă���̂Ȃ�I�������ɕύX
	if (isEasingFinish && isEasingChange_ && !isFinish_)
	{
		//�{�X�̘b���摜�`�悷��悤��
		((BossEnemy*)FindObject("BossEnemy"))->SetTalkImageDraw();

		//�I���ɕύX
		ARGUMENT_INITIALIZE(isFinish_, true);
	}

	//�����^�C�}�[���萔�b�ȏ�o�߂��Ă��ăC�[�W���O�̏���ύX���Ă��Ȃ��Ȃ�
	if (Time::GetTimef(hTime_) >= NEXT_EASING_CHANGE && !isEasingChange_)
	{
		//�ύX�����ɕύX
		ARGUMENT_INITIALIZE(isEasingChange_, true);

		//�C�[�W���O�̓������ύX
		pEasingMove_->Reset(&transform_.position_, EASING_TWO_BEFORE_POS, EASING_TWO_AFTER_POS, EASING_MOVE_TIME, Easing::InQuart);
	}
}

//�`��
void BossWarningImage::Draw()
{
	//�I�����Ă����炱�̐揈�����Ȃ�
	if (isFinish_) return;

	//�^�C�}�[�̃��b�N����������Ă�����
	if (!Time::isLock(hTime_))
	{
		//�w�i�����x�̌v�Z
		BackGroundAlphaCalc();

		//�\���ptransform
		Transform t;

		//�w�i�`��
		Image::SetTransform(hBackGround_, t);
		Image::SetAlpha(hBackGround_, backGroundAlpha_);
		Image::Draw(hBackGround_);
	}

	//�x��
	Image::SetTransform(hWarningPict_, transform_);
	Image::Draw(hWarningPict_);
}

//�w�i�����x�̌v�Z
void BossWarningImage::BackGroundAlphaCalc()
{
	//�����x�v�Z
	backGroundAlpha_ += ALPHA_ADD_VALUE * sign_;

	//�͈͊O�̎��̌v�Z
	if (backGroundAlpha_ > 1)
	{
		sign_ *= -1;
		ARGUMENT_INITIALIZE(backGroundAlpha_, 1);
	}
	if (backGroundAlpha_ < ZERO)
	{
		sign_ *= -1;
		ARGUMENT_INITIALIZE(backGroundAlpha_, ZERO);
	}
}