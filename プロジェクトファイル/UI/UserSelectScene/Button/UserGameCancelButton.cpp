#include "UserGameCancelButton.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/ResourceManager/Time.h"
#include "../../../Engine/ResourceManager/Easing.h"
#include "../../../Engine/Component/EasingMove.h"
#include "../../../OtherObject/SelectPlanetController.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "UserGameStartButton.h"
#include "../NewFileUI.h"

//�萔
namespace
{
	static const float EASING_MOVE_TIME = 2.0f; //�C�[�W���O�̈ړ��ɂ����鎞��
}

//�R���X�g���N�^
UserGameCancelButton::UserGameCancelButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//������
void UserGameCancelButton::ChildInitialize()
{
	////////////////////////////////�C�[�W���O�̏����ݒ�////////////////////////////////////

	ARGUMENT_INITIALIZE(easingAfterPos_, XMFLOAT3(-0.5,-0.5,ZERO));
	ARGUMENT_INITIALIZE(easingBeforePos_, XMFLOAT3(easingAfterPos_.x, easingAfterPos_.y - 1.0f, easingAfterPos_.z));
	ARGUMENT_INITIALIZE(pEasingMove_, new EasingMove(&transform_.position_, easingBeforePos_, easingAfterPos_, EASING_MOVE_TIME, Easing::OutQuart))

	////////////////////////////////�摜�̏����ݒ�////////////////////////////////////
		
	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/Cancel_Select.png"));
}

//�X�V
void UserGameCancelButton::ChildButtonUpdate()
{
	//�ړ�
	pEasingMove_->Move();
}

//�{�^���������ꂽ�牽���邩
void UserGameCancelButton::IsButtonPush()
{
	//�I�𒆂ɖ߂��ԂɃZ�b�g
	SelectPlanetController::SetStatus(SelectPlanetStatus::BackSelecting);

	//���Z�b�g����
	ButtonManager::Reset();

	//�C�[�W���O���Z�b�g
	((UserGameStartButton*)FindObject("UserGameStartButton"))->ResetEasing();
	pEasingMove_->Reset(&transform_.position_, easingAfterPos_, easingBeforePos_, EASING_MOVE_TIME, Easing::OutQuart);
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void UserGameCancelButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void UserGameCancelButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }