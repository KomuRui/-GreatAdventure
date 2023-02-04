#include "UserInfomation.h"
#include <fstream>

//�萔
namespace
{
	//�v���C���[�̑��l��
	static const int TOTAL_PLAYER = 3;
}

//���[�U�[���(3�̃f�[�^�������Ă���)
namespace UserInfomation
{
	//���[�U�[�̏�񂪓����Ă���e�L�X�g�̃p�X
	std::string firstUserModelPath_;
	std::string secondUserModelPath_;
	std::string thirdUserModelPath_;

	//������
	void Initialize()
	{
		//�e�t�@�C�����[�h
		Load(&firstUserModelPath_, "Stage/UserSelect/UserInformation/UserInfo1.txt");
		Load(&secondUserModelPath_, "Stage/UserSelect/UserInformation/UserInfo2.txt");
		Load(&thirdUserModelPath_, "Stage/UserSelect/UserInformation/UserInfo3.txt");
	};

	//�t�@�C�����[�h
	void Load(std::string* str, std::string filePath)
	{
		//�t�@�C���I�[�v��
		std::ifstream ifs(filePath);

		//�����܂œǂ�
		while (!ifs.eof())
		{
			//1��buf�Ɋi�[
			std::getline(ifs, *str);
		}
	}

	//�e�Q�b�g�֐�
	std::string GetFirstModelPath() { return firstUserModelPath_; }
	std::string GetSecondModelPath() { return secondUserModelPath_; }
	std::string GetThirdModelPath() { return thirdUserModelPath_; }
}