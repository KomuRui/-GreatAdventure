#include "CreateStage.h"
#include "../Gimmick/Coin.h"
#include "../Gimmick/Warp.h"
#include "../Block/ItemBlock.h"
#include "../Enemy/Enemy.h"
#include "../Enemy/DropEnemy.h"
#include "../Enemy/PigEnemy.h"
#include "../Block/BrickBlock.h"
#include "../Block/NormalBlock.h"
#include "../Block/TransparentBlock.h"
#include "../Mob/MainMob.h"
#include "../Gimmick/Signboard.h"
#include "../Gimmick/MoveFloor.h"
#include "Light.h"
#include "CameraTransitionObject.h"
#include "../Gimmick/ShineLight.h"
#include "../Gimmick/ShineLightController.h"
#include "../Enemy/BulletPigEnemy.h"
#include "../OtherObject/TitleModel.h"
#include "GameObject.h"

//�R���X�g���N�^
CreateStage::CreateStage()
	:CreateShineController(false)
{
}

//�I�u�W�F�N�g�쐬
void CreateStage::CreateObject(GameObject* parent, std::string ModelPathName, std::string inName, Transform t, XMFLOAT3 camPos)
{
	/////////////////////Mob///////////////////////

	if (inName == "Mob")
	{
		Mob* pNewObject = new Mob(parent, ModelPathName, inName);
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}

	if (inName == "MainMob")
	{
		MainMob* pNewObject = new MainMob(parent, ModelPathName, inName);
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->SetAngle(t.rotate_.y);
		pNewObject->Initialize();
	}

	/////////////////////OtherObject///////////////////////

	if (inName == "TitleModel")
	{
		TitleModel* pNewObject = new TitleModel(parent);
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}


	/////////////////////Camera////////////////////////

	if (inName == "Camera")
	{
		//�J������������ϐ��p��
		StageCameraTransition information;

		//�e��񏉊���
		information.CameraPosition = camPos;
		information.CameraTarget = t.rotate_;
		information.CollisionSize = t.scale_;

		//�R���X�g���N�^�Ă�
		CameraTransitionObject* pNewObject = new CameraTransitionObject(parent, information);
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}

		//��]�Ɗg���0�ɏ���������
		ARGUMENT_INITIALIZE(t.rotate_, XMFLOAT3(0, 0, 0));
		ARGUMENT_INITIALIZE(t.scale_, XMFLOAT3(0, 0, 0));

		pNewObject->SetTransform(t);
		pNewObject->Initialize();

	}

	/////////////////////Light/////////////////////////

	if (inName == "Light")
	{
		Light::SetPositionAndIntensity(XMFLOAT4(t.position_.x, t.position_.y, t.position_.z, 0), t.scale_.x);
	}

	/////////////////////Gimmick///////////////////////

	if (inName == "Coin")
	{
		Coin* pNewObject = new Coin(parent, ModelPathName, inName);
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "Warp" || inName == "Warp1")
	{
		Warp* pNewObject = new Warp(parent, ModelPathName, "Warp");
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		if (inName == "Warp1")pNewObject->SetNumber(1);
	}
	if (inName == "Signboard")
	{
		Signboard* pNewObject = new Signboard(parent, ModelPathName, "Signboard");
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if (inName == "MoveFloor")
	{
		MoveFloor* pNewObject = new MoveFloor(parent, ModelPathName, "MoveFloor");
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}
	if ("ShineLight" == inName)
	{
		if (!CreateShineController)
		{
			ShineLightController* NewObject = new ShineLightController(parent);
			if (parent->GetParent() != nullptr)
			{
				parent->GetParent()->PushBackChild(NewObject);
			}
			NewObject->SetCamPosCamTar(camPos, t.rotate_);
			ARGUMENT_INITIALIZE(t.rotate_, XMFLOAT3(0, 0, 0));

			NewObject->SetTransform(t);
			NewObject->Initialize();
			ARGUMENT_INITIALIZE(CreateShineController, true);
		}

		ShineLight* pNewObject = new ShineLight(parent, ModelPathName, "ShineLight");
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
		ShineLightController* pShineLightController = (ShineLightController*)parent->FindObject("ShineLightController");
		pShineLightController->SetShineLight(pNewObject);
	}

	/////////////////////Block///////////////////////

	if (inName == "ItemBlock" || inName == "ItemBlock1")
	{

		ItemBlock* pNewObject = new ItemBlock(parent, ModelPathName, "ItemBlock");
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		//��]����悤�ɐݒ�
		if (inName == "ItemBlock1")pNewObject->SetStatus(1);

		//�u���b�N�Ȃ̂Œǉ�
		tBlock.push_back(pNewObject);
	}
	if (inName == "BrickBlock")
	{

		BrickBlock* pNewObject = new BrickBlock(parent, ModelPathName, "BrickBlock");
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		//�u���b�N�Ȃ̂Œǉ�
		tBlock.push_back(pNewObject);
	}
	if (inName == "NormalBlock")
	{

		NormalBlock* pNewObject = new NormalBlock(parent, ModelPathName, "NormalBlock");
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		//�u���b�N�Ȃ̂Œǉ�
		tBlock.push_back(pNewObject);
	}
	if (inName == "TransparentBlock")
	{

		TransparentBlock* pNewObject = new TransparentBlock(parent, ModelPathName, "TransparentBlock");
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();

		//�u���b�N�Ȃ̂Œǉ�
		tBlock.push_back(pNewObject);
	}

	/////////////////////Enemy///////////////////////

	if (inName == "Enemy")
	{
		Enemy* pNewObject = new Enemy(parent, ModelPathName, inName);
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}

	if (inName == "DropEnemy")
	{
		DropEnemy* pNewObject = new DropEnemy(parent, ModelPathName, inName);
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}

	if (inName == "PigEnemy")
	{
		PigEnemy* pNewObject = new PigEnemy(parent, ModelPathName, inName);
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->Initialize();
	}

	if (inName == "BulletPigEnemy")
	{
		BulletPigEnemy* pNewObject = new BulletPigEnemy(parent, ModelPathName, inName);
		if (parent->GetParent() != nullptr)
		{
			parent->GetParent()->PushBackChild(pNewObject);
		}
		pNewObject->SetTransform(t);
		pNewObject->SetAngle(t.rotate_.y);
		pNewObject->Initialize();
	}
}

//�e�X�e�[�W�̃t�@�C�����[�h
void CreateStage::LoadFile(std::string filename)
{

}
