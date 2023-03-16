#include "DieState.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Player/PlayerBase.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Manager/MiniGameManager/MiniGameManager.h"
#include "../../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../../Engine/ResourceManager/Time.h"

//定数
namespace
{
    static const float PLAYER_ANIM_SPEED = 1.0f;  //アニメーションの再生速度
    static const float SCENE_CHANGE_TIME = 3.0f;  //シーン変更時間
}

//3D用更新
void DieState::Update3D(PlayerBase* player)
{
    //アニメーションが完全に死亡した状態なら
    if (130 == Model::GetAnimFrame(player->GethModel()))
    {
        //アニメーション停止
        Model::SetAnimFrame(player->GethModel(), 130, 130, ZERO);

        //フェードのステータスがGAME_OVER状態じゃないかつミニゲームシーンじゃないのなら
        if (Fade::GetFadeStatus() != FADE_GAME_OVER && GameManager::GetpSceneManager()->GetSceneId() != SCENE_ID_MINIGAME)
            Fade::SetFadeStatus(FADE_GAME_OVER);
        //フェードのステータスがCIRCLE_OUT状態じゃないかつミニゲームシーンなら
        else if(Fade::GetFadeStatus() != FADE_CIRCLE_OUT && GameManager::GetpSceneManager()->GetSceneId() == SCENE_ID_MINIGAME)
            Fade::SetFadeStatus(FADE_CIRCLE_OUT);

        //タイマースタート
        Time::UnLock(hTime_);
    }

    //定数秒以上経ったのなら
    if (Time::GetTimef(hTime_) > SCENE_CHANGE_TIME && GameManager::GetpSceneManager()->GetSceneId() == SCENE_ID_MINIGAME)
        GameManager::PlayerDie();
}

//状態変化したとき一回だけ呼ばれる関数
void DieState::Enter(PlayerBase* player)
{
    //ミニゲームの状態をEND状態にする
    if (GameManager::GetpSceneManager()->GetSceneId() == SCENE_ID_MINIGAME)
    {
        MiniGameManager::ChangeMiniGameStatus(MiniGameStatus::END);
        MiniGameManager::SetResultDis(player->GetPosition().z);
    }

    //タイマー番号
    hTime_ = Time::Add();

    //エフェクト
    PlayerEffectManager::DieEffect(player->GetPosition(), player->GetNormal());

    //アニメーション
    Model::SetAnimFrame(player->GethModel(), 70, 130, PLAYER_ANIM_SPEED);
    Model::SetAnimFlag(player->GethModel(), true);
}