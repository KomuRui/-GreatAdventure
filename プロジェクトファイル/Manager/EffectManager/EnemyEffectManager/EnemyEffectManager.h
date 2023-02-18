#pragma once
#include "../../../Engine/GameObject.h"

/// <summary>
/// Enemy�̃G�t�F�N�g���Ǘ�����
/// </summary>
namespace EnemyEffectManager
{

	/// <summary>
	/// �����������̃G�t�F�N�g
	/// </summary>
	/// <param name="handle">�G�t�F�N�g�ԍ�</param>
	/// <param name="Hitpos">�G�t�F�N�g�𔭐����������ʒu</param>
	/// <param name="pos">�G�̈ʒu</param>
	void HitEffect(const XMFLOAT3& Hitpos, const XMFLOAT3& pos);

	/// <summary>
	/// ���ʂƂ��̃G�t�F�N�g
	/// </summary>
	/// <param name="handle">�G�t�F�N�g�ԍ�</param>
	/// <param name="pos">�G�̈ʒu</param>
	/// <param name="dir">�G�t�F�N�g�̕���</param>
	void DieEffect(const XMFLOAT3& pos, const XMVECTOR& dir);
}