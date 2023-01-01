#include "BulletPigEnemy.h"
#include "../Gimmick/Bullet.h"

//定数
namespace
{
	//////////////////////アニメーション/////////////////////////

	static const int ANIM_START_FREAM = 0; //アニメーションの開始フレーム
	static const int ANIM_END_FREAM = 90;  //アニメーションの終了フレーム
	static const int SHOT_ANIM_FREAM = 40; //アニメーションの球ショットフレーム
	static const float ANIM_SPEED = 1.0f;  //アニメーションのスピード

	//////////////////////キャラの必要な情報/////////////////////////

	static const float MODEL_BRIGHTNESS = 0.7f; //モデルの明るさ

}

//コンストラクタ
BulletPigEnemy::BulletPigEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Enemy(parent,modelPath,name)
{
}

//更新の前に一度だけ呼ばれる関数
void BulletPigEnemy::EnemyChildStartUpdate()
{
	//アニメーション設定
	Model::SetAnimFlag(hModel_, true);
	Model::SetAnimFrame(hModel_, ANIM_START_FREAM, ANIM_END_FREAM, ANIM_SPEED);

	//モデルの明るさ設定
	Model::SetBrightness(hModel_, MODEL_BRIGHTNESS);

	//重力適用させない
	ARGUMENT_INITIALIZE(useGravity_, false);

	//ずっと動いている状態にしたいので状態をMoveに変更
	ChangeEnemyState(EnemyStateList::GetEnemyMoveState());
}

//動き
void BulletPigEnemy::Move()
{
	//永遠に動いていたいので状態カウントを初期化しておく
	ARGUMENT_INITIALIZE(stateCount_, ZERO);

	//もしアニメーションのフレームが発射フレームなら球発射する
	if (Model::GetAnimFrame(hModel_) == SHOT_ANIM_FREAM)
		ShotBullet();
	
}

//球発射
void BulletPigEnemy::ShotBullet()
{
	//球発射
	Instantiate<Bullet>(this);
}

//当たり判定
void BulletPigEnemy::OnCollision(GameObject* pTarget)
{
}

