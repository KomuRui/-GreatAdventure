#pragma once
#include "UserPlanetBase.h"
#include <vector>

/// <summary>
/// ���[�U�[����I������Ƃ��̏��(�V�K�쐬������̃f�[�^����n�߂��ԂȂ�)
/// </summary>
enum class SelectPlanetStatus
{
	Selecting,  //�I��r��
	Select,     //�I��
	NewCreate,  //�V�K�쐬
	Existing,   //����
};

//���[�U�[����I������Ƃ��̊Ǘ�
namespace SelectPlanetController
{
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �e�������Z�b�g
	/// </summary>
	/// <param name="pUserPlanet"></param>
	void SetUserPlanetFirst(UserPlanetBase* pUserPlanet);
	void SetUserPlanetSecond(UserPlanetBase* pUserPlanet);
	void SetUserPlanetThird(UserPlanetBase* pUserPlanet);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �I��
	/// </summary>
	void NowSelect();

	/// <summary>
	/// �I��
	/// </summary>
	void Select();

	/// <summary>
	/// �V�K�쐬
	/// </summary>
	void NewCreate();

	/// <summary>
	/// ����
	/// </summary>
	void Existing();

	/// <summary>
	/// �v���C���Ă��鐯�̔ԍ����擾
	/// </summary>
	/// <returns>�v���C���Ă��鐯�̔ԍ�</returns>
	int GetPlayPlanetNum();

	/// <summary>
	/// �J�����ړ�
	/// </summary>
	void CameraMove();

	/// <summary>
	/// ���[�U�[����I������Ƃ��̏�Ԃ��擾
	/// </summary>
	/// <returns>���</returns>
	SelectPlanetStatus GetStatus();

	/// <summary>
	/// �A�C�R�����f���p�X��ݒ�
	/// </summary>
	/// <param name="path">�ݒ肵�����A�C�R�����f���p�X</param>
	void SetIconModelPath(std::string path);

	/// <summary>
	/// ����X�e�[�W�̐����Z�b�g
	/// </summary>
	/// <param name="num">�Z�b�g����������X�e�[�W�̐�</param>
	void SetStageReleaseNum(int num);

	/// <summary>
	/// ����X�e�[�W�̐����Q�b�g
	/// </summary>
	/// <returns>����X�e�[�W�̐�</returns>
	int GetStageReleaseNum();
};

