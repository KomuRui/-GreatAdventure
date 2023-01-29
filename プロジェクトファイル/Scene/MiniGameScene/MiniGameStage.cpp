#include "MiniGameStage.h"
#include "../../Engine/Model.h"
#include "../../Engine/Light.h"
#include "../../Engine/Camera.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/CreateStage.h"

//�R���X�g���N�^
MiniGameStage::MiniGameStage(GameObject* parent)
	:Stage(parent, "MiniGameStage")
{
	//��p
	ARGUMENT_INITIALIZE(fieldAngle_, 45);

	//���C�g�̋���
	ARGUMENT_INITIALIZE(lightIntensity_,4);
}

//������
void MiniGameStage::Initialize()
{
	/////////////////////���f���f�[�^�̃��[�h///////////////////////

	hModel_[Base] = Model::Load("Stage/MiniGame/StraightStage.fbx");
	hModel_[PolyModel] = Model::Load("Stage/MiniGame/StraightStage.fbx");

	///////////////////////////�e��ݒ�/////////////////////////////

	//���C�̔����Base�����ꂽ���̂�true�ɂ��Ă���
	Model::SetRayFlag(hModel_[Base], true);

	//���邳��ݒ�
	Model::SetBrightness(hModel_[Base], 1.0f);

	//PolyModel�𓧖��ɐݒ�(�����m�F���邽�߂����Ɏg������)
	Model::SetAlpha(hModel_[PolyModel], ZERO);

	//��p
	Camera::SetFieldAngle(fieldAngle_);

	//�J�����̏�x�N�g��
	Camera::SetUpDirection(UP_VECTOR);

	//���C�g�̋���
	Light::SetPlayerIntensity(lightIntensity_);

	//Player�̏����ʒu
	ARGUMENT_INITIALIZE(pos_,XMFLOAT3(ZERO,ZERO,ZERO));

	//3D�Ȃ̂�true�ɂ���
	ARGUMENT_INITIALIZE(threeDflag_,true);

	//���̎g�p���Ă���̂�true
	ARGUMENT_INITIALIZE(circleFlag_,true);

}

//�X�V
void MiniGameStage::Update()
{
}

//�`��
void MiniGameStage::Draw()
{
	Model::SetTransform(hModel_[Base], transform_);
	Model::Draw(hModel_[Base]);
}

//���
void MiniGameStage::Release()
{
}
