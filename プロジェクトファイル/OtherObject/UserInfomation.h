#pragma once
#include "../Engine/GameObject/GameObject.h"

//���[�U�[���(3�̃f�[�^�������Ă���)
namespace UserInfomation
{
	//���[�U�[���
	struct UserInfo
	{
		std::string modelPath; //���f���p�X
		int coinNum;           //�R�C���̐�
		int stageReleaseNum;   //�X�e�[�W����̐�
	};

	//������
	void Initialize();

	/// <summary>
	/// �t�@�C�����[�h
	/// </summary>
	/// <param name="str">���[�h�������ʂ��i�[����ϐ��̃|�C���^</param>
	/// <param name="filePath">���[�h�������t�@�C���̖��O</param>
	void Load(UserInfo* str,std::string filePath);

	/// <summary>
	/// �V�K�쐬
	/// </summary>
	/// <param name="newModelPath">�V�������̃��f���p�X</param>
	/// <param name="filePath">���[�h�������t�@�C���̖��O</param>
	void CreateNewfile(std::string filePath, std::string newModelPath);

	/////�e�Q�b�g�֐�//////

	//�e���̃��f���p�X�擾
	std::string GetFirstModelPath();
	std::string GetSecondModelPath();
	std::string GetThirdModelPath();

	//�e���̃��[�U�[��񂪓����Ă���e�L�X�g�̃p�X�擾
	std::string GetFirstInfoPath();
	std::string GetSecondInfoPath();
	std::string GetThirdInfoPath();

	///////�e�Z�b�g�֐�///////

	/// <summary>
	/// �e����V�K�쐬����Ƃ��ɌĂԊ֐�
	/// </summary>
	/// <param name="newModelPath">�V�������̃��f���p�X</param>
	void SetFirstNewFile(std::string newModelPath);
	void SetSecondNewFile(std::string newModelPath);
	void SetThirdNewFile(std::string newModelPath);
};

