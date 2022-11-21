#include "camera.h"
#include "Direct3D.h"

XMFLOAT3 _position;
XMFLOAT3 _target;
XMMATRIX _view;
XMMATRIX _proj;
XMVECTOR _UpDirection;
XMMATRIX _billBoard;
int _field_angle;

//////////�U���ɕK�v�ȕϐ�
XMFLOAT3 _targetPos;
float _strength;
bool  _vibrationFlag;

//�������i�v���W�F�N�V�����s��쐬�j
void Camera::Initialize()
{
	_position = XMFLOAT3(0, 50, -50);	    //�J�����̈ʒu
	_target = XMFLOAT3( 0, 0, 0);	        //�J�����̏œ_
	_UpDirection = XMVectorSet(0, 1, 0, 0); //�J�����̏�����̃x�N�g��
	_targetPos = XMFLOAT3(0, 0, 0);         //�U������Ƃ��̃|�W�V����������
	_field_angle = 45;                      //�J�����̉�p
	_vibrationFlag = false;                 //�J�����̐U��Off

	//�v���W�F�N�V�����s��
	_proj = XMMatrixPerspectiveFovLH(XMConvertToRadians(_field_angle), (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//�X�V�i�r���[�s��쐬�j
void Camera::Update()
{
	//�r���[�s��
	_view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, 0),
		XMVectorSet(_target.x, _target.y, _target.z, 0), _UpDirection);

	//�r���{�[�h�s��
	//�i��ɃJ�����̕��������悤�ɉ�]������s��B�p�[�e�B�N���ł����g��Ȃ��j
	_billBoard = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), XMLoadFloat3(&_target) - XMLoadFloat3(&_position), XMVectorSet(0, 1, 0, 0));
	_billBoard = XMMatrixInverse(nullptr, _billBoard);

	//�J�����U���t���O��true�Ȃ�J������U��������
	if (_vibrationFlag)Vibration();
}

//�J�����̐U��
void Camera::Vibration()
{
	//��Ԃ��Ȃ���ړI�̃|�W�V�����܂ŕύX���Ă���
	_position = Transform::VectorToFloat3(XMVectorLerp(XMLoadFloat3(&_position), XMLoadFloat3(&_targetPos), 0.1));

	//������0.01��菬�����Ȃ玟�̖ړI�n��ݒ�
	if (Transform::RangeCalculation(_position, _targetPos) < 0.01)
	{
		_targetPos = { _position.x,-_position.y,_position.z };
	}
}

//�œ_��ݒ�
void Camera::SetTarget(XMFLOAT3 target) { _target = target;}

//�ʒu��ݒ�
void Camera::SetPosition(XMFLOAT3 position) { _position = position; }

//������̃x�N�g����ݒ�
void Camera::SetUpDirection(XMVECTOR direction) { _UpDirection = direction; }

//��p��ݒ�
void Camera::SetFieldAngle(int angle) 
{
	//��p�X�V
	_field_angle = angle;
	//�v���W�F�N�V�����s��
	_proj = XMMatrixPerspectiveFovLH(XMConvertToRadians(_field_angle), (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//�œ_���擾
XMFLOAT3 Camera::GetTarget() { return _target; }

//�J�����U��
//���� : �U���̋���
void Camera::SetCameraVibration(float strength)
{
	//�����ݒ�(1�ȏ�ɂ���������1�𑫂��Ă���)
	_strength = strength + 1;

	//�U������Ƃ��̃|�W�V�����ݒ�
	_targetPos = XMFLOAT3(_position.x,_position.y * _strength,_position.z);

	//�U���t���OON
	_vibrationFlag = true;
}

//�ʒu���擾
XMFLOAT3 Camera::GetPosition() { return _position; }

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix() { return _view; }

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }

//�r���{�[�h�p��]�s����擾
XMMATRIX Camera::GetBillboardMatrix() { return _billBoard; }