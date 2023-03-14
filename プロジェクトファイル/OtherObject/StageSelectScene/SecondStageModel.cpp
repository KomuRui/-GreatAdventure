#include "SecondStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Manager/GameManager/GameManager.h"
#include "BaseSelectStage.h"
#include "../../Engine/ResourceManager/Fade.h"
//�萔
namespace
{
	static const XMFLOAT3 ROTATION_MODEL_POSITION = { -39.5f, ZERO, 1.2f }; //��]���f���̃|�W�V����
	static const float ROTATION_ADD_VALUE = 0.30f;	//��]���鎞�̉��Z����l
	static const float CALL_TIMEMETHOD_TIME = 3.0f; //�^�C�����\�b�h���ĂԎ���
}

//�R���X�g���N�^
SecondStageModel::SecondStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent,ModelPath,name, "Image/StageSelect/SecondStage.png"), hRotationModel_(-1)
{
}

//������
void SecondStageModel::ChildInitialize()
{
	///////////////�`�F�b�N�|�C���g���f���ǉ�///////////////////

	((BaseSelectStage*)GetParent())->SetCheckPointModel(static_cast<int>(CheckPoint::SECOND), this);

	///////////////firstStage�͏�ɉ����Ԃ�///////////////////

	ARGUMENT_INITIALIZE(isStageRelease_, true);

	///////////////���f���f�[�^�̃��[�h///////////////////

	hRotationModel_ = Model::Load("Stage/StageSelect/second/secondStageModel2.fbx");
	assert(hRotationModel_ >= ZERO);

	/////////////////���邳�ݒ�/////////////////

	Model::SetBrightness(hRotationModel_, 1.0f);

	//////////////////�g�����X�t�H�[��������/////////////////////

	ARGUMENT_INITIALIZE(tRotation_.position_, ROTATION_MODEL_POSITION);
	ARGUMENT_INITIALIZE(tRotation_.pParent_, transform_.pParent_);
}

//�X�V
void SecondStageModel::ChildUpdate()
{
	//��]
	tRotation_.rotate_.y += ROTATION_ADD_VALUE;
}

//�`��
void SecondStageModel::ChildDraw()
{
	Model::SetTransform(hRotationModel_, tRotation_);
	Model::Draw(hRotationModel_);
}

//�I������Ă��鎞�Ƀ{�^���������ꂽ��
void SecondStageModel::SelectButtonPush()
{
	//���łɃt�F�[�h�A�E�g���Ă����炱�̐�͏������Ȃ�
	if (Fade::GetFadeStatus() == FADE_CIRCLE_OUT)return;

	//�t�F�[�h�A�E�g
	Fade::SetFadeStatus(FADE_CIRCLE_OUT);

	//�萔�b��ɌĂ�
	SetTimeMethod(CALL_TIMEMETHOD_TIME);
}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void SecondStageModel::TimeMethod()
{
	//�V�[���`�F���W
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_WORLD1);
}