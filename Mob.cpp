#include "Mob.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
Mob::Mob(GameObject* parent, std::string modelPath)
	: GameObject(parent, "Mob"), hModel_(-1), ModelNamePath_(modelPath)
{

}

//������
void Mob::Initialize()
{

	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= 0);

	///////////////transform///////////////////

}

//�X�V
void Mob::Update()
{
}

//�`��
void Mob::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Mob::Release()
{
}

void Mob::StartUpdate()
{
}
