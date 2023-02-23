#pragma once
#include "../Mob/Mob.h"

/// <summary>
/// 動画用のPlayer
/// </summary>
class PlayerMovie : public Mob
{
	//ムービー用のカメラのベクトル
	XMVECTOR vMovieCam_;

public:

	//コンストラクタ
	PlayerMovie(GameObject* parent, std::string modelPath, std::string name);

	/////////////////////オーバーライドする関数//////////////////////
	
	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;

	//のカメラの処理
	void CameraBehavior();

};

