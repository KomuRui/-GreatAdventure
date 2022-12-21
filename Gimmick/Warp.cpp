#include "Warp.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"

//コンストラクタ
Warp::Warp(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name), status_(STOP)
, turnoverRate_(1), playerPos_(0, 0, 0), number_(0)
{
}

Warp::~Warp()
{
}

//初期化
void Warp::ChildInitialize()
{
}

//スタートアップデート
void Warp::ChildStartUpdate()
{
	//自身に当たり判定を追加
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, XMVectorGetY(XMVector3Normalize(vNormal)) * -2 * transform_.scale_.y, 0), 3.5f * transform_.scale_.y);
	AddCollider(collision);

	//ワープにPlayerを乗せるときのPlayerのポジションを設定
	playerPos_ = Float3Add(transform_.position_, VectorToFloat3(XMVector3Normalize(-vNormal)));

	//ワープポジションが設定されていないのなら
	if(warpTarget_.x == 0 && warpTarget_.y == 0 && warpTarget_.z == 0)
	    //ワープの目的地
		warpTarget_ = Float3Add(transform_.position_, VectorToFloat3(XMVector3Normalize(vNormal) * 800));

	/////////////////////////エフェクト////////////////////////////

	//ポリライン初期化
	pLine[RIGHT] = new PolyLine;
	pLine[LEFT] = new PolyLine;
	pLine[BASE] = new PolyLine;

	//テクスチャロード
	pLine[RIGHT]->Load("tex.png");
	pLine[LEFT]->Load("tex.png");
	pLine[BASE]->Load("tex.png");

	//各ポジション初期化
	pLine[RIGHT]->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLine[LEFT]->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pLine[BASE]->AddPosition(Model::GetBonePosition(hModel_, "Base"));

	//上ベクトルをPlayerと同じのに設定
	if(number_ == 2)
		vNormal = GameManager::GetpPlayer()->GetNormal();
}

//更新
void Warp::ChildUpdate()
{
	//Y軸回転させる
	Angle += ROTATION_QUANTITY * turnoverRate_;

	//Y軸の角度が360より大きいなら0に戻す
	if (Angle > TWOPI_DEGREES) Angle = ZEROPI_DEGREES;

	//マックススピードに達したら次の星にワープする(状態によって移動の仕方を変える)
	if (status_ == MOVE) number_ == 2 ? MovingToPurpose() : MovingToStar();

}

//継承先用の描画
void Warp::ChildDraw()
{
	//nullなら
	if (pLine[BASE] == nullptr)
		return;

	//ポリラインを描画
	pLine[RIGHT]->Draw();
	pLine[LEFT]->Draw();
	pLine[BASE]->Draw();
}

//継承先用の開放
void Warp::ChildRelease()
{
	//個数分回す
	for (int i = 0; i < MAX_POLY_LINE; i++)
	{
		SAFE_RELEASE(pLine[i]);
		SAFE_DELETE_ARRAY(pLine[i]);
	}
}

//次の目的地まで移動
void Warp::MovingToPurpose()
{
	//回転速度最高に設定
	turnoverRate_ = MAX_TURNOVERRATE;

	//Playerがnullならこの先の処理はしない
	if (GameManager::GetpPlayer() == nullptr) return;

	//目的地まで進む
	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + XMVector3Normalize(XMLoadFloat3(&warpTarget_) - XMLoadFloat3(&transform_.position_)) * 1.5);

	//今のポジションと目的地の距離を求める
	float dist = RangeCalculation(transform_.position_, warpTarget_);

	//距離が5より小さいならエフェクト表示・ワープ削除　
	if (dist < 5)
	{
		//Playerの落下エフェクト表示
		GameManager::GetpPlayer()->FallEffect();

		//Player法線調べるかをステージ情報みて変える
		GameManager::GetpPlayer()->SetNormalFlag(GameManager::GetpStage()->GetCircleflag());

		//カメラ振動
		Camera::SetCameraVibration(0.5f);

		//削除
		KillMe();
	}

	//nullなら
	if (pLine[BASE] == nullptr)
		return;

	//各エフェクトのポジション設定
	pLine[RIGHT]->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLine[LEFT]->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pLine[BASE]->AddPosition(Model::GetBonePosition(hModel_, "Base"));
}

//次の星にワープ
void Warp::MovingToStar()
{
	//Playerがnullならこの先の処理はしない
	if (GameManager::GetpPlayer() == nullptr) return;

	//カメラのポジションを動かないように設定
	GameManager::GetpPlayer()->SetCamPosFlag();

	//目的地まで補間しながら進む
	XMStoreFloat3(&transform_.position_,XMQuaternionSlerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&warpTarget_), 0.003));

	//今のポジションと目的地の距離を求める
	float dist = RangeCalculation(transform_.position_, warpTarget_);

	//距離が600より小さいなら次のステージに移行
	if (dist < FADE_OUT_DISTANCE)
	{
		//フェードのステータスがFADE_OUT状態じゃなかったら
		if (GameManager::GetStatus() != FADE_OUT)
			GameManager::SetStatus(FADE_OUT);
	}

	//距離が300より小さいなら次のステージに移行
	if (dist < SCENE_MOVE_DISTANCE)
	{
		SceneManager* pScene = (SceneManager*)FindObject("SceneManager");
		pScene->ChangeScene(id_);
	}

	//各エフェクトのポジション設定
	pLine[RIGHT]->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLine[LEFT]->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pLine[BASE]->AddPosition(Model::GetBonePosition(hModel_, "Base"));
}

//当たり判定
void Warp::OnCollision(GameObject* pTarget)
{
	//Playerだけ衝突判定
	if (pTarget->GetObjectName() != "Player")
		return;

	//ワープにPlayerを乗せるときのPlayerのポジションを設定
	XMStoreFloat3(&playerPos_, XMVector3Normalize(-vNormal));
	playerPos_ = Float3Add(transform_.position_, playerPos_);
		
	//Playerポジションをセットする
	pTarget->SetPosition(playerPos_);

	//Player法線更新しないようにする
	GameManager::GetpPlayer()->SetNormalFlag(false);

	//number_が1の状態なら
	if (number_ == 1)
	{
		GameManager::GetpPlayer()->SetInverseNormalAndDown();
		ZERO_INITIALIZE(number_);
	}

	//Playerと当たっている状態なら回転率をどんどん早める
	//もし回転率が最大まで達したら状態をMoveに設定
	if (number_ <= 1)
	{
		if (turnoverRate_ < MAX_TURNOVERRATE)
			turnoverRate_ += ADDITION_TURNOVERRATE;
		else
			ARGUMENT_INITIALIZE(status_, MOVE);
	}
	else
		ARGUMENT_INITIALIZE(status_, MOVE);
}
