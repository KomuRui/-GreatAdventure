#include "Light.h"

XMFLOAT4 _position;
XMFLOAT4 _attenuation;
XMFLOAT4 _direction;

//�������i�v���W�F�N�V�����s��쐬�j
void Light::Initialize()
{
	_position = XMFLOAT4(0, 50, -50, 0);     //���C�g�̈ʒu
	_attenuation = XMFLOAT4(1, 0, 0.2, 0);	 //�J�����̏œ_
	_direction = XMFLOAT4(0, -1, 0, 0);
}

//�����ɂ���Ăǂ̂悤�ɖ��邳��ω������邩(�����p�����[�^)��ݒ�
void Light::SetAttenuation(XMFLOAT4 attenuation) { _attenuation = attenuation; }

//�ʒu��ݒ�
void Light::SetPosition(XMFLOAT4 position) { _position = position; }

//���C�g�̌�����ݒ�
void Light::SetDirection(XMFLOAT4 direction) { _direction = direction; }

//�����p�����[�^���擾
XMFLOAT4 Light::GetAttenuation() { return _attenuation; }

//�ʒu���擾
XMFLOAT4 Light::GetPosition() { return _position; }

//�ʒu���擾
XMFLOAT4 Light::GetDirection() { return _direction; }
