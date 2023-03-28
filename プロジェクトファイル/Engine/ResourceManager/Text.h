#pragma once
#include "Image.h"
#include "Global.h"

/// <summary>
/// 文字を描画するクラス
/// </summary>
class Text
{

	//////////////////////////画像情報/////////////////////////////

	int hPict_;                     //画像番号
	unsigned int width_, height_;	//1文字分の幅と高さ
	char fileName_[MAX_PATH];       //文字の画像
	unsigned int rowLength_;        //画像の中に何文字並んでいるか

	//////////////////////////表示/////////////////////////////

	float textInterval_; //文字の間隔
	float speed_;        //文字の表示する間隔の速度
	int fpsCount_;       //フレームのカウント
	int totalDrawNum_;   //描画していい総数

public:
	Text();
	~Text();

	/// <summary>
	/// 初期化（デフォルトの設定）
	/// </summary>
	/// <returns>成功／失敗</returns>
	HRESULT Initialize(float speed = 1.0f,float textInterval = 0.005f);

	/// <summary>
	/// 初期化（オリジナルの画像を使いたい時）
	/// </summary>
	/// <param name="fileName">画像ファイル名</param>
	/// <param name="charWidth">画像の１文字の幅（ピクセル）</param>
	/// <param name="charHeight">画像の１文字の高さ（ピクセル）</param>
	/// <param name="rowLength">画像の中に横に何文字並んでいるか</param>
	/// <returns>成功／失敗</returns>
	HRESULT Initialize(const char* fileName, const unsigned int charWidth, const unsigned int charHeight, const unsigned int rowLength, float speed = 1.0f, float textInterval = 0.005f);

	/// <summary>
	/// 描画（文字列:数字）
	/// </summary>
	/// <param name="x">表示位置（左上）</param>
	/// <param name="y">表示位置（左上）</param>
	/// <param name="str">表示したい文字列</param>
	/// <param name="ratio">表示する文字の倍率</param>
	void NumberDraw(int x, int y, const char* str, float ratio = 1.0f, float textInterval = 0.005f);

	/// <summary>
    /// 描画（整数値）
    /// </summary>
    /// <param name="x">表示位置（左上）</param>
    /// <param name="y">表示位置（左上）</param>
    /// <param name="value">表示したい値</param>
    /// <param name="ratio">表示する文字の倍率</param>
	void NumberDraw(int x, int y, int value, float ratio = 1.0f, float textInterval = 0.005f);

	/// <summary>
	/// 描画（文字列）一文字ごとに徐々に表示する
	/// </summary>
	/// <param name="x">表示位置（左上）</param>
	/// <param name="y">表示位置（左上）</param>
	/// <param name="str">表示したい文字列</param>
	/// <param name="ratio">表示する文字の倍率</param>
	/// <returns>trueなら最後まで描画されている,falseなら最後まで描画されていない</returns>
	bool SlowlyDraw(int x, int y, const wchar_t* str,float ratio = 1.0f, float textInterval = 0.005f);

	/// <summary>
	/// 描画（文字列）を表示する
	/// </summary>
	/// <param name="x">表示位置（左上）</param>
	/// <param name="y">表示位置（左上）</param>
	/// <param name="str">表示したい文字列</param>
	/// <param name="ratio">表示する文字の倍率</param>
	/// <returns>trueなら最後まで描画されている,falseなら最後まで描画されていない</returns>
	void Draw(int x, int y, const wchar_t* str, float ratio = 1.0f, float textInterval = 0.005f);

	/// <summary>
	/// 描画していい総数をセット
	/// </summary>
	/// <param name="num">セットしたい総数</param>
	void SetTotalDrawNum(int num) { totalDrawNum_ = num; }

	/// <summary>
	/// 描画スピードをセット
	/// </summary>
	/// <param name="spd">セットしたいスピード</param>
	void SetDrawSpeed(float spd) { speed_ = spd * 60; }

	/// <summary>
	/// 描画していい総数をリセット
	/// </summary>
	void ResetTotalDrawNum() { totalDrawNum_ = (int)ZERO; }

	//解放
	void Release();
};

