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
	/// �J�����ړ�
	/// </summary>
	void CameraMove();

	/// <summary>
	/// ���[�U�[����I������Ƃ��̏�Ԃ��擾
	/// </summary>
	/// <returns>���</returns>
	SelectPlanetStatus GetStatus();
};

