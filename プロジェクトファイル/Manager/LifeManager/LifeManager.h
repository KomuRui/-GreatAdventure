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
	/// �_���[�W�H��������ɌĂԃ��\�b�h
	/// </summary>
	/// <param name="damage">�_���[�W�̋���</param>
	void Damage(int damage);

	/// <summary>
	/// ���񂾂ǂ���
	/// </summary>
	/// <returns>true�Ȃ玀��,false�Ȃ�܂������Ă�</returns>
	bool IsDie();
}