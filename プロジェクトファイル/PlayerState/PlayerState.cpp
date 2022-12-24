#include "PlayerState.h"
#include "../Engine/GameManager.h"
#include "../Engine/Model.h"

//各static変数の初期化
JumpingState* PlayerState::playerJumping_ = new JumpingState;
JumpRotationningState* PlayerState::playerJumpRotationning_ = new JumpRotationningState;
RotationningState* PlayerState::playerRotationning_ = new RotationningState;
RunningState* PlayerState::playerRunning_ = new RunningState;
StandingState* PlayerState::playerStanding_ = new StandingState;
WalkingState* PlayerState::playerWalking_ = new WalkingState;
State* PlayerState::playerState_ = playerStanding_;

////定数
namespace
{
    const float RUN_SPEED = 1.5f;                 // GetPrivateProfilefloat("PLAYER", "RunSpeed", "0.02", ".\\/Parameter/Player/PlayerParameter.ini");//走っているときのキャラのスピード
    const float PLAYER_WALK_ANIM_SPEED = 1.0f;    //アニメーションの再生速度
    const float ANIM_RUN_SPEED = 2.0f;            //アニメーションの再生速度(走ってるとき)
}

//コンストラクタ
PlayerState::PlayerState():front_(XMVectorSet(0, 0, 1.0f, 0))
{
}

//更新
void PlayerState::Update2D()
{
    //////すべての状態に共通する処理をしておく

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;
    
    if (PadLx > ZERO || PadLx < ZERO)
    {
        //もしPlayerが何もしていないのならアニメーション開始
        playerState_ == PlayerState::playerStanding_ ? Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), true)
                                         : Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), false);

        //ジャンプ回転をしていないなら
        if (playerState_ != PlayerState::playerJumpRotationning_ && playerState_ != PlayerState::playerRotationning_)
        {
            //キャラの上軸の角度をコントローラーの角度に変換
            GameManager::GetpPlayer()->SetAngle(-atan2(PadLx, -padLy));
            GameManager::GetpPlayer()->SetJampRotationPreviousAngle(GameManager::GetpPlayer()->GetAngle());
        }
        else
            GameManager::GetpPlayer()->SetJampRotationPreviousAngle(-atan2(PadLx, padLy));


        //Playerの移動
        {

            //移動するときにLトリガーを押していたらダッシュをする
            if (Input::GetPadTrrigerL())
            {
                Model::SetAnimSpeed(GameManager::GetpPlayer()->GetPlayerhModel(), ANIM_RUN_SPEED);
                front_ = XMVector3Normalize(front_) * RUN_SPEED;
            }
            else
                Model::SetAnimSpeed(GameManager::GetpPlayer()->GetPlayerhModel(), PLAYER_WALK_ANIM_SPEED);


            //ジャンプ回転をしているかによってPlayerの動く方向を決め,Player移動
            if (playerState_ != PlayerState::playerJumpRotationning_ && playerState_ != PlayerState::playerRotationning_)
                GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(),VectorToFloat3(XMVector3TransformCoord(front_ / 10, GameManager::GetpPlayer()->GetmmRotate()))));
            else
                GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(),VectorToFloat3(XMVector3TransformCoord(front_ / 10, GameManager::GetpPlayer()->GetmPreviousAngle()))));

            //Zのポジションだけ0にする
            GameManager::GetpPlayer()->SetPositionZ(ZERO);

            //前ベクトルの初期化
            ARGUMENT_INITIALIZE(front_, XMVector3Normalize(front_));

        }
    }
    else
        Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), false);

	//現在の状態の更新を呼ぶ
	playerState_->Update2D();
}

//3D用更新
void PlayerState::Update3D()
{
    //////すべての状態に共通する処理をしておく

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;

    //少しでも動いたなら
    if (PadLx > ZERO || padLy > ZERO || PadLx < ZERO || padLy < ZERO)
    {
        //もしPlayerが何もしていないのならアニメーション開始
        playerState_ == PlayerState::playerStanding_ ? Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), true)
                                         : Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), false);

        //ジャンプ回転をしていないなら
        if (playerState_ != PlayerState::playerJumpRotationning_ && playerState_ != PlayerState::playerRotationning_)
        {
            //キャラの上軸の角度をコントローラーの角度に変換
            GameManager::GetpPlayer()->SetAngle(atan2(PadLx, padLy) + GameManager::GetpPlayer()->GetCamAngle());
            GameManager::GetpPlayer()->SetJampRotationPreviousAngle(GameManager::GetpPlayer()->GetAngle());
        }
        else
            GameManager::GetpPlayer()->SetJampRotationPreviousAngle(atan2(PadLx, padLy) + GameManager::GetpPlayer()->GetCamAngle());


        //Playerの移動
        {

            //移動するときにLトリガーを押していたらダッシュをする
            if (Input::GetPadTrrigerL())
            {
                Model::SetAnimSpeed(GameManager::GetpPlayer()->GetPlayerhModel(), ANIM_RUN_SPEED);
                front_ = XMVector3Normalize(front_) * RUN_SPEED;
            }
            else
                Model::SetAnimSpeed(GameManager::GetpPlayer()->GetPlayerhModel(), PLAYER_WALK_ANIM_SPEED);


            //ジャンプ回転をしているかによってPlayerの動く方向を決め,Player移動
            if (playerState_ != PlayerState::playerJumpRotationning_ && playerState_ != PlayerState::playerRotationning_)
                GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(),VectorToFloat3(XMVector3TransformCoord(front_ / 10, GameManager::GetpPlayer()->GetmmRotate()))));
            else
                GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(),VectorToFloat3(XMVector3TransformCoord(front_ / 10, GameManager::GetpPlayer()->GetmPreviousAngle()))));

            //前ベクトルの初期化
            ARGUMENT_INITIALIZE(front_, XMVector3Normalize(front_));
        }
    }
    else
        Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), false);

    //現在の状態の更新を呼ぶ
    playerState_->Update3D();
}

//入力によって状態変化する
void PlayerState::HandleInput()
{
}

//状態変化したとき一回だけ呼ばれる関数
void PlayerState::Enter()
{
}
