#include "TransparentBlock.h"
#include "../Engine/Model.h"

//更新の前に一度だけ呼ばれる関数
void TransparentBlock::BlockChildStartUpdate()
{
	//透明に設定
	Model::SetAlpha(hModel_, ZERO);
}
