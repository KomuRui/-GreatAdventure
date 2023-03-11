#pragma once
#include "../../../Stage.h"

//ステージクラス
class WorldStage2 : public Stage
{
	//ステージ描画するかどうか
	bool isStageDraw_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	WorldStage2(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override {};

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	/// <summary>
	/// ステージ描画するかどうか
	/// </summary>
	/// <param name="flag">trueなら描画する</param>
	void SetStageDraw(bool flag) { isStageDraw_ = flag; }

	/// <summary>
	/// ムービー作成
	/// </summary>
	void CreateMovie();

	/// <summary>
	/// ボスステージ作成
	/// </summary>
	void CreateBossStage();

	/// <summary>
	/// ボス倒すシーン作成
	/// </summary>
	void CreateBossKill();
};

