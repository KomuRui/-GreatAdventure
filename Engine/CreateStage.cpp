#include "CreateStage.h"
#include "../Gimmick/Coin.h"
#include "../Gimmick/Warp.h"
#include "../Block/ItemBlock.h"
#include "../Enemy/Enemy.h"
#include "../Enemy/DropEnemy.h"
#include "../Enemy/PigEnemy.h"
#include "../Block/BrickBlock.h"
#include "../Block/NormalBlock.h"
#include "../Block/TransparentBlock.h"
#include "../Mob/MainMob.h"
#include "../Gimmick/Signboard.h"
#include "../Gimmick/MoveFloor.h"
#include "Light.h"
#include "CameraTransitionObject.h"
#include "../Gimmick/ShineLight.h"
#include "../Gimmick/ShineLightController.h"
#include "../Enemy/BulletPigEnemy.h"
#include "../OtherObject/TitleModel.h"
#include "../OtherObject/TitleModelPlayer.h"
#include "../OtherObject/TitleModelPrincess.h"
#include "../OtherObject/TitleComplexModel.h"
#include "GameObject.h"
#include <fstream>

//コンストラクタ
CreateStage::CreateStage()
	:createShineController_(false)
{
}

//オブジェクト作成
void CreateStage::CreateObject(GameObject* parent, std::string ModelPathName, std::string inName, Transform t, XMFLOAT3 camPos)
{
	/////////////////////Mob///////////////////////

	if (inName == "Mob")
	{
		Mob* pNewObject = new Mob(parent, ModelPathName, inName);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "MainMob")
	{
		MainMob* pNewObject = new MainMob(parent, ModelPathName, inName);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->SetAngle(t.rotate_.y);
		pNewObject->Initialize();
	}

	/////////////////////OtherObject///////////////////////

	if (inName == "TitleModel")
	{
		TitleModel* pNewObject = new TitleModel(parent);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "TitleModelPlayer")
	{
		TitleModelPlayer* pNewObject = new TitleModelPlayer(parent);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "TitleModelPrincess")
	{
		TitleModelPrincess* pNewObject = new TitleModelPrincess(parent);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "TitleComplexModel")
	{
		TitleComplexModel* pNewObject = new TitleComplexModel(parent);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
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

	}

	/////////////////////Light/////////////////////////

	if (inName == "Light")
	{
		Light::SetPositionAndIntensity(XMFLOAT4(t.position_.x, t.position_.y, t.position_.z, 0), t.scale_.x);
	}

	/////////////////////Gimmick///////////////////////

	if (inName == "Coin")
	{
		Coin* pNewObject = new Coin(parent, ModelPathName, inName);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "Warp" || inName == "Warp1")
	{
		Warp* pNewObject = new Warp(parent, ModelPathName, "Warp");
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		if (inName == "Warp1")pNewObject->SetNumber(1);
	}
	if (inName == "Signboard")
	{
		Signboard* pNewObject = new Signboard(parent, ModelPathName, "Signboard");
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "MoveFloor")
	{
		MoveFloor* pNewObject = new MoveFloor(parent, ModelPathName, "MoveFloor");
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if ("ShineLight" == inName)
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

		ItemBlock* pNewObject = new ItemBlock(parent, ModelPathName, "ItemBlock");
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		//回転するように設定
		if (inName == "ItemBlock1")pNewObject->SetStatus(1);

		//ブロックなので追加
		tBlock_.push_back(pNewObject);
	}
	if (inName == "BrickBlock")
	{

		BrickBlock* pNewObject = new BrickBlock(parent, ModelPathName, "BrickBlock");
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		//ブロックなので追加
		tBlock_.push_back(pNewObject);
	}
	if (inName == "NormalBlock")
	{

		NormalBlock* pNewObject = new NormalBlock(parent, ModelPathName, "NormalBlock");
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		//ブロックなので追加
		tBlock_.push_back(pNewObject);
	}
	if (inName == "TransparentBlock")
	{

		TransparentBlock* pNewObject = new TransparentBlock(parent, ModelPathName, "TransparentBlock");
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		//ブロックなので追加
		tBlock_.push_back(pNewObject);
	}

	/////////////////////Enemy///////////////////////

	if (inName == "Enemy")
	{
		Enemy* pNewObject = new Enemy(parent, ModelPathName, inName);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "DropEnemy")
	{
		DropEnemy* pNewObject = new DropEnemy(parent, ModelPathName, inName);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "PigEnemy")
	{
		PigEnemy* pNewObject = new PigEnemy(parent, ModelPathName, inName);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "BulletPigEnemy")
	{
		BulletPigEnemy* pNewObject = new BulletPigEnemy(parent, ModelPathName, inName);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->SetAngle(t.rotate_.y);
		pNewObject->Initialize();
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