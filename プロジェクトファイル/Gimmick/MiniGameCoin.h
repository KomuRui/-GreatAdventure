#pragma once
#include "Coin.h"
#include "../Engine/Component/Posture.h"

/// <summary>
/// �~�j�Q�[���p�̃R�C��
/// </summary>
class MiniGameCoin : public Coin
{
	//�������p���ɂ��Ă����R���|�[�l���g
	Posture posture_;

public:

	//�R���X�g���N�^
	MiniGameCoin(GameObject* parent);


	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//�X�V�̑O�Ɉ�x�����Ă΂��֐�
	void ChildCoinStartUpdate() override;

	//�X�V
	void ChildCoinUpdate() override;

};

