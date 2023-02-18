#include "PlayerStateManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Manager/MiniGameManager/MiniGameManager.h"
#include "../../Engine/Model.h"
#include "../../Player/PlayerBase.h"
#include "../../Engine/ImGuiSet.h"

//各static変数の初期化
JumpingState* PlayerStateManager::playerJumping_ = new JumpingState;
JumpRotationningState* PlayerStateManager::playerJumpRotationning_ = new JumpRotationningState;
RotationningState* PlayerStateManager::playerRotationning_ = new RotationningState;
RunningState* PlayerStateManager::playerRunning_ = new RunningState;
StandingState* PlayerStateManager::playerStanding_ = new StandingState;
WalkingState* PlayerStateManager::playerWalking_ = new WalkingState;
KnockBackState* PlayerStateManager::playerKnockBacking_ = new KnockBackState;
DieState* PlayerStateManager::playerDieing_ = new DieState;
PlayerState* PlayerStateManager::playerState_ = playerStanding_;

////定数
namespace
{
    const float RUN_SPEED = 1.5f;                 // GetPrivateProfilefloat("PLAYER", "RunSpeed", "0.02", ".\\/Parameter/Player/PlayerParameter.ini");//走っているときのキャラのスピード
    const float PLAYER_WALK_ANIM_SPEED = 1.0f;    //アニメーションの再生速度
    const float ANIM_RUN_SPEED = 2.0f;            //アニメーションの再生速度(走ってるとき)
}

//コンストラクタ
PlayerStateManager::PlayerStateManager():front_(XMVectorSet(0, 0, 1.0f, 0))
{
}

//更新
void PlayerStateManager::Update2D(PlayerBase* player)
{
    //////すべての状態に共通する処理をしておく

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;
    
    if (PadLx > ZERO || PadLx < ZERO)
    {
        //もしPlayerが何もしていないのならアニメーション開始
        playerState_ == PlayerStateManager::playerStanding_ ? Model::SetAnimFlag(player->GethModel(), true)
                                         : Model::SetAnimFlag(player->GethModel(), false);

        //ジャンプ回転をしていないなら
        if (!player->IsRotation())
        {
            //キャラの上軸の角度をコントローラーの角度に変換
            player->SetAngle(-atan2(PadLx, -padLy));
            player->SetJampRotationPreviousAngle(player->GetAngle());
        }
        else
            player->SetJampRotationPreviousAngle(-atan2(PadLx, padLy));


        //Playerの移動
        {

            //移動するときにLトリガーを押していたらダッシュをする
            if (Input::GetPadTrrigerL())
            {
                Model::SetAnimSpeed(player->GethModel(), ANIM_RUN_SPEED);
                front_ = XMVector3Normalize(front_) * RUN_SPEED;
            }
            else
                Model::SetAnimSpeed(player->GethModel(), PLAYER_WALK_ANIM_SPEED);


            //ジャンプ回転をしているかによってPlayerの動く方向を決め,Player移動
            if (!player->IsRotation())
                player->SetPosition(Float3Add(player->GetPosition(),VectorToFloat3(XMVector3TransformCoord(front_ / 10, player->GetmmRotate()))));
            else
                player->SetPosition(Float3Add(player->GetPosition(),VectorToFloat3(XMVector3TransformCoord(front_ / 10, player->GetmPreviousAngle()))));

            //Zのポジションだけ0にする
            player->SetPositionZ(ZERO);

            //前ベクトルの初期化
            ARGUMENT_INITIALIZE(front_, XMVector3Normalize(front_));

        }
    }
    else
        Model::SetAnimFlag(player->GethModel(), false);

	//現在の状態の更新を呼ぶ
	playerState_->Update2D(player);
}

//3D用更新
void PlayerStateManager::Update3D(PlayerBase* player)
{
    //もしノックバックの状態ならこの先は処理しない
    if (playerState_ == PlayerStateManager::playerKnockBacking_)
    {
        //現在の状態の更新を呼ぶ
        playerState_->Update3D(player);

        return;
    }

    //////すべての状態に共通する処理をしておく

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;

    //少しでも動いたなら
    if (PadLx > ZERO || padLy > ZERO || PadLx < ZERO || padLy < ZERO)
    {
        //もしPlayerが何もしていないのならアニメーション開始
        playerState_ == PlayerStateManager::playerStanding_ ? Model::SetAnimFlag(player->GethModel(), true)
                                         : Model::SetAnimFlag(player->GethModel(), false);

        //ジャンプ回転をしていないなら
        if (!player->IsRotation())
        {
            //キャラの上軸の角度をコントローラーの角度に変換
            player->SetAngle(atan2(PadLx, padLy) + player->GetCamAngle());
            player->SetJampRotationPreviousAngle(player->GetAngle());
        }
        else
            player->SetJampRotationPreviousAngle(atan2(PadLx, padLy) + player->GetCamAngle());


        //Playerの移動
        {

            //移動するときにLトリガーを押していたらダッシュをする
            if (Input::GetPadTrrigerL())
            {
                Model::SetAnimSpeed(player->GethModel(), ANIM_RUN_SPEED);
                front_ = XMVector3Normalize(front_) * RUN_SPEED;
            }
            else
                Model::SetAnimSpeed(player->GethModel(), PLAYER_WALK_ANIM_SPEED);


            //ジャンプ回転をしているかによってPlayerの動く方向を決め,Player移動
            if (!player->IsRotation())
                player->SetPosition(Float3Add(player->GetPosition(),VectorToFloat3(XMVector3TransformCoord(front_ / 10, player->GetmmRotate()))));
            else
                player->SetPosition(Float3Add(player->GetPosition(),VectorToFloat3(XMVector3TransformCoord(front_ / 10, player->GetmPreviousAngle()))));

            //前ベクトルの初期化
            ARGUMENT_INITIALIZE(front_, XMVector3Normalize(front_));
        }
    }
    else
        Model::SetAnimFlag(player->GethModel(), false);

    //現在の状態の更新を呼ぶ
    playerState_->Update3D(player);
}

//ミニゲーム用更新
void PlayerStateManager::UpdateMiniGame(PlayerBase* player)
{

    //死亡状態じゃないのなら
    if (PlayerStateManager::playerState_ != PlayerStateManager::playerDieing_)
    {

        //////すべての状態に共通する処理をしておく

        float PadLx = Input::GetPadStickL().x;
        float padLy = Input::GetPadStickL().y;

        //コントローラーのX軸を少しでも動かしているかどうか
        bool xFlag = false;

        //もしPlayerが何もしていないのならアニメーション開始
        playerState_ == PlayerStateManager::playerStanding_ ? Model::SetAnimFlag(player->GethModel(), true)
            : Model::SetAnimFlag(player->GethModel(), false);

        //回転をしていないなら
        if (!player->IsRotation())
        {
            //キャラの上軸の角度をコントローラーの角度に変換

            if (PadLx > ZERO || PadLx < ZERO)
            {
                ARGUMENT_INITIALIZE(xFlag, true);

                player->SetAngle(atan2(PadLx, 1));
                player->SetJampRotationPreviousAngle(player->GetAngle());
            }
            else
            {
                player->SetAngle(atan2(ZERO, 1));
                player->SetJampRotationPreviousAngle(player->GetAngle());
            }
        }
        else
        {
            //キャラの上軸の角度をコントローラーの角度に変換

            if (PadLx > ZERO || PadLx < ZERO)
            {
                ARGUMENT_INITIALIZE(xFlag, true);

                player->SetJampRotationPreviousAngle(atan2(PadLx, 1));
            }
            else
                player->SetJampRotationPreviousAngle(atan2(ZERO, 1));

        }


        //Playerの移動
        {

            Model::SetAnimSpeed(player->GethModel(), ANIM_RUN_SPEED);

            if (xFlag)
                front_ = XMVector3Normalize(front_) * 5;
            else
                front_ = XMVector3Normalize(front_) * RUN_SPEED * MiniGameManager::GetRunSpeed();

            //回転をしているかによってPlayerの動く方向を決め,Player移動
            if (!player->IsRotation())
                player->SetPosition(Float3Add(player->GetPosition(), VectorToFloat3(XMVector3TransformCoord(front_ / 10, player->GetmmRotate()))));
            else
                player->SetPosition(Float3Add(player->GetPosition(), VectorToFloat3(XMVector3TransformCoord(front_ / 10, player->GetmPreviousAngle()))));

            //前ベクトルの初期化
            ARGUMENT_INITIALIZE(front_, XMVector3Normalize(front_));
        }
    }

    //現在の状態の更新を呼ぶ
    playerState_->Update3D(player);
}

//入力によって状態変化する
void PlayerStateManager::HandleInput(PlayerBase* player)
{
}

//状態変化したとき一回だけ呼ばれる関数
void PlayerStateManager::Enter(PlayerBase* player)
{
}

//状態チェンジ用
void PlayerStateManager::ChangeState(PlayerState* change, PlayerBase* player)
{
    PlayerStateManager::playerState_ = change;
    PlayerStateManager::playerState_->Enter(player);
}