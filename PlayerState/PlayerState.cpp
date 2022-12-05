#include "PlayerState.h"
#include "../Engine/GameManager.h"
#include "../Engine/Model.h"

//各static変数の初期化
JumpingState* PlayerState::jumping_ = new JumpingState;
JumpRotationningState* PlayerState::jumpRotationning_ = new JumpRotationningState;
RotationningState* PlayerState::rotationning_ = new RotationningState;
RunningState* PlayerState::running_ = new RunningState;
StandingState* PlayerState::standing_ = new StandingState;
WalkingState* PlayerState::walking_ = new WalkingState;
State* PlayerState::state_ = standing_;


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
        state_ == PlayerState::standing_ ? Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), true)
                                         : Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), false);

        //ジャンプ回転をしていないなら
        if (state_ != PlayerState::jumpRotationning_ && state_ != PlayerState::rotationning_)
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
                Model::SetAnimSpeed(GameManager::GetpPlayer()->GetPlayerhModel(), ANIM_SPEED);


            //ジャンプ回転をしているかによってPlayerの動く方向を決め,Player移動
            if (state_ != PlayerState::jumpRotationning_ && state_ != PlayerState::rotationning_)
                GameManager::GetpPlayer()->SetPosition(Transform::Float3Add(GameManager::GetpPlayer()->GetPosition(), Transform::VectorToFloat3(XMVector3TransformCoord(front_ / 10, GameManager::GetpPlayer()->GetmmRotate()))));
            else
                GameManager::GetpPlayer()->SetPosition(Transform::Float3Add(GameManager::GetpPlayer()->GetPosition(), Transform::VectorToFloat3(XMVector3TransformCoord(front_ / 10, GameManager::GetpPlayer()->GetmPreviousAngle()))));

            //Zのポジションだけ0にする
            GameManager::GetpPlayer()->SetPositionZ(ZERO);

            //前ベクトルの初期化
            ARGUMENT_INITIALIZE(front_, XMVector3Normalize(front_));

        }
    }
    else
        Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), false);

	//現在の状態の更新を呼ぶ
	state_->Update2D();
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
        state_ == PlayerState::standing_ ? Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), true)
                                         : Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), false);

        //ジャンプ回転をしていないなら
        if (state_ != PlayerState::jumpRotationning_ && state_ != PlayerState::rotationning_)
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
                Model::SetAnimSpeed(GameManager::GetpPlayer()->GetPlayerhModel(), ANIM_SPEED);


            //ジャンプ回転をしているかによってPlayerの動く方向を決め,Player移動
            if (state_ != PlayerState::jumpRotationning_ && state_ != PlayerState::rotationning_)
                GameManager::GetpPlayer()->SetPosition(Transform::Float3Add(GameManager::GetpPlayer()->GetPosition(), Transform::VectorToFloat3(XMVector3TransformCoord(front_ / 10, GameManager::GetpPlayer()->GetmmRotate()))));
            else
                GameManager::GetpPlayer()->SetPosition(Transform::Float3Add(GameManager::GetpPlayer()->GetPosition(), Transform::VectorToFloat3(XMVector3TransformCoord(front_ / 10, GameManager::GetpPlayer()->GetmPreviousAngle()))));

            //前ベクトルの初期化
            ARGUMENT_INITIALIZE(front_, XMVector3Normalize(front_));
        }
    }
    else
        Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), false);

    //現在の状態の更新を呼ぶ
    state_->Update3D();
}

//入力によって状態変化する
void PlayerState::HandleInput()
{
	//現在の状態の入力処理を呼ぶ
	state_->HandleInput();
}

//状態変化したとき一回だけ呼ばれる関数
void PlayerState::Enter()
{
	//現在の状態のEnter関数を呼ぶ
	state_->Enter();

}
