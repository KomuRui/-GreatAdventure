#pragma once
#include "../GameObject/GameObject.h"

//体力ゲージを管理するクラス
class Gauge : public GameObject
{
    int nowHp_; //現在のＨＰ
    int maxHp_; //最大ＨＰ

    float stopRatio_;       //最大HPに対する固定されたゲージの割合
    float moveRatio_;       //最大HPに対する変化してるゲージの割合
    float speed_;           //変化する時のゲージスピード

    //使用する画像の種類
    enum
    {
        PICT_FRAME,
        PICT_GREEN,
        PICT_LGREEN,
        PICT_RED,
        PICT_MAX
    };

    //画像番号
    int hPict_[PICT_MAX];

public:
    //コンストラクタ
    Gauge(GameObject* parent);

    //デストラクタ
    ~Gauge();

    //初期化
    void Initialize() override;

   //更新の前に一回呼ばれる関数
    void StartUpdate() override {};

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    /// <summary>
    /// ダメージを受ける
    /// </summary>
    /// <param name="value">ダメージ量</param>
    void Damage(int value);

    /// <summary>
    /// 回復
    /// </summary>
    /// <param name="value">回復量</param>
    void Recovery(int value);

    /// <summary>
    /// MaxHPをセット
    /// </summary>
    /// <param name="value">MaxHp</param>
    void SetMaxHp(int value) { maxHp_ = value; }

    /// <summary>
    /// 現在のHpをセット
    /// </summary>
    /// <param name="value">現在のHp</param>
    void SetNowHp(int value) { nowHp_ = value; }
};