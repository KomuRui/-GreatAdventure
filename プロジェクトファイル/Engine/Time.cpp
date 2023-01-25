#include "Time.h"
#include "Global.h"
#include <vector>

//定数宣言
namespace
{
	//60進法
	const char HEX = 60;
}

//変数
namespace
{
	char Hours_;
	char Minuts_;
	double Seconds_;
	bool Lock_ = true;		    //現在の状態で固定するか
	std::vector<int> CountFps_;	//現在のフレームレートを格納しておくもの
	int FPS_;		            //初期化時に最大フレームレートを格納しておく
	int LookAt_;	            //配列のどこを見るか
}

namespace Time
{
	//初期化
	void Initialize(int FPS)
	{
		//各変数初期化
		ARGUMENT_INITIALIZE(Hours_, ZERO);
		ARGUMENT_INITIALIZE(Minuts_, ZERO);
		ARGUMENT_INITIALIZE(Seconds_, ZERO);
		ARGUMENT_INITIALIZE(FPS_, FPS);
		ARGUMENT_INITIALIZE(LookAt_, ZERO);

		CountFps_.clear();		//念のための初期化
		CountFps_.reserve(FPS);	//要素数を確保しておく

		while (CountFps_.size() != CountFps_.capacity())
		{
			CountFps_.push_back(FPS);
		}
	}

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

		//Lockされていたら更新しない
		if (!Lock_)
		{
			float fps = CountFps_.at(LookAt_) * 0.98f;
			Seconds_ += 1.0 / fps;
		}

		CountFps_.at(LookAt_) = 0;
	}

	void Reset()
	{
		Hours_ = 0;
		Minuts_ = 0;
		Seconds_ = 0;
	}

	void Lock()
	{
		Lock_ = true;
	}

	void UnLock()
	{
		Lock_ = false;
	}

	bool isLock()
	{
		return Lock_;
	}

	int GetTimei()
	{
		return (int)Seconds_;
	}
	float GetTimef()
	{
		return (float)Seconds_;
	}
	double GetTime()
	{
		return Seconds_;
	}
}