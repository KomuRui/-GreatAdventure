#pragma once
#include "GameObject.h"
#include "BillBoard.h"
#include <list>


//エミッター（パーティクルの発生源）を作る時のデータ一覧
//Start関数の引数として使う
struct EmitterData
{
	std::string textureFileName;	//画像ファイル名
	XMFLOAT3 position;		//位置
	XMFLOAT3 positionErr;	//位置の誤差
	XMFLOAT3 dir;			//パーティクルの移動方向
	XMFLOAT3 dirErr;		//移動方向の誤差（各軸の角度）
	XMFLOAT3 axisPosMove;   //任意軸の移動
	XMVECTOR axisAngle;     //任意軸で回転させる
	float    Angle;         //任意軸でどのくらいの値で回転させるか
	float	 speed;			//1フレームの速度
	float	 speedErr;		//速度誤差（0～1）
	float	 accel;			//加速度
	float	 gravity;		//重力
	bool     axisFlag;      //軸で回転させるかどうか
	XMFLOAT4 color;			//色（RGBA 0～1）
	XMFLOAT4 deltaColor;	//色の変化量
	XMFLOAT2 size;			//サイズ
	XMFLOAT2 sizeErr;		//サイズ誤差（0～1）
	XMFLOAT2 scale;			//1フレームの拡大率
	float    lifeTime;		//パーティクルの寿命（フレーム数）

	int delay;			//何フレームおきにパーティクルを発生させるか
	int number;			//1度に出すパーティクル量

	//初期化
	EmitterData()
	{
		textureFileName = "";
		position = positionErr = dir = dirErr = XMFLOAT3(0, 0, 0);
		speed = 0.0f;
		accel = 1.0f;
		gravity = 0.0f;
		color = XMFLOAT4(1, 1, 1, 1);
		deltaColor = XMFLOAT4(0, 0, 0, 0);
		size = scale = XMFLOAT2(1.0f, 1.0f);
		lifeTime = 30.0f;
		axisAngle = XMVectorSet(0, 0, 0, 0);
		axisFlag = false;
		Angle = 0;
	}
};



//エフェクトを管理するクラス
class Particle : public GameObject
{
	//エミッター（パーティクルの噴射口）
	struct Emitter
	{
		EmitterData data;		//作成時に指定されたデータ
		int handle = -1;		//ハンドル（番号）
		DWORD frameCount = 0;	//開始してからのフレーム数
		BillBoard* pBillBoard = nullptr;	//パーティクルに使うポリゴン
		bool isDead = false;	//削除対象かどうか（実際はパーティクルが全部消えるまでエミッターは消えない）
		int particleNum = 0;	//このエミッターから出た現存パーティクルの数
	};


	//パーティクルの変化するデータ
	struct Data
	{
		XMFLOAT3 position;	//位置
		XMFLOAT2 scale;		//サイズ
		XMFLOAT4 color;		//色
		float    Angle;     //軸の角度
	};

	//パーティクル1粒のデータ
	struct ParticleData
	{
		Data now;			//現在の情報
		Data delta;			//1フレームの変化量
		DWORD life;			//残り寿命
		float accel;		//加速度
		float gravity;		//重力
		Emitter* pEmitter;	//発生元
	};


	std::list<Emitter*>			emitterList_;	//エミッター達
	std::list<ParticleData*>	particleList_;	//パーティクル達


	//発生中のパーティクルを更新
	void ParticleUpdate();

	//エミッタの更新（タイミング次第でパーティクルを発生させる）
	void EmitterUpdate();

public:
	//コンストラクタ
	Particle(GameObject* parent);

	//デストラクタ
	~Particle();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//開放
	void StartUpdate() override {};


	//エミッタを作成（エフェクト開始）
	//引数：emitterData	各種情報
	//戻値：エフェクト（エミッタ）の番号
	int Start(EmitterData emitterData);

	//エミッタを削除（エフェクト終了）
	//引数：handle	エフェクトの番号
	void End(int handle);
};

