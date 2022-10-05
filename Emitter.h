#pragma once
#include"Engine/GameObject.h"
#include"Particle.h"
#include <vector>

class Emitter : public GameObject
{
    int particleCount_;
    float createTime_;
    float patStart_;
    float patSpeed_;
    float acceleration_;

    XMVECTOR vDir_;

    std::vector<JetParticle> _datas;

public:
	Emitter(GameObject* parent);
	~Emitter();

    //‰Šú‰»
    void Initialize() override;

    //XV
    void Update() override;

    //•`‰æ
    void Draw() override;

    //ŠJ•ú
    void Release() override;

    void StartUpdate() override;

	void CreateParticle();
};