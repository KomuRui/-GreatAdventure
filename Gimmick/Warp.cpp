#include "Warp.h"
#include "../Engine/Model.h"
#include "../Engine/SceneManager.h"

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
	BoxCollider* collision = new BoxCollider(COLLIDER_POS, COLLIDER_SIZE);
	AddCollider(collision);

	//ワープにPlayerを乗せるときのPlayerのポジションを設定
	playerPos_ = Transform::Float3Add(transform_.position_, Transform::VectorToFloat3(XMVector3Normalize(-vNormal)));

	//ワープポジションが設定されていないのなら
	if(warpTarget.x == 0 && warpTarget.y == 0 && warpTarget.z == 0)
	//ワープの目的地
	warpTarget = Transform::Float3Add(transform_.position_, Transform::VectorToFloat3(XMVector3Normalize(vNormal) * 800));

	/////////////////////////エフェクト////////////////////////////

	//ポリライン初期化
	pLine[0] = new PolyLine;
	pLine[1] = new PolyLine;
	pLine[2] = new PolyLine;

	//テクスチャロード
	pLine[0]->Load("tex.png");
	pLine[1]->Load("tex.png");
	pLine[2]->Load("tex.png");

	//各ポジション初期化
	pLine[0]->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLine[1]->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pLine[2]->AddPosition(Model::GetBonePosition(hModel_, "Base"));

	//エフェクト出すために必要なクラス
	pParticle_ = Instantiate<Particle>(this);

	//上ベクトルをPlayerと同じのに設定
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
	if (pLine[0] == nullptr)
		return;

	//ポリラインを描画
	pLine[0]->Draw();
	pLine[1]->Draw();
	pLine[2]->Draw();
}

//継承先用の開放
void Warp::ChildRelease()
{
	SAFE_RELEASE(pLine[0]);
	SAFE_RELEASE(pLine[1]);
	SAFE_RELEASE(pLine[2]);
	SAFE_DELETE_ARRAY(pLine[0]);
	SAFE_DELETE_ARRAY(pLine[1]);
	SAFE_DELETE_ARRAY(pLine[2]);
}

//次の目的地まで移動
void Warp::MovingToPurpose()
{
	//回転速度最高に設定
	turnoverRate_ = MAX_TURNOVERRATE;

	//Playerがnullならこの先の処理はしない
	if (GameManager::GetpPlayer() == nullptr) return;

	//目的地まで進む
	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + XMVector3Normalize(XMLoadFloat3(&warpTarget) - XMLoadFloat3(&transform_.position_)) * 1.5);

	//今のポジションと目的地の距離を求める
	float dist = Transform::RangeCalculation(transform_.position_, warpTarget);

	//距離が50より小さいならポリライン段々透明に
	if (dist < 50)
	{
		pLine[0]->SetMoveAlphaFlag();
		pLine[1]->SetMoveAlphaFlag();
		pLine[2]->SetMoveAlphaFlag();

		//Player法線調べるように
		GameManager::GetpPlayer()->SetNormalFlag(true);
	}

	//距離が5より小さいならエフェクト表示・ワープ削除
	if (dist < 5)
	{
		//Playerの落下エフェクト表示
		GameManager::GetpPlayer()->FallEffect();

		//削除
		KillMe();
	}

	//nullなら
	if (pLine[0] == nullptr)
		return;

	//各エフェクトのポジション設定
	pLine[0]->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLine[1]->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pLine[2]->AddPosition(Model::GetBonePosition(hModel_, "Base"));
}

//次の星にワープ
void Warp::MovingToStar()
{
	//Playerがnullならこの先の処理はしない
	if (GameManager::GetpPlayer() == nullptr) return;

	//カメラのポジションを動かないように設定
	GameManager::GetpPlayer()->SetCamPosFlag();

	//目的地まで補間しながら進む
	XMStoreFloat3(&transform_.position_,XMQuaternionSlerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&warpTarget), 0.003));

	//今のポジションと目的地の距離を求める
	float dist = Transform::RangeCalculation(transform_.position_, warpTarget);

	//距離が300より小さいなら次のステージに移行
	if (dist < 300) 
	{
		SceneManager* pScene = (SceneManager*)FindObject("SceneManager");
		pScene->ChangeScene(SCENE_ID_TUTORIAL2);
	}


	//各エフェクトのポジション設定
	pLine[0]->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLine[1]->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pLine[2]->AddPosition(Model::GetBonePosition(hModel_, "Base"));
}

//当たり判定
void Warp::OnCollision(GameObject* pTarget)
{
	//Playerと衝突したら
	if (pTarget->GetObjectName() == "Player")
	{
		//ワープにPlayerを乗せるときのPlayerのポジションを設定
		XMStoreFloat3(&playerPos_, XMVector3Normalize(-vNormal));
		playerPos_ = Transform::Float3Add(transform_.position_, playerPos_);
		
		//Playerポジションをセットする
		pTarget->SetPosition(playerPos_);

		//number_が1の状態なら
		if (number_ == 1)
		{
			Player* pPlayer_ = (Player*)FindObject("Player");
			if (pPlayer_ == nullptr) return;

			pPlayer_->SetInverseNormalAndDown();
			number_ = 0;
		}

		//Playerと当たっている状態なら回転率をどんどん早める
		//もし回転率が最大まで達したら状態をMoveに設定
		number_ <= 1 ? (turnoverRate_ < MAX_TURNOVERRATE ? turnoverRate_ += ADDITION_TURNOVERRATE : status_ = MOVE)
			         :  status_ = MOVE;
	}
}
