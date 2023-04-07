#pragma once

//インクルード
#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>

//リンカ
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

#define TEX_DIV 4	//テクスチャのサイズ　＝　画面サイズ÷この値

//-----------------------------------------------------------
//画面の描画に関する処理
//-----------------------------------------------------------
namespace Direct3D
{
	////////////////////////外部からもアクセスする変数群///////////////////////////////
	//【デバイス】
	//描画を行うための環境やリソースの作成に使う
	extern ID3D11Device*           pDevice_;

	//【コンテキスト】
	//GPUに命令を出すためのやつ
	extern ID3D11DeviceContext*    pContext_;


	//■シェーダー関連で必要なセット
	enum SHADER_TYPE
	{
		SHADER_3D,			  //3D
		SHADER_2D,			  //2D
		SHADER_UNLIT,		  //当たり判定用
		SHADER_BILLBOARD,	  //ビルボード
		SHADER_SIGNBOARD,	  //看板
		SHADER_FADE_IN,		  //フェードイン
		SHADER_FADE_OUT,	  //フェードアウト
		SHADER_REVERS_COLOR,  //色反転
		SHADER_NORMALMAP,     //ノーマルマップ
		SHADER_OUTLINE,       //アウトライン
		SHADER_MAX			  //シェーダの数
	};

	struct SHADER_BUNDLE
	{
		//【頂点入力レイアウト情報】
		//1つの頂点データがどんな情報をどんな順番で格納してるか（位置と色と法線と…とか）
		ID3D11InputLayout *pVertexLayout;

		//【頂点シェーダ】
		//シェーダー（〇〇.hlsl）の中の頂点シェーダー（VS）部分をコンパイルしたものが入る
		//シェーダーはハードによって動作が異なるので、実行時にコンパイルする。
		ID3D11VertexShader *pVertexShader;

		//【ピクセルシェーダ】
		//シェーダー（〇〇.hlsl）の中のピクセルシェーダー（PS）部分をコンパイルしたものが入る
		ID3D11PixelShader *pPixelShader;

		//【ラスタライザ】
		//頂点の表示位置確定後、画面のどのピクセルを光らせればいいか求めるもの
		ID3D11RasterizerState*	pRasterizerState;
	};
	extern SHADER_BUNDLE shaderBundle[SHADER_MAX];

	//■ブレンドモード
	enum BLEND_MODE
	{
		BLEND_DEFAULT, BLEND_ADD, BLEND_MAX
	};

	//その他
	extern int		screenWidth_;		//スクリーンの幅
	extern int		screenHeight_;		//スクリーンの高さ
	extern bool		isDrawCollision_;	//コリジョンを表示するかフラグ

	////////////////////////ここからは関数///////////////////////////////

	//初期化処理
	//引数：hWnd			ウィンドウハンドル
	//引数：screenWidth		スクリーンの幅
	//引数：screenHeight	スクリーンの高さ
	HRESULT Initialize(HWND hWnd, int screenWidth, int screenHeight);

	//シェーダー関連で必要なセット準備
	void InitShaderBundle();

	//今から描画するShaderBundleを設定
	//引数：type	SHADER_3D, SHADER_2D, SHADER_UNLITのどれか
	void SetShader(SHADER_TYPE type);

	//ShaderBundleをゲット
	SHADER_TYPE GetShader();

	//ブレンドモードの変更
	//引数：blendMode	BLEND_DEFAULT	通常
	//					BLEND_ADD		加算合成（パーティクル用）
	void SetBlendMode(BLEND_MODE blendMode);

	//描画開始
	void BeginDrawToTexture();

	void BeginDraw();

	void ScreenDraw();
	
	//描画終了
	void EndDraw();

	//開放処理
	void Release();

	//時間が止まっているのか取得
	bool GetTimeScale();

	//時間を止めるか設定
	void SetTimeScale(bool a);

	//時間が止まっているのか取得
	bool GetGameFull();

	//ゲーム画面フルにするかどうかセット
	void SetGameFull(bool a);

	//画面がゲーム状態なのか取得
	bool GetScreenGameStatus();

	//画面がゲーム状態にするかどうかセット
	void SetScreenGameStatus(bool a);

	//背景色を設定
	void SetBackScreenColor(XMFLOAT4 color);

	//三角形と線分（レイ）の衝突判定（衝突判定に使用）
	//引数：start　		レイのスタート位置
	//引数：direction	レイの方向
	//引数：v0,v1,v2	三角形の各頂点位置
	//引数：distance	衝突点までの距離を返す
	//戻値：衝突したかどうか
	bool Intersect(XMFLOAT3& start, XMFLOAT3& direction, XMFLOAT3 &v0, XMFLOAT3& v1, XMFLOAT3& v2, float* distance, XMVECTOR* pos);

	//Zバッファへの書き込みON/OFF
	//引数：isWrite	  true=書き込みON／false=書き込みOFF
	void SetDepthBafferWriteEnable(bool isWrite);
};

