#include "NewFileCancelButton.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/ResourceManager/Time.h"
#include "../../../Engine/ResourceManager/Easing.h"
#include "../../../OtherObject/SelectPlanetController.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../NewFileUI.h"

//�R���X�g���N�^
NewFileCancelButton::NewFileCancelButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath,name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//������
void NewFileCancelButton::ChildInitialize()
{
	//�Z���N�g�摜�̔ԍ��擾
	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);

	//���[�h
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/Cancel_Select.png"));
}

//�{�^���������ꂽ�牽���邩
void NewFileCancelButton::IsButtonPush()
{
	//�I�𒆂ɖ߂��ԂɃZ�b�g
	SelectPlanetController::SetStatus(SelectPlanetStatus::BackSelecting);
	SelectPlanetController::ResetPlanetMove();

	//���Z�b�g����
	ButtonManager::Reset();

	//�I����ԉ���
	ARGUMENT_INITIALIZE(isSelect_, false);

	//���֖߂�Ɛe�ɓ`����
	((NewFileUI*)GetParent())->ChangeEasingMoveReturn();
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void NewFileCancelButton::IsButtonSelect(){ ARGUMENT_INITIALIZE(hPict_, hSelectPict_);}

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void NewFileCancelButton::IsButtonSelectRelease(){ ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_);}