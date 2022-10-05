#include "Particle.h"
#include"Engine/Model.h"

Particle::Particle(GameObject* parent,std::string name)
    :GameObject(parent,name),hModel_(-1), speed_(0.1f)
{
}
Particle::~Particle()
{

}

void Particle::SetParticle(float timeLimit, float attenuationRate, float speed, XMVECTOR vDir)
{
    SetLifeLimit(timeLimit);
    SetAttenution(attenuationRate);
    SetSpeed(speed);
    SetDir(vDir);
}

void Particle::SetLifeLimit(float timeLimit)
{
    lifeLimit_ = timeLimit;
}

void Particle::SetAttenution(float attenuationRate)
{
    attenuationRate_ = attenuationRate;
}
void Particle::SetSpeed(float speed)
{
    speed_ = speed;
}

void Particle::SetDir(XMVECTOR dir)
{
    vDir_ = dir;
}


//////////////////////////////ジェットパーティクル/////////////////////////////
//コンストラクタ
    //引数：parent  親オブジェクト（PlayScene）
JetParticle::JetParticle(GameObject* parent)
    :Particle(parent,"JetParticle"), a_(0)
{

}

//デストラクタ
JetParticle::~JetParticle()
{

}

//初期化
void JetParticle::Initialize()
{
    hModel_ = Model::Load("EarthScene/Model/FireBullet.fbx");
    transform_.scale_ = XMFLOAT3(0.5, 0.5, 0.5);
    transform_.position_.z = (rand() % 11) - 5;

    beforePos = transform_.position_;

    assert(hModel_ >= 0);

}

//更新
void JetParticle::Update()
{
        vDir_ = XMVector3Normalize(vDir_) * speed_;
        XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
        XMVECTOR vParDir = vPos + vDir_;
        transform_.rotate_.x += 1;
        XMStoreFloat3(&transform_.position_, vParDir);
        Model::SetAlpha(hModel_, (float)a_ / (lifeLimit_ * 60.0f) - 0.35);

        if (a_ == lifeLimit_ * 60.0f)
        {
            transform_.position_ = beforePos;
            Model::SetAlpha(hModel_, 1);
            a_ = 0;
        }
        a_++;
}

//描画
void JetParticle::Draw()
{
     Model::SetTransform(hModel_, transform_);
     Model::Draw(hModel_);
}

//開放
void JetParticle::JetParticle::Release()
{

}

void JetParticle::StartUpdate()
{
}

