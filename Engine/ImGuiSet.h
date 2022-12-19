#pragma once
#include <vector>
#include "GameObject.h"
#include "../Player.h"
#include "../Block/Block.h"

//�ő��Imgui�ŏo����I�u�W�F�N�g�T�C�Y
const int MAX_OBJECT_SIZE = 50;


//�����V�[�����Ǘ�����N���X
class ImGuiSet : public GameObject
{
	//�\���������I�u�W�F�N�g���i�[����ꏊ
	//first->���f���ԍ�
	//second->���f���ԍ����Ƃ̃g�����X�t�H�[��
	std::vector<std::pair<int,Transform>>obj_;

	//first->��������ǂ���
	//second->���������
	std::pair<bool,int> create3D_;               //3D�I�u�W�F�N�g
	std::pair<bool,int> createSigeboard_;        //�Ŕ�
	std::pair<bool,int> createCameraTransition_; //�J�����J��
	std::pair<bool,int> createImage_;            //�摜

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ImGuiSet(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//3D�I�u�W�F�N�g�쐬
	void Create3D();

	//�Ŕ쐬
	void CreateSigeboard();

	//�J�����̑J�ڍ쐬(�R���C�_�[�ɓ���������J�����̃|�W�V�����ς���@�\)
	void CreateCameraTransition();
	
	//�摜�쐬
	void CreateImage();

	//�J��
	void Release() override;

	//�X�V�̑O�Ɉ�x�����Ă΂��֐�
	void StartUpdate() override;

};