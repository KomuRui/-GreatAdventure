#include "TitleModel.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/ResourceManager/VFX.h"

//�萔
namespace
{
	static const XMVECTOR MIN_SCALE = { 0.25f,0.25f,1.0f };  //�Œ�g�嗦
	static const XMVECTOR MAX_SCALE = { 0.30f,0.30f,1.0f };  //�ō��g�嗦
	static const float INTERPOLATION_FACTOR = 0.03f;         //��ԌW��
	static const float CHANGE_TARGET_DISTANCE = 0.01f;       //�^�[�Q�b�g�ύX����Ƃ��̋���
}

//�R���X�g���N�^
TitleModel::TitleModel(GameObject* parent)
	:GameObject(parent,"TitleModel"),hModel_(-1), beforeScale_(XMVectorSet(ZERO, ZERO, ZERO, ZERO)), targetScale_(XMVectorSet(0, 0, 0, 0))
{
}

//������
void TitleModel::Initialize()
{
	///////////////���f���f�[�^�̃��[�h///////////////////

	ARGUMENT_INITIALIZE(pathName_, "Stage/Title/Model/TitleModel.fbx");
	hModel_ = Model::Load(pathName_);
	assert(hModel_ >= ZERO);
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void TitleModel::StartUpdate()
{
	//��Ԃ���O�̊g�嗦�ۑ�
	ARGUMENT_INITIALIZE(beforeScale_, MIN_SCALE);

	//���̖ڕW�Ƃ���g�嗦�̕ۑ�
	ARGUMENT_INITIALIZE(targetScale_, MAX_SCALE);
}

//�X�V
void TitleModel::Update()
{
	//�g�嗦���Ԃ��Ȃ���ς��Ă���
	XMStoreFloat3(&transform_.scale_,XMVectorLerp(XMLoadFloat3(&transform_.scale_), targetScale_, INTERPOLATION_FACTOR));

	//������0.01���Z���̂Ȃ�
	if (RangeCalculation(transform_.scale_, VectorToFloat3(targetScale_)) < CHANGE_TARGET_DISTANCE)
	{
		//�^�[�Q�b�g����
		std::swap(beforeScale_, targetScale_);
	}
}

//�`��
void TitleModel::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void TitleModel::Release()
{
}

//�V�[���ύX�G�t�F�N�g
void TitleModel::SceneChangeEffect()
{
	EmitterData data;
	data.textureFileName = "Image/Effect/Cloud.png";
	data.position = transform_.position_;
	data.delay = 0;
	data.number = 60;
	data.lifeTime = 150;
	data.direction = XMFLOAT3(0, 1, 0);
	data.directionRnd = XMFLOAT3(90, 90, 90);
	data.speed = 0.05f;
	data.speedRnd = 0.8f;
	data.size = XMFLOAT2(5.0f, 5.0f);
	data.sizeRnd = XMFLOAT2(0.4f, 0.4f);
	data.scale = XMFLOAT2(1.05f, 1.05f);
	data.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	data.deltaColor = XMFLOAT4(-0.01f, -0.01f, 0.0f, -1.0f / 50.0f);
	VFX::Start(data);
}