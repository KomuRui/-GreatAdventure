#include "WalkingState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"

//�X�V
void WalkingState::Update2D(PlayerBase* player)
{
	HandleInput(player);
}

//3D�p�X�V
void WalkingState::Update3D(PlayerBase* player)
{
}

//���͂ɂ���ď�ԕω�����
void WalkingState::HandleInput(PlayerBase* player)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void WalkingState::Enter(PlayerBase* player)
{
}