#include "TutorialStage1.h"
#include "../../Engine/Model.h"
#include "../../Engine/ImGuiSet.h"
#include "../../Engine/Light.h"
#include "../../Engine/Camera.h"
#include "../../Gimmick/Warp.h"

//�R���X�g���N�^
TutorialStage1::TutorialStage1(GameObject* parent)
	:Stage(parent,"TutorialStage1")
{
	//��p
	fieldAngle_ = 45;

	//���C�g�̋���
	lightIntensity_ = 3;
}

//������
void TutorialStage1::Initialize()
{
	/////////////////�X�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	//�X�e�[�W�쐬
	ImGuiSet* a = Instantiate<ImGuiSet>(this);
	a->CreateStage("Stage/Tutorial/StageInformation/TutorialStage1.txt");

	//���[�v�̃V�[���J�ڐ�����߂Ă���
	Warp* pWarp = (Warp*)FindObject("Warp");
	pWarp->SetSceneId(SCENE_ID_TUTORIAL2);

	//�e�u���b�N�̔z�u���擾
	tBlock_ = a->GetTransformBlock();

	/////////////////////���f���f�[�^�̃��[�h///////////////////////

	hModel_[Base] = Model::Load("Stage/Tutorial/first_1.fbx");
	hModel_[Space] = Model::Load("Stage/SpaceModel/Space.fbx");

	///////////////////////////�e��ݒ�/////////////////////////////

	//���C�̔����Base�����ꂽ���̂�true�ɂ��Ă���
	Model::SetRayFlag(hModel_[Base], true);

	//Space���f���̖��邳�ݒ�
	Model::SetBrightness(hModel_[Space], 0.5);

	//��p
	Camera::SetFieldAngle(fieldAngle_);

	//�J�����̏�x�N�g��
	Camera::SetUpDirection(XMVectorSet(0, 1, 0, 0));

	//���C�g�̋���
	Light::SetIntensity(lightIntensity_);

	//Player�̏����ʒu
	pos_ = { 2,2,0 };

	//�^��2D�Ȃ̂�false�ɐݒ肵�Ă���
	threeDflag_ = false;

	//���̎g�p���Ă��Ȃ��̂�false
	circleFlag_ = false;

}

//�X�V
void TutorialStage1::Update()
{
	tSpace_.rotate_.y += 0.1;
}

//�`��
void TutorialStage1::Draw()
{
	Model::SetTransform(hModel_[Base], transform_);
	Model::Draw(hModel_[Base]);

	Model::SetTransform(hModel_[Space], tSpace_);
	Model::Draw(hModel_[Space]);
}

//���
void TutorialStage1::Release()
{
}
