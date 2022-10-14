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
	void SetPosition(XMFLOAT4 position);

	//�����ɂ���Ăǂ̂悤�ɖ��邳��ω������邩(�����p�����[�^)��ݒ�
	void SetAttenuation(XMFLOAT4 attenuation);

	//���C�g�̌�����ݒ�
	void SetDirection(XMFLOAT4 direction);

	//�ʒu���擾
	XMFLOAT4 GetPosition();

	//�����p�����[�^���擾
	XMFLOAT4 GetAttenuation();

	//���C�g�̌���
	XMFLOAT4 GetDirection();
};
