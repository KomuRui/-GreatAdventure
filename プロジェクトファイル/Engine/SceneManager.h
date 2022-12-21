#pragma once
#include "global.h"
#include "GameObject.h"

//ゲームに登場するシーン
enum SCENE_ID
{
	SCENE_ID_TITLE = 0,
	SCENE_ID_USER_SELECT,
	SCENE_ID_TUTORIAL1,
	SCENE_ID_TUTORIAL2,
	SCENE_ID_HOME,
	SCENE_ID_WORLD1,
	SCENE_ID_MAX
};

//-----------------------------------------------------------
//シーン切り替えを担当するオブジェクト
//-----------------------------------------------------------
class SceneManager : public GameObject
{
private:

	SCENE_ID currentSceneID_;	//現在のシーン
	SCENE_ID nextSceneID_;		//次のシーン;

	bool     loadDrawFlag_;     //ロードをしてる時に画像表示するか

public:

	//コンストラクタ
	//引数：parent	親オブジェクト
	SceneManager(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void StartUpdate() override;

	//シーン切り替え（実際に切り替わるのはこの次のフレーム）
	//引数：next	次のシーンのID
	void ChangeScene(SCENE_ID next);

	//ロードをしてる時に画像表示するかセットする
	void SetLoadDrawFlag(bool flag);

	//現在のシーンIDゲット
	SCENE_ID GetSceneId();
};