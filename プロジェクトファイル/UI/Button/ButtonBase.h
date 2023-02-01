#pragma once
#include "../ImageBase.h"

/// <summary>
/// ボタンクラス
/// </summary>
class Button : public ImageBase
{
private:

	//押したときの関数ポインタ
	void(*OnPushFunc);

	//ボタン選択された瞬間によぶ関数ポインタ
	void(*ButtonSelect);

	//ボタンが選択されているとき何をするか
	void(*ButtonSelecting);

	//選択されているかどうか
	bool isSelect_;

public:

	//コンストラクタ
	Button(GameObject* parent, std::string modelPath, std::string name);
	
	////////////////////オーバーライドする関数/////////////////////////

	/// <summary>
	/// 継承先用の初期化
	/// </summary>
	virtual void ChildInitialize() override {};

	/// <summary>
	/// 継承先用のスタートアップデート
	/// </summary>
	virtual void ChildStartUpdate()override {};

	/// <summary>
	/// 継承先ごとにUpdateでの動き方を変える
	/// </summary>
	virtual void ChildUpdate() override {};

	/// <summary>
	/// 継承先用の描画
	/// </summary>
	virtual void ChildDraw()override {};

	/////////////////////////////関数////////////////////////////////

	/// <summary>
	/// ボタンが押されたら何するか
	/// </summary>
	/// <param name="p">実行したい関数ポインタ</param>
    void IsButtonPush(void (*p)()) { p(); }

	/// <summary>
	/// ボタンが選択された瞬間に何をするか
	/// </summary>
	/// <param name="p">実行したい関数ポインタ</param>
	void IsButtonSelect(void (*p)()) { p(); }

	/// <summary>
	/// ボタンが選択されているとき何をするか
	/// </summary>
	/// <param name="p">実行したい関数ポインタ</param>
	void IsButtonSelecting(void (*p)()) { p(); }

	//////////////////////////セットゲット関数/////////////////////////////

	/// <summary>
	/// 選択されているかをセット 
	/// </summary>
	/// <param name="flag">trueなら選択されてる</param>
	void SetSelect(bool flag) { isSelect_ = flag; }

	/// <summary>
	/// 選択されているかを取得
	/// </summary>
	/// <returns>trueなら選択されている</returns>
	bool IsSelect() { return isSelect_; }
};

