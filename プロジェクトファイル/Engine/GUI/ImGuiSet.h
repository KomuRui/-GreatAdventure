#pragma once
#include "../GameObject/GameObject.h"
#include "../../Player/PlayerBase.h"
#include "../../Block/Block.h"

//最大のImguiで出せるオブジェクトサイズ
static const int MAX_OBJECT_SIZE = 50;

//エディタモード
enum class Mode
{
	GAME = 0,
	SCENE,
	EFFECT_EDIT,
	START,
	STOP
};

/// <summary>
/// Debug用のUIを表示する
/// </summary>
namespace ImGuiSet
{

	//初期化
	void Initialize();

	//ゲーム画面がフルサイズではない時の描画
	void GameScreenNotFullDraw();

	//ゲーム画面がフルサイズの時の描画
	void GameScreenFullDraw();

	//開放
	void Release();

	////////////////////////////////////ステージ作成用ImGui///////////////////////////////////////

	/// <summary>
	/// ステージ作成するImGuiのUIを出してくれる
	/// </summary>
	void StageCreater();

	/// <summary>
	/// 3Dオブジェクト作成
	/// </summary>
	void Create3D();

	/// <summary>
	/// 看板作成
	/// </summary>
	void CreateSigeboard();

	/// <summary>
	/// カメラの遷移作成(コライダーに当たったらカメラのポジション変える機能)
	/// </summary>
	void CreateCameraTransition();

	/// <summary>
	/// 画像作成
	/// </summary>
	void CreateImage();

	//////////////////////////////ステージのオブジェクトのトランスフォーム表示////////////////////////////

	/// <summary>
	/// ステージオブジェのトランスフォームすべて表示するImGuiを表示
	/// </summary>
	void StageObjImGuiDisplay();

	/// <summary>
	/// ステージオブジェのトランスフォームすべて表示
	/// </summary>
	void StageObjTransformDisplay(GameObject* pObj);

	//////////////////////////////////////ログ表示///////////////////////////////////////

	/// <summary>
	/// デバッグログを管理する(ImGuiはここで表示する)
	/// </summary>
	void DebugLogManager();

	/// <summary>
	/// 任意の値を表示してくれる
	/// </summary>
	/// <param name="text">表示したい変数の名前</param>
	/// <param name="num">表示したい値</param>
	void DebugLog(std::string text ,int num);
	void DebugLog(std::string text, float num);
	void DebugLog(std::string text, bool num);
	void DebugLog(std::string text, XMFLOAT3 num);
	void DebugLog(std::string text, std::string str);

	///////////////////////////////シーン変更表示///////////////////////////////////////

	/// <summary>
	/// シーン変更用ボタン表示
	/// </summary>
	void SceneChangeButton();

	///////////////////////////////ゲーム画面設定///////////////////////////////////////

	/// <summary>
	/// ゲーム画面がフルサイズではない時の設定
	/// </summary>
	void GameScreenNotFullPreference();

	/// <summary>
	/// ゲーム画面がフルサイズの時の設定
	/// </summary>
	void GameScreenFullPreference();

	/// <summary>
	/// エフェクトエディタのGUI
	/// </summary>
	void EffectEditGui();

	/// <summary>
	/// 画面の状態設定
	/// </summary>
	void ScreenStatusPreference();

	/// <summary>
	/// 各セット関数
	/// </summary>
	/// <param name="mode">セットしたいモード</param>
	void SetScreenMode(int mode);
	void SetGameMode(int mode);

	/// <summary>
	/// 各ゲット関数
	/// </summary>
	/// <returns>エディタモードを取得</returns>
	int GetScreenMode();

	///////////////////////////////プロセスメモリ表示///////////////////////////////////////

	/// <summary>
	/// プロセスメモリ表示
	/// </summary>
	void ProcessMemory();

	///////////////////////////////ファイル(インポート・エクスポート)///////////////////////////////////////

	/// <summary>
	/// ファイル欄表示
	/// </summary>
	void File();

	/// <summary>
	/// ステージインポート
	/// </summary>
	void Import();

	/// <summary>
	/// ステージオブジェエクスポートするための関数
	/// </summary>
	/// <param name="pObj">SceneManagerを入れる</param>
	void ExportStageObjTransform(GameObject* pObj);

	/// <summary>
	/// ステージエクスポート
	/// </summary>
	void Export();
};