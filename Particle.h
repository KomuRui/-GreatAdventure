#pragma once
#include"Engine/GameObject.h"
#include<string>
class Particle : public GameObject
{
protected:

    int hModel_;
    float lifeLimit_;
    float attenuationRate_;
    float speed_;  

    XMVECTOR vDir_;
    XMFLOAT3 beforePos;

public:
    //デストラクタ
    Particle(GameObject* parent,std::string name);
    virtual ~Particle();

    
    void SetParticle(float timeLimit,float attenuationRate, float speed,XMVECTOR vDir);
    void SetLifeLimit(float timeLimit);
    void SetAttenution(float attenuationRate);
    void SetSpeed(float speed);
    void SetDir(XMVECTOR dir);
};

class JetParticle : public Particle
{
    int a_;

public:
    //コンストラクタ
    //引数：parent  親オブジェクト（PlayScene）
    JetParticle(GameObject* parent);

    //デストラクタ
    ~JetParticle();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void StartUpdate() override;
};