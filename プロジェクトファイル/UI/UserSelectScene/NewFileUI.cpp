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
	: GameObject(parent, "NewFileUI"), isEasingChange_(false)
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
	//�C�[�W���O�̓������Ō�܂ŏI����Ă��邩�C�[�W���O�̏������ł��ύX���Ă�����
	if (pEasingMove_->Move() && isEasingChange_)
	{
		//���Z�b�g����
		ButtonManager::Reset();

		//�A�C�R���I��UI�쐬
		Instantiate<IconSelectUI>(GetParent());

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

//�C�[�W���O�̓������ύX
void NewFileUI::ChangeEasingMove()
{
	//�ύX����Ă���ꍇ�͂��̐�̏��������Ȃ�
	if (isEasingChange_) return;

	//�ύX�����ɕύX
	ARGUMENT_INITIALIZE(isEasingChange_, true);

	//���ύX
	pEasingMove_->Reset(&transform_.position_, EASING_TWO_BEFORE_POS, EASING_TWO_AFTER_POS, EASING_MOVE_TIME, Easing::InQuart);
}