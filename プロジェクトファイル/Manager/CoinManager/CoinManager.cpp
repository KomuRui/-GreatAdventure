#include "CoinManager.h"
#include "../../Engine/Transform.h"
#include "../../Engine/Text.h"
#include "../../Engine/Global.h"
#include "../../Engine/Image.h"

/// <summary>
/// Player�̎����Ă�R�C���Ǘ�
/// </summary>
namespace CoinManager
{
	///////////////////////////////�ϐ�//////////////////////////////////

	//�R�C���̑���
	int coinTotalCount;

	//�摜
	int coinImageNum;               //�R�C���̉摜�ԍ�
	int crossImageNum;              //�~UI�̉摜�ԍ�
	Transform coinImageTransform_;  //�R�C���摜�̈ʒu�E�g�嗦
	Transform crossImageTransform_; //�~�摜�̈ʒu�E�g�嗦

	//�e�L�X�g
	Text* pCoinText_;           //�R�C���̐��\������e�L�X�g
	XMFLOAT2 textPositiom_;     //�e�L�X�g�̃|�W�V����

	///////////////////////////////�֐�//////////////////////////////////

	//������
	void CoinManager::Initialize()
	{
		//�R�C���̑���������
		ARGUMENT_INITIALIZE(coinTotalCount, ZERO);

		//�摜�̃��[�h
		coinImageNum = Image::Load("Image/Coin/Coin.png");
		crossImageNum = Image::Load("Image/Coin/Cross.png");

		//�e�L�X�g�̏�����
		ARGUMENT_INITIALIZE(pCoinText_, new Text);
		pCoinText_->Initialize();

		//�摜�̃|�W�V�����ݒ�
		ARGUMENT_INITIALIZE(coinImageTransform_.position_.x, GetPrivateProfilefloat("POSITION", "coinImageX", "1", "Image/Coin/CoinPosition.ini"));
		ARGUMENT_INITIALIZE(coinImageTransform_.position_.y, GetPrivateProfilefloat("POSITION", "coinImageY", "1", "Image/Coin/CoinPosition.ini"));
		ARGUMENT_INITIALIZE(crossImageTransform_.position_.x, GetPrivateProfilefloat("POSITION", "crossImageX", "1", "Image/Coin/CoinPosition.ini"));
		ARGUMENT_INITIALIZE(crossImageTransform_.position_.y, GetPrivateProfilefloat("POSITION", "crossImageY", "1", "Image/Coin/CoinPosition.ini"));

		//�e�L�X�g�̃|�W�V�����ݒ�
		ARGUMENT_INITIALIZE(textPositiom_.x, GetPrivateProfilefloat("POSITION", "coinTextX", "1", "Image/Coin/CoinPosition.ini"))
		ARGUMENT_INITIALIZE(textPositiom_.y, GetPrivateProfilefloat("POSITION", "coinTextY", "1", "Image/Coin/CoinPosition.ini"))
	}

	//�R�C�����������Ă��邩�`��
	void CoinManager::Draw()
	{
		//�摜
		Image::SetTransform(coinImageNum, coinImageTransform_);
		Image::Draw(coinImageNum);
		//Image::SetTransform(crossImageNum, crossImageTransform_);
		//Image::Draw(crossImageNum);

		//�e�L�X�g
		pCoinText_->Draw(textPositiom_.x, textPositiom_.y, coinTotalCount, coinImageTransform_.scale_.x);
	}


	//�R�C���̒ǉ�
	void AddCoin(int num){ coinTotalCount += num; }
}