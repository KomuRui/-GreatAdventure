#include "UserInfomation.h"
#include <fstream>

//�萔
namespace
{
	//�v���C���[�̑��l��
	static const int TOTAL_PLAYER = 3;

	//�e���[�U�[��񂪓����Ă���e�L�X�g�̃p�X
	static const std::string FIRST_USER_INFO_PATH =  "Stage/UserSelect/UserInformation/UserInfo1.txt";
	static const std::string SECOND_USER_INFO_PATH = "Stage/UserSelect/UserInformation/UserInfo2.txt";
	static const std::string THIRD_USER_INFO_PATH =  "Stage/UserSelect/UserInformation/UserInfo3.txt";
}

//���[�U�[���(3�̃f�[�^�������Ă���)
namespace UserInfomation
{
	//�e���̃��f���̃p�X
	std::string firstModelPath_;
	std::string secondModelPath_;
	std::string thirdModelPath_;

	//������
	void Initialize()
	{
		//�e�t�@�C�����[�h
		Load(&firstModelPath_, FIRST_USER_INFO_PATH);
		Load(&secondModelPath_,SECOND_USER_INFO_PATH);
		Load(&thirdModelPath_, THIRD_USER_INFO_PATH);
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

	//�V�K�쐬
	void CreateNewfile(std::string filePath, std::string newModelPath)
	{
		//�t�@�C���I�[�v��
		std::ofstream ofs(filePath, std::ios::out);
		ofs << newModelPath;
	}

	///////�e�Q�b�g�֐�///////

	//�e���̃��f���p�X�擾
	std::string GetFirstModelPath()  { return firstModelPath_; }
	std::string GetSecondModelPath() { return secondModelPath_; }
	std::string GetThirdModelPath()  { return thirdModelPath_; }

	//�e���̃��[�U�[��񂪓����Ă���e�L�X�g�̃p�X�擾
	std::string GetFirstInfoPath()  { return FIRST_USER_INFO_PATH; }
	std::string GetSecondInfoPath() { return SECOND_USER_INFO_PATH; }
	std::string GetThirdInfoPath()  { return THIRD_USER_INFO_PATH; }


	///////�e�Z�b�g�֐�///////

	//�e����V�K�쐬����Ƃ��ɌĂԊ֐�
	void SetFirstNewFile(std::string newModelPath) { CreateNewfile(FIRST_USER_INFO_PATH, newModelPath); }
	void SetSecondNewFile(std::string newModelPath) { CreateNewfile(SECOND_USER_INFO_PATH, newModelPath); }
	void SetThirdNewFile(std::string newModelPath) { CreateNewfile(THIRD_USER_INFO_PATH, newModelPath); }
}