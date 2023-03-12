#include "FirstStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Manager/GameManager/GameManager.h"
#include "BaseSelectStage.h"
#include "../../Engine/ResourceManager/Fade.h"

//�萔
namespace
{
	static const float ROTATION_ADD_VALUE = 0.25f;	//��]���鎞�̉��Z����l
}

//�R���X�g���N�^
FirstStageModel::FirstStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent,ModelPath, name)
{
}

//������
void FirstStageModel::ChildInitialize()
{
	//�`�F�b�N�|�C���g���f���ǉ�
	((BaseSelectStage*)GetParent())->SetCheckPointModel(static_cast<int>(CheckPoint::FIRST),this);
}

//�X�V
void FirstStageModel::ChildUpdate()
{
	transform_.rotate_.y += ROTATION_ADD_VALUE;
}

//�I������Ă��鎞�Ƀ{�^���������ꂽ��
void FirstStageModel::SelectButtonPush()
{
	//�t�F�[�h�A�E�g
	Fade::SetFadeStatus(FADE_CIRCLE_OUT);

	//�萔�b��ɌĂ�
	SetTimeMethod(3.0f);
}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void FirstStageModel::TimeMethod()
{
	//�V�[���`�F���W
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TUTORIAL2);
}