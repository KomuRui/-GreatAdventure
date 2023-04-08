#include "camera.h"
#include "../DirectX/Direct3D.h"
#include "../ResourceManager/Model.h"
#include "../../Manager/AudioManager/OtherAudioManager/OtherAudioManager.h"
#include "../GUI/ImGuiSet.h"

//////////カメラに必要な変数
XMFLOAT3 _position;
XMFLOAT3 _target;
XMMATRIX _view;
XMMATRIX _proj;
XMVECTOR _UpDirection;
XMMATRIX _billBoard;
int _field_angle;

//////////フレームワーク上でカメラを操作する時に必要な変数
XMFLOAT3 _fPosition;
XMFLOAT3 _fTarget;
XMVECTOR _fUpDirection;
XMVECTOR _fFront;

//////////エフェクトエディタの時に必要な変数
int _keep_field_angle;

//////////振動に必要な変数
float _vibrationQuantity;     //振動量
float _vibrationAttenuation;  //振動の減衰
bool  _vibrationFlag;         //カメラを振動させるかどうか
int   _sign;                  //符号

//初期化（プロジェクション行列作成）
void Camera::Initialize()
{
	ARGUMENT_INITIALIZE(_position,XMFLOAT3(ZERO, 50, -50));	            //カメラの位置
	ARGUMENT_INITIALIZE(_fPosition, _position);							//フレームワーク上でカメラを操作する時のカメラの位置
	ARGUMENT_INITIALIZE(_target,XMFLOAT3(ZERO, ZERO, ZERO));	        //カメラの焦点
	ARGUMENT_INITIALIZE(_fTarget, _target);								//フレームワーク上でカメラを操作する時のカメラの焦点
	ARGUMENT_INITIALIZE(_UpDirection,XMVectorSet(ZERO, 1, ZERO, ZERO)); //カメラの上方向のベクトル
	ARGUMENT_INITIALIZE(_fUpDirection, _UpDirection);					//フレームワーク上でカメラを操作する時のカメラの上方向のベクトル
	ARGUMENT_INITIALIZE(_fFront, STRAIGHT_VECTOR);					    //フレームワーク上でカメラを操作する時のカメラの前方向のベクトル
	ARGUMENT_INITIALIZE(_field_angle,45);                               //カメラの画角
	ARGUMENT_INITIALIZE(_keep_field_angle,45);                               //カメラの画角
	ARGUMENT_INITIALIZE(_vibrationFlag,false);                          //カメラの振動Off
	ARGUMENT_INITIALIZE(_vibrationQuantity, ZERO);                      //振動量
	ARGUMENT_INITIALIZE(_vibrationAttenuation,0.01f);                   //振動の減衰
	ARGUMENT_INITIALIZE(_sign,1);                                       //符号

	//プロジェクション行列
	_proj = XMMatrixPerspectiveFovLH(XMConvertToRadians((float)_field_angle), (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//更新（ビュー行列作成）
void Camera::Update()
{
	//カメラの振動 
	_target = Float3Add(_target,Vibration());

	//画面がゲーム状態なら
	if (Direct3D::GetScreenGameStatus())
	{
		//ビュー行列
		_view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, ZERO),
			XMVectorSet(_target.x, _target.y, _target.z, ZERO), _UpDirection);

		//ビルボード行列
		//（常にカメラの方を向くように回転させる行列。パーティクルでしか使わない）
		_billBoard = XMMatrixLookAtLH(XMVectorSet(ZERO, ZERO, ZERO, ZERO), XMLoadFloat3(&_target) - XMLoadFloat3(&_position), _UpDirection);
		_billBoard = XMMatrixInverse(nullptr, _billBoard);
	}
	else
	{
		//マウスによるカメラ移動
		CamMouseMove();

		//ビュー行列
		_view = XMMatrixLookAtLH(XMVectorSet(_fPosition.x, _fPosition.y, _fPosition.z, ZERO),
			XMVectorSet(_fTarget.x, _fTarget.y, _fTarget.z, ZERO), _fUpDirection);

		//ビルボード行列
		//（常にカメラの方を向くように回転させる行列。パーティクルでしか使わない）
		_billBoard = XMMatrixLookAtLH(XMVectorSet(ZERO, ZERO, ZERO, ZERO), XMLoadFloat3(&_fTarget) - XMLoadFloat3(&_fPosition), _fUpDirection);
		_billBoard = XMMatrixInverse(nullptr, _billBoard);
	}

	
}

//カメラの振動
XMFLOAT3 Camera::Vibration()
{
	//振動量どんどん減らしておく
	if (abs(_vibrationQuantity) < 0.01)
		_vibrationQuantity = ZERO;
	else
		_vibrationQuantity = _sign * (abs(_vibrationQuantity) - _vibrationAttenuation);

	//符号反対に
	_sign *= -1;

	return XMFLOAT3(_vibrationQuantity, _vibrationQuantity, _vibrationQuantity);
}

//補間移動
void Camera::InterpolationMove(const XMFLOAT3& pos, const XMFLOAT3& tar, const float& factor)
{
	//カメラのポジションとターゲットセット(補間しながら変更)
	XMVECTOR vCamPos = XMVectorLerp(XMLoadFloat3(&_position), XMLoadFloat3(&pos), factor);
	XMVECTOR vCamTar = XMVectorLerp(XMLoadFloat3(&_target), XMLoadFloat3(&tar), factor);
	ARGUMENT_INITIALIZE(_position,VectorToFloat3(vCamPos));
	ARGUMENT_INITIALIZE(_target,VectorToFloat3(vCamTar));
}

//カメラをマウスで移動(フレームワーク上でのシーン画面の時だけ)
void Camera::CamMouseMove()
{

	//マウスの動きを取得
	XMFLOAT3 mouseMove = Input::GetMouseMove();

	//前ベクトルを求める
	ARGUMENT_INITIALIZE(_fFront, _fTarget - _fPosition);

	//前ベクトルに対して垂直なベクトルが欲しいのでポジションを上に少しずらした前ベクトルを取得
	XMVECTOR v = _fTarget - (_fPosition + _fUpDirection);

	//カメラの回転・移動
	{
		//タブとマウスの左ボタンが同時押しされているのなら
		if (Input::IsKey(DIK_LALT) && Input::IsMouseButton(0))
		{
			
			//回転行列を作成
			XMMATRIX mY = XMMatrixRotationY(XMConvertToRadians(mouseMove.x * 0.5f));
			mY *= XMMatrixRotationAxis(XMVector3Cross(_fFront, v), XMConvertToRadians(mouseMove.y * 0.5f));

			//ベクトルを回転
			ARGUMENT_INITIALIZE(_fFront, XMVector3TransformCoord(_fFront, mY));

			//ポジション更新
			ARGUMENT_INITIALIZE(_fPosition, VectorToFloat3(_fTarget - _fFront));

			//上ベクトル更新
			ARGUMENT_INITIALIZE(_fUpDirection, XMVector3TransformCoord(_fUpDirection, mY));
		}
		//同時押しされていないかつマウスホイールを押しているのなら
		else if (Input::IsMouseButton(2))
		{
			XMVECTOR horizontal = XMVector3Cross(XMVector3Normalize(_fFront), v);
			XMVECTOR vertical = XMVector3TransformCoord(horizontal,XMMatrixRotationAxis(XMVector3Normalize(_fFront), XMConvertToRadians(90)));

			//位置とターゲット移動
			_fPosition = VectorToFloat3(_fPosition + horizontal * -mouseMove.x * 0.05f);
			_fTarget   = VectorToFloat3(_fTarget + horizontal * -mouseMove.x * 0.05f);
			_fPosition = VectorToFloat3(_fPosition + vertical * mouseMove.y * 0.05f);
			_fTarget   = VectorToFloat3(_fTarget + vertical * mouseMove.y * 0.05f);
		}
	}

	//ズームイン・ズームアウト
	{
		//ホイールの動きでズームイン・ズームアウト
		ARGUMENT_INITIALIZE(_fPosition, VectorToFloat3(_fPosition + (XMVector3Normalize(_fFront) * mouseMove.z * 0.01f)));
		ARGUMENT_INITIALIZE(_fTarget, VectorToFloat3(_fTarget + (XMVector3Normalize(_fFront) * mouseMove.z * 0.01f)));
	}

	//アウトライン
	{
		if (Input::IsMouseButtonDown(0) && !Input::IsKey(DIK_LALT))
		{

			//ビューポート行列
			float w = 0;
			float h = 0;

			//スクリーンの横と縦の長さ入れる
			if (Direct3D::GetGameFull())
			{
				w = Direct3D::screenWidth_ / 2.0f;
				h = Direct3D::screenHeight_ / 2.0f;
			}
			//マップエディタ状態なら
			else
			{
				w = (Direct3D::screenWidth_ / 1.5f) / 2.0f;
				h = (Direct3D::screenHeight_ / 1.5f) / 2.0f + 100;
			}

			XMMATRIX vp = {
				w, 0, 0, 0,
				0,-h, 0, 0,
				0, 0, 1, 0,
				w, h, 0, 1
			};

			//ビューポート行列の逆行列
			XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
			XMMATRIX invPrj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
			XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

			//マウス位置(手前)
			XMFLOAT3 mousePosFront = Input::GetMousePosition();


			//マウス位置(奥)
			XMFLOAT3 mousePosBack = Input::GetMousePosition();
			mousePosBack.z = 1.0f;

			//手前
			XMVECTOR vFront = XMLoadFloat3(&mousePosFront);
			vFront = XMVector3TransformCoord(vFront, invVP * invPrj * invView);

			//奥
			XMVECTOR vBack = XMLoadFloat3(&mousePosBack);
			vBack = XMVector3TransformCoord(vBack, invVP * invPrj * invView);

			RayCastData data;
			XMStoreFloat3(&data.start, vFront);
			XMStoreFloat3(&data.dir, vBack - vFront);
			Model::RayCastOutLineSet(&data,XMFLOAT4(0,1,1,1));
		}
	}
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
	_proj = XMMatrixPerspectiveFovLH(XMConvertToRadians((float)_field_angle), (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//フレームワーク上のカメラを初期化
void Camera::FrameCameraInitialize()
{
	ARGUMENT_INITIALIZE(_fPosition, _position);
	ARGUMENT_INITIALIZE(_fTarget, _target);
	ARGUMENT_INITIALIZE(_fUpDirection, _UpDirection);
}

//エフェクトエディタのカメラにセット
void Camera::SetEffectEditCamera()
{
	KeepGameSceneFieldAngle(_field_angle);
	SetFieldAngle(45);
	ARGUMENT_INITIALIZE(_fPosition, XMFLOAT3(ZERO,5,15));
	ARGUMENT_INITIALIZE(_fTarget, XMFLOAT3(ZERO, ZERO, ZERO));
	ARGUMENT_INITIALIZE(_fUpDirection, UP_VECTOR);
}

//画角を元に戻す
void Camera::UndoFiledAngle() { SetFieldAngle(_keep_field_angle); }

//ゲームシーンの画角を保存しておく
void Camera::KeepGameSceneFieldAngle(int angle) { _keep_field_angle = angle; }

//焦点を取得
XMFLOAT3 Camera::GetTarget() { return _target; }

//カメラ振動
//引数 : 振動の強さ
void Camera::SetCameraVibration(float strength,float attenuation)
{
	//強さ設定
	ARGUMENT_INITIALIZE(_vibrationQuantity, strength);

	//減衰設定
	ARGUMENT_INITIALIZE(_vibrationAttenuation, attenuation);

	//符号を1にしておく
	ARGUMENT_INITIALIZE(_sign,1);

}

//位置を取得
XMFLOAT3 Camera::GetPosition() { return _position; }

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix() { return _view; }

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }

//ビルボード用回転行列を取得
XMMATRIX Camera::GetBillboardMatrix() { return _billBoard; }