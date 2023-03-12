#pragma once
#include "../../Engine/GameObject/GameObject.h"


/// <summary>
/// ステージを選択する時のステージモデルのベースとなるクラス
/// </summary>
class StageModelBase : public GameObject
{
protected:

	//モデル番号
	int hModel_;

	//画像番号
	int hPict_;

	//画像のtransform
	Transform tPict_;

	//モデルパスネーム
	std::string modelPathName_;

	//自身が選択されているかどうか
	bool isSelect_;             

	//ステージが解放されているかどうか
	bool isStageRelease_;

public:

	//コンストラクタ
	StageModelBase(GameObject* parent, std::string ModelPath, std::string name);

	/////////////////////オーバーライドする関数//////////////////////
	
	//初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	/////////////////////継承先用の関数//////////////////////

	/// <summary>
	/// 選択されている時にボタンを押した時の処理
	/// </summary>
	virtual void SelectButtonPush() {};

	/// <summary>
	/// 解放されていないステージの時にボタンを押した時の処置
	/// </summary>
	virtual void NotStageReleaseButtonPush();

	//継承先ごとにUpdateでの動き方を変える
	virtual void ChildUpdate() {};

	//継承先用の初期化
	virtual void ChildInitialize() {};

	//継承先用の描画
	virtual void ChildDraw() {};

	//継承先用のスタートアップデート
	virtual void ChildStartUpdate() {};

	//継承先用の開放
	virtual void ChildRelease() {};

	/////////////////////関数//////////////////////

	/// <summary>
	/// 選択されているかセット
	/// </summary>
	/// <param name="flag">trueならセットされている</param>
	void SetSelect(bool flag) { isSelect_ = flag; }
};

