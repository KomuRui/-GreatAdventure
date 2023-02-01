#pragma once
#include "../ImageBase.h"

/// <summary>
/// �{�^���N���X
/// </summary>
class Button : public ImageBase
{
private:

	//�������Ƃ��̊֐��|�C���^
	void(*OnPushFunc);

	//�{�^���I�����ꂽ�u�Ԃɂ�Ԋ֐��|�C���^
	void(*ButtonSelect);

	//�{�^�����I������Ă���Ƃ��������邩
	void(*ButtonSelecting);

	//�I������Ă��邩�ǂ���
	bool isSelect_;

public:

	//�R���X�g���N�^
	Button(GameObject* parent, std::string modelPath, std::string name);
	
	////////////////////�I�[�o�[���C�h����֐�/////////////////////////

	/// <summary>
	/// �p����p�̏�����
	/// </summary>
	virtual void ChildInitialize() override {};

	/// <summary>
	/// �p����p�̃X�^�[�g�A�b�v�f�[�g
	/// </summary>
	virtual void ChildStartUpdate()override {};

	/// <summary>
	/// �p���悲�Ƃ�Update�ł̓�������ς���
	/// </summary>
	virtual void ChildUpdate() override {};

	/// <summary>
	/// �p����p�̕`��
	/// </summary>
	virtual void ChildDraw()override {};

	/////////////////////////////�֐�////////////////////////////////

	/// <summary>
	/// �{�^���������ꂽ�牽���邩
	/// </summary>
	/// <param name="p">���s�������֐��|�C���^</param>
    void IsButtonPush(void (*p)()) { p(); }

	/// <summary>
	/// �{�^�����I�����ꂽ�u�Ԃɉ������邩
	/// </summary>
	/// <param name="p">���s�������֐��|�C���^</param>
	void IsButtonSelect(void (*p)()) { p(); }

	/// <summary>
	/// �{�^�����I������Ă���Ƃ��������邩
	/// </summary>
	/// <param name="p">���s�������֐��|�C���^</param>
	void IsButtonSelecting(void (*p)()) { p(); }

	//////////////////////////�Z�b�g�Q�b�g�֐�/////////////////////////////

	/// <summary>
	/// �I������Ă��邩���Z�b�g 
	/// </summary>
	/// <param name="flag">true�Ȃ�I������Ă�</param>
	void SetSelect(bool flag) { isSelect_ = flag; }

	/// <summary>
	/// �I������Ă��邩���擾
	/// </summary>
	/// <returns>true�Ȃ�I������Ă���</returns>
	bool IsSelect() { return isSelect_; }
};

