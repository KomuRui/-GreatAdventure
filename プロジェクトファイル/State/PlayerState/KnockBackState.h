#pragma once
#include "PlayerState.h"

class PlayerBase;

/// <summary>
/// ノックバック状態
/// </summary>
class KnockBackState : public PlayerState
{
	//ノックバックの方向と距離
	XMVECTOR knockBackDir_;

	//空飛ぶときの元となる上ベクトル
	XMVECTOR vFly_;

	//元となるフライベクトルを保存しておく
	XMVECTOR keepFly_;

	//当たった敵のポジション
	XMFLOAT3 hitEnemyPos_;

public:

	//2D用更新
	void Update2D(PlayerBase* player) override;

	//3D用更新
	void Update3D(PlayerBase* player) override;

	//ミニゲーム用更新
	void UpdateMiniGame(PlayerBase* player) override {};

	//入力によって状態変化する
	void HandleInput(PlayerBase* player) override;

	//状態変化したとき一回だけ呼ばれる関数
	void Enter(PlayerBase* player) override;

	/// <summary>
	/// 当たった敵のポジションをセット
	/// </summary>
	/// <param name="pos">当たった敵のポジション</param>
	void SetHitEnemyPos(const XMFLOAT3& pos) { hitEnemyPos_ = pos; }
};

