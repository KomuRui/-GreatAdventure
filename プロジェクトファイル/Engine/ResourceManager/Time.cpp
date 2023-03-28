#include "Time.h"
#include "Global.h"
#include <vector>

//変数
namespace
{
	//時間測定に必要な情報
	std::vector<int> CountFps_;	//現在のフレームレートを格納しておくもの
	int FPS_;		            //初期化時に最大フレームレートを格納しておく
	int LookAt_;	            //配列のどこを見るか

	//タイマーに必要な情報
	struct TimeInfo{
		double Seconds_ = ZERO; //どのくらいの秒数たったか
		bool Lock_ = true;		//現在の状態で固定するか
	};
	
	//現在使用されてるタイマーを全てまとめているもの
	std::vector<TimeInfo*> date;
	
}

//時間
namespace Time
{
	//初期化
	void Initialize(int FPS)
	{
		//各変数初期化
		ARGUMENT_INITIALIZE(FPS_, FPS);
		ARGUMENT_INITIALIZE(LookAt_, (int)ZERO);

		date.clear();           //念のための初期化
		CountFps_.clear();		//念のための初期化
		CountFps_.reserve(FPS);	//要素数を確保しておく

		//初期化
		while (CountFps_.size() != CountFps_.capacity())
		{
			CountFps_.push_back(FPS);
		}
	}

	//タイマー追加
	int Add()
	{
		//データ作成
		TimeInfo* pDate = new TimeInfo;
		ARGUMENT_INITIALIZE(pDate->Lock_,false);
		ARGUMENT_INITIALIZE(pDate->Seconds_,ZERO);

		//新たに追加
		date.push_back(pDate);
		return (int)date.size() - 1;
	}

	//更新
	void Update()
	{
		for (int i = 0; i < CountFps_.size(); i++)
		{
			//最大フレームレートを超えることはないので
			if (CountFps_.at(i) < FPS_)
				CountFps_.at(i)++;
		}

		LookAt_++;
		if (LookAt_ >= FPS_)
			LookAt_ -= FPS_;


		//現在のタイマーの数分だけ回す
		for (auto i = date.begin(); i != date.end(); i++)
		{
			//ロックされていないのなら
			if (!(*i)->Lock_)
			{
				float fps = CountFps_.at(LookAt_) * 0.98f;
				(*i)->Seconds_ += 1.0 / fps;
			}
		}

		//初期化
		ARGUMENT_INITIALIZE(CountFps_.at(LookAt_),ZERO);
	}

	//解放
	void AllRelease()
	{
		//削除
		for (auto i = date.begin(); i != date.end(); i++)
		{
			SAFE_DELETE((*i));
		}

		//空にする
		date.clear();
	}

	/// <summary>
	/// リセット(秒数0に)
	/// </summary>
	/// <param name="handle">ハンドル番号</param>
	void Reset(int handle){ ARGUMENT_INITIALIZE(date[handle]->Seconds_,ZERO);}

	/// <summary>
	/// ロック(タイマーストップ)
	/// </summary>
	/// <param name="handle">ハンドル番号</param>
	void Lock(int handle){ ARGUMENT_INITIALIZE(date[handle]->Lock_,true); }

	/// <summary>
	/// アンロック(タイマー開始)
	/// </summary>
	/// <param name="handle">ハンドル番号</param>
	void UnLock(int handle){ ARGUMENT_INITIALIZE(date[handle]->Lock_,false); }

	/// <summary>
	/// ロックしているかどうか
	/// </summary>
	/// <param name="handle">ハンドル番号</param>
	/// <returns>trueならロックしている</returns>
	bool isLock(int handle){ return date[handle]->Lock_; }

	//時間取得
	int GetTimei(int handle){ return (int)date[handle]->Seconds_;}
	float GetTimef(int handle){ return (float)date[handle]->Seconds_;}
	double GetTime(int handle){ return date[handle]->Seconds_;}
}