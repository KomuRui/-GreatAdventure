#pragma once
#include "../Engine/GameObject/GameObject.h"
#include "../Engine/ResourceManager/Text.h"

//�O���錾
class CsvReader;

/// <summary>
/// ���u�Ƙb���Ƃ��̉摜��\����������N���X
/// </summary>
class TalkImage : public GameObject
{
	///////////////////////������///////////////////////////

	int drawTextNum_;			//���`�悵�Ă镶����̔ԍ�
	bool isLastDraw_;			//�Ō�܂ŕ`�悵�����ǂ���
	bool isButtonPushTextNext_; //�{�^���������Ď��̕�����ɍX�V���邩

	CsvReader* pCsv_; //�������O���擾���邽�߂̕ϐ�

	/////////////////////////�摜///////////////////////////

	int hBasePict_;      //�x�[�X�摜�ԍ�
	int hCharaPict_;     //�L�����摜�ԍ�
	int hNextPict_;      //Next�摜�ԍ�

	Transform tBase_;    //�x�[�XTransform
	Transform tChara_;   //�L����Transform
	Transform tNext_;    //NextTransform

	////////////////////////�e�L�X�g/////////////////////////

	Text* pText_;        //�����\������p

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TalkImage(GameObject* parent);

	//�f�X�g���N�^
	~TalkImage();

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	/// <summary>
	/// �{�^���������ĕ`�悷�镶��������̕�����ɍX�V����
	/// </summary>
	void ButtonPushDrawTextNext();

	/// <summary>
	/// ���̕������
	/// </summary>
	void NextText();

	/// <summary>
	/// �V����Csv�ǂݍ��݂�����
	/// </summary>
	/// <param name="fileNamePath">Csv�ǂݍ��݂��������t�@�C���p�X</param>
	void NewCsvFile(std::string fileNamePath);

	/// <summary>
	/// �g�p���Ă��镶���̕ϐ����擾
	/// </summary>
	/// <returns>�g�p���Ă��镶���̕ϐ�</returns>
	Text* GetText() { return pText_; }

	/// <summary>
	/// �Ō�܂ŕ`�悵�����ǂ���
	/// </summary>
	/// <returns>true�Ȃ炵��,false�Ȃ炵�ĂȂ�</returns>
	bool IsLastDraw() { return isLastDraw_; }

	/// <summary>
	/// �{�^���������Ď��̕�����ɍX�V���邩���Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ�{�^���������Ď��̕�����ɍX�V����悤��</param>
	void SetButtonPushTextNext(bool flag) { isButtonPushTextNext_ = flag; }
};

