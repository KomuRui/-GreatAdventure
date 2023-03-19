#include "UserGameStartUI.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Engine/ResourceManager/Easing.h"
#include "../../Engine/ResourceManager/Text.h"
#include "../../Engine/Component/EasingMove.h"
#include "../../Manager/ButtonManager/ButtonManager.h"
#include "../../OtherObject/UserInfomation.h"
#include "IconSelectUI.h"

//�R���X�g���N�^
UserGameStartUI::UserGameStartUI(GameObject* parent)
	: GameObject(parent, "UserGameStartUI"), pCreateStage_(new CreateStage)
{}

//������
void UserGameStartUI::Initialize()
{
	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	pCreateStage_->LoadFileCreateStage(this, "Stage/UserSelect/StageInformation/UserGameStartUI.txt");

	/////////////////�摜�E�e�N�X�`���̃��[�h///////////////////

	//�摜
	hCoinPict_ = Image::Load("Image/Coin/Coin.png");
	assert(hCoinPict_ >= ZERO);
	hStagePict_ = Image::Load("Image/UserSelect/Stage.png");
	assert(hStagePict_ >= ZERO);
	hCrossPict_ = Image::Load("Image/Coin/Cross.png");
	assert(hCrossPict_ >= ZERO);

	//�e�L�X�g�̏�����
	ARGUMENT_INITIALIZE(pText_, new Text);
	pText_->Initialize("Text/NumberFont.png", 128, 256, 10);
}


//�X�V
void UserGameStartUI::Update()
{
}

//�`��
void UserGameStartUI::Draw()
{
	//�R�C��
	Transform t;
	ARGUMENT_INITIALIZE(t.scale_.x, 0.6f);
	ARGUMENT_INITIALIZE(t.scale_.y, 0.6f);
	ARGUMENT_INITIALIZE(t.position_.x, 0.30f);
	ARGUMENT_INITIALIZE(t.position_.y, 0.40f);
	Image::SetTransform(hCoinPict_, t);
	Image::Draw(hCoinPict_);

	//�X�e�[�W
	ARGUMENT_INITIALIZE(t.position_.x, 0.30f);
	ARGUMENT_INITIALIZE(t.position_.y, 0.7f);
	Image::SetTransform(hStagePict_, t);
	Image::Draw(hStagePict_);

	//�N���X
	ARGUMENT_INITIALIZE(t.position_.x, 0.45f);
	ARGUMENT_INITIALIZE(t.position_.y, 0.40f);
	Image::SetTransform(hCrossPict_, t);
	Image::Draw(hCrossPict_);
	ARGUMENT_INITIALIZE(t.position_.x, 0.45f);
	ARGUMENT_INITIALIZE(t.position_.y, 0.7f);
	Image::SetTransform(hCrossPict_, t);
	Image::Draw(hCrossPict_);

	//�e�L�X�g
	pText_->NumberDraw(1500, 315, UserInfomation::GetCoinNum(), 0.8f, 0.02f);
	pText_->NumberDraw(1500, 155, UserInfomation::GetStageReleaseNum(), 0.8f, 0.01f);
}