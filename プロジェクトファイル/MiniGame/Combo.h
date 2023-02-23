#pragma once
#include "../Engine/ResourceManager/Text.h"

/// <summary>
/// �~�j�Q�[���ɓo�ꂷ��R���{
/// </summary>
class Combo
{
	Text* pComboText_;           //�R���{�̕����\������e�L�X�g
	Text* pComboNumText_;        //�R���{���\������e�L�X�g
	XMFLOAT2 comboPositiom_;     //�e�L�X�g�̃|�W�V����
	XMFLOAT2 numberPositiom_;    //�����̃|�W�V����
	int ComboTotalCount_;        //�ǂ̂��炢�R���{���Ă��邩
	float scale_;                //�g�嗦

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Combo();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	///////////////////////////////Combo�֐�////////////////////////////////////

	/// <summary>
	/// �R���{���Z
	/// </summary>
	void AddCombo();

	/// <summary>
	/// �����̊g�嗦���Z�b�g
	/// </summary>
	void SetTextScale(const float& scale);

	/// <summary>
	/// �R���{�̐����Z�b�g
	/// </summary>
	void ComboReset();

};

