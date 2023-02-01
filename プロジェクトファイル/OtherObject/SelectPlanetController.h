#pragma once
#include "UserPlanetBase.h"
#include <vector>

/// <summary>
/// ユーザー情報を選択するときの状態(新規作成や既存のデータから始める状態など)
/// </summary>
enum class SelectPlanetStatus
{
	Selecting,  //選択途中
	Select,     //選択
	NewCreate,  //新規作成
	Existing,   //既存
};

//ユーザー情報を選択するときの管理
namespace SelectPlanetController
{
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 各星情報をセット
	/// </summary>
	/// <param name="pUserPlanet"></param>
	void SetUserPlanetFirst(UserPlanetBase* pUserPlanet);
	void SetUserPlanetSecond(UserPlanetBase* pUserPlanet);
	void SetUserPlanetThird(UserPlanetBase* pUserPlanet);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 選択中
	/// </summary>
	void NowSelect();

	/// <summary>
	/// 選択
	/// </summary>
	void Select();

	/// <summary>
	/// カメラ移動
	/// </summary>
	void CameraMove();

	/// <summary>
	/// ユーザー情報を選択するときの状態を取得
	/// </summary>
	/// <returns>状態</returns>
	SelectPlanetStatus GetStatus();
};

