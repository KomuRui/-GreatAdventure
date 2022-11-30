#pragma once
#include "GameObject.h"

//-----------------------------------------------------------
//�_�����J����
//-----------------------------------------------------------
namespace Light
{
	//�������i���C�g��Pos�ƌ����j
	void Initialize();

	//���C�g�̈ʒu��ݒ�
	void SetPlayerPosition(XMFLOAT4 position);

	//�ʒu��ݒ�
	void SetPosition(XMFLOAT4 position);

	//�����ɂ���Ăǂ̂悤�ɖ��邳��ω������邩(�����p�����[�^)��ݒ�
	void SetAttenuation(XMFLOAT4 attenuation);

	//���C�g�̌�����ݒ�
	void SetDirection(XMFLOAT4 direction);

	//���C�g�̋�����ݒ�
	void SetIntensity(int intensity);

	//�ʒu���擾
	XMFLOAT4 GetPosition(int num);

	//�����p�����[�^���擾
	XMFLOAT4 GetAttenuation();

	//���C�g�̌���
	XMFLOAT4 GetDirection();

	//���C�g�̋���
	int  GetIntensity();
};

