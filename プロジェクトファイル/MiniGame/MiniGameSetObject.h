#pragma once
#include "../Engine/GameObject/GameObject.h"
#include <stdio.h>

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

	//////////////////生成の仕方の関数/////////////////////

	void Center();       //真ん中
	void Edge();         //端
	void MultipleEdge(); //複数体に端

	/// <summary>
	///  枠の真ん中に生成
	/// </summary>
	/// <typeparam name="T">クラスによって分けるため</typeparam>
	/// <param name="Class">生成するクラス</param>
	template <class T>
	void Instantiate_Center(XMFLOAT3 pos);

	/// <summary>
	/// 枠の端に生成
	/// </summary>
	/// <typeparam name="T">クラスによって分けるため</typeparam>
	/// <param name="Class">生成するクラス</param>
	template <class T>
	void Instantiate_Edge(XMFLOAT3 pos);

	/// <summary>
	/// 枠の端に複数体生成
	/// </summary>
	/// <typeparam name="T">クラスによって分けるため</typeparam>
	/// <param name="Class">生成するクラス</param>
	template <class T>
	void Instantiate_Multiple_Edge(XMFLOAT3 pos);

};
