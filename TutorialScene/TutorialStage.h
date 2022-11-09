#pragma once
#include "../Engine/GameObject.h"
#include <vector>

//■■シーンを管理するクラス
class TutorialStage : public GameObject
{
	//ステージ種類の数
	enum StageCategory
	{
		first,
		Two,
		MAX
	};

	//背景モデル
	int spaceModel_;

	//背景モデルのトランスフォーム
	Transform tSpace_;

	//モデル番号
	int hModel_[MAX];

	//球体に物体を乗せるために疑似モデル
	int CirclePolyModel_;

	//ステージごとのPlayerの初期位置
	XMFLOAT3 pos_[MAX];

	//現在どこのステージを表示してるかのステータス
	int status_;

	//3Dのモデルを使用しているかどうか
	bool threeDflag_[MAX];

	//ブロックのポジションを保存しておくVector(後にブロックとの当たり判定を行うために使う)
	std::vector<Transform> tBlock_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TutorialStage(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override;

	//そこにブロックがあるかどうか,もしあったら重なっている分ずらす
	//引数:status 0:右 1:左 2:上 3:下 
	bool IsBlock(XMFLOAT3 *pos, int status);

	//モデル番号のゲット関数
	int GethModel() { return hModel_[status_]; }

	//球体に物体を乗せるために疑似モデル番号のゲット関数
	int GetPolyModell() { return CirclePolyModel_; }

	//Posのゲット関数
	XMFLOAT3 GetPos() { return pos_[status_]; }

	//3Dの動きをさせたいか
	bool GetthreeDflag() { return threeDflag_[status_]; }

	//ステージの切り替え
	void StatusPlus() { status_++; }

};

