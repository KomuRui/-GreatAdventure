#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/Component/EasingMove.h"
#include "StageModelBase.h"
#include <map>

//�e�`�F�b�N�|�C���g�̔ԍ�
enum class CheckPoint
{
	FIRST = 1,
	NONE,
	SECOND,
	NONE2,
	THIRD,
	NONE3,
	FOURTH,
	NONE4,
};

/// <summary>
/// �X�e�[�W��I�����鎞�̃x�[�X�ƂȂ�N���X
/// </summary>
class BaseSelectStage : public GameObject
{
	//���f���ԍ�
	int hModel_;

	//�C�[�W���O�ɕK�v�ȕϐ�
	EasingMove* pEasing_;

	//�ǂ̃`�F�b�N�|�C���g�����Ă��邩
	int lookCheckPoint_;

	//�`�F�b�N�|�C���g�ɊY������StageModel���i�[����ꏊ
	std::map<int, StageModelBase*> table_;

public:

	//�R���X�g���N�^
	BaseSelectStage(GameObject* parent);

	////////////////////////�I�[�o�[���C�h����֐�//////////////////////////////

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override {};

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override {};

	////////////////////////�֐�//////////////////////////////

	/// <summary>
	/// �`�F�b�N�|�C���g�v�Z
	/// </summary>
	/// <param name="sige">�v���X�������}�C�i�X������</param>
	void CheckPointCalc(int sige);

	/// <summary>
	/// �`�F�b�N�|�C���g���f�����Z�b�g
	/// </summary>
	/// <param name="checkPointNum">���Ԗڂ̃`�F�b�N�|�C���g��</param>
	/// <param name="p">�Z�b�g������StageModel</param>
	void SetCheckPointModel(int checkPointNum, StageModelBase* p) { table_[checkPointNum] = p; }
};

