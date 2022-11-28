#pragma once
#include <list>
#include "Direct3D.h"
#include "Texture.h"
#include <DirectXMath.h>
#include <string>
#include "BillBoard.h"

using namespace DirectX;
using namespace std;

class PolyLine
{
	const float WIDTH_;		//太さ
	const int LENGTH_;		//長さ

	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;	            //画像


	list<XMFLOAT3> positions_;	    //過去length_回分の位置

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

};

