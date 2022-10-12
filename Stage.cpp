#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), hModel_(-1)
{

}

//������
void Stage::Initialize()
{

	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("first_planet.fbx");
	assert(hModel_ >= 0);

	///////////////transform///////////////////

}

//�X�V
void Stage::Update()
{

	//A�{�^������������Play�V�[���ֈڍs
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
	}

	//Pad���Ȃ��Ƃ��Ɉڍs����p
	if (Input::IsKeyDown(DIK_RETURN))
	{
	}

}

//�`��
void Stage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Stage::Release()
{
}

void Stage::StartUpdate()
{
}
