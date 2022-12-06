#include "camera.h"
#include "Direct3D.h"

XMFLOAT3 _position;
XMFLOAT3 _target;
XMMATRIX _view;
XMMATRIX _proj;
XMVECTOR _UpDirection;
XMMATRIX _billBoard;
int _field_angle;

//////////振動に必要な変数
XMFLOAT3 _targetPos;          //
float _vibrationQuantity;     //振動量
bool  _vibrationFlag;         //カメラを振動させるかどうか
int   _sign;                  //符号

//初期化（プロジェクション行列作成）
void Camera::Initialize()
{
	_position = XMFLOAT3(0, 50, -50);	    //カメラの位置
	_target = XMFLOAT3( 0, 0, 0);	        //カメラの焦点
	_UpDirection = XMVectorSet(0, 1, 0, 0); //カメラの上方向のベクトル
	_targetPos = XMFLOAT3(0, 0, 0);         //振動するときのポジション初期化
	_field_angle = 45;                      //カメラの画角
	_vibrationFlag = false;                 //カメラの振動Off
	_vibrationQuantity = 0;
	_sign = 1;

	//プロジェクション行列
	_proj = XMMatrixPerspectiveFovLH(XMConvertToRadians(_field_angle), (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//更新（ビュー行列作成）
void Camera::Update()
{
	//カメラの振動 
	_target = Transform::Float3Add(_target,Vibration());

	//ビュー行列
	_view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, 0),
		XMVectorSet(_target.x, _target.y, _target.z, 0), _UpDirection);

	//ビルボード行列
	//（常にカメラの方を向くように回転させる行列。パーティクルでしか使わない）
	_billBoard = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), XMLoadFloat3(&_target) - XMLoadFloat3(&_position), XMVectorSet(0, 1, 0, 0));
	_billBoard = XMMatrixInverse(nullptr, _billBoard);
}

//カメラの振動
XMFLOAT3 Camera::Vibration()
{
	//振動量どんどん減らしておく
	if (abs(_vibrationQuantity) < 0.01)
		_vibrationQuantity = 0.0;
	else
		_vibrationQuantity = _sign * (abs(_vibrationQuantity) - 0.01);

	//符号反対に
	_sign *= -1;

	return XMFLOAT3(_vibrationQuantity, _vibrationQuantity, _vibrationQuantity);
}

//焦点を設定
void Camera::SetTarget(const XMFLOAT3& target) { _target = target;}

//位置を設定
void Camera::SetPosition(const XMFLOAT3& position) { _position = position; }

//上方向のベクトルを設定
void Camera::SetUpDirection(XMVECTOR direction) { _UpDirection = direction; }

//画角を設定
void Camera::SetFieldAngle(int angle) 
{
	//画角更新
	_field_angle = angle;
	//プロジェクション行列
	_proj = XMMatrixPerspectiveFovLH(XMConvertToRadians(_field_angle), (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//焦点を取得
XMFLOAT3 Camera::GetTarget() { return _target; }

//カメラ振動
//引数 : 振動の強さ
void Camera::SetCameraVibration(float strength)
{
	//強さ設定
	_vibrationQuantity = strength;

	//符号を1にしておく
	_sign = 1;

}

//位置を取得
XMFLOAT3 Camera::GetPosition() { return _position; }

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix() { return _view; }

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }

//ビルボード用回転行列を取得
XMMATRIX Camera::GetBillboardMatrix() { return _billBoard; }