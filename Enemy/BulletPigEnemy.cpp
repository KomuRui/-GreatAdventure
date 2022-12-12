#include "BulletPigEnemy.h"
#include "../Gimmick/Bullet.h"

//コンストラクタ
BulletPigEnemy::BulletPigEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent,modelPath,name)
{
}

//更新の前に一度だけ呼ばれる関数
void BulletPigEnemy::ChildStartUpdate()
{
	//アニメーション設定
	Model::SetAnimFlag(hModel_, true);
	Model::SetAnimFrame(hModel_, ANIM_START_FREAM, ANIM_END_FREAM, ANIM_SPEED);

	//モデルの明るさ設定
	Model::SetBrightness(hModel_, 0.5f);
}

//更新
void BulletPigEnemy::ChildUpdate()
{
	//もしアニメーションのフレームが終了フレームなら球発射する
	if (Model::GetAnimFrame(hModel_) == 40)
		ShotBullet();
}

//球発射
void BulletPigEnemy::ShotBullet()
{
	//球発射(球の動く方向を決めるので)
	Bullet *pBullet = Instantiate<Bullet>(this);

	//球のポジションセット
	pBullet->SetPosition(Transform::Float3Add(pBullet->GetPosition(), Transform::VectorToFloat3(vNormal)));
}

//当たり判定
void BulletPigEnemy::OnCollision(GameObject* pTarget)
{
}

