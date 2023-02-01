#include "MiniGameLevelSelectStage.h"
#include "../../Engine/Model.h"
#include "../../Engine/Light.h"
#include "../../Engine/Camera.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/CreateStage.h"

//�R���X�g���N�^
MiniGameLevelSelectStage::MiniGameLevelSelectStage(GameObject* parent)
	:Stage(parent, "MiniGameLevelSelectStage")
{
	//��p
	fieldAngle_ = 100;

	//���C�g�̋���
	lightIntensity_ = 3;
}

//������
void MiniGameLevelSelectStage::Initialize()
{

	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	//////�X�e�[�W�쐬
	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/MiniGameLevelSelect/StageInformation/MiniGameLevelSelectStage.txt");

	//���[�v�̃V�[���J�ڐ�����߂Ă���
	Warp* pWarp = (Warp*)FindObject("Warp");
	pWarp->SetSceneId(SCENE_ID_HOME);

	////�e�u���b�N�̔z�u���擾
	tBlock_ = pCreateStage_->GetTransformBlock();

	/////////////////////���f���f�[�^�̃��[�h///////////////////////

	hModel_[Base] = Model::Load("Stage/MiniGameLevelSelect/MiniGameLevelSelectStage.fbx");
	hModel_[Space] = Model::Load("Stage/SpaceModel/Space.fbx");
	hModel_[PolyModel] = Model::Load("Stage/MiniGameLevelSelect/MiniGameLevelSelectStage.fbx");

	///////////////////////////�e��ݒ�/////////////////////////////

	//���C�̔����Base�����ꂽ���̂�true�ɂ��Ă���
	Model::SetRayFlag(hModel_[Base], true);

	//Space���f���̖��邳�ݒ�
	Model::SetBrightness(hModel_[Space], 0.5);

	//PolyModel�𓧖��ɐݒ�(�����m�F���邽�߂����Ɏg������)
	Model::SetAlpha(hModel_[PolyModel], ZERO);

	//��p
	Camera::SetFieldAngle(fieldAngle_);

	//�J�����̏�x�N�g��
	Camera::SetUpDirection(UP_VECTOR);

	//���C�g�̋���
	Light::SetPlayerIntensity(lightIntensity_);

	//Warp�̈ړ���
	warpPos_ = { 0, 3, 0 };

	//Player�̏����ʒu
	pos_ = { 0,203,0 };

	//3D�Ȃ̂�true�ɂ���
	threeDflag_ = true;

	//���̎g�p���Ă���̂�true
	circleFlag_ = true;

}

//�X�V
void MiniGameLevelSelectStage::Update()
{
	tSpace_.rotate_.y += 0.2;
}

//�`��
void MiniGameLevelSelectStage::Draw()
{
	Model::SetTransform(hModel_[Base], transform_);
	Model::Draw(hModel_[Base]);

	Model::SetTransform(hModel_[Space], tSpace_);
	Model::Draw(hModel_[Space]);
}

//���
void MiniGameLevelSelectStage::Release()
{
}
