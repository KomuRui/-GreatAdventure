#include "NewFileUI.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Engine/ResourceManager/Easing.h"
#include "../../Engine/ResourceManager/Text.h"
#include "../../Engine/Component/EasingMove.h"
#include "../../Manager/ButtonManager/ButtonManager.h"
#include "IconSelectUI.h"

//�萔
namespace
{
	static const XMFLOAT3 EASING_ONE_BEFORE_POS = { 2,0,0 }; //�C�[�W���O1��ڂ̈ړ��O�|�W�V����
	static const XMFLOAT3 EASING_ONE_AFTER_POS =  { 0,0,0 }; //�C�[�W���O1��ڂ̈ړ���|�W�V����
	static const XMFLOAT3 EASING_TWO_BEFORE_POS = { 0,0,0 }; //�C�[�W���O2��ڂ̈ړ��O�|�W�V����
	static const XMFLOAT3 EASING_TWO_AFTER_POS = { -2,0,0 }; //�C�[�W���O2��ڂ̈ړ���|�W�V����

	static const float EASING_MOVE_TIME = 2.0f; //�C�[�W���O�̈ړ��ɂ����鎞��
}

//�R���X�g���N�^
NewFileUI::NewFileUI(GameObject* parent)
	: GameObject(parent, "NewFileUI"), isEasingChangeIcon_(false), isEasingChangeReturn_(false)
{}

//������
void NewFileUI::Initialize()
{
	////////////////////////////////�C�[�W���O�̏����ݒ�////////////////////////////////////

	ARGUMENT_INITIALIZE(pEasingMove_, new EasingMove(&transform_.position_, EASING_ONE_BEFORE_POS, EASING_ONE_AFTER_POS, EASING_MOVE_TIME, Easing::OutQuart))

	////////////////////////////////transform////////////////////////////////////

	ARGUMENT_INITIALIZE(transform_.position_, EASING_ONE_BEFORE_POS);

	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/UserSelect/StageInformation/NewFileUI.txt");
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void NewFileUI::StartUpdate()
{
}

//�X�V
void NewFileUI::Update()
{
	//�C�[�W���O�̓������Ō�܂ŏI����Ă��邩�A�C�R���֍s���̂Ȃ�
	if (pEasingMove_->Move() && isEasingChangeIcon_)
	{
		//���Z�b�g����
		ButtonManager::Reset();

		//�A�C�R���I��UI�쐬
		Instantiate<IconSelectUI>(GetParent());

		//�폜
		KillMe();
	}

	//�C�[�W���O�̓������Ō�܂ŏI����Ă��邩���ɖ߂�̂Ȃ�
	if (pEasingMove_->Move() && isEasingChangeReturn_)
	{
		//���Z�b�g����
		ButtonManager::Reset();

		//�폜
		KillMe();
	}
}

//�`��
void NewFileUI::Draw()
{

}

//���
void NewFileUI::Release()
{
}

//�C�[�W���O�̓������ύX���ăA�C�R���I����
void NewFileUI::ChangeEasingMoveIcon()
{
	//�ύX����Ă���ꍇ�͂��̐�̏��������Ȃ�
	if (isEasingChangeIcon_) return;

	//�ύX�����ɕύX
	ARGUMENT_INITIALIZE(isEasingChangeIcon_, true);

	//���ύX
	pEasingMove_->Reset(&transform_.position_, EASING_TWO_BEFORE_POS, EASING_TWO_AFTER_POS, EASING_MOVE_TIME, Easing::InQuart);
}

//�C�[�W���O�̓������ύX���Č��Ƀ��f��
void NewFileUI::ChangeEasingMoveReturn()
{
	//�ύX����Ă���ꍇ�͂��̐�̏��������Ȃ�
	if (isEasingChangeReturn_) return;

	//�ύX�����ɕύX
	ARGUMENT_INITIALIZE(isEasingChangeReturn_, true);

	//���ύX
	pEasingMove_->Reset(&transform_.position_, EASING_TWO_BEFORE_POS, EASING_TWO_AFTER_POS, EASING_MOVE_TIME, Easing::OutQuart);
}