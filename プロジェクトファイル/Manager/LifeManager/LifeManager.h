#pragma once

/// <summary>
/// Player�̃��C�t�Ǘ�
/// </summary>
namespace LifeManager
{
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �V�[���J�ڂ̎��̏�����
	/// </summary>
	void SceneTransitionInitialize();

	/// <summary>
	/// �_���[�W�H��������ɌĂԃ��\�b�h
	/// </summary>
	void Damage();

	/// <summary>
	/// HPUI�`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �摜�̊g��k��
	/// </summary>
	void ImageScaling();

	/// <summary>
	/// ���񂾂ǂ���
	/// </summary>
	/// <returns>true�Ȃ玀��,false�Ȃ�܂������Ă�</returns>
	bool IsDie();
}