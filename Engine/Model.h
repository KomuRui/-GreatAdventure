#pragma once
#include <DirectXMath.h>
#include <assert.h>
#include <vector>
#include <string>
#include "Fbx.h"
#include "Transform.h"

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

		//ロードしたモデルデータのアドレス
		Fbx*		pFbx;

		//行列
		Transform 	transform;

		//アルファ
		float		alpha;

		//アンビエント
		int         ambient;

		//ライトの向き
		XMFLOAT4    lightDirection;

		//レイの当たり判定を付けるか
		bool rayFlag;

		//アニメーションのフレーム
		float nowFrame, animSpeed;
		int startFrame, endFrame;


		//初期化
		ModelData() : pFbx(nullptr), rayFlag(true), nowFrame(0), startFrame(0), endFrame(0), animSpeed(0), alpha(1), ambient(1)
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
	void SetAmbient(int handle, float ambt = 1);

	//ワールド行列を設定
	//引数：handle	設定したいモデルの番号
	//引数：matrix	ワールド行列
	void SetRayFlag(int handle, bool flag);

	//アニメーションのフレーム数をセット
	//引数：handle		設定したいモデルの番号
	//引数：startFrame	開始フレーム
	//引数：endFrame	終了フレーム
	//引数：animSpeed	アニメーション速度
	void SetAnimFrame(int handle, int startFrame, int endFrame, float animSpeed);

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


	//レイキャスト（レイを飛ばして当たり判定）　※未実装
	//引数：handle	判定したいモデルの番号
	//引数：data	必要なものをまとめたデータ
	void RayCast(int handle, RayCastData *data);

	//レイキャスト(全部のモデルの当たり判定)
	//引数：data	必要なものをまとめたデータ
	void AllRayCast(int handle, RayCastData* data,std::string name = "error");

};