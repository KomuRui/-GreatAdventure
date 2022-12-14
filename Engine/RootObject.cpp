#include "RootObject.h"
#include "SceneManager.h"
#include "GameManager.h"

RootObject::RootObject():
	GameObject(nullptr, "RootObject")
{
}


RootObject::~RootObject()
{
}

void RootObject::Initialize()
{
	GameManager::SetpSceneManager(Instantiate<SceneManager>(this));
}

void RootObject::Update()
{
}

void RootObject::Draw()
{
}

void RootObject::Release()
{
}

void RootObject::StartUpdate()
{
}
