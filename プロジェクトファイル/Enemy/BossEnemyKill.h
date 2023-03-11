#pragma once
#include "../Engine/GameObject/GameObject.h"

/// <summary>
/// �{�X���|���ꂽ�V�[���p
/// </summary>
class BossEnemyKill : public GameObject
{

	int hModel_;	  //���f���ԍ�
	int hImage_;      //�摜�ԍ�
	int sign_;        //����

	float colorR_;    //RGB�l��R�̒l
	float imageAlpha_;//�摜�̓����x

	bool isExplosion_;//����������
	bool isFadeIn_;   //�t�F�[�h�C�����邩
	bool isModelDraw_;//���f���`�悷�邩 

	XMFLOAT3 camTar_; //�J�����̃^�[�Q�b�g

public:

	//�R���X�g���N�^
	BossEnemyKill(GameObject* parent);

	/////////////////////�I�[�o�[���C�h����֐�///////////////////////////

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override {};

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override {};

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;
};

