#include "UserGameStartButton.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/ResourceManager/Time.h"
#include "../../../Engine/ResourceManager/Easing.h"
#include "../../../Engine/Component/EasingMove.h"
#include "../../../OtherObject/UserInfomation.h"
#include "../../../Manager/GameManager/GameManager.h"
#include "../../../Manager/CoinManager/CoinManager.h"
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

	ARGUMENT_INITIALIZE(easingAfterPos_, XMFLOAT3(0.5, -0.5, ZERO));
	ARGUMENT_INITIALIZE(easingBeforePos_,XMFLOAT3(easingAfterPos_.x, easingAfterPos_.y - 1.0f, easingAfterPos_.z));
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
	//����X�e�[�W�̐����擾
	int num = UserInfomation::GetStageReleaseNum();

	//����1�Ȃ�`���[�g���A���V�[������X�^�[�g
	if (num == 1)
		GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TUTORIAL1);
	//����ȊO�Ȃ�HomeScene����X�^�[�g
	else
		GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_HOME);

	//�R�C���̑������Z�b�g
	CoinManager::SetCoinNum(UserInfomation::GetCoinNum());

}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void UserGameStartButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void UserGameStartButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }

//�C�[�W���O���Z�b�g
void UserGameStartButton::ResetEasing() { pEasingMove_->Reset(&transform_.position_, easingAfterPos_, easingBeforePos_, EASING_MOVE_TIME, Easing::OutQuart);}