#include "BossEnemyKill.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/GameObject/Camera.h"
#include "../Manager/EffectManager/OtherEffectManager/OtherEffectManager.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Engine/ResourceManager/Fade.h"

//�萔
namespace
{
	static const float ROTATION_ADD_VALUE = 5.0f;      //��]�̉��Z���鎞�̒l    
	static const float COLOR_R_ADD_VALUE = 0.002f;     //�F��R�l�����Z���鎞�̒l
	static const float SCALE_X_ADD_VALUE = 0.002f;     //X�̊g�嗦�����Z���鎞�̒l
	static const float CAM_TAR_Y_ADD_VALUE = 10.0f;	   //�J�����̃^�[�Q�b�gY�ɉ��Z���鎞�̒l
	static const float EFFECT_POS_Y_ADD_VALUE = 9.0f;  //�G�t�F�N�g�|�W�V����Y�ɉ��Z���鎞�̒l
	static const float CALL_TIME_METHOD = 0.5f;        //�^�C�����\�b�h���ĂԎ���
	static const XMFLOAT3 CAM_POS = { ZERO,11,10 };    //�J�����̃|�W�V����
}

//�R���X�g���N�^
BossEnemyKill::BossEnemyKill(GameObject* parent)
	: GameObject(parent), hModel_(-1), sign_(1), colorR_(ZERO), isExplosion_(false)
{
}

//������
void BossEnemyKill::Initialize()
{
	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Enemy/Model/MainBoss.fbx");
	assert(hModel_ >= ZERO);

	/////////////////���邳�ݒ�/////////////////

	Model::SetBrightness(hModel_, 1.0f);

	///////////////�J�����̐ݒ�///////////////////

	ARGUMENT_INITIALIZE(camTar_,XMFLOAT3(transform_.position_.x, transform_.position_.y + CAM_TAR_Y_ADD_VALUE, transform_.position_.z));
	Camera::SetPosition(CAM_POS);
	Camera::SetUpDirection(UP_VECTOR);
	Camera::SetTarget(camTar_);
}

//�X�V
void BossEnemyKill::Update()
{
	//����colorR_��1�ȏォ�������Ă��Ȃ��̂Ȃ�
	if (colorR_ >= 1 && !isExplosion_)
	{
		//���������ɕύX
		ARGUMENT_INITIALIZE(isExplosion_, true);

		//�G�t�F�N�g�̔����|�W�V���������߂�
		XMFLOAT3 effectPos = transform_.position_;
		effectPos.y += EFFECT_POS_Y_ADD_VALUE;

		//�����G�t�F�N�g
		OtherEffectManager::ExplosionEffect(effectPos);

		//�`�悵�Ȃ�
		Invisible();

		//�萔�b��Ƀ^�C�����\�b�h���Ă�
		SetTimeMethod(CALL_TIME_METHOD);

		return;
	}

	//�t�F�[�h���Ō�܂ŏI����Ă����������Ă���̂Ȃ�LastScene�ֈڍs
	if (Fade::isNormalFadeNotTransparency() && isExplosion_)
	{
		//���[�h��ʂ�`�悵�Ȃ�
		GameManager::GetpSceneManager()->SetLoadDrawFlag(false);

		//���X�g�V�[����
		GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_LAST);

		//�t�F�[�h�A�E�g
		Fade::SetFadeStatus(FADE_NORMAL_OUT);
	}

	//�A���r�G���g�l�ݒ�
	Model::SetAmbient(hModel_, XMFLOAT4(colorR_, ZERO, ZERO, 1.0f));
	colorR_ += COLOR_R_ADD_VALUE;

	//�т��т��k�킹��
	ARGUMENT_INITIALIZE(transform_.rotate_.y,ROTATION_ADD_VALUE * sign_);
	sign_ *= -1;

	//���点��
	transform_.scale_.x += SCALE_X_ADD_VALUE;

	//��Ƀ{�X����悤��
	Camera::SetPosition(CAM_POS);
	Camera::SetUpDirection(UP_VECTOR);
	Camera::SetTarget(camTar_);
}

//�`��
void BossEnemyKill::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void BossEnemyKill::TimeMethod()
{
	//�t�F�[�h�C��
	Fade::SetFadeStatus(FADE_NORMAL_IN);
}
