#include "Mob.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
Mob::Mob(GameObject* parent, std::string modelPath,std::string name)
	: GameObject(parent, name), hModel_(-1), ModelNamePath_(modelPath)
{
}

//������
void Mob::Initialize()
{
	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= 0);

	SetEmission();

	///////////////���X����Transform.Rotate���g��Ȃ�����Flag��True�ɂ���///////////////////

	transform_.mFlag_ = true;

	////////////////////�p����ŐV���ɏ������̓��e�ǉ�����p///////////////////////

	ChildInitialize();
}

//�X�V�̑O�Ɉ�񂾂��Ă΂��֐�
void Mob::StartUpdate()
{
	ChildStartUpdate();
}

//�X�V
void Mob::Update()
{
	//�p���悲�Ƃɓ�����ς����
	UpdateMove();
}

//�`��
void Mob::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	ChildDraw();
}

//�J��
void Mob::Release()
{
}




