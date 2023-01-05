#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Text.h"

/// <summary>
/// ���u�Ƙb���Ƃ��̉摜��\����������N���X
/// </summary>
class TalkImage : public GameObject
{
	///////////////////////������///////////////////////////



	/////////////////////////�摜///////////////////////////

	int hBasePict_;      //�x�[�X�摜�ԍ�
	int hCharaPict_;     //�L�����摜�ԍ�
	int hNextPict_;      //Next�摜�ԍ�

	Transform tBase_;    //�x�[�XTransform
	Transform tChara_;   //�L����Transform
	Transform tNext_;    //NextTransform

	////////////////////////�e�L�X�g/////////////////////////

	Text* pText_;        //�����\������p

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TalkImage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

