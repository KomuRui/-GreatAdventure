#include "PauseBackTitleButton.h"
#include "../../../../Engine/ResourceManager/Global.h"
#include "../../../../Engine/ResourceManager/Image.h"
#include "../../../../Manager/GameManager/GameManager.h"


//�R���X�g���N�^
PauseBackTitleButton::PauseBackTitleButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1),hSelectPict2_(-1)
{}

//������
void PauseBackTitleButton::ChildInitialize()
{
	////////////////////////////////�摜�̏����ݒ�////////////////////////////////////

	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/Pause/BackTitle_Select.png"));
	ARGUMENT_INITIALIZE(hSelectPict2_, Image::Load("Image/Pause/BackTitle_Explain.png"));
}

//�`��
void PauseBackTitleButton::ChildDraw()
{
	//�I������Ă���̂Ȃ�
	if (isSelect_)
	{
		Transform t;
		Image::SetTransform(hSelectPict2_, t);
		Image::Draw(hSelectPict2_);
	}
}

//�{�^���������ꂽ�牽���邩
void PauseBackTitleButton::IsButtonPush()
{
	//�|�[�Y�폜
	GameManager::PauseDelete();

	//���[�h�`������Ȃ�
	GameManager::GetpSceneManager()->SetLoadDrawFlag(false);

	//�^�C�g���V�[����
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TITLE);
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void PauseBackTitleButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void PauseBackTitleButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }
