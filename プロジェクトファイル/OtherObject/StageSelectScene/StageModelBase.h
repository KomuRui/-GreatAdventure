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

	//モデルパスネーム
	std::string modelPathName_;

	//自身が選択されているかどうか
	bool isSelect_;             

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
};

