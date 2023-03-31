#include "TitleModelPlayer.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/GameObject/Camera.h"
#include "../Engine/DirectX/Input.h"

//�萔
namespace
{
	static const int START_FRAME = 1;	  //�J�n�t���[��
	static const int END_FRAME = 60;      //�I���t���[��
	static const float ANIM_SPEED = 1.0f; //�A�j���[�V�����̍Đ����x
}

//�R���X�g���N�^
TitleModelPlayer::TitleModelPlayer(GameObject* parent)
	:GameObject(parent, "TitleModelPlayer"), hModel_(-1)
{
}

//������
void TitleModelPlayer::Initialize()
{
	//���f���f�[�^���[�h
	ARGUMENT_INITIALIZE(pathName_, "MainCharacter/Star_Main_Character.fbx");
	hModel_ = Model::Load(pathName_);
	assert(hModel_ >= ZERO);

	//�A�j���[�V����
	Model::SetAnimFlag(hModel_, true);
	Model::SetAnimFrame(hModel_, START_FRAME, END_FRAME, ANIM_SPEED);
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void TitleModelPlayer::StartUpdate()
{
}

//�X�V
void TitleModelPlayer::Update()
{
}

//�`��
void TitleModelPlayer::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void TitleModelPlayer::Release()
{
}
