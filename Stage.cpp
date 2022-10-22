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

	hModel_ = Model::Load("first_Stage.fbx");
	assert(hModel_ >= 0);

	///////////////transform///////////////////

}

//�X�V
void Stage::Update()
{
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
