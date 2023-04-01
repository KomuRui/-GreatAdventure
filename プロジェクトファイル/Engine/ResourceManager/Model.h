#pragma once
#include <DirectXMath.h>
#include <assert.h>
#include <vector>
#include <string>
#include "../DirectX/Fbx.h"
#include "../GameObject/Transform.h"
#include "Global.h"
#include "../GameObject/GameObject.h"

//前定義
class Block;

//-----------------------------------------------------------
//3Dモデル（FBXファイル）を管理する
//-----------------------------------------------------------
namespace Model
{
	//モデル情報
	struct ModelData
	{
		//ファイル名
		std::string fileName;

		//レイで障害物と当たった時を知りたいので用意しておく
		GameObject* pObstacle;

		//レイでブロックに当たった時動かしたいので用意しておく
		Block* pBlock;

		//ロードしたモデルデータのアドレス
		Fbx* pFbx;

		//どのシェーダを使うか
		Direct3D::SHADER_TYPE  shaderType;

		//行列
		Transform 	transform;

		//アルファ
		float		alpha;

		//アンビエント
		XMFLOAT4    ambient;

		//スペキュラー
		XMFLOAT4    speculer;

		//アウトラインを表示する時の色
		XMFLOAT4    outLineColor;

		//明るさ
		float brightness;

		//uvスクロールの値
		float uvScroll;

		//レイの当たり判定を付けるか
		bool isRay;

		//アウトライン描画するか
		bool isOutLineDraw;

		//アニメーション再生するか
		bool isAnim;

		//アニメーションのフレーム
		float nowFrame, animSpeed;
		int startFrame, endFrame;


		//初期化
		ModelData() : pFbx(nullptr), isRay(false), nowFrame(ZERO), startFrame((int)ZERO), endFrame((int)ZERO), animSpeed(ZERO), shaderType(Direct3D::SHADER_3D), outLineColor(ZERO, ZERO, ZERO, 1.0f),
			alpha(1), ambient(ZERO, ZERO, ZERO, ZERO), isAnim(false), speculer(ZERO, ZERO, ZERO, ZERO), brightness(ZERO), pBlock(nullptr), pObstacle(nullptr), uvScroll(ZERO), isOutLineDraw(false)
		{
		}

		//アニメーションのフレーム数をセット
		//引数：startFrame	開始フレーム
		//引数：endFrame	終了フレーム
		//引数：animSpeed	アニメーション速度
		void SetAnimFrame(int start, int end, float speed)
		{
			nowFrame = (float)start;
			startFrame = start;
			endFrame = end;
			animSpeed = speed;
		}
	};


	//初期化
	void Initialize();

	//モデルをロード
	//引数：fileName　ファイル名
	//戻値：そのモデルデータに割り当てられた番号
	int Load(std::string fileName);

	//描画
	//引数：handle	描画したいモデルの番号
	//引数：matrix	ワールド行列
	void Draw(int handle);

	//任意のモデルを開放
	//引数：handle	開放したいモデルの番号
	void Release(int handle);

	//全てのモデルを解放
	//（シーンが切り替わるときは必ず実行）
	void AllRelease();

	//ワールド行列を設定
	//引数：handle	設定したいモデルの番号
	//引数：matrix	ワールド行列
	void SetAlpha(int handle, float Alpha);

	//ワールド行列を設定
	//引数：handle	設定したいモデルの番号
	//引数：matrix	ワールド行列
	void SetAmbient(int handle, XMFLOAT4 ambt = { ZERO,ZERO,ZERO,ZERO });

	//ワールド行列を設定
	//引数：handle	設定したいモデルの番号
	//引数：matrix	ワールド行列
	void SetSpeculer(int handle, XMFLOAT4 Speculer = { ZERO,ZERO,ZERO,ZERO });

	/// <summary>
	/// アウトラインの色をセット
	/// </summary>
	/// <param name="handle">モデル番号</param>
	/// <param name="OutLine">設定したいアウトラインの色</param>
	void SetOutLineColor(int handle, XMFLOAT4 OutLine = { ZERO,ZERO,ZERO,1.0f });

	//ワールド行列を設定
	//引数：handle	設定したいモデルの番号
	//引数：matrix	ワールド行列
	void SetBrightness(int handle, float Brightness = ZERO);

	//ワールド行列を設定
	//引数：handle	設定したいモデルの番号
	//引数：matrix	ワールド行列
	void SetRayFlag(int handle, bool flag);

	/// <summary>
	/// アウトラインを描画するかセット
	/// </summary>
	/// <param name="handle">モデルの番号</param>
	/// <param name="flag">trueなら描画する</param>
	void SetOutLineDrawFlag(int handle, bool flag);

	/// <summary>
	/// ブロックオブジェのポインタをセット
	/// </summary>
	/// <param name="handle">モデル番号</param>
	/// <param name="block">ブロックオブジェのポインタ</param>
	void SetBlockObj(int handle, Block* block);

	/// <summary>
	/// 障害物のポインタをセット
	/// </summary>
	/// <param name="handle">モデル番号</param>
	/// <param name="block">Obstacleのポインタ</param>
	void SetObstacleObj(int handle, GameObject* Obstacle);

	/// <summary>
	/// 使うシェーダをセット
	/// </summary>
	/// <param name="type">使いたいシェーダ</param>
	void SetShederType(int handle, Direct3D::SHADER_TYPE type);

	/// <summary>
	/// UVスクロールの値をセット
	/// </summary>
	/// <param name="handle">モデル番号</param>
	/// <param name="scroll">scrollの値</param>
	void SetUvScroll(int handle, float scroll);

	//アニメーションのフレーム数をセット
	//引数：handle		設定したいモデルの番号
	//引数：startFrame	開始フレーム
	//引数：endFrame	終了フレーム
	//引数：animSpeed	アニメーション速度
	void SetAnimFrame(int handle, int startFrame, int endFrame, float animSpeed);

	//アニメーションするかしないか
	void SetAnimFlag(int handle, bool flag);

	//アニメーションのスピードをセットする関数
	void SetAnimSpeed(int handle, float speed);

	//現在のアニメーションのフレームを取得
	int GetAnimFrame(int handle);

	//任意のボーンの位置を取得
	//引数：handle		調べたいモデルの番号
	//引数：boneName	調べたいボーンの名前
	//戻値：ボーンの位置（ワールド座標）
	XMFLOAT3 GetBonePosition(int handle, std::string boneName);

	//ワールド行列を設定
	//引数：handle	設定したいモデルの番号
	//引数：matrix	ワールド行列
	void SetTransform(int handle, Transform& transform);

	//ワールド行列の取得
	//引数：handle	知りたいモデルの番号
	//戻値：ワールド行列
	XMMATRIX GetMatrix(int handle);


	//レイキャスト（レイを飛ばして当たり判定）
	//引数：handle	判定したいモデルの番号
	//引数：data	必要なものをまとめたデータ
	void RayCast(int handle, RayCastData* data);

	//一番近いポリゴンの法線とポジションをRayCastDataに格納
	//引数：handle	判定したいモデルの番号
	//引数：data	必要なものをまとめたデータ
	void NearPolyNormal(int handle, NearPolyData* data);

	//レイキャスト(当たったモデルのアウトラインを表示させる)
	//引数：data	必要なものをまとめたデータ
	void RayCastOutLineSet(RayCastData* data, XMFLOAT4 outLineColor = {0,0,0,1});

	//レイキャスト(指定されたオブジェクトとステージとの当たり判定)
	//引数：data	必要なものをまとめたデータ
	void AllRayCast(int handle, RayCastData* data);

};