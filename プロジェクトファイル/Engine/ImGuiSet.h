#pragma once
#include "GameObject.h"
#include "../Player.h"
#include "../Block/Block.h"

//最大のImguiで出せるオブジェクトサイズ
const int MAX_OBJECT_SIZE = 50;


/// <summary>
/// Debug用のUIを表示する
/// </summary>
namespace ImGuiSet
{

	//初期化
	void Initialize();

	//描画
	void Draw();

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
};