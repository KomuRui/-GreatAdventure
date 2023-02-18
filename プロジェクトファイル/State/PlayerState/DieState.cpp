#include "DieState.h"
#include "../../Engine/Model.h"
#include "../../Player/PlayerBase.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/Time.h"
#include "../../Manager/MiniGameManager/MiniGameManager.h"
#include "../../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"

//定数
namespace
{
    static const float PLAYER_ANIM_SPEED = 1.0f;  //アニメーションの再生速度
}

//3D用更新
void DieState::Update3D(PlayerBase* player)
{
    //アニメーションが完全に死亡した状態なら
    if (130 == Model::GetAnimFrame(player->GethModel()))
    {
        //アニメーション停止
        Model::SetAnimFrame(player->GethModel(), 130, 130, ZERO);

        //フェードのステータスがFADE_OUT状態じゃなかったら
        if (GameManager::GetStatus() != FADE_OUT)
            GameManager::SetStatus(FADE_OUT, "Image/Fade/BaseFade.png");
    }
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

    //エフェクト
    PlayerEffectManager::DieEffect(player->GetPosition(), player->GetNormal());

    //アニメーション
    Model::SetAnimFrame(player->GethModel(), 70, 130, PLAYER_ANIM_SPEED);
    Model::SetAnimFlag(player->GethModel(), true);
}