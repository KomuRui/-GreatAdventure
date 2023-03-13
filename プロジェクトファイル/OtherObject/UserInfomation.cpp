#include "UserInfomation.h"
#include "SelectPlanetController.h"
#include "../Manager/CoinManager/CoinManager.h"
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

	//�e���̏��
	UserInfo first_;
	UserInfo second_;
	UserInfo third_;

	//������
	void Initialize()
	{
		//�e�t�@�C�����[�h
		Load(&first_, FIRST_USER_INFO_PATH);
		Load(&first_,SECOND_USER_INFO_PATH);
		Load(&first_, THIRD_USER_INFO_PATH);
	};

	//�t�@�C�����[�h
	void Load(UserInfo* str, std::string filePath)
	{
		//�t�@�C���I�[�v��
		std::ifstream ifs(filePath);

		//�f�[�^��1������ϐ�
		std::string buf;

		//�K�v�Ȋe�p�����[�^��ۑ�����p�̕�����z��
		std::string data[3] = { "" };

		//,�̐�
		int sum = ZERO;

		//1��buf�Ɋi�[
		std::getline(ifs, buf);

		//buf�̃T�C�Y�����[�v
		for (int i = ZERO; i < buf.size(); i++)
		{
			//�e�p�����[�^�������data�Ɋi�[���Ă���
			if (buf[i] != ',')
			{
				data[sum] += buf[i];
			}
			else
				sum++;
		}

		//�e���i�[
		str->modelPath = data[0];
		str->coinNum = std::stoi(data[1]);
		str->stageReleaseNum = std::stoi(data[2]);
	}

	//�V�K�쐬
	void CreateNewfile(std::string filePath, std::string newModelPath)
	{
		//�t�@�C���I�[�v��
		std::ofstream ofs(filePath, std::ios::out);
		ofs << newModelPath + ",0,1";
	}

	//�Z�[�u
	void Save(UserInfo str,std::string filePath, int coinNum, int stageReleaseNum)
	{
		//�t�@�C���I�[�v��
		std::ofstream ofs(filePath, std::ios::out);
		ofs << str.modelPath + "," + std::to_string(coinNum) + "," + std::to_string(stageReleaseNum);
	}

	//�Z�[�u�֐����Ă�
	void CallSave()
	{
		//�v���C���Ă��鐯�̔ԍ����擾
		int num = SelectPlanetController::GetPlayPlanetNum();

		//�R�C���̑����擾
		int coinNum = CoinManager::GetCoinNum();

		//����X�e�[�W�̐����擾
		int stageReleaseNum = SelectPlanetController::GetStageReleaseNum();

		//�v���C���Ă���ԍ��ɑΉ�����Z�[�u�֐����Ă�
		switch (num)
		{
		case 1:
			FirstSave(coinNum,stageReleaseNum);
			break;
		case 2:
			SecondSave(coinNum, stageReleaseNum);
			break;
		case 3:
			ThirdSave(coinNum, stageReleaseNum);
			break;
		default:
			break;
		}
	}

	///////�e�Z�[�u�֐�///////

	void FirstSave(int coinNum, int stageReleaseNum) { Save(first_, FIRST_USER_INFO_PATH, coinNum, stageReleaseNum); }
	void SecondSave(int coinNum, int stageReleaseNum){ Save(second_,SECOND_USER_INFO_PATH,coinNum, stageReleaseNum); }
	void ThirdSave(int coinNum, int stageReleaseNum) { Save(third_, THIRD_USER_INFO_PATH, coinNum, stageReleaseNum); }

	///////�e�Q�b�g�֐�///////

	//�e���̃��f���p�X�擾
	std::string GetFirstModelPath()  { return first_.modelPath; }
	std::string GetSecondModelPath() { return second_.modelPath;}
	std::string GetThirdModelPath()  { return third_.modelPath; }

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