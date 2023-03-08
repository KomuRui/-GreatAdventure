#include "Water.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/ResourceManager/VFX.h"

//�R���X�g���N�^
Water::Water(GameObject* parent, std::string modelFilePath_, std::string name)
	:GameObject(parent, name), hModel_(-1),filePath_(modelFilePath_)
{
}

//������
void Water::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load(filePath_);
	assert(hModel_ >= ZERO);

	Model::SetShederType(hModel_,Direct3D::SHADER_NORMALMAP);
}

//�X�V
void Water::Update()
{
	static float scroll = 0.0f;
	scroll += 0.002f;

	Model::SetUvScroll(hModel_, scroll);
}

//�`��
void Water::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void Water::Release()
{
}
