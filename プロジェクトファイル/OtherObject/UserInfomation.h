#pragma once
#include "../Engine/GameObject.h"

//���[�U�[���(3�̃f�[�^�������Ă���)
namespace UserInfomation
{
	//������
	void Initialize();

	/// <summary>
	/// �t�@�C�����[�h
	/// </summary>
	/// <param name="str">���[�h�������ʂ��i�[����ϐ��̃|�C���^</param>
	/// <param name="filePath">���[�h�������t�@�C���̖��O</param>
	void Load(std::string* str,std::string filePath);

	//�e�Q�b�g�֐�
	std::string GetFirstModelPath();
	std::string GetSecondModelPath();
	std::string GetThirdModelPath();
};

