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


	static XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	static float RangeCalculation(XMFLOAT3 a, XMFLOAT3 b)
	{
		    return (sqrt(pow(a.x - b.x, 2) +
			             pow(a.y - b.y, 2) +
			             pow(a.z - b.z, 2)));
	}

	static XMFLOAT3 VectorToFloat3(XMVECTOR v)
	{
		XMFLOAT3 a;
		XMStoreFloat3(&a, v);

		return a;
	}

};

