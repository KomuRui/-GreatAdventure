#include "TransparentBlock.h"
#include "../Engine/ResourceManager/Model.h"

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void TransparentBlock::BlockChildStartUpdate()
{
	//�����ɐݒ�
	Model::SetAlpha(hModel_, ZERO);
}
