#include "FourthStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Manager/GameManager/GameManager.h"
#include "BaseSelectStage.h"
#include "../../Engine/ResourceManager/Fade.h"

//�萔
namespace
{
	static const XMFLOAT4 INITIALIZE_AMBIENT = { -0.6f, -0.6f, -0.6f, ZERO }; //�����A���r�G���g�l
	static const float ROTATION_ADD_VALUE = 0.35f;	//��]���鎞�̉��Z����l
	static const float CALL_TIMEMETHOD_TIME = 3.0f; //�^�C�����\�b�h���ĂԎ���
}

//�R���X�g���N�^
FourthStageModel::FourthStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent, ModelPath,name, "Image/StageSelect/FirstStage.png")
{
}

//������
void FourthStageModel::ChildInitialize()
{
	//�`�F�b�N�|�C���g�ǉ�
	((BaseSelectStage*)GetParent())->SetCheckPointModel(static_cast<int>(CheckPoint::FOURTH), this);

	//�A���r�G���g�ݒ�
	Model::SetAmbient(hModel_, INITIALIZE_AMBIENT);
}

//�X�V
void FourthStageModel::ChildUpdate()
{
	transform_.rotate_.y += ROTATION_ADD_VALUE;
}

//�I������Ă��鎞�Ƀ{�^���������ꂽ��
void FourthStageModel::SelectButtonPush()
{
	//���łɃt�F�[�h�A�E�g���Ă����炱�̐�͏������Ȃ�
	if (Fade::GetFadeStatus() == FADE_CIRCLE_OUT)return;

	//�t�F�[�h�A�E�g
	Fade::SetFadeStatus(FADE_CIRCLE_OUT);

	//�萔�b��ɌĂ�
	SetTimeMethod(CALL_TIMEMETHOD_TIME);
}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void FourthStageModel::TimeMethod()
{
	//�V�[���`�F���W
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_WORLD1);
}