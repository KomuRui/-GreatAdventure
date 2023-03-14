#include "ThirdStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Manager/GameManager/GameManager.h"
#include "BaseSelectStage.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../OtherObject/UserInfomation.h"

//�萔
namespace
{
	static const XMFLOAT4 INITIALIZE_AMBIENT = { -0.7, -0.7, -0.7, ZERO }; //�����A���r�G���g�l
	static const float ROTATION_ADD_VALUE = 0.25f;	//��]���鎞�̉��Z����l
	static const float CALL_TIMEMETHOD_TIME = 3.0f; //�^�C�����\�b�h���ĂԎ���
}

//�R���X�g���N�^
ThirdStageModel::ThirdStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent,ModelPath,name, "Image/StageSelect/ThirdStage.png")
{
}

//������
void ThirdStageModel::ChildInitialize()
{
	//�`�F�b�N�|�C���g�ǉ�
	((BaseSelectStage*)GetParent())->SetCheckPointModel(static_cast<int>(CheckPoint::THIRD), this);

	//��������X�e�[�W��3��菬�����Ȃ������Ȃ�
	if(UserInfomation::GetStageReleaseNum() < 3)
		Model::SetAmbient(hModel_, INITIALIZE_AMBIENT);
	//3�ȏ�Ȃ���
	else
	ARGUMENT_INITIALIZE(isStageRelease_, true);
}

//�X�V
void ThirdStageModel::ChildUpdate()
{
	transform_.rotate_.y += ROTATION_ADD_VALUE;
}

//�I������Ă��鎞�Ƀ{�^���������ꂽ��
void ThirdStageModel::SelectButtonPush()
{
	//���łɃt�F�[�h�A�E�g���Ă����炱�̐�͏������Ȃ�
	if (Fade::GetFadeStatus() == FADE_CIRCLE_OUT)return;

	//�t�F�[�h�A�E�g
	Fade::SetFadeStatus(FADE_CIRCLE_OUT);

	//�萔�b��ɌĂ�
	SetTimeMethod(CALL_TIMEMETHOD_TIME);
}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void ThirdStageModel::TimeMethod()
{
	//�V�[���`�F���W
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_WORLD2);
}