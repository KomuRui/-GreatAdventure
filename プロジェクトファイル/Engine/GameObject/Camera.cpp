#include "camera.h"
#include "../DirectX/Direct3D.h"

//////////�J�����ɕK�v�ȕϐ�
XMFLOAT3 _position;
XMFLOAT3 _target;
XMMATRIX _view;
XMMATRIX _proj;
XMVECTOR _UpDirection;
XMMATRIX _billBoard;
int _field_angle;

//////////�t���[�����[�N��ŃJ�����𑀍삷�鎞�ɕK�v�ȕϐ�
XMFLOAT3 _fPosition;
XMFLOAT3 _fTarget;
XMVECTOR _fUpDirection;
XMVECTOR _fFront;

//////////�U���ɕK�v�ȕϐ�
float _vibrationQuantity;     //�U����
float _vibrationAttenuation;  //�U���̌���
bool  _vibrationFlag;         //�J������U�������邩�ǂ���
int   _sign;                  //����

//�������i�v���W�F�N�V�����s��쐬�j
void Camera::Initialize()
{
	ARGUMENT_INITIALIZE(_position,XMFLOAT3(ZERO, 50, -50));	            //�J�����̈ʒu
	ARGUMENT_INITIALIZE(_fPosition, _position);							//�t���[�����[�N��ŃJ�����𑀍삷�鎞�̃J�����̈ʒu
	ARGUMENT_INITIALIZE(_target,XMFLOAT3(ZERO, ZERO, ZERO));	        //�J�����̏œ_
	ARGUMENT_INITIALIZE(_fTarget, _target);								//�t���[�����[�N��ŃJ�����𑀍삷�鎞�̃J�����̏œ_
	ARGUMENT_INITIALIZE(_UpDirection,XMVectorSet(ZERO, 1, ZERO, ZERO)); //�J�����̏�����̃x�N�g��
	ARGUMENT_INITIALIZE(_fUpDirection, _UpDirection);					//�t���[�����[�N��ŃJ�����𑀍삷�鎞�̃J�����̏�����̃x�N�g��
	ARGUMENT_INITIALIZE(_fFront, STRAIGHT_VECTOR);					    //�t���[�����[�N��ŃJ�����𑀍삷�鎞�̃J�����̑O�����̃x�N�g��
	ARGUMENT_INITIALIZE(_field_angle,45);                               //�J�����̉�p
	ARGUMENT_INITIALIZE(_vibrationFlag,false);                          //�J�����̐U��Off
	ARGUMENT_INITIALIZE(_vibrationQuantity, ZERO);                      //�U����
	ARGUMENT_INITIALIZE(_vibrationAttenuation,0.01f);                   //�U���̌���
	ARGUMENT_INITIALIZE(_sign,1);                                       //����

	//�v���W�F�N�V�����s��
	_proj = XMMatrixPerspectiveFovLH(XMConvertToRadians((float)_field_angle), (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//�X�V�i�r���[�s��쐬�j
void Camera::Update()
{
	//�J�����̐U�� 
	_target = Float3Add(_target,Vibration());

	//��ʂ��Q�[����ԂȂ�
	if (Direct3D::GetScreenGameStatus())
	{
		//�r���[�s��
		_view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, ZERO),
			XMVectorSet(_target.x, _target.y, _target.z, ZERO), _UpDirection);

		//�r���{�[�h�s��
		//�i��ɃJ�����̕��������悤�ɉ�]������s��B�p�[�e�B�N���ł����g��Ȃ��j
		_billBoard = XMMatrixLookAtLH(XMVectorSet(ZERO, ZERO, ZERO, ZERO), XMLoadFloat3(&_target) - XMLoadFloat3(&_position), _UpDirection);
		_billBoard = XMMatrixInverse(nullptr, _billBoard);
	}
	else
	{
		//�}�E�X�ŃJ�����ړ�
		CamMouseMove();

		//�r���[�s��
		_view = XMMatrixLookAtLH(XMVectorSet(_fPosition.x, _fPosition.y, _fPosition.z, ZERO),
			XMVectorSet(_fTarget.x, _fTarget.y, _fTarget.z, ZERO), _fUpDirection);

		//�r���{�[�h�s��
		//�i��ɃJ�����̕��������悤�ɉ�]������s��B�p�[�e�B�N���ł����g��Ȃ��j
		_billBoard = XMMatrixLookAtLH(XMVectorSet(ZERO, ZERO, ZERO, ZERO), XMLoadFloat3(&_fTarget) - XMLoadFloat3(&_fPosition), _fUpDirection);
		_billBoard = XMMatrixInverse(nullptr, _billBoard);
	}

	
}

//�J�����̐U��
XMFLOAT3 Camera::Vibration()
{
	//�U���ʂǂ�ǂ񌸂炵�Ă���
	if (abs(_vibrationQuantity) < 0.01)
		_vibrationQuantity = ZERO;
	else
		_vibrationQuantity = _sign * (abs(_vibrationQuantity) - _vibrationAttenuation);

	//�������΂�
	_sign *= -1;

	return XMFLOAT3(_vibrationQuantity, _vibrationQuantity, _vibrationQuantity);
}

//��Ԉړ�
void Camera::InterpolationMove(const XMFLOAT3& pos, const XMFLOAT3& tar, const float& factor)
{
	//�J�����̃|�W�V�����ƃ^�[�Q�b�g�Z�b�g(��Ԃ��Ȃ���ύX)
	XMVECTOR vCamPos = XMVectorLerp(XMLoadFloat3(&_position), XMLoadFloat3(&pos), factor);
	XMVECTOR vCamTar = XMVectorLerp(XMLoadFloat3(&_target), XMLoadFloat3(&tar), factor);
	ARGUMENT_INITIALIZE(_position,VectorToFloat3(vCamPos));
	ARGUMENT_INITIALIZE(_target,VectorToFloat3(vCamTar));
}

//�J�������}�E�X�ňړ�(�t���[�����[�N��ł̃V�[����ʂ̎�����)
void Camera::CamMouseMove()
{

	//�}�E�X�̓������擾
	XMFLOAT3 mouseMove = Input::GetMouseMove();

	//�O�x�N�g�������߂�
	ARGUMENT_INITIALIZE(_fFront, _fTarget - _fPosition);

	//�J�����̉�]
	{
		//�^�u�ƃ}�E�X�̍��{�^����������������Ă���̂Ȃ�
		if (Input::IsKey(DIK_LALT) && Input::IsMouseButton(0))
		{

			//�O�x�N�g���ɑ΂��Đ����ȃx�N�g�����~�����̂Ń|�W�V��������ɏ������炵���O�x�N�g�����擾
			XMVECTOR v = _fTarget - (_fPosition + UP_VECTOR);

			//��]�s����쐬
			XMMATRIX mY = XMMatrixRotationY(XMConvertToRadians(mouseMove.x * 0.5f));
			mY *= XMMatrixRotationAxis(XMVector3Cross(_fFront, v), XMConvertToRadians(mouseMove.y * 0.5f));

			//�x�N�g������]
			ARGUMENT_INITIALIZE(_fFront, XMVector3TransformCoord(_fFront, mY));

			//�|�W�V�����X�V
			ARGUMENT_INITIALIZE(_fPosition, VectorToFloat3(_fTarget - _fFront));
		}
	}

	//�Y�[���C���E�Y�[���A�E�g
	{
		//�z�C�[���̓����ŃY�[���C���E�Y�[���A�E�g
		ARGUMENT_INITIALIZE(_fPosition, VectorToFloat3(_fPosition + (XMVector3Normalize(_fFront) * mouseMove.z * 0.01f)));
	}
}

//�œ_��ݒ�
void Camera::SetTarget(const XMFLOAT3& target) { _target = target;}

//�ʒu��ݒ�
void Camera::SetPosition(const XMFLOAT3& position) { _position = position; }

//������̃x�N�g����ݒ�
void Camera::SetUpDirection(XMVECTOR direction) { _UpDirection = direction; }

//��p��ݒ�
void Camera::SetFieldAngle(int angle) 
{
	//��p�X�V
	_field_angle = angle;
	//�v���W�F�N�V�����s��
	_proj = XMMatrixPerspectiveFovLH(XMConvertToRadians((float)_field_angle), (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//�t���[�����[�N��̃J������������
void Camera::FrameCameraInitialize()
{
	ARGUMENT_INITIALIZE(_fPosition, _position);
	ARGUMENT_INITIALIZE(_fTarget, _target);
	ARGUMENT_INITIALIZE(_fUpDirection, _UpDirection);
}

//�œ_���擾
XMFLOAT3 Camera::GetTarget() { return _target; }

//�J�����U��
//���� : �U���̋���
void Camera::SetCameraVibration(float strength,float attenuation)
{
	//�����ݒ�
	ARGUMENT_INITIALIZE(_vibrationQuantity, strength);

	//�����ݒ�
	ARGUMENT_INITIALIZE(_vibrationAttenuation, attenuation);

	//������1�ɂ��Ă���
	ARGUMENT_INITIALIZE(_sign,1);

}

//�ʒu���擾
XMFLOAT3 Camera::GetPosition() { return _position; }

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix() { return _view; }

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }

//�r���{�[�h�p��]�s����擾
XMMATRIX Camera::GetBillboardMatrix() { return _billBoard; }