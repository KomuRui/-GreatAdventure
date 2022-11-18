#include "Warp.h"
#include "../Engine/Model.h"

//コンストラクタ
Warp::Warp(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name), status_(STOP)
, turnoverRate_(1), playerPos_(0, 0, 0), number_(0)
{
}

//スタートアップデート
void Warp::ChildStartUpdate()
{

	//自身に当たり判定を追加
	BoxCollider* collision = new BoxCollider(COLLIDER_POS, COLLIDER_SIZE);
	AddCollider(collision);

	//ワープにPlayerを乗せるときのPlayerのポジションを設定
	playerPos_ = Transform::Float3Add(transform_.position_,Transform::VectorToFloat3(XMVector3Normalize(-vNormal)));
	
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
}

//更新
void Warp::ChildUpdate()
{
	//Y軸回転させる
	Angle += ROTATION_QUANTITY * turnoverRate_;

	//Y軸の角度が360より大きいなら0に戻す
	if (Angle > TWOPI_DEGREES) Angle = ZEROPI_DEGREES;

	//マックススピードに達したら次の星にワープする
	if(status_ == MOVE)
		MovingToStar();
}

//継承先用の描画
void Warp::ChildDraw()
{
	//ポリラインを描画
	pLine[0]->Draw();
	pLine[1]->Draw();
	pLine[2]->Draw();
}

//次の星にワープ
void Warp::MovingToStar()
{
	//Player探す
	Player* pPlayer_ = (Player*)FindObject("Player");
	if (pPlayer_ == nullptr) return;

	//カメラのポジションを動かないように設定
	pPlayer_->SetCamPosFlag();

	//目的地まで補間しながら進む
	XMStoreFloat3(&transform_.position_,XMQuaternionSlerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&warpTarget), 0.003));

	//今のポジションと目的地の距離を求める
	float dist = Transform::RangeCalculation(transform_.position_, warpTarget);

	//距離が300より小さいなら次のステージに移行
	if (dist < 300) 
	{
		int a = 0;
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
		(turnoverRate_ < MAX_TURNOVERRATE ? turnoverRate_ += ADDITION_TURNOVERRATE : status_ = MOVE);
	}
}