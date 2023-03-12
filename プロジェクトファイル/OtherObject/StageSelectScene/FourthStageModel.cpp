#include "FourthStageModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "BaseSelectStage.h"

//�萔
namespace
{
	static const XMFLOAT4 INITIALIZE_AMBIENT = { -0.6, -0.6, -0.6, ZERO }; //�����A���r�G���g�l
	static const float ROTATION_ADD_VALUE = 0.35f;	//��]���鎞�̉��Z����l
}

//�R���X�g���N�^
FourthStageModel::FourthStageModel(GameObject* parent, std::string ModelPath, std::string name)
	:StageModelBase(parent, ModelPath,name)
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

}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void FourthStageModel::TimeMethod()
{

}