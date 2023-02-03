#pragma once
#include "Global.h"

//各イージング関数の説明
//こちらのサイトを参照しています
//https://easings.net/ja

/// <summary>
/// イージング(緩急みたいなもの)
/// </summary>
namespace Easing
{

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InSine(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float OutSine(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InOutSine(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InQuad(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float OutQuad(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InOutQuad(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InCubic(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float OutCubic(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InOutCubic(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InQuart(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float OutQuart(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InOutQuart(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InQuint(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float OutQuint(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InOutQuint(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InExpo(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float OutExpo(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InOutExpo(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InCirc(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float OutCirc(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InOutCirc(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InBack(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float OutBack(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InOutBack(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InElastic(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float OutElastic(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InOutElastic(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InBounce(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float OutBounce(float x);

	/// <param name="x">0～1の間の値　0 : アニメーションの開始  1 : アニメーションの終了</param>
	/// <returns>0～1の間の値 : 倍率</returns>
	float InOutBounce(float x);
};
