#include "GameManager.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/Sprite.h"
#include "../../Engine/Time.h"
#include "../../Engine/Component/EasingMove.h"
#include "../../Engine/Easing.h"
#include "../../Engine/Light.h"
#include "../LifeManager/LifeManager.h"
#include "../CoinManager/CoinManager.h"
#include "../TextManager/TextManager.h"
#include "../MiniGameManager/MiniGameManager.h"
#include "../ButtonManager/ButtonManager.h"
#include "../../OtherObject/UserInfomation.h"
#include <cmath>

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

//�Q�[���̂��낢��ȊǗ�������
namespace GameManager
{
	///////////////////////////////�ϐ�//////////////////////////////////

	//�t�F�[�h�̏��:0 �������Ȃ�,1 �t�F�[�h�C��, 2�t�F�[�h�A�E�g 
	int FadeStatus_;

	//�t�F�[�h�Ŏg�p����ő勗��
	float maxDistance_;

	//�t�F�[�h�Ŏg�p���鍡�̋���
	float nowDistance_;

	//�t�F�[�h�p�̉摜(�V�[���̐���)
	Sprite* pSprite_[SCENE_ID_MAX];

	//�Q�[���I�[�o�[�p�̉摜
	Sprite* pGameOver_;
	EasingMove* pEasingScale_; //�C�[�W���O���邽�߂̃N���X(�g��k��)
	EasingMove* pEasingRotate_;//�C�[�W���O���邽�߂̃N���X(��])
	Transform GameOver_;       //�Q�[���I�[�o�[�摜�p�̃g�����X�t�H�[��

	//���ݎg�p����Ă���v���C���[�̃|�C���^�i�[�p
	PlayerBase* pNowPlayer_;

	//���݂̎g�p����Ă���X�e�[�W�̃|�C���^�i�[�p
	Stage* pNowStage_;

	//���݂̎g�p����Ă��郏�[�v�̃|�C���^�i�[�p
	Warp* pNowWarp_;

	//�V�[���}�l�[�W���[�̃|�C���^�i�[�p
	SceneManager* pSceneManager_;

	//�t�F�[�h�p�̉摜�̕�����(�V�[���̐���)
	std::string fadeImage_[SCENE_ID_MAX];

	///////////////////////////////�֐�//////////////////////////////////

	//������
	void GameManager::Initialize()
	{
		//���[�U�[���̏�����
		UserInfomation::Initialize();

		//���C�t�}�l�[�W���[�̏�����
		LifeManager::Initialize();

		//�R�C���}�l�[�W���[�̏�����
		CoinManager::Initialize();

		//�e�L�X�g�}�l�[�W���̏�����
		TextManager::Initialize();

		//�~�j�Q�[���}�l�[�W���[�̏�����
		MiniGameManager::Initialize();

		//�t�F�[�h�p�̉摜���[�h
		for (auto& f : FNAME) {
			ARGUMENT_INITIALIZE(pSprite_[f.ID], new Sprite);
			pSprite_[f.ID]->Load(PATH+f.NAME+".png");
		}

		//�Q�[���I�[�o�[�p�̉摜���[�h
		ARGUMENT_INITIALIZE(pGameOver_,new Sprite);
		pGameOver_->Load("Image/Player/GameOver.png");

		//�e�ϐ�������
		ARGUMENT_INITIALIZE(FadeStatus_, NOOP);
		ARGUMENT_INITIALIZE(pNowPlayer_, nullptr);
		ARGUMENT_INITIALIZE(pNowStage_, nullptr);
		ARGUMENT_INITIALIZE(pNowWarp_, nullptr);
		ARGUMENT_INITIALIZE(pSceneManager_, nullptr);
		ARGUMENT_INITIALIZE(maxDistance_,std::sqrt(pow((Direct3D::screenHeight_ / 2), 2) + pow((Direct3D::screenWidth_ / 2), 2)));
		ARGUMENT_INITIALIZE(nowDistance_, ZERO);
		ARGUMENT_INITIALIZE(pEasingScale_, new EasingMove(&GameOver_.scale_,XMFLOAT3(5,5,5),XMFLOAT3(1,1,1),4.0f, Easing::OutQuart));
		ARGUMENT_INITIALIZE(pEasingRotate_, new EasingMove(&GameOver_.rotate_,XMFLOAT3(0,0,720),XMFLOAT3(0,0,0),4.0f, Easing::OutQuart));
	}

	//�V�[���J�ڂ̎��̏�����
	void GameManager::SceneTransitionInitialize()
	{
		//���낢�돉������Ԃɂ��Ă���
		Light::Initialize();
		MiniGameManager::Initialize();
		CoinManager::SceneTransitionInitialize();
		LifeManager::SceneTransitionInitialize();
		ARGUMENT_INITIALIZE(pEasingScale_, new EasingMove(&GameOver_.scale_, XMFLOAT3(5, 5, 5), XMFLOAT3(1, 1, 1), 4.0f, Easing::OutQuart));
		ARGUMENT_INITIALIZE(pEasingRotate_, new EasingMove(&GameOver_.rotate_, XMFLOAT3(0, 0, 720), XMFLOAT3(0, 0, 0), 4.0f, Easing::OutQuart));
	}

	//Player�����S��������LifeManager����Ă΂��
	void GameManager::PlayerDie()
	{
		//���C�t���ʂ��
		LifeManager::ResetLife();

		//�������񂾃V�[�����`���[�g���A���V�[���Ȃ�
		if(pSceneManager_->GetSceneId() == SCENE_ID_TUTORIAL1 || pSceneManager_->GetSceneId() == SCENE_ID_TUTORIAL2)
			pSceneManager_->ChangeScene(SCENE_ID_TUTORIAL1);
		else
			pSceneManager_->ChangeScene(SCENE_ID_HOME);
	}

	//�X�V
	void GameManager::Update()
	{
		//�{�^���}�l�[�W���̍X�V���Ă�
		ButtonManager::Update();
	}

	//�`��(�R�C���̎擾����Player���C�t�̕\��)
	void GameManager::Draw()
	{
		//�����~�j�Q�[���Ȃ�
		if (pSceneManager_->GetSceneId() == SCENE_ID_MINIGAME)
		{
			//�~�j�Q�[���̊e����`��
			MiniGameManager::Draw();

			//�R�C���̎擾���̕\��
			CoinManager::Draw();
		}
		//����Play�V�[���Ȃ�
		else if (pSceneManager_->GetSceneId() != SCENE_ID_TITLE && pSceneManager_->GetSceneId() != SCENE_ID_USER_SELECT)
		{
			//Player���C�t�̕\��
			LifeManager::Draw();

			//�R�C���̎擾���̕\��
			CoinManager::Draw();
		}
			
		//�t�F�[�h�p�̕`��
		FadeDraw();
	}

	///////////////////////////////�Z�b�g�Q�b�g�֐�//////////////////////////////////
	
	//�v���C���[�̃|�C���^�Z�b�g
	void GameManager::SetpPlayer(PlayerBase* player) { pNowPlayer_ = player; }

	//�v���C���[�̃|�C���^�Q�b�g
	PlayerBase* GameManager::GetpPlayer() { return pNowPlayer_; }

	//�X�e�[�W�̃|�C���^�Z�b�g
	void GameManager::SetpStage(Stage* stage) { pNowStage_ = stage; }

	//�X�e�[�W�̃|�C���^�Q�b�g
	Stage* GameManager::GetpStage() { return pNowStage_; }

	//���[�v�̃|�C���^�Z�b�g
	void GameManager::SetpWarp(Warp* warp) { pNowWarp_ = warp; }

	//���[�v�̃|�C���^�Q�b�g
	Warp* GameManager::GetpWarp() { return pNowWarp_; }

	//�V�[���}�l�[�W���[�̃|�C���^�Z�b�g
	void GameManager::SetpSceneManager(SceneManager* scene) { pSceneManager_ = scene; }

	//�V�[���}�l�[�W���[�̃|�C���^�Q�b�g
	SceneManager* GameManager::GetpSceneManager() { return pSceneManager_; }

	//��ԃZ�b�g
	void GameManager::SetStatus(int status, std::string filename)
	{
		ARGUMENT_INITIALIZE(FadeStatus_,status);

		//��Ԃɂ���ĕ�����
		switch (FadeStatus_)
		{

		//�摜�����`��
		case DRAW:

			NormalDraw();
			break;

		//�t�F�[�h�C��
		case FADE_IN:

			ARGUMENT_INITIALIZE(nowDistance_, ZERO);
			break;

		//�t�F�[�h�A�E�g
		case FADE_OUT:

			ARGUMENT_INITIALIZE(nowDistance_, maxDistance_);
			break;

		//�Q�[���I�[�o�[
		case GAME_OVER:

			pEasingScale_->Reset(&GameOver_.scale_, XMFLOAT3(5, 5, 5), XMFLOAT3(1, 1, 1), 4.0f, Easing::OutQuart);
			pEasingRotate_->Reset(&GameOver_.rotate_, XMFLOAT3(0, 0, 720), XMFLOAT3(0, 0, 0), 4.0f, Easing::OutQuart);
			break;

		//����ȊO
		default:

			break;
		}
	}

	//��ԃQ�b�g
	int GameManager::GetStatus() { return FadeStatus_; }

	///////////////////////////////�t�F�[�h�p�֐�////////////////////////////////////

	//�t�F�[�h�`��
	void GameManager::FadeDraw()
	{
		//��Ԃɂ���ĕς���
		switch (FadeStatus_)
		{
			//�摜�����`��
			case DRAW:

				NormalDraw();
				break;

			//�t�F�[�h�C��
			case FADE_IN:

				FadeInDraw();
				break;

			//�t�F�[�h�A�E�g
			case FADE_OUT:

				FadeOutDraw();
				break;

				//�Q�[���I�[�o�[
			case GAME_OVER:

				GameOverDraw();
				break;

			//����ȊO
			default:

				break;
		}
	
	}

	//�`��
	void GameManager::NormalDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_[pSceneManager_->GetSceneId()]->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//�`��
		pSprite_[pSceneManager_->GetSceneId()]->Draw(t,rect);
	}

	//�t�F�[�h�C���`��
	void GameManager::FadeInDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_[pSceneManager_->GetSceneId()]->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = ZERO;
		rect.top = ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ += FADE_ADD_DISTANCE;

		//�`��
		pSprite_[pSceneManager_->GetSceneId()]->Draw(t, nowDistance_,rect);
	};

	//�t�F�[�h�A�E�g�`��
	void GameManager::FadeOutDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_[pSceneManager_->GetSceneId()]->GetTextureSize();

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
		pSprite_[pSceneManager_->GetSceneId()]->Draw(t, nowDistance_, rect);
	};

	//�Q�[���I�[�o�[�`��
	void GameManager::GameOverDraw()
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
		pGameOver_->ReversalColorDraw(GameOver_, rect,XMFLOAT4(0.0f,0.0f, 0.0f,1.0f));

		//�����C�[�W���O�̓������I����Ă���̂Ȃ玀�񂾊֐����Ă�
		if (f) PlayerDie();
	}
}