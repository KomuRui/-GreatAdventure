#include "Warp.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/GameObject/Camera.h"
#include "../Engine/ResourceManager/Fade.h"
#include "../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../Manager/GameManager/GameManager.h"

//定数
namespace
{
	////////////////ワープの移動に必要////////////////////

	static const int      FADE_OUT_DISTANCE = 600;          //フェードアウトする時の距離
	static const int      SCENE_MOVE_DISTANCE = 300;        //シーン移行する時の距離
	static const float    DESTINATION_DISTANCE = 800;       //目的地までの距離
	static const float    WARP_KILL_DISTANCE = 5;           //ワープを削除するときの距離
	static const float    INTERPOLATION_COEFFICIENT = 0.003;//補間係数

	////////////////ワープの回転に必要////////////////////

	static const float    ROTATION_QUANTITY = 0.02f;        //回転量
	static const float    ADDITION_TURNOVERRATE = 0.03f;    //回転率を加算する量
	static const float    MAX_TURNOVERRATE = 10.0f;         //最大回転率
	
	////////////////////当たり判定/////////////////////

	static const int      COLLIDER_POS_Y = -2;              //コライダーポジション
	static const float    COLLIDER_SIZE = 3.5f;             //コライダーサイズ

	//////////////////////その他///////////////////////

	static const float    VIBRATION_INTENSITY = 0.5f;       //カメラ振動の強さ
}

//コンストラクタ
Warp::Warp(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name), status_(STOP)
, turnoverRate_(1), playerPos_(ZERO, ZERO, ZERO), type_(Normal),warpTarget_(ZERO, ZERO, ZERO), id_(SCENE_ID_HOME)
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
	SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)) * COLLIDER_POS_Y * transform_.scale_.y, ZERO), COLLIDER_SIZE * transform_.scale_.y);
	AddCollider(collision);

	//ワープにPlayerを乗せるときのPlayerのポジションを設定
	playerPos_ = Float3Add(transform_.position_, VectorToFloat3(XMVector3Normalize(-vNormal_)));

	//ワープポジションが設定されていないのなら
	if(warpTarget_.x == ZERO && warpTarget_.y == ZERO && warpTarget_.z == ZERO)
	    //ワープの目的地
		warpTarget_ = Float3Add(transform_.position_, VectorToFloat3(XMVector3Normalize(vNormal_) * DESTINATION_DISTANCE));

	/////////////////////////エフェクト////////////////////////////

	pRightLine_ = new PolyLine;
	pLeftLine_  = new PolyLine;
	pBaseLine_  = new PolyLine;

	//テクスチャロード
	pRightLine_->Load("tex.png");
	pLeftLine_->Load("tex.png");
	pBaseLine_->Load("tex.png");

	//各ポジション初期化
	pRightLine_->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLeftLine_->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pBaseLine_->AddPosition(Model::GetBonePosition(hModel_, "Base"));

	//上ベクトルをPlayerと同じのに設定
	if(type_ == MoveToPurpose)
		vNormal_ = GameManager::GetpPlayer()->GetNormal();
}

//更新
void Warp::ChildUpdate()
{
	//Y軸回転させる
	angle_ += ROTATION_QUANTITY * turnoverRate_;

	//Y軸の角度が360より大きいなら0に戻す
	if (angle_ > TWOPI_DEGREES) angle_ = ZEROPI_DEGREES;

	//マックススピードに達したら次の星にワープする(状態によって移動の仕方を変える)
	if (status_ == MOVE) type_ == MoveToPurpose ? MovingToPurpose() : MovingToStar();

}

//継承先用の描画
void Warp::ChildDraw()
{
	//nullなら
	if (pBaseLine_ == nullptr)
		return;

	//ポリラインを描画
	pBaseLine_->Draw();
	pRightLine_->Draw();
	pLeftLine_->Draw();
}

//継承先用の開放
void Warp::ChildRelease()
{
	SAFE_RELEASE(pBaseLine_);
	SAFE_DELETE_ARRAY(pBaseLine_);
	SAFE_RELEASE(pLeftLine_);
	SAFE_DELETE_ARRAY(pLeftLine_);
	SAFE_RELEASE(pRightLine_);
	SAFE_DELETE_ARRAY(pRightLine_);
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
	if (dist < WARP_KILL_DISTANCE)
	{
		//Playerの落下エフェクト表示
		PlayerEffectManager::FallEffect(GameManager::GetpPlayer()->GetPosition());

		//Player法線調べるかをステージ情報みて変える
		GameManager::GetpPlayer()->SetCheckNormal(GameManager::GetpStage()->GetCircleflag());

		//カメラ振動
		Camera::SetCameraVibration(VIBRATION_INTENSITY);

		//削除
		KillMe();
	}

	//nullなら
	if (pBaseLine_ == nullptr)
		return;

	//各エフェクトのポジション設定
	pRightLine_->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLeftLine_->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pBaseLine_->AddPosition(Model::GetBonePosition(hModel_, "Base"));
}

//次の星にワープ
void Warp::MovingToStar()
{
	//Playerがnullならこの先の処理はしない
	if (GameManager::GetpPlayer() == nullptr) return;

	//カメラのポジションを動かないように設定
	GameManager::GetpPlayer()->SetCamPosNotMove();

	//目的地まで補間しながら進む
	XMStoreFloat3(&transform_.position_,XMQuaternionSlerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&warpTarget_), INTERPOLATION_COEFFICIENT));

	//今のポジションと目的地の距離を求める
	float dist = RangeCalculation(transform_.position_, warpTarget_);

	//距離が600より小さいなら次のステージに移行
	if (dist < FADE_OUT_DISTANCE)
	{
		//フェードのステータスがFADE_OUT状態じゃなかったら
		if (Fade::GetFadeStatus() != FADE_CIRCLE_OUT)
			Fade::SetFadeStatus(FADE_CIRCLE_OUT);
	}

	//距離が300より小さいなら次のステージに移行
	if (dist < SCENE_MOVE_DISTANCE)
	{
		GameManager::GetpSceneManager()->ChangeScene(id_);
	}

	//nullなら
	if (pBaseLine_ == nullptr)
		return;

	//各エフェクトのポジション設定
	pRightLine_->AddPosition(Model::GetBonePosition(hModel_, "Right"));
	pLeftLine_->AddPosition(Model::GetBonePosition(hModel_, "Left"));
	pBaseLine_->AddPosition(Model::GetBonePosition(hModel_, "Base"));
}

//当たり判定
void Warp::OnCollision(GameObject* pTarget)
{
	//Playerだけ衝突判定
	if (pTarget->GetObjectName() != "Player")
		return;

	//ワープにPlayerを乗せるときのPlayerのポジションを設定
	XMStoreFloat3(&playerPos_, XMVector3Normalize(-vNormal_));
	playerPos_ = Float3Add(transform_.position_, playerPos_);
		
	//Playerポジションをセットする
	pTarget->SetPosition(playerPos_);

	//Player法線更新しないようにする
	GameManager::GetpPlayer()->SetCheckNormal(false);

	//型がInverseNormalAndDownの状態なら
	if (type_ == InverseNormalAndDown)
	{
		GameManager::GetpPlayer()->SetInverseNormalAndDown();
		ZERO_INITIALIZE(type_);
	}

	//Playerと当たっている状態なら回転率をどんどん早める
	//もし回転率が最大まで達したら状態をMoveに設定
	if (type_ <= InverseNormalAndDown)
	{
		if (turnoverRate_ < MAX_TURNOVERRATE)
			turnoverRate_ += ADDITION_TURNOVERRATE;
		else
			ARGUMENT_INITIALIZE(status_, MOVE);
	}
	else
		ARGUMENT_INITIALIZE(status_, MOVE);
}
