#pragma once
#include "../Engine/GameObject/GameObject.h"

/// <summary>
/// 画像を表示させる基底クラス
/// </summary>
class ImageBase : public GameObject
{
protected:

	int hPict_;                   //画像番号
	std::string ModelNamePath_;   //ファイルネームパス

public:

	//コンストラクタ
	ImageBase(GameObject* parent, std::string modelPath, std::string name);

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

	///////////////////継承先用関数/////////////////////

	/// <summary>
	/// 継承先用の初期化
	/// </summary>
	virtual void ChildInitialize() {};

	/// <summary>
	/// 継承先用のスタートアップデート
	/// </summary>
	virtual void ChildStartUpdate() {};

	/// <summary>
	/// 継承先ごとにUpdateでの動き方を変える
	/// </summary>
	virtual void ChildUpdate() {};

	/// <summary>
	/// 継承先用の描画
	/// </summary>
	virtual void ChildDraw() {};
};

