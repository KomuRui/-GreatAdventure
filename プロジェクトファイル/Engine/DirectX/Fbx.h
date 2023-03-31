#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <vector>
#include <string>
#include "../GameObject/Transform.h"
#include "Direct3D.h"

class FbxParts;
class Block;
class GameObject;

//レイキャスト用構造体
struct RayCastData
{
	XMFLOAT3	start;	   //レイ発射位置
	XMFLOAT3	dir;	   //レイの向きベクトル
	float       dist;	   //衝突点までの距離
	BOOL        hit;	   //レイが当たったか
	XMFLOAT3 normal;	   //法線
	XMFLOAT3 pos;          //ポジション
	Block* block;          //ブロックオブジェのポインタ
	GameObject* obstacle;  //障害物のポインタ

	RayCastData() { dist = 5000.0f; block = nullptr; obstacle = nullptr; hit = false; }
};

//一番近いポリゴンを保存するデータ
struct NearPolyData
{
	XMFLOAT3 start;  	//基準となる位置
	XMFLOAT3 normal;	//法線
	XMFLOAT3 pos;       //ポジション
	float    dist;	//衝突点までの距離

	NearPolyData() { dist = 99999.0f; normal = { 0,1,0 }; }
};

//-----------------------------------------------------------
//　FBXファイルを扱うクラス
//　ほとんどの処理は各パーツごとにFbxPartsクラスで行う
//-----------------------------------------------------------
class Fbx
{
	//FbxPartクラスをフレンドクラスにする
	//FbxPartのprivateな関数にもアクセス可
	friend class FbxParts;



	//モデルの各パーツ（複数あるかも）
	std::vector<FbxParts*>	parts_;

	//FBXファイルを扱う機能の本体
	FbxManager* pFbxManager_;

	//FBXファイルのシーン（Mayaで作ったすべての物体）を扱う
	FbxScene*	pFbxScene_;


	// アニメーションのフレームレート
	FbxTime::EMode	_frameRate;

	//アニメーション速度
	float			_animSpeed;

	//アニメーションの最初と最後のフレーム
	int _startFrame, _endFrame;


	//ノードの中身を調べる
	//引数：pNode		調べるノード
	//引数：pPartsList	パーツのリスト
	void CheckNode(FbxNode* pNode, std::vector<FbxParts*> *pPartsList);

public:
	Fbx();
	~Fbx();

	//ロード
	//引数：fileName	ファイル名
	//戻値：成功したかどうか
	virtual HRESULT Load(std::string fileName);

	//描画
	//引数：World	ワールド行列
	void    Draw(Transform& transform, int frame, float Diffuse, XMFLOAT4 Ambient, XMFLOAT4 Speculer, float Brightness,float scroll,XMFLOAT4 OutLineColor,bool isOutLineDraw, Direct3D::SHADER_TYPE shaderType);

	//解放
	void    Release();

	//任意のボーンの位置を取得
	//引数：boneName	取得したいボーンの位置
	//戻値：ボーンの位置
	XMFLOAT3 GetBonePosition(std::string boneName);

	//レイキャスト（レイを飛ばして当たり判定）
	//引数：data	必要なものをまとめたデータ
	void RayCast(RayCastData *data);

	//一番近いポリゴンを検索する
	//引数：data	必要なものをまとめたデータ
	void NearPolyNormal(NearPolyData* data);

};

