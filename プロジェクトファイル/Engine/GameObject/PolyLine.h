#pragma once
#include <list>
#include "../DirectX/Direct3D.h"
#include "../DirectX/Texture.h"
#include <DirectXMath.h>
#include <string>
#include "../DirectX/BillBoard.h"

using namespace DirectX;
using namespace std;

class PolyLine
{
	float width_;		//太さ
	int length_;		//長さ

	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;	            //画像


	list<XMFLOAT3> positions_;	    //過去length_回分の位置

	XMFLOAT3 color_;                //色
	float alpha_;                   //透明度
	bool  moveAlpha_;               //徐々に透明にしておく

public:
	//コンストラクタ
	PolyLine();


	//現在の位置を記憶させる
	//引数：pos	現在の位置
	void AddPosition(XMFLOAT3 pos);

	//ロード
	//引数：fileName	画像ファイル名
	//戻値：成功/失敗
	HRESULT Load(std::string fileName);

	//描画
	void Draw();

	//徐々に透明になるように設定
	void SetMoveAlphaFlag() { moveAlpha_ = true; }

	//解放
	void Release();

	/// <summary>
	/// 色セット
	/// </summary>
	void SetColor(XMFLOAT3 color) { color_ = color; }

	/// <summary>
	/// 長さセット
	/// </summary>
	/// <param name="len">セットしたい長さ</param>
	void SetLengh(int len) { length_ = len; }

	/// <summary>
	/// 太さセット
	/// </summary>
	/// <param name="width">セットしたい長さ</param>
	void SetWidth(float width) { width_ = width; }
};

