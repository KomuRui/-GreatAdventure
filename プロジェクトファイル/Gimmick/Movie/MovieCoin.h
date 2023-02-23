#pragma once
#include "../Coin.h"
#include "../../Engine/Component/EasingMove.h"

/// <summary>
/// ���[�r�[�p�̃R�C��
/// </summary>
class MovieCoin : public Coin
{
	//�ړ���|�W�V����
	XMFLOAT3 destinationPos_;

	//�C�[�W���O�ňړ����邽�߂ɕK�v�ȃR���|�[�l���g
	EasingMove* pEasing_;

	//�`�F���W���Ă��邩�ǂ���
	bool isChange_;

public:

	//�R���X�g���N�^
	MovieCoin(GameObject* parent);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//�X�V�̑O�Ɉ�x�����Ă΂��֐�
	void ChildCoinStartUpdate() override;

	//�X�V
	void ChildCoinUpdate() override;

};

