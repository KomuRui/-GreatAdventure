#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Text.h"

/// <summary>
/// モブと話すときの画像を表示させる基底クラス
/// </summary>
class TalkImage : public GameObject
{
	///////////////////////文字列///////////////////////////



	/////////////////////////画像///////////////////////////

	int hBasePict_;      //ベース画像番号
	int hCharaPict_;     //キャラ画像番号
	int hNextPict_;      //Next画像番号

	Transform tBase_;    //ベースTransform
	Transform tChara_;   //キャラTransform
	Transform tNext_;    //NextTransform

	////////////////////////テキスト/////////////////////////

	Text* pText_;        //文字表示する用

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TalkImage(GameObject* parent);

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
};

