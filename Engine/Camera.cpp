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
XMFLOAT3 _targetPos;
float _strength;
bool  _vibrationFlag;

//初期化（プロジェクション行列作成）
void Camera::Initialize()
{
	_position = XMFLOAT3(0, 50, -50);	    //カメラの位置
	_target = XMFLOAT3( 0, 0, 0);	        //カメラの焦点
	_UpDirection = XMVectorSet(0, 1, 0, 0); //カメラの上方向のベクトル
	_targetPos = XMFLOAT3(0, 0, 0);         //振動するときのポジション初期化
	_field_angle = 45;                      //カメラの画角
	_vibrationFlag = false;                 //カメラの振動Off

	//プロジェクション行列
	_proj = XMMatrixPerspectiveFovLH(XMConvertToRadians(_field_angle), (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//更新（ビュー行列作成）
void Camera::Update()
{
	//ビュー行列
	_view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, 0),
		XMVectorSet(_target.x, _target.y, _target.z, 0), _UpDirection);

	//ビルボード行列
	//（常にカメラの方を向くように回転させる行列。パーティクルでしか使わない）
	_billBoard = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), XMLoadFloat3(&_target) - XMLoadFloat3(&_position), XMVectorSet(0, 1, 0, 0));
	_billBoard = XMMatrixInverse(nullptr, _billBoard);

	//カメラ振動フラグがtrueならカメラを振動させる
	if (_vibrationFlag)Vibration();
}

//カメラの振動
void Camera::Vibration()
{
	//補間しながら目的のポジションまで変更していく
	_position = Transform::VectorToFloat3(XMVectorLerp(XMLoadFloat3(&_position), XMLoadFloat3(&_targetPos), 0.1));

	//距離が0.01より小さいなら次の目的地を設定
	if (Transform::RangeCalculation(_position, _targetPos) < 0.01)
	{
		_targetPos = { _position.x,-_position.y,_position.z };
	}
}

//焦点を設定
void Camera::SetTarget(XMFLOAT3 target) { _target = target;}

//位置を設定
void Camera::SetPosition(XMFLOAT3 position) { _position = position; }

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
	//強さ設定(1以上にしたいから1を足しておく)
	_strength = strength + 1;

	//振動するときのポジション設定
	_targetPos = XMFLOAT3(_position.x,_position.y * _strength,_position.z);

	//振動フラグON
	_vibrationFlag = true;
}

//位置を取得
XMFLOAT3 Camera::GetPosition() { return _position; }

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix() { return _view; }

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }

//ビルボード用回転行列を取得
XMMATRIX Camera::GetBillboardMatrix() { return _billBoard; }