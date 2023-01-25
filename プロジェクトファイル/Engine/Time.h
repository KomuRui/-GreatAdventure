#pragma once

/// <summary>
/// DirectX���Ɉˑ����Ȃ�Time
/// </summary>
namespace Time
{
	//������(Main�ŏ�����)
	void Initialize(int FPS);

	//�X�V(Main�ŌĂяo��)
	void Update();

	/// <summary>
	/// �^�C�����Z�b�g
	/// </summary>
	void Reset();

	/// <summary>
	/// �^�C�����X�V���Ȃ��悤�ɂ���
	/// </summary>
	void Lock();

	/// <summary>
	/// �^�C�����X�V����悤�ɂ���
	/// </summary>
	void UnLock();

	/// <summary>
	/// �����b�N���Ă��邩�ǂ���
	/// </summary>
	/// <returns>true�Ȃ烍�b�N���Ă���</returns>
	bool isLock();

	/// <summary>
	/// �Ăяo�����_�̎��Ԃ��擾
	/// </summary>
	/// <returns>int�^�̎���</returns>
	int GetTimei();

	/// <summary>
	/// �Ăяo�����_�̎��Ԃ��擾
	/// </summary>
	/// <returns>float�^�̎���</returns>
	float GetTimef();

	/// <summary>
	/// �Ăяo�����_�̎��Ԃ��擾
	/// </summary>
	/// <returns>double�^�̎���</returns>
	double GetTime();
};

