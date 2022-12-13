#include "GameManager.h"
#include "Sprite.h"
#include <cmath>

namespace GameManager
{
	///////////////////////////////�ϐ�//////////////////////////////////

	//�t�F�[�h�̏��:0 �������Ȃ�,1 �t�F�[�h�C��, 2�t�F�[�h�A�E�g 
	int FadeStatus_;

	//�t�F�[�h�Ŏg�p����ő勗��
	float maxDistance_;

	//�t�F�[�h�Ŏg�p���鍡�̋���
	float nowDistance_;

	//�t�F�[�h�p�̉摜
	Sprite* pSprite_;

	//���ݎg�p����Ă���v���C���[�̃|�C���^�i�[�p
	Player* pNowPlayer_;

	//���݂̎g�p����Ă���X�e�[�W�̃|�C���^�i�[�p
	Stage* pNowStage_;

	///////////////////////////////�֐�//////////////////////////////////

	//������
	void GameManager::Initialize()
	{
		//�ϐ�������
		ARGUMENT_INITIALIZE(FadeStatus_, DRAW);
		ARGUMENT_INITIALIZE(pNowPlayer_, nullptr);
		ARGUMENT_INITIALIZE(pNowStage_, nullptr);
		ARGUMENT_INITIALIZE(pSprite_, new Sprite);
		ARGUMENT_INITIALIZE(maxDistance_,std::sqrt(pow((Direct3D::screenHeight_ / 2), 2) + pow((Direct3D::screenWidth_ / 2), 2)));
		ARGUMENT_INITIALIZE(nowDistance_, 0);

		//�t�F�[�h�p�̉摜���[�h
		pSprite_->Load("Image/Fade/NormalFade.png");
	}

	///////////////////////////////�Z�b�g�Q�b�g�֐�//////////////////////////////////
	
	//�v���C���[�̃|�C���^�Z�b�g
	void GameManager::SetpPlayer(Player* player) { pNowPlayer_ = player; }

	//�v���C���[�̃|�C���^�Q�b�g
	Player* GameManager::GetpPlayer() { return pNowPlayer_; }

	//�X�e�[�W�̃|�C���^�Z�b�g
	void GameManager::SetpStage(Stage* stage) { pNowStage_ = stage; }

	//�X�e�[�W�̃|�C���^�Q�b�g
	Stage* GameManager::GetpStage() { return pNowStage_; }

	//��ԃZ�b�g
	void GameManager::SetStatus(int status)
	{
		FadeStatus_ = status;

		//��Ԃɂ���ĕ�����
		switch (FadeStatus_)
		{
			//�摜�����`��
		case DRAW:

			Draw();

			//�t�F�[�h�C��
		case FADE_IN:

			ARGUMENT_INITIALIZE(nowDistance_, 0);
			break;

			//�t�F�[�h�A�E�g
		case FADE_OUT:

			ARGUMENT_INITIALIZE(nowDistance_, maxDistance_);
			break;

			//����ȊO
		default:

			break;
		}
	}

	///////////////////////////////�t�F�[�h�p�֐�////////////////////////////////////

	//�t�F�[�h�`��
	void GameManager::FadeDraw()
	{
		//��Ԃɂ���ĕς���
		switch (FadeStatus_)
		{
			//�摜�����`��
			case DRAW:

				Draw();
				break;

			//�t�F�[�h�C��
			case FADE_IN:

				FadeInDraw();
				break;

			//�t�F�[�h�A�E�g
			case FADE_OUT:

				FadeOutDraw();
				break;

			//����ȊO
			default:

				break;
		}
	
	}

	//�`��
	void GameManager::Draw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//�`��
		pSprite_->Draw(t,rect,1.0f);
	}

	//�t�F�[�h�C���`��
	void GameManager::FadeInDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ += 10;

		//�`��
		pSprite_->Draw(t, nowDistance_,rect);
	};

	//�t�F�[�h�A�E�g�`��
	void GameManager::FadeOutDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ -= 10;

		if (nowDistance_ < 0)
			ARGUMENT_INITIALIZE(nowDistance_, 0);

		//�`��
		pSprite_->Draw(t, nowDistance_, rect);
	};
}