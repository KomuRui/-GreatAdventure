#include "ButtonManager.h"
#include "../../UI/Button/ButtonBase.h"
#include "../../Engine/ResourceManager/Global.h"
#include "../AudioManager/OtherAudioManager/OtherAudioManager.h"
#include <vector>
#include<algorithm>


//定数
namespace
{
	static const float PAD_STICK_SLOPE_RIGHT = 0.8f;  //パッドのLスティックの右の傾き
	static const float PAD_STICK_SLOPE_LEFT  = -0.8f; //パッドのLスティックの左の傾き
	static const float PAD_STICK_SLOPE_UP    = 0.8f;  //パッドのLスティックの上の傾き
	static const float PAD_STICK_SLOPE_DOWN  = -0.8f; //パッドのLスティックの下の傾き
}


//画面に表示されているボタンを管理する
namespace ButtonManager
{

	//現在使われているボタンを格納する変数
	std::vector<ButtonBase*> nowUseButton;

	//XとYの前回入力保存用
	float beforeXSlope = ZERO;
	float beforeYSlope = ZERO;

	//XとYの現在の入力保存用
	float NowXSlope = ZERO;
	float NowYSlope = ZERO;

	//更新
	void Update()
	{
		//もしボタンが使われていなかったらこの先は処理しない
		if (nowUseButton.empty()) return;

		//選択されているボタン格納用
		ButtonBase* pButton = nullptr; 

		//最後まで回してnullptrのものは削除・選択されているボタンを見つける
		for (auto i = nowUseButton.begin(); i != nowUseButton.end();)
		{
			//nullptrだったら削除
			if ((*i) == nullptr)
				i = nowUseButton.erase(i);
			else
			{
				//選択されていたら格納
				if ((*i)->IsSelect()) pButton = (*i);

				//次に進める
				i++;
			}
		}

		//nullptrならここで処理終わり
		if (pButton == nullptr) return;

		//入力処理
		Input(pButton);
	}

	//入力
	void Input(ButtonBase* button)
	{
		//選択されているボタンのxとyを保存
		float x = button->GetPosition().x;
		float y = button->GetPosition().y;

		//前回の傾きを取得
		ARGUMENT_INITIALIZE(beforeXSlope, NowXSlope);
		ARGUMENT_INITIALIZE(beforeYSlope, NowYSlope);

		//PadLスティックの傾きを保存
		ARGUMENT_INITIALIZE(NowXSlope,Input::GetPadStickL().x);
		ARGUMENT_INITIALIZE(NowYSlope,Input::GetPadStickL().y);

		//保存用
		std::vector<std::pair<float, ButtonBase*>> date;

		//傾きが定数より大きければ
		if (NowXSlope >= PAD_STICK_SLOPE_RIGHT && beforeXSlope <= PAD_STICK_SLOPE_RIGHT)
		{

			for (auto i = nowUseButton.begin(); i != nowUseButton.end(); i++)
			{
				//Xの座標が選択されていたボタンをよりも大きければ
				if ((*i)->GetPosition().x > x)
				{
					date.push_back({ (*i)->GetPosition().x,(*i)});
				}
			}
		}

		//もし空じゃなければ
		if (!date.empty())
		{
			//音
			OtherAudioManager::ClickAudio();

			//選択されているボタンも追加
			date.push_back({ x,button });

			//ソート(昇順)
			sort(date.begin(), date.end());

			//選択解除
			button->SetSelect(false);

			//ボタン格納
			ARGUMENT_INITIALIZE(button, (*(date.begin() + 1)).second);

			//選択されるようにする
			button->SetSelect(true);

			return;
		}

		//傾きが定数より小さければ
		if (NowXSlope <= PAD_STICK_SLOPE_LEFT && beforeXSlope >= PAD_STICK_SLOPE_LEFT)
		{
			for (auto i = nowUseButton.begin(); i != nowUseButton.end(); i++)
			{
				//Xの座標が選択されていたボタンをよりも小さければ
				if ((*i)->GetPosition().x < x)
				{
					date.push_back({ (*i)->GetPosition().x,(*i) });
				}
			}
		}

		//もし空じゃなければ
		if (!date.empty())
		{
			//音
			OtherAudioManager::ClickAudio();

			//選択されているボタンも追加
			date.push_back({ x,button });

			//ソート(降順)
			sort(date.rbegin(), date.rend());

			//選択解除
			button->SetSelect(false);

			//ボタン格納
			ARGUMENT_INITIALIZE(button, (*(date.begin() + 1)).second);

			//選択されるようにする
			button->SetSelect(true);

			return;
		}

		//傾きが定数より大きければ
		if (NowYSlope >= PAD_STICK_SLOPE_UP && beforeYSlope <= PAD_STICK_SLOPE_UP)
		{
			for (auto i = nowUseButton.begin(); i != nowUseButton.end(); i++)
			{
				//Yの座標が選択されていたボタンをよりも大きければ
				if ((*i)->GetPosition().y > y)
				{
					date.push_back({ (*i)->GetPosition().y,(*i) });
				}
			}
		}

		//もし空じゃなければ
		if (!date.empty())
		{
			//音
			OtherAudioManager::ClickAudio();

			//選択されているボタンも追加
			date.push_back({ y,button });

			//ソート(昇順)
			sort(date.begin(), date.end());

			//選択解除
			button->SetSelect(false);

			//ボタン格納
			ARGUMENT_INITIALIZE(button, (*(date.begin() + 1)).second);

			//選択されるようにする
			button->SetSelect(true);

			return;
		}

		//傾きが定数より小さければ
		if (NowYSlope <= PAD_STICK_SLOPE_DOWN && beforeYSlope >= PAD_STICK_SLOPE_DOWN)
		{
			for (auto i = nowUseButton.begin(); i != nowUseButton.end(); i++)
			{
				//Xの座標が選択されていたボタンをよりも小さければ
				if ((*i)->GetPosition().y < y)
				{
					date.push_back({ (*i)->GetPosition().y,(*i) });
				}
			}
		}

		//もし空じゃなければ
		if (!date.empty())
		{
			//音
			OtherAudioManager::ClickAudio();

			//選択されているボタンも追加
			date.push_back({ y,button });

			//ソート(降順)
			sort(date.rbegin(), date.rend());

			//選択解除
			button->SetSelect(false);

			//ボタン格納
			ARGUMENT_INITIALIZE(button, (*(date.begin() + 1)).second);

			//選択されるようにする
			button->SetSelect(true);

			return;
		}
				
	}


	//ボタンを追加
	void AddButton(ButtonBase* button) 
	{	
		//ボタンがまだ１つも登録されていないのなら
		if (nowUseButton.empty()) button->SetSelect(true);

		//ボタンを追加
		nowUseButton.push_back(button);
	}

	//リセットする
	void Reset()
	{
		//空にする
		nowUseButton.clear();
	}
};