#include "UserGameStartButton.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/ResourceManager/Time.h"
#include "../../../Engine/ResourceManager/Easing.h"
#include "../../../Engine/Component/EasingMove.h"
#include "../../../Manager/GameManager/GameManager.h"
#include "../NewFileUI.h"

//�萔
namespace
{
	static const float EASING_MOVE_TIME = 2.0f; //�C�[�W���O�̈ړ��ɂ����鎞��
}

//�R���X�g���N�^
UserGameStartButton::UserGameStartButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//������
void UserGameStartButton::ChildInitialize()
{
	////////////////////////////////�C�[�W���O�̏����ݒ�////////////////////////////////////

	ARGUMENT_INITIALIZE(easingAfterPos_, transform_.position_);
	ARGUMENT_INITIALIZE(easingBeforePos_,XMFLOAT3(transform_.position_.x,transform_.position_.y - 1.0f,transform_.position_.z));
	ARGUMENT_INITIALIZE(pEasingMove_, new EasingMove(&transform_.position_, easingBeforePos_, easingAfterPos_, EASING_MOVE_TIME, Easing::OutQuart))

	////////////////////////////////�摜�̏����ݒ�////////////////////////////////////

	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/Ok_Select.png"));
}

//�X�V
void UserGameStartButton::ChildButtonUpdate()
{
	//�ړ�
	pEasingMove_->Move();
}

//�{�^���������ꂽ�牽���邩
void UserGameStartButton::IsButtonPush()
{
	//�V�[���`�F���W
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TUTORIAL1);
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void UserGameStartButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void UserGameStartButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }