#include "Light.h"
#include "Global.h"
#include <map>

//�萔
const XMFLOAT4 LIGHT_ATTENUATION = { 1, 0, 0.2, 0 };                 //���C�g�̌���
const XMFLOAT4 LIGHT_DIR = { 0, -1, 0, 0 };                          //���C�g�̌���
const XMFLOAT4 LIGHT_INIT_POSITION = { 99999, 99999, 99999, 99999 }; //���C�g�̃|�W�V�����̏����l(�g��Ȃ��Ƃ���99999�ɂ��邽��)
const int LIGHT_TOTAL_NUM = 8;                                       //���C�g�̑���          
const int LIGHT_STAGE_START_NUM = 1;                                 //�X�e�[�W�̃��C�g�̃X�^�[�g�ԍ�(�O�Ԃ�Player�̃��C�g���g������1�Ԃ���X�^�[�g)
const int LIGHT_INTENSITY = 1;                                       //���C�g�̋���

//�ϐ�
XMFLOAT4 _LightPos[LIGHT_TOTAL_NUM];  //���C�g��Position�i�[
XMFLOAT4 _LightPosition;	          //���C�g�̃|�W�V����
XMFLOAT4 _LightAttenuation;		      //���C�g�̌���
XMFLOAT4 _direction;			      //���C�g�̌���
int      _intensity;			      //���C�g�̋���
int      _LightNowNumber;             //���̃��C�g�̊i�[�ԍ�    

//�������i�v���W�F�N�V�����s��쐬�j
void Light::Initialize()
{
	//���C�g�̃|�W�V�������ׂď�����
	for (int counter = 0; counter < LIGHT_TOTAL_NUM; counter++)
	{
		ARGUMENT_INITIALIZE(_LightPos[counter],LIGHT_INIT_POSITION);
	}

	//�e�ϐ��̏�����
	ARGUMENT_INITIALIZE(_LightNowNumber,LIGHT_STAGE_START_NUM);     //���C�g�̊i�[�ԍ��̏�����
	ARGUMENT_INITIALIZE(_LightPosition,LIGHT_INIT_POSITION);        //���C�g�̈ʒu
	ARGUMENT_INITIALIZE(_LightAttenuation,LIGHT_ATTENUATION);	    //���C�g�̌����p�����[�^
	ARGUMENT_INITIALIZE(_direction,LIGHT_DIR);                      //���C�g�̌���
	ARGUMENT_INITIALIZE(_intensity,LIGHT_INTENSITY);                //���C�g�̋���
}

//�����ɂ���Ăǂ̂悤�ɖ��邳��ω������邩(�����p�����[�^)��ݒ�
void Light::SetAttenuation(XMFLOAT4 attenuation) { _LightAttenuation = attenuation; }

//PlayerLight�̈ʒu��ݒ�
void Light::SetPlayerPosition(XMFLOAT4 position) { _LightPos[0] = position; }

//�ʒu��ݒ�
void Light::SetPosition(XMFLOAT4 position) { _LightPos[_LightNowNumber] = position; _LightNowNumber++; }

//���C�g�̌�����ݒ�
void Light::SetDirection(XMFLOAT4 direction) { _direction = direction; }

//���C�g�̋�����ݒ�
void Light::SetIntensity(int intensity) { _intensity = intensity; }

//�����p�����[�^���擾
XMFLOAT4 Light::GetAttenuation() { return _LightAttenuation; }

//�ʒu���擾
XMFLOAT4 Light::GetPosition(int num) { return _LightPos[num]; }

//���C�g�̌������擾
XMFLOAT4 Light::GetDirection() { return _direction; }

//���C�g�̋������擾
int  Light::GetIntensity() { return _intensity; }
