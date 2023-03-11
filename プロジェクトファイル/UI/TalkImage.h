#pragma once
#include "../Engine/GameObject/GameObject.h"
#include "../Engine/ResourceManager/Text.h"

//前方宣言
class CsvReader;

/// <summary>
/// モブと話すときの画像を表示させる基底クラス
/// </summary>
class TalkImage : public GameObject
{
	///////////////////////文字列///////////////////////////

	int drawTextNum_;			//今描画してる文字列の番号
	bool isLastDraw_;			//最後まで描画したかどうか
	bool isButtonPushTextNext_; //ボタンを押して次の文字列に更新するか

	CsvReader* pCsv_; //文字を外部取得するための変数

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

	//デストラクタ
	~TalkImage();

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

	/// <summary>
	/// ボタンを押して描画する文字列を次の文字列に更新する
	/// </summary>
	void ButtonPushDrawTextNext();

	/// <summary>
	/// 次の文字列へ
	/// </summary>
	void NextText();

	/// <summary>
	/// 新しくCsv読み込みをする
	/// </summary>
	/// <param name="fileNamePath">Csv読み込みをしたいファイルパス</param>
	void NewCsvFile(std::string fileNamePath);

	/// <summary>
	/// 使用している文字の変数を取得
	/// </summary>
	/// <returns>使用している文字の変数</returns>
	Text* GetText() { return pText_; }

	/// <summary>
	/// 最後まで描画したかどうか
	/// </summary>
	/// <returns>trueならした,falseならしてない</returns>
	bool IsLastDraw() { return isLastDraw_; }

	/// <summary>
	/// ボタンを押して次の文字列に更新するかをセット
	/// </summary>
	/// <param name="flag">trueならボタンを押して次の文字列に更新するように</param>
	void SetButtonPushTextNext(bool flag) { isButtonPushTextNext_ = flag; }
};

