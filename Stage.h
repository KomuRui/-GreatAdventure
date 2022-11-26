#pragma once
#include "Engine/GameObject.h"
#include <vector>

//前方宣言
class Block;

//各ステージクラスのもととなるクラス
class Stage : public GameObject
{
protected:

	//モデルの種類
	enum StageCategory
	{
		Base,   //ステージのモデル
		Space,  //背景の宇宙モデル
		MAX
	};

	//背景モデル
	int spaceModel_;

	//背景モデルのトランスフォーム
	Transform tSpace_;

	//ステージ作る時の名前
	std::string StageFileNmae_[MAX];

	//ステージごとの画角
	int fieldAngle_[MAX];

	//ステージごとのライトの強さ
	int lightIntensity_[MAX];

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

	//ブロックを保存しておくVector(後にブロックとの当たり判定を行うために使う)
	std::vector<Block*> tBlock_;

public:
};

