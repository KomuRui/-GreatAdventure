#include "MiniGameManager.h"
#include "../../Engine/ResourceManager/Global.h"
#include "../../Engine/ResourceManager/Text.h"
#include "../../MiniGame/MiniGameTime.h"
#include "../GameManager/GameManager.h"
#include "../../MiniGame/Combo.h"
#include <locale.h>

//�萔
namespace
{
	static const float TEXT_INTERVAL = -0.06f;		   //�����̊Ԋu
	static const float PLAYER_NORMAL_RUN_SPEED = 5.0f; //Player�̒ʏ��Ԃ̑��x
}

//�~�j�Q�[���̊Ǘ�������
namespace MiniGameManager
{
	//�~�j�Q�[���̏��
	MiniGameStatus miniGameStatus_;   

	//�~�j�Q�[���̎��ԂȂǕ\������
	MiniGameTime* miniGameTime_;

	//�R���{�\��
	Combo* combo_;

	//���ʕ\�����邽�߂̕ϐ�
	Text* pResultTimeText_;      //���ʂ𕶎��ŕ\�����邽�߂̕ϐ�     
	int resultDis_;              //�ŏI�I�Ȍ���(����)

	//Player(���̃N���X�ł��g�������̂�Manager�ɕϐ��������Ă���)
	bool  isRunMode_;			 //���郂�[�h�ɂȂ��Ă��邩
	float runSpeed_;			 //���鑬�x             

	//������
	void Initialize()
	{
		//�����̏�����
		ARGUMENT_INITIALIZE(pResultTimeText_, new Text);
		pResultTimeText_->Initialize(TEXT_INTERVAL);

		//������
		ARGUMENT_INITIALIZE(miniGameTime_, new MiniGameTime);
		ARGUMENT_INITIALIZE(combo_, new Combo);
		ARGUMENT_INITIALIZE(isRunMode_,false);
		ARGUMENT_INITIALIZE(runSpeed_, PLAYER_NORMAL_RUN_SPEED);
		miniGameTime_->Initialize();
		combo_->Initialize();

		//�J�n���Ă��Ȃ��ɏ�����
		ARGUMENT_INITIALIZE(miniGameStatus_, MiniGameStatus::NOT_START);

		//����������
		ARGUMENT_INITIALIZE(resultDis_, ZERO);
	}

	//�`��
	void Draw()
	{
		//�R���{�\��
		combo_->Draw();

		//�~�j�Q�[���̏�Ԃɂ���ĕ\�����镨��ς���
		switch (miniGameStatus_)
		{
			//�܂��J�n���Ă��Ȃ�
		case MiniGameStatus::NOT_START:
			miniGameTime_->StartCountDraw();
			break;
			//�Q�[����
		case MiniGameStatus::PLAY:
			miniGameTime_->LimitTimeDraw();
			break;
			//�I���
		case MiniGameStatus::END:
			ResultDraw();
			break;

		default:
			break;
		}

	}

	//���ʕ\��
	void MiniGameManager::ResultDraw()
	{
		//���C�h������i�[�p
		wchar_t wtext[FILENAME_MAX];
		std::string text = std::to_string(resultDis_) + "m";

		//���C�h������ɕϊ�
		size_t ret;
		setlocale(LC_ALL, ".932");
		mbstowcs_s(&ret, wtext, text.c_str(), strlen(text.c_str()));

		//���ʕ`��
		pResultTimeText_->Draw(760, 540, wtext, 2.5f, -0.15f);
	}

	//�J�n���Ă��邩���Z�b�g
	void ChangeMiniGameStatus(MiniGameStatus status) { miniGameStatus_ = status; }

	//�X�s�[�h�����Z�b�g
	void ResetRunSpeed() { runSpeed_ = PLAYER_NORMAL_RUN_SPEED; }

	//�R���{�����Z�b�g
	void ResetCombo() { combo_->ComboReset(); }

	//�R���{�����Z
	void AddCombo() { combo_->AddCombo(); }

    //���鑬�x���擾
	float GetRunSpeed() { return runSpeed_; }

	//�X�s�[�h���Z�b�g
	void SetRunSpeed(const float& speed) { runSpeed_ = speed; }

	//�~�j�Q�[���̏�Ԃ��Q�b�g
	MiniGameStatus  MiniGameManager::GetMiniGameStatus() { return miniGameStatus_; }

	//�J�n���Ă��邩
	bool MiniGameManager::IsPlay() { return (miniGameStatus_ == MiniGameStatus::PLAY); }

	//������ݒ�
	void SetResultDis(const int& dis) { resultDis_ = dis; }

	//Run���[�h���ǂ���
	bool IsRunMode() { return isRunMode_; }

	//RunMode�ɐݒ�
	void SetRunMode(const bool& flag) {

		//�ݒ�
		isRunMode_ = flag;

		//Player�̃J�������������Ȃ�
		if (GameManager::GetpPlayer()->IsCamLong()) {

			//Player�̃J�����܂ł̃x�N�g���𒷋����̏�����O�ɐݒ�
			GameManager::GetpPlayer()->SetCamVec(XMVectorSet(ZERO, 5, -35, ZERO));
		}
		else {

			//Player�J�����𒷋����ɐݒ�
			GameManager::GetpPlayer()->SetCamLong();
		}
	}

	//�R���{�̕����̊g�嗦���Z�b�g
	void SetComboTextScale(const float& scale) { combo_->SetTextScale(scale); }

    //�o�ߎ��Ԃ��Q�b�g
	float GetTime() { return miniGameTime_->GetTime(); }

}