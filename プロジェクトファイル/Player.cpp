#include "Player.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include <cmath>
#include "Engine/Light.h"
#include "Engine/BoxCollider.h"
#include "Engine/SphereCollider.h"
#include "Manager/GameManager/GameManager.h"
#include "Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "Block/Block.h"
#include <algorithm>
#include <iostream>

////定数
namespace
{
    //Playerのパラメータを保存してあるパス
    LPCTSTR parameterPath = "Parameter/Player/PlayerParameter.ini";

    ///////////////キャラの必要な情報///////////////////

    static const float NORMAL_INTERPOLATION_FACTOR = GetPrivateProfilefloat("PLAYER", "NormalFactor", "0.045", parameterPath); //法線を補間するときの補間係数
    static const float PLAYER_ANIM_SPEED = GetPrivateProfilefloat("PLAYER", "AnimSpeed", "1.0", parameterPath);                //アニメーションの再生速度
    static const int ANIM_START_FRAME = GetPrivateProfilefloat("PLAYER", "AnimStartFrame", "1", parameterPath);                //アニメーションの開始フレーム
    static const int ANIM_END_FRAME = GetPrivateProfilefloat("PLAYER", "AnimEndFrame", "60", parameterPath);			       //アニメーションの終了フレーム
    static const int MAX_NORMAL_RADIANS = GetPrivateProfilefloat("PLAYER", "MaxNormalRadians", "50", parameterPath);   	       //法線との最大角度			
    static const float PLAYER_MODEL_SIZE_X = 1.0f;  //PlayerのXのモデルサイズ
    static const float PLAYER_MODEL_SIZE_Y = 2.0f;  //PlayerのYのモデルサイズ
    static const float GRAVITY_ADDITION = 0.03f;    //重力の加算値

    ////////////////ライト///////////////////
    
    static const float LIGHT_POS_Z = GetPrivateProfilefloat("LIGHT", "LightZPos", "2", parameterPath);  //ライトのZのポジション

    ////////////////カメラ///////////////////

    static const float CAMERA_INTERPOLATION_FACTOR = GetPrivateProfilefloat("CAMERA", "CamFactor", "0.08", parameterPath);  //カメラの移動を補間するときの補間係数
    static const float CAM_POS_2D_Z = GetPrivateProfilefloat("CAMERA", "CamPos2DZ", "20", parameterPath);                   //2Dの時のカメラのZの位置
    static const float CAM_SHOULDER_ADD_VALUE = 0.5f; //ショルダーでカメラ操作する時の加算する値
    static const float CAM_STICR_ADD_VALUE = 0.03f;   //スティックRでカメラを操作するときの加算する値

    ////////////////コライダー///////////////////

    static const XMFLOAT3 COLLIDER_POS = { ZERO,ZERO,ZERO };  //コライダーの位置
    static const float    COLLIDER_SIZE = 1.0f;               //コライダーのサイズ
}

//コンストラクタ
Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), 

    ///////////////キャラの必要な情報///////////////////

    //モデル
    hModel_(-1),
    hGroundModel_(ZERO),

    //各方向ベクトル
    vNormal_(XMVectorSet(ZERO, -1, ZERO, ZERO)),
    up_(XMVectorSet(ZERO, 1, ZERO, ZERO)),
    down_(XMVectorSet(ZERO, -1, ZERO, ZERO)),
    front_(XMVectorSet(ZERO, ZERO, 1, ZERO)),

    //キャラの軸回転に必要な変数
    totalMx_(XMMatrixIdentity()),
    jampRotationPreviousAngle_(ZERO),
    angle_(ZERO),
    normalFlag_(true),

    //ジャンプ
    vJamp_(XMVectorSet(ZERO, ZERO, ZERO, ZERO)),

    //その他
    acceleration_(1),
    pState_(new PlayerStateManager),
    beforePos_(ZERO, ZERO, ZERO),

    ///////////////////カメラ///////////////////////

    camMat_(XMMatrixIdentity()),
    camStatus_(LONG),
    camAngle_(1),
    camPosFlag_(true),
    camFlag_(true)
    
{
    camVec_[LONG] = XMVectorSet(ZERO, 15, -15, ZERO);
    camVec_[SHORT] = XMVectorSet(ZERO, 4, -4, ZERO);
}

/////////////////////オーバーライドする関数//////////////////////

//初期化
void Player::Initialize()
{
    ///////////////Playerの状態初期化///////////////////

    PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;

	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load("Star_Main_Character.fbx");
	assert(hModel_ >= ZERO);

    ///////////////Playerは元々あるTransform.Rotateを使わないためFlagをTrueにする///////////////////

    transform_.mFlag_ = true;

    ///////////////Playerの当たり判定設定///////////////////

    SphereCollider* collision = new SphereCollider(COLLIDER_POS, COLLIDER_SIZE);
    AddCollider(collision);

    ///////////////エフェクトとアニメーション設定///////////////////

    //エフェクト出すために必要
    PlayerEffectManager::Initialize(this);

    //アニメーション
    Model::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, PLAYER_ANIM_SPEED);

    ///////////////Stageのデータ取得///////////////////

    //モデル番号取得
    pstage_ = GameManager::GetpStage();
    hGroundModel_ = pstage_->GethModel();

    //自身のポジションセット
    transform_.position_ = pstage_->GetPos();

    //レイを飛ばして自身の軸を設定する
    RayCastData dataNormal;
    dataNormal.start = transform_.position_;      
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, down_);
    dataNormal.dir = moveY2;
    Model::RayCast(hGroundModel_, &dataNormal);   

    //自身の上軸設定
    vNormal_ = XMLoadFloat3(&dataNormal.normal);

}

//更新の前に一回呼ばれる関数
void Player::StartUpdate()
{
}

//更新
void Player::Update()
{
    //ステージ情報がnullならこの先は実行しない
    if (pstage_ == nullptr) return;

    //真下の法線を調べる
    CheckUnderNormal();

    //ステージが3Dなら
    if (pstage_->GetthreeDflag())
    {
        MovingOperation();       //Player操作
        RotationInStage();       //ステージに合わせて回転
        StageRayCast();          //ステージとの当たり判定
    }
    //ステージが疑似2Dなら
    else
    {
        MovingOperation2D();     //Player操作
        RotationInStage2D();     //ステージに合わせて回転
        StageRayCast2D();        //ステージとの当たり判定
    }

    //カメラの挙動
    CameraBehavior();
} 

//描画
void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Player::Release()
{
}

/////////////////////関数//////////////////////

//カメラの処理
void Player::CameraBehavior()
{
    static XMFLOAT3 camTar = transform_.position_;
    static XMFLOAT3 campos = transform_.position_;

    //カメラ動作をするかしないかFlagがfalseならこの先処理しない
    if (!camFlag_)
    {
        //カメラのポジションをyだけPlayerと同じにする(同じ高さで計算したいため)
        XMFLOAT3 camPos = Camera::GetPosition();
        camPos.y = transform_.position_.y;
        
        //カメラからPlayerへの方向ベクトル
        XMVECTOR dir = XMLoadFloat3(&transform_.position_) - XMLoadFloat3(&camPos);

        //角度求める
        float dotX = acos(XMVectorGetX(XMVector3Dot(XMVector3Normalize(dir), front_)));

        //求めた角度分軸を回転
        transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, dotX);

        //Playerが回転しているなら
        if (IsRotation()) mPreviousAngle_ *= XMMatrixRotationAxis(vNormal_, dotX);

        ARGUMENT_INITIALIZE(camAngle_, ZERO);
        ARGUMENT_INITIALIZE(campos, Camera::GetPosition());
        ARGUMENT_INITIALIZE(camTar, Camera::GetTarget());

        //ライト設定
        XMFLOAT3 lightPos;
        XMStoreFloat3(&lightPos, vNormal_ + XMLoadFloat3(&transform_.position_));
        Light::SetPlayerPosition(XMFLOAT4(lightPos.x, lightPos.y, lightPos.z, ZERO));

        return;
    }

    if (pstage_->GetthreeDflag())
    {
        XMFLOAT3 camPos;                                         //最終的なカメラの位置を入れる変数
        XMVECTOR vPos = XMLoadFloat3(&transform_.position_);     //transform_.position_のVector型
        XMVECTOR vCam = camVec_[camStatus_];                     //Playerからカメラのベクトルを作成
        vCam = XMVector3TransformCoord(vCam, camMat_);            //vCamを回す
        vCam = XMVector3TransformCoord(vCam, XMMatrixRotationAxis(vNormal_, camAngle_));

        vPos += vCam;                    //PlayerのPosにPlayerからカメラのベクトルをたす
        XMStoreFloat3(&camPos, vPos);    //camPosにvPosをXMFLOAT3に変えていれる

        //カメラの上方向を求めるためにStagePotisionを引いて上方向のベクトルを作成
        XMFLOAT3 UpDirection = { XMVectorGetX(-vNormal_), XMVectorGetY(-vNormal_), XMVectorGetZ(-vNormal_) };

        XMStoreFloat3(&camTar, XMVectorLerp(XMLoadFloat3(&camTar), XMLoadFloat3(&transform_.position_), CAMERA_INTERPOLATION_FACTOR));

        //flagがtrueなら位置動かす
        if (camPosFlag_)
            XMStoreFloat3(&campos, XMVectorLerp(XMLoadFloat3(&campos), XMLoadFloat3(&camPos), CAMERA_INTERPOLATION_FACTOR));

        //カメラのいろいろ設定
        Camera::SetUpDirection(vNormal_);
        Camera::SetPosition(campos);
        Camera::SetTarget(camTar);

        //ライト設定
        XMFLOAT3 lightPos;
        XMStoreFloat3(&lightPos, vNormal_ + XMLoadFloat3(&transform_.position_));

        Light::SetPlayerPosition(XMFLOAT4(lightPos.x, lightPos.y, lightPos.z, ZERO));
    }
    else
    {

        XMFLOAT3 camTar2 = { transform_.position_.x,transform_.position_.y,transform_.position_.z };
        XMFLOAT3 camPos2 = { transform_.position_.x, transform_.position_.y, CAM_POS_2D_Z };

        //flagがtrueなら位置動かす
        if (camPosFlag_)
            XMStoreFloat3(&campos, XMVectorLerp(XMLoadFloat3(&campos), XMLoadFloat3(&camPos2), CAMERA_INTERPOLATION_FACTOR));

        XMStoreFloat3(&camTar, XMVectorLerp(XMLoadFloat3(&camTar), XMLoadFloat3(&camTar2), CAMERA_INTERPOLATION_FACTOR));

        //カメラのいろいろ設定
        Camera::SetPosition(campos);
        Camera::SetTarget(camTar);

        //Playerについてるライトの位置調整
        Light::SetPlayerPosition(XMFLOAT4(transform_.position_.x, transform_.position_.y, LIGHT_POS_Z, ZERO));
    }

}

//真下の法線を調べる
void Player::CheckUnderNormal()
{
    //レイを真下に打つ
    RayCastData data;
    data.start = transform_.position_;
    data.dir = VectorToFloat3(down_);
    Model::AllRayCast(hGroundModel_, &data);

    //法線を調べるかどうかのFlagがtrueなら
    if (normalFlag_)
    {
        //レイが当たっていてかつ少しでも上ベクトルとvNormal_の値が違うのなら
        if (data.hit && (XMVectorGetX(vNormal_) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetY(-vNormal_) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetZ(-vNormal_) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&data.normal)))))
        {
            //元のキャラの上ベクトルvNormalと下の法線の内積を求める
            float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&data.normal)), XMVector3Normalize(vNormal_)));

            //角度が50度以内に収まっていたら(壁とかに上らせないため)
            if (acos(dotX) < XMConvertToRadians(MAX_NORMAL_RADIANS) && acos(dotX) > XMConvertToRadians(-MAX_NORMAL_RADIANS))
            {
                //ちょっと補間
                vNormal_ = XMVector3Normalize((XMVectorLerp( XMVector3Normalize(vNormal_), XMLoadFloat3(&data.normal), NORMAL_INTERPOLATION_FACTOR)));
                down_ = -vNormal_;
            }

        }
    }
}

//ステージに合わせてPlayerを回転(3D用)
void Player::RotationInStage()
{
    //Xのベクトルを抜き取る
    float dotX = ZERO;

    //自キャラまでのベクトルと自キャラの真上のベクトルが少しでも違うなら
    if (XMVectorGetX(up_) != XMVectorGetX(vNormal_) || XMVectorGetY(up_) != XMVectorGetY(vNormal_) || XMVectorGetZ(up_) != XMVectorGetZ(vNormal_))
    {
        //自キャラまでのベクトルと自キャラの真上のベクトルの内積を求める
        dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(up_), XMVector3Normalize(vNormal_)));
    }

    //外積を求める(この結果の軸を横軸にする)
    XMVECTOR cross = XMVector3Cross(up_, vNormal_);

    //エラーの範囲内ではなければ
    if (dotX != ZERO && dotX <= 1 && dotX >= -1)
    {
        //Playerを回転させるために二つの軸で回転させる
        totalMx_ *= XMMatrixRotationAxis(cross, acos(dotX));
        transform_.mmRotate_ = totalMx_;
        transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);

        //Playerが回転しているなら
        if (IsRotation()) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(cross, acos(dotX))) * XMMatrixRotationAxis(vNormal_, jampRotationPreviousAngle_);

        //カメラの行列用意
        camMat_ = totalMx_;
    }
    else
    {
        //Playerを回転させるために軸で回転させる
        transform_.mmRotate_ = totalMx_;
        transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);

        //Playerが回転しているなら
        if (IsRotation()) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(vNormal_, jampRotationPreviousAngle_));
    }

    //自身の上ベクトル更新
    up_ = vNormal_;
}

//ステージに合わせてPlayerを回転(2D用)
void Player::RotationInStage2D()
{
    //Playerの向きの角度分軸ベクトルを回転させる
    transform_.mmRotate_ = XMMatrixRotationAxis(UP_VECTOR, angle_);

    //Playerが回転しているなら
    if (IsRotation()) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(UP_VECTOR, jampRotationPreviousAngle_));
}

//プレイヤー操作(3D用)
void Player::MovingOperation()
{
    //移動する前のポジションを格納
    ARGUMENT_INITIALIZE(beforePos_, transform_.position_);

    //今の状態の動き
    pState_->Update3D(this);

    //Bを押したらカメラの位置変更
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
    {
        //カメラの状態変更
        camStatus_ = (camStatus_ == LONG) ? SHORT
                                          : LONG;
    }

    //左ショルダーを押したら角度変更
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_LEFT_SHOULDER)) camAngle_ += CAM_SHOULDER_ADD_VALUE;
    
    //右ショルダーを押したら角度変更
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_RIGHT_SHOULDER)) camAngle_ -= CAM_SHOULDER_ADD_VALUE;

    //右スティックでカメラの角度かえる
    if (Input::GetPadStickR().x) camAngle_ += CAM_STICR_ADD_VALUE * Input::GetPadStickR().x;
}

//プレイヤー操作(2D用)
void Player::MovingOperation2D()
{
    //今の状態の動き
    pState_->Update2D(this);
}

//レイ(3D用)
void Player::StageRayCast()
{

     //各方向
    RayCastData rightData;
    RayCastData leftData;
    RayCastData straightData;
    RayCastData upData;
    RayCastData downData;

    //当たってるか確認
    HitTest(&rightData, RIGHT_VECTOR);
    HitTest(&leftData, LEFT_VECTOR);
    HitTest(&straightData, STRAIGHT_VECTOR);
    HitTest(&upData, UP_VECTOR);
    HitTest(&downData, DOWN_VECTOR);

    ////////////////////////////////はみ出した分下げる//////////////////////////////////////

    //先にベクトル型のポジションを作っておく
    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    //右
    if (rightData.dist <= 1.0)
    {
        XMVECTOR dis = { rightData.dist,ZERO,ZERO };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(RIGHT_VECTOR, transform_.mmRotate_) - dis));
    }

    //左
    if (leftData.dist <= 1.0)
    {
        XMVECTOR dis = { -leftData.dist,ZERO,ZERO };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(LEFT_VECTOR, transform_.mmRotate_) - dis));
    }

    //前
    if (straightData.dist <= 1.0)
    {
        XMVECTOR dis = { ZERO,ZERO,straightData.dist };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(STRAIGHT_VECTOR, transform_.mmRotate_) - dis));
    }

    //上
    if (upData.dist <= 1.0)
    {
        XMVECTOR dis = { ZERO,upData.dist,ZERO };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(UP_VECTOR, transform_.mmRotate_) - dis));

        //状態変更
        ARGUMENT_INITIALIZE(PlayerStateManager::playerState_, PlayerStateManager::playerStanding_);
        PlayerStateManager::playerState_->Enter(this);

        //ブロック情報がnullptrじゃないのなら
        if (upData.block != nullptr)
        {
            //ブロックを当たっている状態にする
            upData.block->SetIsHit(true);
        }
    }

    //下
    if (downData.dist >= 1.0)
    {
        transform_.position_ = Float3Add(transform_.position_, VectorToFloat3((down_ / 10) * acceleration_));
        acceleration_ += GRAVITY_ADDITION;
    }
    else
    {
        //回転じゃないなら
        if (PlayerStateManager::playerState_ != PlayerStateManager::playerRotationning_)
        {
            //状態変更
            PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
            PlayerStateManager::playerState_->Enter(this);
        }

        ARGUMENT_INITIALIZE(acceleration_, 1);
    }
}

//レイ(2D用)
void Player::StageRayCast2D()
{
    //ブロックとの当たり判定をするためにトランスフォームを保存
    XMFLOAT3 Colpos = transform_.position_;
    Colpos.x -= (PLAYER_MODEL_SIZE_X / 2);

    //右
    if (pstage_->IsBlock(&Colpos, Right))
    {
        ARGUMENT_INITIALIZE(transform_.position_, Colpos);
    }

    ARGUMENT_INITIALIZE(Colpos,transform_.position_);
    Colpos.x += (PLAYER_MODEL_SIZE_X / 2);

    //左
    if (pstage_->IsBlock(&Colpos,Left))
    {
        ARGUMENT_INITIALIZE(transform_.position_,Colpos);
    }

    ARGUMENT_INITIALIZE(Colpos,transform_.position_);
    Colpos.y -= (PLAYER_MODEL_SIZE_Y / 2);

    //下
    if (pstage_->IsBlock(&Colpos, Under))
    {
        ARGUMENT_INITIALIZE(transform_.position_,Colpos);
        
        //回転じゃないなら
        if (PlayerStateManager::playerState_ != PlayerStateManager::playerRotationning_)
        {
            //状態変更
            ARGUMENT_INITIALIZE(PlayerStateManager::playerState_, PlayerStateManager::playerStanding_);
            PlayerStateManager::playerState_->Enter(this);
        }

        ARGUMENT_INITIALIZE(acceleration_,1);
    }

    ARGUMENT_INITIALIZE(Colpos,transform_.position_);
    Colpos.y += (PLAYER_MODEL_SIZE_Y / 2);

    //上
    if (pstage_->IsBlock(&Colpos, Top))
    {
        ARGUMENT_INITIALIZE(transform_.position_,Colpos);

        //状態変更
        ARGUMENT_INITIALIZE(PlayerStateManager::playerState_, PlayerStateManager::playerStanding_);
        PlayerStateManager::playerState_->Enter(this);

        ARGUMENT_INITIALIZE(acceleration_,1);
    }

    //各方向
    RayCastData rightData;
    RayCastData leftData;
    RayCastData upData;
    RayCastData downData;

    //当たってるか確認
    HitTest2D(&rightData, RIGHT_VECTOR);
    HitTest2D(&leftData, LEFT_VECTOR);
    HitTest2D(&upData, UP_VECTOR);
    HitTest2D(&downData, DOWN_VECTOR);

    //////////////////////////////はみ出した分下げる//////////////////////////////////////

    if (rightData.dist <= 1)
    {
        XMVECTOR dis = { rightData.dist,ZERO,ZERO };
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (RIGHT_VECTOR - dis));
    }
    if (leftData.dist <= 1)
    {
        XMVECTOR dis = { -leftData.dist,ZERO,ZERO };
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (LEFT_VECTOR - dis));
    }

    if (upData.dist <= 1)
    {
        XMVECTOR dis = { ZERO,upData.dist,ZERO };
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (UP_VECTOR - dis));
    }

    if (downData.dist >= 0.9)
    {
        transform_.position_ = Float3Add(transform_.position_, VectorToFloat3((DOWN_VECTOR / 10) * acceleration_));
        acceleration_ += GRAVITY_ADDITION;
    }
    else
    {
        //回転じゃないなら
        if (PlayerStateManager::playerState_ != PlayerStateManager::playerRotationning_)
        {
            //状態変更
            PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
            PlayerStateManager::playerState_->Enter(this);
        }

        ARGUMENT_INITIALIZE(acceleration_,1);
    }

}

//当たり判定
void Player::HitTest(RayCastData* data, const XMVECTOR& dir)
{
    data->start = transform_.position_;                                               //レイの発射位置  
    XMStoreFloat3(&data->dir, XMVector3TransformCoord(dir, transform_.mmRotate_));    //レイの方向
    Model::AllRayCast(hGroundModel_, data);                                           //レイを発射
}

//当たり判定
void Player::HitTest2D(RayCastData* data, const XMVECTOR& dir)
{
    data->start = transform_.position_;       //レイの発射位置  
    XMStoreFloat3(&data->dir, dir);           //レイの方向
    Model::RayCast(hGroundModel_, data);      //レイを発射
}

//継承先用の指定した時間で呼ばれるメソッド
void Player::TimeMethod()
{
    Enter();
}

//何かに当たった
void Player::OnCollision(GameObject* pTarget)
{
    //Warpと当たったなら
    if (pTarget->GetObjectName() == "Warp")
    {
        ARGUMENT_INITIALIZE(PlayerStateManager::playerState_, PlayerStateManager::playerStanding_);
        PlayerStateManager::playerState_->Enter(this);

        ARGUMENT_INITIALIZE(acceleration_,1);
    }
}

