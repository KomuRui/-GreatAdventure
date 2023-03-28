#include "Gauge.h"
#include "../ResourceManager/Image.h"

//コンストラクタ
Gauge::Gauge(GameObject* parent)
    :GameObject(parent, "Gauge"),
    hPict_{ -1,-1,-1,-1 },
    stopRatio_((float)nowHp_ / (float)maxHp_), moveRatio_(stopRatio_),

    nowHp_(1),      //初期HP 
    maxHp_(1),      //MaxHP
    speed_(0.002f)  //バーの移動速度
{
}

//デストラクタ
Gauge::~Gauge()
{
}

//初期化
void Gauge::Initialize()
{
    //画像ファイルロード
    //使用する画像ファイル名
    string fileName[] = { "Gauge_Frame", "Gauge_Green", "Gauge_LightGreen", "Gauge_Red" };

    //ロード
    for (int i = (int)ZERO; i < PICT_MAX; i++)
    {
        hPict_[i] = Image::Load("Image/Gauge/" + fileName[i] + ".png");
        assert(hPict_[i] >= ZERO);
    }
}

//更新
void Gauge::Update()
{
    //最大HPに対する、現在HPの割合
    ARGUMENT_INITIALIZE(stopRatio_,(float)nowHp_ / (float)maxHp_);

    //バーを動かす
    if (moveRatio_ < stopRatio_) moveRatio_ += speed_;
    if (moveRatio_ > stopRatio_) moveRatio_ -= speed_;

}

//描画
void Gauge::Draw()
{
    //画像表示用
    Transform gaugeTrans;

    //HP変化なし
    if (abs(moveRatio_ - stopRatio_) < speed_)
    {
        //緑ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[PICT_GREEN]);
    }


    //回復中
    else if (moveRatio_ < stopRatio_)
    {
        //黄緑ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[PICT_LGREEN], gaugeTrans);
        Image::Draw(hPict_[PICT_LGREEN]);

        //緑ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= moveRatio_;
        Image::SetTransform(hPict_[PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[PICT_GREEN]);
    }

    //ダメージ中
    else
    {
        //赤ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= moveRatio_;
        Image::SetTransform(hPict_[PICT_RED], gaugeTrans);
        Image::Draw(hPict_[PICT_RED]);

        //緑ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[PICT_GREEN]);
    }


    //枠
    gaugeTrans = transform_;
    Image::SetTransform(hPict_[PICT_FRAME], gaugeTrans);
    Image::Draw(hPict_[PICT_FRAME]);
}


//開放
void Gauge::Release()
{
}

//ダメージ
void Gauge::Damage(int value)
{
    nowHp_ -= value;
    if (nowHp_ < ZERO) nowHp_ = (int)ZERO;
}

//回復
void Gauge::Recovery(int value)
{
    nowHp_ += value;
    if (nowHp_ > maxHp_) nowHp_ = maxHp_;
}
