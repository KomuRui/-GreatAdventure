#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Texture.h"
#include "../Engine/BillBoard.h"
#include "../Engine/Light.h"

//看板クラス(板ポリゴンにテクスチャをはる)
//描画は板の分しかしないのでMobを継承しないでGameObjectを継承する
class Signboard : public GameObject
{
	// 一つの頂点情報を格納する構造体
	struct VERTEX
	{
		XMFLOAT3 position;
		XMFLOAT3 normal;
		XMFLOAT3 uv;
	};

	//【コンスタントバッファー】
	// GPU(シェーダ側)へ送る数値をまとめた構造体
	//Simple3D.hlslのグローバル変数と対応させる
	struct CONSTANT_BUFFER
	{
		XMMATRIX worldVewProj; 			     //ワールド、ビュー、プロジェクション行列の合成（頂点変換に使用）
		XMMATRIX normalTrans;				 //回転行列と拡大行列の逆行列を合成したもの（法線の変形に使用）
		XMMATRIX world;						 //ワールド行列
		XMFLOAT4 lightDirection;			 //ライトの向き
		XMFLOAT4 cameraPosition;			 //カメラの位置（ハイライトの計算に必要）
		XMFLOAT4 lightPosition;				 //ライトの位置
		XMFLOAT4 pos[LIGHT_TOTAL_NUM];       //ライトの数分の位置
		XMFLOAT4 intensity[LIGHT_TOTAL_NUM]; //ライトの数分の強さ
		FLOAT    isBrightness;				 //明るさ
	};

	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

	std::string fileName_; //ファイルネーム
	Texture* pTexture_;	   //画像

	float polySize_;       //ポリゴンのサイズ

	bool isLookCamera_;    //カメラの方に向けるかどうか

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Signboard(GameObject* parent, std::string fileName, std::string name);

	//ロード
	//引数：fileName	画像ファイル名
	//戻値：成功/失敗
	HRESULT Load();

	/////////////////////オーバーライドする関数//////////////////////
	
	//初期化
	void Initialize() override;

	//更新
	void Update() override {};

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override {};

	/// <summary>
	/// カメラの方向けるかどうかセット
	/// </summary>
	/// <param name="flag">向けるならtrue,向けないのならfalse</param>
	void SetLookCamera(const bool& flag) { isLookCamera_ = flag; }
};

