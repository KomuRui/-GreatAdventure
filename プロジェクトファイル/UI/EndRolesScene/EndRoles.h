#pragma once
#include "../ImageBase.h"

/// <summary>
/// エンドロールを流すクラス
/// </summary>
class EndRoles : public ImageBase
{

public:


	//コンストラクタ
	EndRoles(GameObject* parent, std::string modelPath, std::string name);

	//更新の前に一度だけ呼ばれる
	void ChildStartUpdate() override;

	//更新
	void ChildUpdate() override;

};

