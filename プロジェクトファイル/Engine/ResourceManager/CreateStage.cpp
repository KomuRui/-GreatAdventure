#include "CreateStage.h"
#include "../../Player/PlayerMovie.h"
#include "../../Player/Player3D.h"
#include "../../Gimmick/Coin.h"
#include "../../Gimmick/Warp.h"
#include "../../Block/ItemBlock.h"
#include "../../Enemy/Enemy.h"
#include "../../Enemy/DropEnemy.h"
#include "../../Enemy/PigEnemy.h"
#include "../../Enemy/BossEnemy.h"
#include "../../Enemy/BossEnemyMovie.h"
#include "../../Enemy/BossEnemyKill.h"
#include "../../Block/BrickBlock.h"
#include "../../Block/NormalBlock.h"
#include "../../Block/TransparentBlock.h"
#include "../../Mob/MainMob.h"
#include "../../Mob/TalkMainMob.h"
#include "../../Gimmick/Signboard.h"
#include "../../Gimmick/MoveFloor.h"
#include "../GameObject/Light.h"
#include "../GameObject/CameraTransitionObject.h"
#include "../../Gimmick/ShineLight.h"
#include "../../Gimmick/ShineLightController.h"
#include "../../Gimmick/FlyBall.h"
#include "../../Enemy/BulletPigEnemy.h"
#include "../../OtherObject/TitleModel.h"
#include "../../OtherObject/TitleModelPlayer.h"
#include "../../OtherObject/TitleModelPrincess.h"
#include "../../OtherObject/TitleComplexModel.h"
#include "../../OtherObject/UserPlanetBase.h"
#include "../../OtherObject/UserPlanet1.h"
#include "../../OtherObject/UserPlanet2.h"
#include "../../OtherObject/UserPlanet3.h"
#include "../../OtherObject/SelectPlanetController.h"
#include "../../OtherObject/Water.h"
#include "../../OtherObject/ShootingStar.h"
#include "../../OtherObject/WaterCurrentStick.h"
#include "../../UI/ImageBase.h"
#include "../../UI/TitleScene/TitleStartImage.h"
#include "../../UI/ScalingImage.h"
#include "../../UI/UserSelectScene/Button/NewFileCancelButton.h"
#include "../../UI/UserSelectScene/Button/NewFileOkButton.h"
#include "../../UI/UserSelectScene/Button/DropIconButton.h"
#include "../../UI/UserSelectScene/Button/MainCharIconButton.h"
#include "../../UI/UserSelectScene/Button/MobIconButton.h"
#include "../../UI/UserSelectScene/Button/PigIconButton.h"
#include "../../UI/UserSelectScene/Button/PrincessIconButton.h"
#include "../../UI/UserSelectScene/Button/UserGameCancelButton.h"
#include "../../UI/UserSelectScene/Button/UserGameStartButton.h"
#include "../../Manager/ButtonManager/ButtonManager.h"
#include "../GameObject/GameObject.h"
#include <fstream>


//コンストラクタ
CreateStage::CreateStage()
	:createShineController_(false)
{
}

//オブジェクト作成
void CreateStage::CreateObject(GameObject* parent, std::string ModelPathName, std::string inName, Transform t, XMFLOAT3 camPos)
{
	////////////////////////Movie/////////////////////////
	
	if (inName == "BossEnemyMovie")
	{
		InstantiateMob3D<BossEnemyMovie>(parent, ModelPathName, inName, t);
	}
	if (inName == "PlayerMovie")
	{
		InstantiateMob3D<PlayerMovie>(parent, ModelPathName, inName, t);
	}
	/////////////////////Player///////////////////////

	if (inName == "Player3D")
	{
		GameManager::SetpPlayer(InstantiateMob3D<Player3D>(parent, ModelPathName, inName, t));
		GameManager::GetpPlayer()->SetPosition(t.position_);
	}

	/////////////////////Mob///////////////////////

	if (inName == "Mob")
	{
		InstantiateMob3D<Mob>(parent, ModelPathName, inName, t);
	}
	if (inName == "MainMob" || inName == "2DTalkMainMob")
	{
		MainMob* pNewObject = InstantiateMob3D<MainMob>(parent, ModelPathName, inName, t);

		//もし話すなら
		if (inName == "2DTalkMainMob")
			pNewObject->SetTalk(true);
	}
	if (inName == "TalkMainMob")
	{
		InstantiateMob3D<TalkMainMob>(parent, ModelPathName, inName, t);
	}

	/////////////////////UI///////////////////////

	if (inName == "ImageBase")
	{
		InstantiateNormal<ImageBase>(parent, ModelPathName, inName, t);
	}
	if (inName == "TitleStartImage")
	{
		InstantiateNormal<TitleStartImage>(parent, ModelPathName, inName, t);
	}
	if (inName == "ScalingImage")
	{
		InstantiateNormal<ScalingImage>(parent, ModelPathName, inName, t);
	}
	if (inName == "NewFileOkButton")
	{
		InstantiateButton<NewFileOkButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "NewFileCancelButton")
	{
		InstantiateButton<NewFileCancelButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "MainCharIconButton")
	{
		InstantiateButton<MainCharIconButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "PrincessIconButton")
	{
		InstantiateButton<PrincessIconButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "PigIconButton")
	{
		InstantiateButton<PigIconButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "MobIconButton")
	{
		InstantiateButton<MobIconButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "DropIconButton")
	{
		InstantiateButton<DropIconButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "UserGameCancelButton")
	{
		InstantiateButton<UserGameCancelButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "UserGameStartButton")
	{
		InstantiateButton<UserGameStartButton>(parent, ModelPathName, inName, t);
	}

	/////////////////////OtherObject///////////////////////

	if (inName == "TitleModel")
	{
		InstantiateNormal<TitleModel>(parent, t);
	}
	if (inName == "TitleModelPlayer")
	{
		InstantiateNormal<TitleModelPlayer>(parent, t);
	}
	if (inName == "TitleModelPrincess")
	{
		InstantiateNormal<TitleModelPrincess>(parent, t);
	}
	if (inName == "TitleComplexModel")
	{
		InstantiateNormal<TitleComplexModel>(parent, t);
	}
	if (inName == "UserPlanet1")
	{
		SelectPlanetController::SetUserPlanetFirst(InstantiatePlanet<UserPlanet1>(parent, ModelPathName, inName, t));
	}
	if (inName == "UserPlanet2")
	{
		SelectPlanetController::SetUserPlanetSecond(InstantiatePlanet<UserPlanet2>(parent, ModelPathName, inName, t));
	}
	if (inName == "UserPlanet3")
	{
		SelectPlanetController::SetUserPlanetThird(InstantiatePlanet<UserPlanet3>(parent, ModelPathName, inName, t));
	}
	if (inName == "Water")
	{
		InstantiateNormal<Water>(parent, ModelPathName, inName, t);
	}
	if (inName == "ShootingStar")
	{
		InstantiateNormal<ShootingStar>(parent, ModelPathName, inName, t);
	}
	if (inName.find("WaterCurrentStick") != std::string::npos)
	{
		WaterCurrentStick *p = InstantiateNormal<WaterCurrentStick>(parent, ModelPathName, "WaterCurrentStick", t);
		
		//もし回転タイプなら
		if (inName == "WaterCurrentStickRotation")
			p->SetType(WaterCurrentStickType::ROTATION);
	}

	/////////////////////Camera////////////////////////

	if (inName == "Camera")
	{
		//カメラ情報を入れる変数用意
		StageCameraTransition information;

		//各情報初期化
		information.CameraPosition = camPos;
		information.CameraTarget = t.rotate_;
		information.CollisionSize = t.scale_;

		//コンストラクタ呼ぶ
		CameraTransitionObject* pNewObject = new CameraTransitionObject(parent, information);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}

		//回転と拡大を0に初期化する
		ARGUMENT_INITIALIZE(t.rotate_, XMFLOAT3(0, 0, 0));
		ARGUMENT_INITIALIZE(t.scale_, XMFLOAT3(0, 0, 0));

		pNewObject->SetTransform(t);
		pNewObject->Initialize();
		createStageAllObject_.push_back(pNewObject);
	}

	/////////////////////Light/////////////////////////

	if (inName == "Light")
	{
		Light::CreateLight(XMFLOAT4(t.position_.x, t.position_.y, t.position_.z, 0), t.scale_.x);
	}

	/////////////////////Gimmick///////////////////////

	if (inName == "Coin")
	{
		InstantiateNormal<Coin>(parent, ModelPathName, inName, t);
	}
	if (inName.find("Warp") != std::string::npos)
	{
		Warp* pNewObject =  InstantiateNormal<Warp>(parent, ModelPathName, "Warp", t);

		if (inName == "Warp1")pNewObject->SetWarpType(InverseNormalAndDown);
		if (inName == "GoMiniGameSelectWarp")
		{
			pNewObject->SetSceneId(SCENE_ID_MINIGAME_LEVEL_SELECT);
			pNewObject->SetObjectName(inName);
		}
		if (inName == "GoMiniGameWarp")
		{
			pNewObject->SetSceneId(SCENE_ID_MINIGAME);
			pNewObject->SetObjectName(inName);
		}

		GameManager::SetpWarp(pNewObject);
	}
	if (inName.find("Signboard") != std::string::npos)
	{
		Signboard* pNewObject = new Signboard(parent, ModelPathName, inName);

		//看板なのでシーンマネージャーの子にする
		GameManager::GetpSceneManager()->PushBackChild(pNewObject);

		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		//もしカメラの方向けるなら
		if (inName == "LookCamSignboard")
			pNewObject->SetLookCamera(true);

		createStageAllObject_.push_back(pNewObject);
	}
	if (inName == "MoveFloor")
	{
		InstantiateNormal<MoveFloor>(parent, ModelPathName, inName, t);
	}
	if (inName == "FlyBall")
	{
		InstantiateMob3D<FlyBall>(parent, ModelPathName, inName, t);
	}
	if (inName == "ShineLight")
	{
		if (!createShineController_)
		{
			ShineLightController* NewObject = new ShineLightController(parent);
			if (parent != nullptr)
			{
				parent->PushBackChild(NewObject);
			}
			NewObject->SetCamPosCamTar(camPos, t.rotate_);
			ARGUMENT_INITIALIZE(t.rotate_, XMFLOAT3(0, 0, 0));

			NewObject->SetTransform(t);
			NewObject->Initialize();
			ARGUMENT_INITIALIZE(createShineController_, true);
		}

		ShineLight* pNewObject = new ShineLight(parent, ModelPathName, "ShineLight");
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
		ShineLightController* pShineLightController = (ShineLightController*)parent->FindObject("ShineLightController");
		pShineLightController->SetShineLight(pNewObject);
	}

	/////////////////////Block///////////////////////

	if (inName == "ItemBlock" || inName == "ItemBlock1")
	{
		ItemBlock* pNewObject = InstantiateBlock<ItemBlock>(parent, ModelPathName, inName, t);

		//回転するように設定
		if (inName == "ItemBlock1")pNewObject->SetType(1);
	}
	if (inName == "BrickBlock")
	{
		InstantiateBlock<BrickBlock>(parent, ModelPathName, inName, t);
	}
	if (inName == "NormalBlock")
	{
		InstantiateBlock<NormalBlock>(parent, ModelPathName, inName, t);
	}
	if (inName == "TransparentBlock")
	{

		TransparentBlock* pNewObject = new TransparentBlock(parent, ModelPathName, "TransparentBlock");

		//透明なのでシーンマネージャの子供にする
		GameManager::GetpSceneManager()->PushBackChild(pNewObject);
		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		//ブロックなので追加
		tBlock_.push_back(pNewObject);
		createStageAllObject_.push_back(pNewObject);
	}

	/////////////////////Enemy///////////////////////

	if (inName == "Enemy")
	{
		InstantiateMob3D<Enemy>(parent, ModelPathName, inName, t);
	}
	if (inName == "DropEnemy")
	{
		InstantiateMob3D<DropEnemy>(parent, ModelPathName, inName, t);
	}
	if (inName == "PigEnemy")
	{
		InstantiateMob3D<PigEnemy>(parent, ModelPathName, inName, t);
	}
	if (inName == "BulletPigEnemy")
	{
		InstantiateMob3D<BulletPigEnemy>(parent, ModelPathName, inName, t);
	}
	if (inName == "BossEnemy")
	{
		InstantiateMob3D<BossEnemy>(parent, ModelPathName, inName, t);
	}
	if (inName == "BossEnemyKill")
	{
		InstantiateNormal<BossEnemyKill>(parent, ModelPathName, inName, t);
	}
}

//各ステージのファイルロードしステージを作成してくれる
void CreateStage::LoadFileCreateStage(GameObject* parent, std::string filename)
{
	//ファイルオープン
	const char* fileName = filename.c_str();
	std::ifstream ifs(fileName);

	//データを1列入れる変数
	std::string buf;

	//必要な各パラメータを保存する用の文字列配列(pos.x,pos,y,pos.zとか)
	std::string data[14] = { "" };

	//,の数
	int sum = 0;

	//末尾まで読む
	while (!ifs.eof())
	{
		//1列bufに格納
		std::getline(ifs, buf);

		//bufのサイズ分ループ
		for (int i = 0; i < buf.size(); i++)
		{
			//各パラメータを一つずつdataに格納していく
			if (buf[i] != ',')
			{
				data[sum] += buf[i];
			}
			else
				sum++;
		}

		//各パラメータを変数に格納していく
		std::string ModelPathName = data[0];
		std::string Name = data[1];

		Transform t;

		t.position_ = { std::stof(data[2]),std::stof(data[3]),std::stof(data[4]) };
		t.rotate_ = { std::stof(data[5]),std::stof(data[6]),std::stof(data[7]) };
		t.scale_ = { std::stof(data[8]),std::stof(data[9]),std::stof(data[10]) };

		t.pParent_ = parent->GetTransform();

		//カメラのポジション入れる変数
		XMFLOAT3 camPos;

		//カメラのポジションを必要とするオブジェクトなら
		if (Name.find("Camera") != std::string::npos || Name == "ShineLight")
			camPos = { std::stof(data[11]),std::stof(data[12]),std::stof(data[13]) };
		//それ以外は使わないので0にしておく
		else
			camPos = { 0,0,0 };

		//パラメータを基にオブジェクト作成
		CreateObject(parent,ModelPathName, Name, t, camPos);

		//すべて初期化
		for (int i = 0; i < 14; i++)
		{
			data[i] = "";
		}
		sum = 0;
	}


}

//各ステージのファイルロードだけしてくれる
void CreateStage::LoadFile(GameObject* parent, std::string filename)
{
	//ファイルオープン
	const char* fileName = filename.c_str();
	std::ifstream ifs(fileName);

	//データを1列入れる変数
	std::string buf;

	//必要な各パラメータを保存する用の文字列配列(pos.x,pos,y,pos.zとか)
	std::string data[14] = { "" };

	//,の数
	int sum = 0;

	//末尾まで読む
	while (!ifs.eof())
	{
		//1列bufに格納
		std::getline(ifs, buf);

		//bufのサイズ分ループ
		for (int i = 0; i < buf.size(); i++)
		{
			//各パラメータを一つずつdataに格納していく
			if (buf[i] != ',')
			{
				data[sum] += buf[i];
			}
			else
				sum++;
		}

		//情報を格納しておく変数
		CreateStageInfo info;


		//各パラメータを変数に格納していく
		info.parent = parent;
		info.ModelPathName = data[0];
		info .inName = data[1];

		Transform t;

		info.t.position_ = { std::stof(data[2]),std::stof(data[3]),std::stof(data[4]) };
		info.t.rotate_ = { std::stof(data[5]),std::stof(data[6]),std::stof(data[7]) };
		info.t.scale_ = { std::stof(data[8]),std::stof(data[9]),std::stof(data[10]) };


		//カメラのポジションを必要とするオブジェクトなら
		if (info.inName.find("Camera") != std::string::npos || info.inName == "ShineLight")
			info.camPos = { std::stof(data[11]),std::stof(data[12]),std::stof(data[13]) };
		//それ以外は使わないので0にしておく
		else
			info.camPos = { 0,0,0 };

		info_.push_back(info);

		//すべて初期化
		for (int i = 0; i < 14; i++)
		{
			data[i] = "";
		}
		sum = 0;
	}

}

//LoadFileを使ってロードしたファイルを元にステージを作成
void CreateStage::LoadFileBasedCreateStage()
{
	for (auto i = info_.begin(); i != info_.end(); i++)
	{
		CreateObject((*i).parent, (*i).ModelPathName, (*i).inName, (*i).t, (*i).camPos);
	}
}

//作成したステージをすべて削除
void CreateStage::AllCreateStageDelete()
{
	//作ったステージ分回す
	for (auto i = createStageAllObject_.begin(); i != createStageAllObject_.end();)
	{
		(*i)->KillMe();
		i = createStageAllObject_.erase(i);
	}

	//もしPlayerがいるのなら
	if (GameManager::GetpPlayer() != nullptr)GameManager::GetpPlayer()->KillMe();
}

/// <summary>
/// 作成したステージすべて描画と更新しないように
/// </summary>
void CreateStage::AllCreateStageInvisibleAndLeave()
{
	//作ったステージ分回す
	for (auto i = createStageAllObject_.begin(); i != createStageAllObject_.end(); i++)
	{
		(*i)->Invisible();
		(*i)->Leave();
	}
}

/// <summary>
/// 作成したステージすべて描画と更新するように
/// </summary>
void CreateStage::AllCreateStageVisibleAndEnter()
{
	//作ったステージ分回す
	for (auto i = createStageAllObject_.begin(); i != createStageAllObject_.end(); i++)
	{
		(*i)->Visible();
		(*i)->Enter();
	}
}

//普通の生成
template <class T>
T* CreateStage::InstantiateNormal(GameObject* pParent,std::string modelPath, std::string name, Transform t)
{
	T* pNewObject = new T(pParent, modelPath,name);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->SetTransform(t);
	pNewObject->Initialize();
	createStageAllObject_.push_back(pNewObject);

	return pNewObject;
}

//普通型の生成(名前とモデルパス指定しない)
template <class T>
T* CreateStage::InstantiateNormal(GameObject* pParent, Transform t)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->SetTransform(t);
	pNewObject->Initialize();

	return pNewObject;
}

//Mobを継承した3Dオブジェ生成
template <class T>
T* CreateStage::InstantiateMob3D(GameObject* pParent, std::string modelPath, std::string name, Transform t)
{
	T* pNewObject = new T(pParent, modelPath, name);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->SetTransform(t);
	pNewObject->SetAngle(t.rotate_.y);
	pNewObject->Initialize();
	createStageAllObject_.push_back(pNewObject);

	return pNewObject;
}

//ボタンの生成
template <class T>
T* CreateStage::InstantiateButton(GameObject* pParent, std::string modelPath, std::string name, Transform t)
{
	T* p = InstantiateNormal<T>(pParent, modelPath, name, t);
	ButtonManager::AddButton(p);

	return p;
}

//ブロックの生成
template <class T>
T* CreateStage::InstantiateBlock(GameObject* pParent, std::string modelPath, std::string name, Transform t)
{
	T* p = InstantiateNormal<T>(pParent, modelPath, name, t);
	tBlock_.push_back(p);

	return p;
}

//星の生成
template <class T>
T* CreateStage::InstantiatePlanet(GameObject* pParent, std::string modelPath, std::string name, Transform t)
{
	T* pNewObject = new T(pParent, modelPath, name);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->SetTransform(t);
	pNewObject->Initialize();

	return pNewObject;
}