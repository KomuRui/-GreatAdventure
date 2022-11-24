#pragma once
#include <vector>
#include "GameObject.h"
#include "../Player.h"
#include "../Block/Block.h"

const int MAX_OBJECT_SIZE = 50;

//■■シーンを管理するクラス
class ImGuiSet : public GameObject
{
	//表示させたオブジェクトを格納する場所
	//first->モデル番号
	//second->モデル番号ごとのトランスフォーム
	std::vector<std::pair<int,Transform>>obj;

	//3Dを作るボタンを押していたらtrue
	bool Create3Dflag;

	//看板を作るボタンを押したら
	bool CreateSigeboardflag;

	//3Dを何個作ったか
	int ObjectCount;

	//看板何個作ったか
	int SigeboardCount;

	//トランスフォーム保存するために持っておく
	Player* pPlayer_;

	//各ステージのブロックのトランスフォームを保存
	std::vector<Block*> tBlock;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ImGuiSet(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	void Create3D();

	void CreateSigeboard();

	//開放
	void Release() override;

	void StartUpdate() override;

	void CreateStage(std::string filename);

	void InstantiateString(std::string ModelPathName, std::string inName, Transform t);

	std::vector<Block*> GetTransformBlock() { return tBlock; }
};