#include "ShootingStar.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/ResourceManager/VFX.h"

//�萔
namespace
{
	static const XMFLOAT3 MOVE_ADD_VALUE = { 0.3f,0.2f,0.3f };
	static const float ROTATION_ADD_VALUE = 5.5f;
	static const float KILL_POSY_VALUE = -10;
}

//�R���X�g���N�^
ShootingStar::ShootingStar(GameObject* parent, std::string modelFilePath_, std::string name)
	:GameObject(parent, name), hModel_(-1), filePath_(modelFilePath_)
{
}

ShootingStar::ShootingStar(GameObject* parent)
	:GameObject(parent,"ShootingStar"), hModel_(-1), filePath_("Stage/Last/SootingStar.fbx")
{
}

//������
void ShootingStar::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load(filePath_);
	assert(hModel_ >= ZERO);

	//���邳�ύX
	Model::SetBrightness(hModel_, 1.0f);

	//�e�N�X�`�����[�h
	ARGUMENT_INITIALIZE(pBaseLine_,new PolyLine);
	pBaseLine_->Load("Image/Effect/tex.png");

	//�e�|�W�V����������
	pBaseLine_->AddPosition(transform_.position_);
	pBaseLine_->SetColor({ 1,1,ZERO });
	pBaseLine_->SetLengh(80);
}

//�X�V
void ShootingStar::Update()
{
	//�ړ�
	ARGUMENT_INITIALIZE(transform_.position_,SubTract(transform_.position_, MOVE_ADD_VALUE));

	//��]
	transform_.rotate_.y += ROTATION_ADD_VALUE;

	//�|�W�V�����ǉ�
	pBaseLine_->AddPosition(transform_.position_);

	//�|�W�V�������萔�l������������΍폜
	if (transform_.position_.y < KILL_POSY_VALUE)KillMe();
}

//�`��
void ShootingStar::Draw()
{
	//���f���`��
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	//�|�����C����`��
	pBaseLine_->Draw();
}

//���
void ShootingStar::Release()
{
	SAFE_RELEASE(pBaseLine_);
	SAFE_DELETE_ARRAY(pBaseLine_);
}
