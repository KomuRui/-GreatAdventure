#include "SelectPlanetController.h"
#include "../Engine/DirectX/Input.h"
#include "../Engine/GameObject/Camera.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Engine/ResourceManager/CreateStage.h"
#include "../Engine/ResourceManager/Easing.h"
#include "../Engine/Component/EasingMove.h"
#include "../UI/UserSelectScene/NewFileUI.h"
#include "../UI/UserSelectScene/UserGameStartUI.h"
#include "../Scene/UserSelectScene/UserSelectStage.h"
#include "../Manager/AudioManager/OtherAudioManager/OtherAudioManager.h"

//定数
namespace
{
	static const XMFLOAT3 CAM_POS = { ZERO,ZERO, 5 };		//カメラの初期位置
	static const XMFLOAT3 CAM_MOVE_POS = { ZERO,ZERO,15 };  //カメラの移動位置
	static const float STATUS_CHANGE_DISTANCE = 0.5f;		//状態を変更する距離
	static const float INTERPOLATION_FACTOR = 0.01f;        //補間係数
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

	//プレイしている星の番号
	int playPlanetNum_;

	//イージング用
	EasingMove* easing_;

	//カメラのポジション
	XMFLOAT3 camPos_;

	//新規作成した時の選択したアイコンのモデルパス
	std::string newCreateIconModelPath_;

	//星をセット
	void SetUserPlanetFirst(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(firstPlanetInfo_,pUserPlanet); }
	void SetUserPlanetSecond(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(secondPlanetInfo_,pUserPlanet); }
	void SetUserPlanetThird(UserPlanetBase* pUserPlanet) { ARGUMENT_INITIALIZE(thirdPlanetInfo_,pUserPlanet); }


	//初期化
	void Initialize()
	{
		ARGUMENT_INITIALIZE(playPlanetNum_, 1);
		ARGUMENT_INITIALIZE(newCreateIconModelPath_, "");
		ARGUMENT_INITIALIZE(selectPlanet_, nullptr);
		ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::Selecting);
		ARGUMENT_INITIALIZE(easing_, new EasingMove());
		ARGUMENT_INITIALIZE(camPos_, CAM_POS);
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

		//選択中に戻る
		case SelectPlanetStatus::BackSelecting:
			BackSelecting();
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

		//左にスティックを傾けたら
		if (Input::IsPadStickLeftL() && IsStop)
		{
			//音
			OtherAudioManager::ClickAudio();

			//各ポジション格納
			firstPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());
			
			//選択されているか取得
			bool first =  firstPlanetInfo_->IsSelectToChange();
			bool second = secondPlanetInfo_->IsSelectToChange();
			bool third =  thirdPlanetInfo_->IsSelectToChange();

			//選択されているかどうかで次の星を選択状態に
			if (first)
			{
				thirdPlanetInfo_->SetIsSelect(true);
				ARGUMENT_INITIALIZE(playPlanetNum_, 3);
			}
			if (second)
			{
				firstPlanetInfo_->SetIsSelect(true);
				ARGUMENT_INITIALIZE(playPlanetNum_, 1);
			}
			if (third)
			{
				secondPlanetInfo_->SetIsSelect(true);
				ARGUMENT_INITIALIZE(playPlanetNum_, 2);
			}

		}
		//右にスティックを傾けたら
		else if (Input::IsPadStickRightL() && IsStop)
		{
			//音
			OtherAudioManager::ClickAudio();

			//各ポジション格納
			firstPlanetInfo_->SetNextPosition(thirdPlanetInfo_->GetPosition());
			thirdPlanetInfo_->SetNextPosition(secondPlanetInfo_->GetPosition());
			secondPlanetInfo_->SetNextPosition(firstPlanetInfo_->GetPosition());

			//選択されているか取得
			bool first = firstPlanetInfo_->IsSelectToChange();
			bool second = secondPlanetInfo_->IsSelectToChange();
			bool third = thirdPlanetInfo_->IsSelectToChange();

			//選択されているかどうかで次の星を選択状態に
			if (first)
			{
				secondPlanetInfo_->SetIsSelect(true);
				ARGUMENT_INITIALIZE(playPlanetNum_, 2);
			}
			if (second)
			{
				thirdPlanetInfo_->SetIsSelect(true);
				ARGUMENT_INITIALIZE(playPlanetNum_, 3);
			}
			if (third)
			{
				firstPlanetInfo_->SetIsSelect(true);
				ARGUMENT_INITIALIZE(playPlanetNum_, 1);
			}
		}

		//Aボタンを押したなら
		if (Input::IsPadButton(XINPUT_GAMEPAD_A) && IsStop)
		{
			//音
			OtherAudioManager::ClickAudio();

			//状態が変更できていなかったら選択されている星に入れる
			if (!firstPlanetInfo_->SetFallStatus())
			{
				ARGUMENT_INITIALIZE(selectPlanet_, firstPlanetInfo_);
				ARGUMENT_INITIALIZE(playPlanetNum_, 1);
			}

			//状態が変更できていなかったら選択されている星に入れる
			if (!secondPlanetInfo_->SetFallStatus())
			{
				ARGUMENT_INITIALIZE(selectPlanet_, secondPlanetInfo_);
				ARGUMENT_INITIALIZE(playPlanetNum_, 2);
			}

			//状態が変更できていなかったら選択されている星に入れる
			if (!thirdPlanetInfo_->SetFallStatus())
			{
				ARGUMENT_INITIALIZE(selectPlanet_, thirdPlanetInfo_);
				ARGUMENT_INITIALIZE(playPlanetNum_, 3);
			}

			//選択状態に
			ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::Select);
			easing_->Reset(&camPos_, CAM_POS, CAM_MOVE_POS, 2.0f, Easing::OutQuart);
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

	//選択中に戻る
	void BackSelecting()
	{
		//カメラのポジションを移動
		easing_->Move();
		Camera::SetPosition(camPos_);

		//もし距離が近くなったら
		if (RangeCalculation(camPos_, CAM_POS) < STATUS_CHANGE_DISTANCE)
		{
			//UIを表示
			((UserSelectStage*)GameManager::GetpStage())->CreateStageUI();

			//選択中状態に
			ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::Selecting);
		}
	}

	//プレイしている星の番号を取得
	int GetPlayPlanetNum() { return playPlanetNum_; }

	//カメラ移動
	void CameraMove(){ 

		//カメラのポジションを移動
		easing_->Move();
		Camera::SetPosition(camPos_);

		//もし距離が近くなったら
		if (RangeCalculation(camPos_, CAM_MOVE_POS) < STATUS_CHANGE_DISTANCE)
		{
			//作成したステージ削除
			GameManager::GetpStage()->GetCreateStage()->AllCreateStageDelete();

			//既存ファイルなら
			if (selectPlanet_->IsExisting())
			{
				//既存状態に
				ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::Existing);

				//次のUIを表示
				Instantiate<UserGameStartUI>(GameManager::GetpStage());
			}
			//新規作成なら
			else
			{
				//新規作成状態に
				ARGUMENT_INITIALIZE(userSelectStatus_, SelectPlanetStatus::NewCreate);

				//次のUIを表示
				Instantiate<NewFileUI>(GameManager::GetpStage());
			}

			//イージングリセット
			easing_->Reset(&camPos_, CAM_MOVE_POS, CAM_POS, 2.0f, Easing::OutQuart);
		}
	}

	//星の移動をリセット
	void ResetPlanetMove()
	{
		if (!firstPlanetInfo_->IsSelect())
		{
			firstPlanetInfo_->SetStatus(PlanetStatus::ReturnPosition);
			firstPlanetInfo_->SetReturnEasingMove();
		}
		if (!secondPlanetInfo_->IsSelect())
		{
			secondPlanetInfo_->SetStatus(PlanetStatus::ReturnPosition);
			secondPlanetInfo_->SetReturnEasingMove();
		}
		if (!thirdPlanetInfo_->IsSelect())
		{
			thirdPlanetInfo_->SetStatus(PlanetStatus::ReturnPosition);
			thirdPlanetInfo_->SetReturnEasingMove();
		}
	}

	//ユーザー情報を選択するときの状態を取得
	SelectPlanetStatus GetStatus() { return userSelectStatus_; }

	//ユーザー情報を選択するときの状態をセット
	void SetStatus(SelectPlanetStatus status) { ARGUMENT_INITIALIZE(userSelectStatus_,status); }

    //アイコンモデルパスを設定
	void SetIconModelPath(std::string path) { ARGUMENT_INITIALIZE(newCreateIconModelPath_, path);  }
};