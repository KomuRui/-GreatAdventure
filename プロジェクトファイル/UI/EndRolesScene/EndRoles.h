#pragma once
#include "../ImageBase.h"

/// <summary>
/// エンドロールを流すクラス
/// </summary>
class EndRoles : public ImageBase
{

	//戻る画像番号
	int hReturnImage_;

	//戻る画像番号のトランスフォーム
	Transform tReturnImage_;

public:


	//コンストラクタ
	EndRoles(GameObject* parent, std::string modelPath, std::string name);

	//更新の前に一度だけ呼ばれる
	void ChildStartUpdate() override;

	//更新
	void ChildUpdate() override;

	//描画
	void ChildDraw() override;

};

