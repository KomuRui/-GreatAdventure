#include "ButtonBase.h"

//�R���X�g���N�^
ButtonBase::ButtonBase(GameObject* parent, std::string modelPath, std::string name)
	:ImageBase(parent,modelPath,name), isSelect_(false)
{}

