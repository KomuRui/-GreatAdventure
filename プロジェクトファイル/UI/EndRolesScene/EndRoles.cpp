#include "EndRoles.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Time.h"

//�萔
namespace
{
	static const float RETURN_IMAGE_X_POS = 0.6f;  //�߂�摜�̏���X�ʒu
	static const float RETURN_IMAGE_Y_POS = -0.7f; //�߂�摜�̏���Y�ʒu
	static const float MOVE_RANGE = 13.6f;         //�ړ��ł���͈�
	static const float START_Y_POS = -12.0f;	   //����
	static const float MOVE_ADD_VALUE = 0.005f;    //�ړ�����Ƃ��̉��Z��
	static const float START_TIME = 3.0f;          //�J�n���鎞��
}

//�R���X�g���N�^
EndRoles::EndRoles(GameObject* parent, std::string modelPath, std::string name)
	: ImageBase(parent, modelPath, name),hReturnImage_((int)ZERO), hTime_((int)ZERO), isMove_(false)
{
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void EndRoles::ChildStartUpdate()
{
	//�摜���[�h
	hReturnImage_ = Image::Load("Image/EndRole/ReturnTitle.png");
	assert(hReturnImage_ >= ZERO);

	//�^�C�}�[�ǉ�
	ARGUMENT_INITIALIZE(hTime_,Time::Add());

	//�^�C�}�[�X�^�[�g
	Time::UnLock(hTime_);

	//�g�����X�t�H�[���ݒ�
	ARGUMENT_INITIALIZE(tReturnImage_.position_.x,RETURN_IMAGE_X_POS);
	ARGUMENT_INITIALIZE(tReturnImage_.position_.y,RETURN_IMAGE_Y_POS);

	//�����ʒu
	ARGUMENT_INITIALIZE(transform_.position_.y,START_Y_POS);
}

//�X�V
void EndRoles::ChildUpdate()
{
	//�萔�b�ȏソ���Ă����瓮����
	if (Time::GetTimef(hTime_) >= START_TIME) ARGUMENT_INITIALIZE(isMove_, true);

	//�����̂Ȃ�
	if (isMove_)
	{
		//�ړ��͈͓��Ȃ�ړ�
		if (transform_.position_.y < MOVE_RANGE) transform_.position_.y += MOVE_ADD_VALUE;

		//�ړ��͈͊O��AButton�������Ȃ�^�C�g���ɖ߂�
		if (transform_.position_.y >= MOVE_RANGE && Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
		{
			//���[�h��`�悵�Ȃ�
			GameManager::GetpSceneManager()->SetLoadDrawFlag(false);

			//�V�[���ύX
			GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TITLE);
		}
	}
	
}

//�`��
void EndRoles::ChildDraw()
{
	//�ړ��͈͊O�Ȃ�`��
	if (transform_.position_.y >= MOVE_RANGE)
	{
		Image::SetTransform(hReturnImage_, tReturnImage_);
		Image::Draw(hReturnImage_);
	}
}