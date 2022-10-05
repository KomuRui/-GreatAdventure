#include "Emitter.h"
#include"Particle.h"

Emitter::Emitter(GameObject* parent)
	:GameObject(parent,"Emitter"),particleCount_(0),createTime_(300),vDir_(XMVectorSet(0,0,-1,0))
{

}

Emitter::~Emitter()
{

}


//‰Šú‰»
void Emitter::Initialize()
{
	transform_.position_.y += 2.5;
	transform_.position_.z -= 4;
}

//XV
void Emitter::Update()
{
	//Debug‚ÌŽž‚Í‚P‚O
	//ReleaseŽž‚Í‚W‚O
	if (10 >= _datas.size())
	{
		vDir_ = XMVectorSet(0, 0, -1, 0);
		XMMATRIX matDir = XMMatrixRotationX((float(rand() % 201) - 100) / 1000) * XMMatrixRotationY((float(rand() % 201) - 100) / 1000) * XMMatrixRotationZ(0);
		vDir_ = XMVector3TransformCoord(vDir_, matDir);

		JetParticle* particle = Instantiate<JetParticle>(this);
		particle->SetParticle(0.4f, 0.0f, 1.0f, vDir_);

		_datas.push_back(particle);
	}
}

//•`‰æ
void Emitter::Draw()
{

}

//ŠJ•ú
void Emitter::Release()
{

}

void Emitter::StartUpdate()
{
}

void Emitter::CreateParticle()
{

}