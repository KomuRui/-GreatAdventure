#pragma once
#include "../Engine/GameObject/GameObject.h"
#include "../Engine/Component/EasingMove.h"
#include "../Engine/ResourceManager/Text.h"

/// <summary>
/// 星の状態
/// </summary>
enum class PlanetStatus
{
	Stop,          //停止
	Move,          //移動
	Fall,          //落ちる
	Explosion,     //爆発
	ReturnPosition,//元の位置に戻る
	MAX_STATUS
};

/// <summary>
/// ユーザーの星のベースクラス
/// </summary>
class UserPlanetBase : public GameObject
{
protected:

	//ユーザ情報
	void(*UserCreateNewFile)(std::string);  //ユーザ情報を新規登録する時に呼ぶ関数

	//モデル
	int hModel_; 				//モデル番号格納用
	std::string ModelNamePath_; //ファイルネームパス

	//画像
	int hNewFilePict_;          //新規作成画像番号
	int hCoinPict_;             //コイン画像
	int hStagePict_;            //ステージ画像
	int hCrossPict_;            //×画像
	
    //状態
	PlanetStatus status_;      

	//その他
	Text* pText_;			    //コインの数表示する用
	EasingMove* pEasingRotate_; //回転イージング用
	EasingMove* pEasingMove_;   //移動イージング用
	XMFLOAT3 nextPos_;          //移動するときの次のポジション
	bool isSelect_;             //自身が選択されているかどうか

public:

	//コンストラクタ
	UserPlanetBase(GameObject* parent, std::string modelPath, std::string name);

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

	//指定した時間で呼ばれるメソッド
    void TimeMethod() override;

	/////////////////////継承先用の関数//////////////////////

	//継承先ごとにUpdateでの動き方を変える
	virtual void ChildUpdate() {};

	//継承先用の初期化
	virtual void ChildInitialize() {};

	//継承先用の描画
	virtual void ChildDraw() {};

	//継承先用のスタートアップデート
	virtual void ChildStartUpdate() {};

	//継承先用の開放
	virtual void ChildRelease() {};

	/////////////////////関数//////////////////////

	/// <summary>
	/// 次の位置へ移動
	/// </summary>
	void NextPositionToMove();

	/// <summary>
	/// 次のポジションセット
	/// </summary>
	/// <param name="nextPos">次のポジション</param>
	void SetNextPosition(const XMFLOAT3& nextPos); 

	/// <summary>
	/// 選択されていないのなら落ちる
	/// </summary>
	void Fall();

	/// <summary>
	/// 爆発してモデル変更
	/// </summary>
	void Explosion();

	/// <summary>
	/// 爆発エフェクト
	/// </summary>
	void ExplosionEffect();

	/// <summary>
	/// 新規作成
	/// </summary>
	void CreateNewFile();

	/// <summary>
	/// 元の位置に戻る
	/// </summary>
	void ReturnPosition();

	/// <summary>
	/// イージング移動をセット
	/// </summary>
	void SetEasingMove();

	/// <summary>
	/// 戻るイージング移動をセット
	/// </summary>
	void SetReturnEasingMove();

	/// <summary>
	/// 状態をセット
	/// </summary>
	/// <param name="status">セットしたい状態</param>
	void SetStatus(PlanetStatus status,std::string iconModelPath = "");

	/// <summary>
	/// 落ちる状態に変更
	/// </summary>
	/// <returns>trueなら状態を変更した</returns>
	bool SetFallStatus();

	/// <summary>
	/// 状態をゲット
	/// </summary>
	/// <returns>状態</returns>
	PlanetStatus GetStatus() { return status_; }

	/// <summary>
	/// 選択されているかどうか(選択されていたら選択状態解除)
	/// </summary>
	/// <returns>trueなら選択されている</returns>
	bool IsSelectToChange();

	/// <summary>
	/// 選択されているかどうか
	/// </summary>
	/// <returns>trueなら選択されている</returns>
	bool IsSelect();

	/// <summary>
	/// 選択されているかどうかセット
	/// </summary>
	/// <param name="flag">trueなら選択されている,falseならされていない</param>
	void SetIsSelect(const bool& flag);

	/// <summary>
	/// 既存ファイルかどうか
	/// </summary>
	/// <returns>trueなら既存ファイル</returns>
	bool IsExisting();
};

