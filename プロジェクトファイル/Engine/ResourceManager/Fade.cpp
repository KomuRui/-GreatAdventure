#include "Fade.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../DirectX/Sprite.h"
#include "../Component/EasingMove.h"
#include "Easing.h"
#include "../../Manager/GameManager/GameManager.h"

//�萔
namespace
{
	//�t�@�C���l�[���ɕK�v�ȏ��
	struct FNAME_LIST {
		int ID;
		std::string NAME;
	};

	//�V�[����ID�ƃt�@�C���p�X�l�[���̐ݒ�
	static const FNAME_LIST FNAME[] = {
		{ SCENE_ID_TITLE, "Tutorial1Fade" },
		{ SCENE_ID_USER_SELECT, "Tutorial2Fade" },
		{ SCENE_ID_TUTORIAL1, "Tutorial1Fade" },
		{ SCENE_ID_TUTORIAL2, "Tutorial2Fade" },
		{ SCENE_ID_MINIGAME, "Tutorial2Fade" },
		{ SCENE_ID_MINIGAME_LEVEL_SELECT, "Tutorial2Fade" },
		{ SCENE_ID_HOME, "HomeFade" },
		{ SCENE_ID_WORLD1, "World1Fade" },
		{ SCENE_ID_WORLD2, "World2Fade" },
	};

	//�t�@�C���p�X�ɋ��ʂ��ĕK�v�Ȃ���
	static const std::string PATH = "Image/Fade/";

	//�t�F�[�h����Ƃ��̉��Z���鋗��
	static const float FADE_ADD_DISTANCE = 10.0f;
}

//�t�F�[�h���s���Ƃ��Ɏg��(��̂P�x�ɂP�񂵂��g���Ȃ��̂�namespace)
namespace Fade
{

	///////////////////////////////�ϐ�//////////////////////////////////

	int FadeStatus_;    //�t�F�[�h�̏��
	float maxDistance_; //�~�t�F�[�h�Ŏg�p����ő勗��
	float nowDistance_; //�t�F�[�h�Ŏg�p���鍡�̋���

	//�t�F�[�h�p�̉摜(�V�[���̐���)
	Sprite* pSprite_[SCENE_ID_MAX];

	//�Q�[���I�[�o�[�t�F�C�h�p�̉摜
	Sprite* pGameOver_;
	EasingMove* pEasingScale_; //�C�[�W���O���邽�߂̃N���X(�g��k��)
	EasingMove* pEasingRotate_;//�C�[�W���O���邽�߂̃N���X(��])
	Transform GameOver_;       //�Q�[���I�[�o�[�摜�p�̃g�����X�t�H�[��

	//�t�F�[�h�p�̉摜�̕�����(�V�[���̐���)
	std::string fadeImage_[SCENE_ID_MAX];

	///////////////////////////////�֐�//////////////////////////////////

	//������
	void Fade::Initialize()
	{
		//�t�F�[�h�p�̉摜���[�h
		for (auto& f : FNAME) {
			ARGUMENT_INITIALIZE(pSprite_[f.ID], new Sprite);
			pSprite_[f.ID]->Load(PATH + f.NAME + ".png");
		}

		//�Q�[���I�[�o�[�p�̉摜���[�h
		ARGUMENT_INITIALIZE(pGameOver_, new Sprite);
		pGameOver_->Load("Image/Player/GameOver.png");

		//�e�ϐ�������
		ARGUMENT_INITIALIZE(FadeStatus_, NOOP);
		ARGUMENT_INITIALIZE(maxDistance_, std::sqrt(pow((Direct3D::screenHeight_ / 2), 2) + pow((Direct3D::screenWidth_ / 2), 2)));
		ARGUMENT_INITIALIZE(nowDistance_, ZERO);
	}

	//�V�[���J�ڂ̎��̏�����
	void Fade::SceneTransitionInitialize()
	{
		//���낢�돉������Ԃɂ��Ă���
		ARGUMENT_INITIALIZE(pEasingScale_, new EasingMove(&GameOver_.scale_, XMFLOAT3(5, 5, 5), XMFLOAT3(1, 1, 1), 4.0f, Easing::OutQuart));
		ARGUMENT_INITIALIZE(pEasingRotate_, new EasingMove(&GameOver_.rotate_, XMFLOAT3(0, 0, 720), XMFLOAT3(0, 0, 0), 4.0f, Easing::OutQuart));
	}

	//�`��
	void Fade::Draw()
	{
		//�t�F�[�h�p�̕`��
		FadeDraw();
	}

	///////////////////////////////�Z�b�g�Q�b�g�֐�//////////////////////////////////

	//��ԃZ�b�g
	void Fade::SetFadeStatus(int status, std::string filename)
	{
		ARGUMENT_INITIALIZE(FadeStatus_, status);

		//��Ԃɂ���ĕ�����
		switch (FadeStatus_)
		{

			//�摜�����`��
		case DRAW:

			NormalDraw();
			break;

			//�t�F�[�h�C��
		case FADE_CIRCLE_IN:

			ARGUMENT_INITIALIZE(nowDistance_, ZERO);
			break;

			//�t�F�[�h�A�E�g
		case FADE_CIRCLE_OUT:

			ARGUMENT_INITIALIZE(nowDistance_, maxDistance_);
			break;

			//�Q�[���I�[�o�[
		case FADE_GAME_OVER:

			pEasingScale_->Reset(&GameOver_.scale_, XMFLOAT3(5, 5, 5), XMFLOAT3(1, 1, 1), 4.0f, Easing::OutQuart);
			pEasingRotate_->Reset(&GameOver_.rotate_, XMFLOAT3(0, 0, 720), XMFLOAT3(0, 0, 0), 4.0f, Easing::OutQuart);
			break;

			//����ȊO
		default:

			break;
		}
	}

	//��ԃQ�b�g
	int Fade::GetFadeStatus() { return FadeStatus_; }

	///////////////////////////////�t�F�[�h�p�֐�////////////////////////////////////

	//�t�F�[�h�`��
	void Fade::FadeDraw()
	{
		//��Ԃɂ���ĕς���
		switch (FadeStatus_)
		{
			//�摜�����`��
		case DRAW:

			NormalDraw();
			break;

			//�t�F�[�h�C��
		case FADE_CIRCLE_IN:

			FadeInCircleDraw();
			break;

			//�t�F�[�h�A�E�g
		case FADE_CIRCLE_OUT:

			FadeOutCircleDraw();
			break;

			//�Q�[���I�[�o�[
		case FADE_GAME_OVER:

			GameOverDraw();
			break;

			//����ȊO
		default:

			break;
		}

	}

	//�`��
	void Fade::NormalDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//�`��
		pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->Draw(t, rect);
	}

	//�t�F�[�h�C���`��
	void Fade::FadeInCircleDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ += FADE_ADD_DISTANCE;

		//�`��
		pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->Draw(t, nowDistance_, rect);
	};

	//�t�F�[�h�A�E�g�`��
	void Fade::FadeOutCircleDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ -= FADE_ADD_DISTANCE;

		if (nowDistance_ < ZERO)
			ARGUMENT_INITIALIZE(nowDistance_, ZERO);

		//�`��
		pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->Draw(t, nowDistance_, rect);
	};

	//�Q�[���I�[�o�[�`��
	void Fade::GameOverDraw()
	{
		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pGameOver_->GetTextureSize();

		//������
		pEasingScale_->Move();
		bool f = pEasingRotate_->Move();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//�`��
		pGameOver_->ReversalColorDraw(GameOver_, rect, XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

		//�����C�[�W���O�̓������I����Ă���̂Ȃ玀�񂾊֐����Ă�
		if (f) GameManager::PlayerDie();
	}


}
