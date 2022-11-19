#pragma once
#include <vector>
#include "GameObject.h"
#include "../Player.h"
#include "../Block/Block.h"

const int MAX_OBJECT_SIZE = 50;

//�����V�[�����Ǘ�����N���X
class ImGuiSet : public GameObject
{
	//�\���������I�u�W�F�N�g���i�[����ꏊ
	//first->���f���ԍ�
	//second->���f���ԍ����Ƃ̃g�����X�t�H�[��
	std::vector<std::pair<int,Transform>>obj;

	//3D�����{�^���������Ă�����true
	bool Create3Dflag;

	//3D�����������
	int ObjectCount;

	//�g�����X�t�H�[���ۑ����邽�߂Ɏ����Ă���
	Player* pPlayer_;

	//�e�X�e�[�W�̃u���b�N�̃g�����X�t�H�[����ۑ�
	std::vector<Block*> tBlock;

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

	void Create3D();

	//�J��
	void Release() override;

	void StartUpdate() override;

	void CreateStage(std::string filename);

	void InstantiateString(std::string ModelPathName, std::string inName, Transform t);

	std::vector<Block*> GetTransformBlock() { return tBlock; }
};