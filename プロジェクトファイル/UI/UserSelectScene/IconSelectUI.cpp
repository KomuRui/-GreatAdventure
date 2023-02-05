#include "IconSelectUI.h"
#include "../../Engine/CreateStage.h"
#include "../../Engine/Easing.h"
#include "../../Engine/Text.h"
#include "../../Engine/Component/EasingMove.h"
#include "../../OtherObject/SelectPlanetController.h"
#include "../../Manager/ButtonManager/ButtonManager.h"

//�萔
namespace
{
	static const XMFLOAT3 EASING_ONE_BEFORE_POS = { 2,0,0 }; //�C�[�W���O1��ڂ̈ړ��O�|�W�V����
	static const XMFLOAT3 EASING_ONE_AFTER_POS = { 0,0,0 };  //�C�[�W���O1��ڂ̈ړ��O�|�W�V����
	static const XMFLOAT3 EASING_TWO_BEFORE_POS = { 0,0,0 }; //�C�[�W���O2��ڂ̈ړ��O�|�W�V����
	static const XMFLOAT3 EASING_TWO_AFTER_POS = { -2,0,0 };  //�C�[�W���O2��ڂ̈ړ��O�|�W�V����

	static const float EASING_MOVE_TIME = 2.0f; //�C�[�W���O�̈ړ��ɂ����鎞��
}

//�R���X�g���N�^
IconSelectUI::IconSelectUI(GameObject* parent)
	: GameObject(parent, "IconSelectUI"), isEasingChange_(false), iconModelPath_("")
{}

//������
void IconSelectUI::Initialize()
{

	////////////////////////////////�C�[�W���O�̏����ݒ�////////////////////////////////////

	ARGUMENT_INITIALIZE(pEasingMove_, new EasingMove(&transform_.position_, EASING_ONE_BEFORE_POS, EASING_ONE_AFTER_POS, EASING_MOVE_TIME, Easing::OutQuart))

	////////////////////////////////transform////////////////////////////////////

	ARGUMENT_INITIALIZE(transform_.position_, EASING_ONE_BEFORE_POS);

	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/UserSelect/StageInformation/IconSelectUI.txt");
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void IconSelectUI::StartUpdate()
{
}

//�X�V
void IconSelectUI::Update()
{
	//�C�[�W���O�̓������Ō�܂ŏI����Ă��邩�C�[�W���O�̏������ł��ύX���Ă�����
	if (pEasingMove_->Move() && isEasingChange_)
	{
		//���f���p�X��ݒ�
		SelectPlanetController::SetIconModelPath(iconModelPath_);

		//�폜
		KillMe();
	}
}

//�`��
void IconSelectUI::Draw()
{

}

//���
void IconSelectUI::Release()
{
}

//�C�[�W���O�̓������ύX
void IconSelectUI::ChangeEasingMove(std::string path)
{
	//�ύX����Ă���ꍇ�͂��̐�̏��������Ȃ�
	if (isEasingChange_) return;

	//�A�C�R���̃��f���p�X�ۑ�
	ARGUMENT_INITIALIZE(iconModelPath_, path);

	//�ύX�����ɕύX
	ARGUMENT_INITIALIZE(isEasingChange_, true);

	//���ύX
	pEasingMove_->Reset(&transform_.position_, EASING_TWO_BEFORE_POS, EASING_TWO_AFTER_POS, EASING_MOVE_TIME, Easing::InQuart);
}