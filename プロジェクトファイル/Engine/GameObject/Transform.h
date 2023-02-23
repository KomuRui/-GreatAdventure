#pragma once
#include <DirectXMath.h>
#include "windowsnumerics.h"

using namespace DirectX;


//-----------------------------------------------------------
//位置、向き、拡大率などを管理するクラス
//-----------------------------------------------------------
class Transform
{
public:
	XMMATRIX matTranslate_;	//移動行列
	XMMATRIX matRotate_;	//回転行列	
	XMMATRIX matScale_;		//拡大行列
	XMFLOAT3 position_;		//位置
	XMFLOAT3 rotate_;		//向き
	XMFLOAT3 scale_;		//拡大率
	XMMATRIX mmRotate_;	    //回転行列	
	bool     mFlag_;        //フラグ
	Transform* pParent_;	//親オブジェクトの情報

	//コンストラクタ
	Transform();

	//デストラクタ
	~Transform();

	//各行列の計算
	//引数：なし
	//戻値：なし
	void Calclation();

	//ワールド行列を取得
	//引数：なし
	//戻値：その時点でのワールド行列
	XMMATRIX GetWorldMatrix();

	/// <summary>
	/// 親のワールド行列を取得
	/// </summary>
	/// <returns>親のワールド行列</returns>
	XMMATRIX GetParentWorldMatrix();
};

