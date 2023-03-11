#pragma once
#include "../Engine/GameObject/GameObject.h"

/// <summary>
/// ボスが倒されたシーン用
/// </summary>
class BossEnemyKill : public GameObject
{
	
	int hModel_; //モデル番号

private:

	//コンストラクタ
	BossEnemyKill(GameObject* parent);

	/////////////////////オーバーライドする関数///////////////////////////

	//初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override {};

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override {};
};

