#pragma once
#include "../Engine/GameObject.h"

/// <summary>
/// 障害物を設置するクラス
/// </summary>
class MiniGameSetObject : public GameObject
{
	float radius_;           //ステージの半径
	int fpsCount_;           //どのくらいfpsがたっているか
	int generatingSpeed_;    //生成スピード

public:

	//コンストラクタ
	MiniGameSetObject(GameObject* parent);

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

	/////////////////////////関数//////////////////////////

	/// <summary>
	/// オブジェクト生成
	/// </summary>
	void ObjectGeneration();

	/// <summary>
	/// 生成
	/// </summary>
	void Generation();
};

