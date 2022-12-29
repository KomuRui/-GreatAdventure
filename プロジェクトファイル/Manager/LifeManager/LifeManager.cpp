#include "LifeManager.h"
#include "../../Engine/Global.h"
#include "../GameManager/GameManager.h"
#include "../../Engine/Sprite.h"
#include "../../Engine/Transform.h"
#include "../../Engine/Text.h"

//�萔
namespace
{
	//���C�t
	static const int NORMAL_PLAYER_LIFE = 3; //���ʂ�Player�̃��C�t�̐�

	//�g��k��
	static const XMFLOAT3 NORMAL_SCALE = { 1.0f,1.0f,1.0f }; //�ʏ�g�嗦
	static const XMVECTOR MIN_SCALE = { 1.0f,1.0f,1.0f };    //�Œ�g�嗦
	static const XMVECTOR MAX_SCALE = { 1.1f,1.1f,1.0f };    //�ō��g�嗦
	static const float NORMAL_INTERPOLATION_FACTOR = 0.2f;   //�ʏ��ԌW��
	static const float ONELIFE_INTERPOLATION_FACTOR = 0.4f;  //1���C�t�����Ȃ��Ƃ��̕�ԌW��
	static const float CHANGE_TARGET_DISTANCE = 0.005f;      //�^�[�Q�b�g�ύX����Ƃ��̋���
}

/// <summary>
/// Player�̃��C�t�Ǘ�
/// </summary>
namespace LifeManager
{
	/// <summary>
	/// ���C�t���Ƃɉ摜�𕪂������̂ŗ񋓂���
	/// </summary>
	enum Life
	{
		Zero,		//HP0
		One,		//HP1
		Two,		//HP2
		Three,		//HP3
		MAX_LIFE_IMAGE
	};

	///////////////////////////////�ϐ�//////////////////////////////////

	//Player�̌��݂̃��C�t�̑���
	int playerLife_;

	//�摜
	Sprite* lifeImage[MAX_LIFE_IMAGE]; //���C�t���Ƃ̉摜�ԍ�
	Transform imageTransform_;		   //�摜�̈ʒu�E�g�嗦

	//�e�L�X�g
	Text* pLifeText_;                  //���C�t�̐��\������p
	XMFLOAT2 textPositiom_;            //�e�L�X�g�̃|�W�V����

	//�g��k��
	XMVECTOR  beforeScale_;		       //��Ԃ���O�̊g�嗦�ۑ�
	XMVECTOR  targetScale_;            //���̖ڕW�Ƃ���g�嗦

	///////////////////////////////�֐�//////////////////////////////////

	//������
	void LifeManager::Initialize()
	{
		//�e���C�t�̉摜���[�h
		for (int i = Zero; i < MAX_LIFE_IMAGE; i++) { lifeImage[i] = new Sprite; }
		
		lifeImage[Zero]->Load("Image/Player/PlayerHP0.png");
		lifeImage[One]->Load("Image/Player/PlayerHP1.png");
		lifeImage[Two]->Load("Image/Player/PlayerHP2.png");
		lifeImage[Three]->Load("Image/Player/PlayerHP3.png");

		//�e�L�X�g�̏�����
		ARGUMENT_INITIALIZE(pLifeText_, new Text);
		pLifeText_->Initialize();

		//�摜�̃|�W�V�����ݒ�
		ARGUMENT_INITIALIZE(imageTransform_.position_.x, GetPrivateProfilefloat("POSITION", "lifeImageX", "1", "Image/Player/lifePosition.ini"));
		ARGUMENT_INITIALIZE(imageTransform_.position_.y, GetPrivateProfilefloat("POSITION", "lifeImageY", "1", "Image/Player/lifePosition.ini"));
		
		//�e�L�X�g�̃|�W�V�����ݒ�
		ARGUMENT_INITIALIZE(textPositiom_.x, GetPrivateProfilefloat("POSITION", "lifeTextX", "1", "Image/Player/lifePosition.ini"))
		ARGUMENT_INITIALIZE(textPositiom_.y, GetPrivateProfilefloat("POSITION", "lifeTextY", "1", "Image/Player/lifePosition.ini"))

		//��Ԃ���O�̊g�嗦�ۑ�
		ARGUMENT_INITIALIZE(beforeScale_, MIN_SCALE);

		//���̖ڕW�Ƃ���g�嗦�̕ۑ�
		ARGUMENT_INITIALIZE(targetScale_, MAX_SCALE);

		//Playre�̃��C�t������
		ARGUMENT_INITIALIZE(playerLife_, NORMAL_PLAYER_LIFE);
	}

	//�V�[���J�ڂ̎��̏�����
	void LifeManager::SceneTransitionInitialize()
	{
		//�e�L�X�g�̏�����
		ARGUMENT_INITIALIZE(pLifeText_, new Text);
		pLifeText_->Initialize();
	}

	//�_���[�W�H��������ɌĂԃ��\�b�h
	void LifeManager::Damage(int damage)
	{
		//���C�t�����
		playerLife_ -= damage;

		//��������ł�����GameManager�Ɏ��񂾂��Ɠ`����
		if(IsDie()){ GameManager::PlayerDie(); }
	}

	//HPUI�`��
	void LifeManager::Draw()
	{
		//����Player�̃��C�t��2�ȉ��Ȃ�
		if (playerLife_ <= Two)
			ImageScaling();
		else
		{
			ARGUMENT_INITIALIZE(imageTransform_.scale_, XMFLOAT3(NORMAL_SCALE))
		}

		//�摜
		{
			//�e�N�X�`���̃T�C�Y�擾
			XMFLOAT3 size = lifeImage[playerLife_]->GetTextureSize();

			//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
			RECT rect;
			rect.left = ZERO;
			rect.top = ZERO;
			rect.right = (long)size.x;
			rect.bottom = (long)size.y;

			//�`��
			lifeImage[playerLife_]->Draw(imageTransform_, rect);
		}


		//�e�L�X�g
		{
			pLifeText_->Draw(textPositiom_.x, textPositiom_.y, playerLife_, imageTransform_.scale_.x);
		}

#pragma region HP����

		if (Input::IsKeyDown(DIK_A))
		{
			playerLife_--;
		}
		if (Input::IsKeyDown(DIK_D))
		{
			playerLife_++;
		}

#pragma endregion

	}

	//�摜�̊g��k��
	void LifeManager::ImageScaling()
	{
		//�g�嗦���Ԃ��Ȃ���ς��Ă����v���C���[���C�t��1�̎��͕�ԌW������������
		if(playerLife_ == One)
			XMStoreFloat3(&imageTransform_.scale_, XMVectorLerp(XMLoadFloat3(&imageTransform_.scale_), targetScale_, ONELIFE_INTERPOLATION_FACTOR));
		else
			XMStoreFloat3(&imageTransform_.scale_, XMVectorLerp(XMLoadFloat3(&imageTransform_.scale_), targetScale_, NORMAL_INTERPOLATION_FACTOR));

		//������0.01���Z���̂Ȃ�
		if (RangeCalculation(imageTransform_.scale_, VectorToFloat3(targetScale_)) < CHANGE_TARGET_DISTANCE)
		{
			//�^�[�Q�b�g����
			std::swap(beforeScale_, targetScale_);
		}
	}

	//���񂾂ǂ���
	bool LifeManager::IsDie() { return (playerLife_ <= ZERO); }
}