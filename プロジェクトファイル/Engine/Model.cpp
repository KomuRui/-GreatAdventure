#include "Global.h"
#include "Model.h"

//3Dモデル（FBXファイル）を管理する
namespace Model
{
	//ロード済みのモデルデータ一覧
	std::vector<ModelData*>	_datas;

	//初期化
	void Initialize()
	{
		AllRelease();
	}

	//モデルをロード
	int Load(std::string fileName)
	{
			ModelData* pData = new ModelData;


			//開いたファイル一覧から同じファイル名のものが無いか探す
			bool isExist = false;
			for (int i = 0; i < _datas.size(); i++)
			{
				//すでに開いている場合
				if (_datas[i] != nullptr && _datas[i]->fileName == fileName)
				{
					pData->pFbx = _datas[i]->pFbx;
					isExist = true;
					break;
				}
			}

			//新たにファイルを開く
			if (isExist == false)
			{
				pData->pFbx = new Fbx;
				if (FAILED(pData->pFbx->Load(fileName)))
				{
					//開けなかった
					SAFE_DELETE(pData->pFbx);
					SAFE_DELETE(pData);
					return -1;
				}

				//無事開けた
				pData->fileName = fileName;
			}


			//使ってない番号が無いか探す
			for (int i = 0; i < _datas.size(); i++)
			{
				if (_datas[i] == nullptr)
				{
					_datas[i] = pData;
					return i;
				}
			}

			//新たに追加
			_datas.push_back(pData);
			return (int)_datas.size() - 1;
	}



	//描画
	void Draw(int handle)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		if (_datas[handle]->animFlag)
			//アニメーションを進める
			_datas[handle]->nowFrame += _datas[handle]->animSpeed;
		else
		{
			_datas[handle]->nowFrame = 0;
		}

		//最後までアニメーションしたら戻す
		if (_datas[handle]->nowFrame > (float)_datas[handle]->endFrame)
			_datas[handle]->nowFrame = (float)_datas[handle]->startFrame;



		if (_datas[handle]->pFbx)
		{
			_datas[handle]->pFbx->Draw(_datas[handle]->transform, (int)_datas[handle]->nowFrame, _datas[handle]->alpha, _datas[handle]->ambient,_datas[handle]->speculer, _datas[handle]->brightness);
		}
	}

	void SetAlpha(int handle, float Alpha)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->alpha = Alpha;
		
	}

	void SetAmbient(int handle, float ambt)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->ambient = ambt;
	}

	void SetSpeculer(int handle, XMFLOAT4 Speculer)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->speculer = Speculer;
	}

	void SetBrightness(int handle, float Brightness)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->brightness = Brightness;
	}

	void SetRayFlag(int handle, bool flag)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->rayFlag = flag;
	}

	void SetBlockObj(int handle, Block* block)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->pBlock = block;
	}

	//任意のモデルを開放
	void Release(int handle)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		//同じモデルを他でも使っていないか
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//すでに開いている場合
			if (_datas[i] != nullptr && i != handle && _datas[i]->pFbx == _datas[handle]->pFbx)
			{
				isExist = true;
				break;
			}
		}

		//使ってなければモデル解放
		if (isExist == false )
		{
			SAFE_DELETE(_datas[handle]->pFbx);
		}


		SAFE_DELETE(_datas[handle]);
	}


	//全てのモデルを解放
	void AllRelease()
	{
		for (int i = 0; i < _datas.size(); i++)
		{
			if (_datas[i] != nullptr)
			{
				Release(i);
			}
		}
		_datas.clear();
	}


	//アニメーションのフレーム数をセット
	void SetAnimFrame(int handle, int startFrame, int endFrame, float animSpeed)
	{
		_datas[handle]->SetAnimFrame(startFrame, endFrame, animSpeed);
	}

	void SetAnimFlag(int handle,bool flag)
	{
		_datas[handle]->animFlag = flag;
	}

	void SetAnimSpeed(int handle, int speed)
	{
		_datas[handle]->animSpeed = speed;
	}

	//現在のアニメーションのフレームを取得
	int GetAnimFrame(int handle)
	{
		return (int)_datas[handle]->nowFrame;
	}


	//任意のボーンの位置を取得
	XMFLOAT3 GetBonePosition(int handle, std::string boneName)
	{
		XMFLOAT3 pos = _datas[handle]->pFbx->GetBonePosition(boneName);
		XMVECTOR vec = XMVector3TransformCoord(XMLoadFloat3(&pos), _datas[handle]->transform.GetWorldMatrix());
		XMStoreFloat3(&pos, vec);
		return pos;
	}


	//ワールド行列を設定
	void SetTransform(int handle, Transform & transform)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		_datas[handle]->transform = transform;
	}


	//ワールド行列の取得
	XMMATRIX GetMatrix(int handle)
	{
		return _datas[handle]->transform.GetWorldMatrix();
	}


	//レイキャスト（レイを飛ばして当たり判定）
	void RayCast(int handle, RayCastData *data)
	{
			XMFLOAT3 target = Float3Add(data->start, data->dir);
			XMMATRIX matInv = XMMatrixInverse(nullptr, _datas[handle]->transform.GetWorldMatrix());
			XMVECTOR vecStart = XMVector3TransformCoord(XMLoadFloat3(&data->start), matInv);
			XMVECTOR vecTarget = XMVector3TransformCoord(XMLoadFloat3(&target), matInv);
			XMVECTOR vecDir = vecTarget - vecStart;

			XMStoreFloat3(&data->start, vecStart);
			XMStoreFloat3(&data->dir, vecDir);

			_datas[handle]->pFbx->RayCast(data); 
			matInv = _datas[handle]->transform.GetWorldMatrix();
			XMStoreFloat3(&data->pos, XMVector3TransformCoord(XMLoadFloat3(&data->pos), matInv));
	}

	//一番近いポリゴンの法線とポジションをRayCastDataに格納
	void NearPolyNormal(int handle, NearPolyData* data)
	{
		XMFLOAT3 target = data->start;
		XMMATRIX matInv = XMMatrixInverse(nullptr, _datas[handle]->transform.GetWorldMatrix());
		XMVECTOR vecStart = XMVector3TransformCoord(XMLoadFloat3(&data->start), matInv);
		XMVECTOR vecTarget = XMVector3TransformCoord(XMLoadFloat3(&target), matInv);
		XMVECTOR vecDir = vecTarget - vecStart;

		XMStoreFloat3(&data->start, vecStart);

		_datas[handle]->pFbx->NearPolyNormal(data);

		matInv = _datas[handle]->transform.GetWorldMatrix();
		XMStoreFloat3(&data->pos, XMVector3TransformCoord(XMLoadFloat3(&data->pos), matInv));
	}

	//レイキャスト(Blockもいれる)
	void AllRayCast(int handle, RayCastData* data)
	{
		auto ehandle = _datas.begin();
		XMFLOAT3 start = data->start;
		XMFLOAT3 dir = data->dir;
		float dist = 99999.0f;

		do
		{
			//レイをとばすモデルがレイの当たり判定をすると設定しているとき
			if ((*ehandle)->rayFlag)
			{

					XMFLOAT3 target = Float3Add(start, dir);
					XMMATRIX matInv = XMMatrixInverse(nullptr, (*ehandle)->transform.GetWorldMatrix());
					XMVECTOR vecStart = XMVector3TransformCoord(XMLoadFloat3(&start), matInv);
					XMVECTOR vecTarget = XMVector3TransformCoord(XMLoadFloat3(&target), matInv);
					XMVECTOR vecDir = XMVector3Normalize(vecTarget - vecStart);

					XMStoreFloat3(&data->start, vecStart);
					XMStoreFloat3(&data->dir, vecDir);

					(*ehandle)->pFbx->RayCast(data);

					if (data->hit)
					{
						if (dist > data->dist)
							dist = data->dist;

						data->start = start;
						matInv = (*ehandle)->transform.GetWorldMatrix();
						XMStoreFloat3(&data->pos, XMVector3TransformCoord(XMLoadFloat3(&data->pos), matInv));

						data->block = (*ehandle)->pBlock;
					}
			}

			ehandle++;
		} while (ehandle != _datas.end());

	}
}