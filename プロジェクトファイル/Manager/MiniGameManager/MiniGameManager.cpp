#include "MiniGameManager.h"
#include "../../Engine/Global.h"
#include "../../Engine/Text.h"
#include <locale.h>

//�~�j�Q�[���̊Ǘ�������
namespace MiniGameManager
{
	//�~�j�Q�[���̏��
	MiniGameStatus miniGameStatus_;   

	//���ʕ\�����邽�߂̕ϐ�
	Text* pResultTimeText_;      //���ʂ𕶎��ŕ\�����邽�߂̕ϐ�     
	int resultDis_;              //�ŏI�I�Ȍ���(����)

	//������
	void Initialize()
	{
		//�J�n���Ă��Ȃ��ɏ�����
		ARGUMENT_INITIALIZE(miniGameStatus_, MiniGameStatus::NOT_START);

		//����������
		ARGUMENT_INITIALIZE(resultDis_, ZERO);
	}

	//�`��
	void Draw()
	{
		switch (miniGameStatus_)
		{
			//�܂��J�n���Ă��Ȃ�
		case MiniGameStatus::NOT_START:
			StartCountDraw();
			break;
			//�Q�[����
		case MiniGameStatus::PLAY:
			LimitTimeDraw();
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

	//�~�j�Q�[���̏�Ԃ��Q�b�g
	MiniGameStatus  MiniGameManager::GetMiniGameStatus() { return miniGameStatus_; }

	//�J�n���Ă��邩
	bool MiniGameManager::IsPlay() { return (miniGameStatus_ == MiniGameStatus::PLAY); }

	//������ݒ�
	void SetResultDis(const int& dis) { resultDis_ = dis; }

}