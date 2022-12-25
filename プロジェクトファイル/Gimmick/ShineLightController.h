#pragma once
#include "ShineLight.h"
#include "../Engine/GameObject.h"

/// <summary>
/// 光るライトギミックを管理するクラス
/// </summary>
class ShineLightController : public GameObject
{
	//光るライトをすべて保管しておく変数(第一:ライトのオブジェクト,第二:光っているかどうか)
	std::vector<std::pair<ShineLight*,bool>> controller_;

	//ギミック発動させたときに使うカメラの位置とターゲット
	XMFLOAT3 camPos_;
	XMFLOAT3 camTar_;
	
	//今何番目を見ているか
	int nowNumber_;

	//順番通りに光らせることが出来たか
	bool success_;

	//調べるかどうか
	bool checkFlag_;

	//カメラ動かすかどうか
	bool camMove_;

	//指定した時間で関数を呼ぶ時にどの関数呼ぶか決める列挙
	enum TimeMethodStatus
	{
		MOVE_FLOOR,
		CAM_RESET
	};

	//指定した時間で関数を呼ぶ時にどの関数呼ぶか決める用の状態
	int TimeMethodStatus_;


public:

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

	////////////////////関数//////////////////////

	//コンストラクタ
	ShineLightController(GameObject* parent);

	/// <summary>
	/// すべて光っているかどうか
	/// </summary>
	/// <returns>光っているならtrue,一つでも光っていないならfalse</returns>
	bool IsAllShine(); 

	/// <summary>
	/// 順番通り光らせているか調べる
	/// </summary>
	void CheckinOrderShine();

	/// <summary>
	/// カメラを動かす
	/// </summary>
	void CameraMove();

	////////////////////セッターゲッター//////////////////////

	/// <summary>
	/// 自身のコントローラーにセット
	/// </summary>
	/// <param name="shine">セットしたいShineLightのポインタ</param>
	void SetShineLight(ShineLight* shine) { std::pair<ShineLight*, bool> a = { shine, false }; controller_.push_back(a);  }

	/// <summary>
	/// カメラの位置とカメラのターゲットセット
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="tar">ターゲット</param>
	void SetCamPosCamTar(XMFLOAT3 pos, XMFLOAT3 tar) { camPos_ = pos; camTar_ = tar; }
};

