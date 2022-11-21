#include "Light.h"
#include <map>

std::map<std::string,XMFLOAT4> LightPos;       //���C�g���Ƃ�Position�i�[(�i�[����Ƃ��͖��O�ƃ|�W�V�����ݒ�)
std::map<std::string,XMFLOAT4> LightIntensity; //���C�g���Ƃ̋����i�[(�i�[����Ƃ��͖��O�ƃ|�W�V�����ݒ�)
XMFLOAT4 _LightPosition;	     	           //���C�g�̃|�W�V����
XMFLOAT4 _LightAttenuation;				       //���C�g�̌���
XMFLOAT4 _direction;						   //���C�g�̌���
int      _intensity;						   //���C�g�̋���

//�������i�v���W�F�N�V�����s��쐬�j
void Light::Initialize()
{
	_LightPosition = XMFLOAT4(0, 50, -50, 0);    //���C�g�̈ʒu
	_LightAttenuation = XMFLOAT4(1, 0, 0.2, 0);	 //���C�g�̌����p�����[�^
	_direction = XMFLOAT4(0, -1, 0, 0);          //���C�g�̌���
	_intensity = 1;                              //���C�g�̋���
}

//�����ɂ���Ăǂ̂悤�ɖ��邳��ω������邩(�����p�����[�^)��ݒ�
void Light::SetAttenuation(XMFLOAT4 attenuation) { _LightAttenuation = attenuation; }

//�ʒu��ݒ�
void Light::SetPosition(XMFLOAT4 position) { _LightPosition = position; }

//���C�g�̌�����ݒ�
void Light::SetDirection(XMFLOAT4 direction) { _direction = direction; }

//���C�g�̋�����ݒ�
void Light::SetIntensity(int intensity) { _intensity = intensity; }

//�����p�����[�^���擾
XMFLOAT4 Light::GetAttenuation() { return _LightAttenuation; }

//�ʒu���擾
XMFLOAT4 Light::GetPosition() { return _LightPosition; }

//���C�g�̌������擾
XMFLOAT4 Light::GetDirection() { return _direction; }

//���C�g�̋������擾
int  Light::GetIntensity() { return _intensity; }
