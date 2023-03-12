#include "BaseSelectStage.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"

//�R���X�g���N�^
BaseSelectStage::BaseSelectStage(GameObject* parent)
	:GameObject(parent, "BaseSelectStage"), hModel_(-1)
{
}

//������
void BaseSelectStage::Initialize()
{
	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Stage/StageSelect/Base.fbx");
	assert(hModel_ >= ZERO);
}

//�X�V
void BaseSelectStage::Update()
{
}

//�`��
void BaseSelectStage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

