#include "SelectPlanetController.h"
#include "../Engine/DirectX/Input.h"
#include "../Engine/GameObject/Camera.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Engine/ResourceManager/CreateStage.h"
#include "../UI/UserSelectScene/NewFileUI.h"

//定数
namespace
{
	static const XMFLOAT3 CAM_MOVE_POS = { ZERO,ZERO,15 };  //カメラの移動位置
	static const float STATUS_CHANGE_DISTANCE = 5.0f;		//状態を変更する距離
	static const float INTERPOLATION_FACTOR = 0.01f;        //補間係数
	static const float PAD_STICK_SLOPE_RIGHT = 0.8f;        //パッドのLスティックの右の傾き
	static const float PAD_STICK_SLOPE_LEFT = -0.8f;        //パッドのLスティックの左の傾き
	static const float PAD_STICK_SLOPE_UP = 0.8f;           //パッドのLスティックの上の傾き
	static const float PAD_STICK_SLOPE_DOWN = -0.8f;        //パッドのLスティックの下の傾き

}

//ユーザー情報を選択するときに管理
namespace SelectPlanetController
{
	//状態
	SelectPlanetStatus userSelectStatus_;

	//各星の情報
	UserPlanetBase* firstPlanetInfo_;  //1
	UserPlanetBase* secondPlanetInfo_; //2
	UserPlanetBase* thirdPlanetInfo_;  //3

	//選択している星
	UserPlanetBase* selectPlanet_;

	//新規作成した時の選択したアイコンのモデルパス
	std::string newCreateIconModelPath_;

	//XとYの前回入力保存用
	float beforeXSlope = ZERO;
	float beforeYSlope = ZERO;

	//XとYの現在の入力保存用
	float NowXSlope = ZERO;
	float NowYSlope = ZERO;


	//星をセット
	void SetUserPlanetFirst(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(firstPlanetInfo_,pUserPlanet); }
	void SetUserPlanetSecond(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(secondPlanetInfo_,pUserPlanet); }
	void SetUserPlanetThird(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(thirdPlanetInfo_,pUserPlanet); }


	//初期化
	void Initialize()
	{
		ARGUMENT_INITIALIZE(newCreateIconModelPath_, "");
		ARGUMENT_INITIALIZE(selectPlanet_, nullptr);
		ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::Selecting);
	}

	//更新処理
	void Update()
	{
		//状態によって分ける
		switch(userSelectStatus_)
		{
		//選択中
		case SelectPlanetStatus::Selecting:
			NowSelect();
			break;

		//選択
		case SelectPlanetStatus::Select:
			Select();
			break;

		//新規作成
		case SelectPlanetStatus::NewCreate:
			NewCreate();
			break;

		//既存
		case SelectPlanetStatus::Existing:

			break;

		//その他
		default:
			break;
		}

	}

    //選択中
	void NowSelect()
	{
		//すべての星がストップしている状況かどうか
		bool IsStop = (firstPlanetInfo_->GetStatus() == PlanetStatus::Stop) && (secondPlanetInfo_->GetStatus() == PlanetStatus::Stop) && (thirdPlanetInfo_->GetStatus() == PlanetStatus::Stop);

		//前回の傾きを取得
		ARGUMENT_INITIALIZE(beforeXSlope, NowXSlope);
		ARGUMENT_INITIALIZE(beforeYSlope, NowYSlope);

		//PadLスティックの傾きを保存
		ARGUMENT_INITIALIZE(NowXSlope, Input::GetPadStickL().x);
		ARGUMENT_INITIALIZE(NowYSlope, Input::GetPadStickL().y);


		//左にスティックを傾けたら
		if (NowXSlope <= PAD_STICK_SLOPE_LEFT && beforeXSlope >= PAD_STICK_SLOPE_LEFT && IsStop)
		{
			//各ポジション格納
			firstPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());
			
			//選択されているか取得
			bool first =  firstPlanetInfo_->IsSelect();
			bool second = secondPlanetInfo_->IsSelect();
			bool third =  thirdPlanetInfo_->IsSelect();

			//選択されているかどうかで次の星を選択状態に
			if (first)  thirdPlanetInfo_->SetIsSelect(true);
			if (second) firstPlanetInfo_->SetIsSelect(true);
			if (third)  secondPlanetInfo_->SetIsSelect(true);

		}
		//右にスティックを傾けたら
		else if (NowXSlope >= PAD_STICK_SLOPE_RIGHT && beforeXSlope <= PAD_STICK_SLOPE_RIGHT && IsStop)
		{
			//各ポジション格納
			firstPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());

			//選択されているか取得
			bool first = firstPlanetInfo_->IsSelect();
			bool second = secondPlanetInfo_->IsSelect();
			bool third = thirdPlanetInfo_->IsSelect();

			//選択されているかどうかで次の星を選択状態に
			if (first)  secondPlanetInfo_->SetIsSelect(true);
			if (second) thirdPlanetInfo_->SetIsSelect(true);
			if (third)  firstPlanetInfo_->SetIsSelect(true);
		}

		//Aボタンを押したなら
		if (Input::IsPadButton(XINPUT_GAMEPAD_A) && IsStop)
		{
			//状態が変更できていなかったら選択されている星に入れる
			if (!firstPlanetInfo_->SetFallStatus())
				ARGUMENT_INITIALIZE(selectPlanet_, firstPlanetInfo_);

			//状態が変更できていなかったら選択されている星に入れる
			if (!secondPlanetInfo_->SetFallStatus())
				ARGUMENT_INITIALIZE(selectPlanet_, secondPlanetInfo_);

			//状態が変更できていなかったら選択されている星に入れる
			if (!thirdPlanetInfo_->SetFallStatus())
				ARGUMENT_INITIALIZE(selectPlanet_, thirdPlanetInfo_);

			//選択状態に
			ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::Select);
		}

	}

	//選択
	void Select() { CameraMove(); }

	//新規作成
	void NewCreate()
	{
		//もし情報がないのならこの先処理しない
		if (newCreateIconModelPath_ == "") return;

		//選択されてる星の状態を変更
		selectPlanet_->SetStatus(PlanetStatus::Explosion, newCreateIconModelPath_);

		//新規作成
		selectPlanet_->CreateNewFile();

		//ユーザー選択状態を既存に変更
		ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::Existing);
	}

	//既存
	void Existing()
	{

	}

	//カメラ移動
	void CameraMove(){ 

		//カメラのポジションを移動
		XMFLOAT3 pos = Camera::GetPosition();
		Camera::SetPosition(VectorToFloat3(XMVectorLerp(XMLoadFloat3(&pos),XMLoadFloat3(&CAM_MOVE_POS), INTERPOLATION_FACTOR)));
	
		//もし距離が近くなったら
		if (RangeCalculation(pos, CAM_MOVE_POS) < STATUS_CHANGE_DISTANCE)
		{
			//作成したステージ削除
			GameManager::GetpStage()->GetCreateStage()->AllCreateStageDelete();

			//選択状態に
			ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::NewCreate);

			//次のUIを表示
			Instantiate<NewFileUI>(GameManager::GetpStage());
		}
	}

	//ユーザー情報を選択するときの状態を取得
	SelectPlanetStatus GetStatus() { return userSelectStatus_; }

    //アイコンモデルパスを設定
	void SetIconModelPath(std::string path) { ARGUMENT_INITIALIZE(newCreateIconModelPath_, path);  }
};