#pragma once
#include "Transform.h"
#include "GameObject.h"
#include "../Block/Block.h"

//�e�X�e�[�W�ŃJ�����J�ڂ���Ƃ��̕K�v�ȏ��
struct StageCameraTransition
{
	XMFLOAT3 CameraPosition;  //�J�����̃|�W�V����
	XMFLOAT3 CameraTarget;    //�J�����̃^�[�Q�b�g
	XMFLOAT3 CollisionSize;   //�R���C�_�[�̃T�C�Y
};

//�e�V�[���̃X�e�[�W����Ă����
class CreateStage
{

	//���郉�C�g�̃R���g���[���[����x�������Ȃ��̂�flag�ō�������ǂ����m�F����
	bool CreateShineController;

	//�e�X�e�[�W�̃u���b�N�̃g�����X�t�H�[����ۑ�
	std::vector<Block*> tBlock;

public:

	//�R���X�g���N�^
	CreateStage();

	//�I�u�W�F�N�g�쐬
	void CreateObject(GameObject* parent,std::string ModelPathName, std::string inName, Transform t, XMFLOAT3 camPos);

	//�e�X�e�[�W�̃t�@�C�����[�h
	void LoadFile(std::string filename);

	//�e�u���b�N�̃|�C���^�Q�b�g
	std::vector<Block*> GetTransformBlock() { return tBlock; }
};
