#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include <cmath>
#include "Engine/Light.h"
#include "Engine/BoxCollider.h"
#include "Engine/SphereCollider.h"
#include "Engine/GameManager.h"

//コンストラクタ
Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), 

    ///////////////キャラの必要な情報///////////////////

    //モデル
    hModel_(-1),
    hGroundModel_(0),

    //各方向ベクトル
    vNormal_(XMVectorSet(0, -1, 0, 0)),
    up_(XMVectorSet(0, 1, 0, 0)),
    down_(XMVectorSet(0, -1, 0, 0)),
    front_(XMVectorSet(0, 0, 1, 0)),

    //キャラの軸回転に必要な変数
    totalMx_(XMMatrixIdentity()),
    jampRotationPreviousAngle_(0),
    angle_(0),
    normalFlag_(true),

    //ジャンプ
    vJamp_(XMVectorSet(0, 0, 0, 0)),
    isJampRotation_(false),
    isJamp_(false),

    //その他
    acceleration_(1),
    isFly_(false),
    isRotation_(false),

    ///////////////////カメラ///////////////////////

    camMat_(XMMatrixIdentity()),
    camStatus_(LONG),
    camAngle_(1),
    camPosFlag_(true)
    
{
    camVec_[LONG] = XMVectorSet(0.0f, 15, -15, 0.0f);
    camVec_[SHORT] = XMVectorSet(0.0f, 4, -4, 0.0f);
}

/////////////////////オーバーライドする関数//////////////////////

//初期化
void Player::Initialize()
{

	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load("Star_Main_Character.fbx");
	assert(hModel_ >= ZERO);

    ///////////////Playerは元々あるTransform.Rotateを使わないためFlagをTrueにする///////////////////

    transform_.mFlag_ = true;

    ///////////////Playerの当たり判定設定///////////////////

    SphereCollider* collision = new SphereCollider(COLLIDER_POS, COLLIDER_SIZE);
    AddCollider(collision);

    ///////////////エフェクトとアニメーション設定///////////////////

    //エフェクト出すために必要なクラス
    pParticle_ = Instantiate<Particle>(this);

    //アニメーション
    Model::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, ANIM_SPEED);

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

    //レイを真下に打つ
    RayCastData data[MAX_RAY_SIZE];                        
    data[Under].start = transform_.position_;              
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, down_);
    data[Under].dir = moveY2;
    Model::BlockRayCast(hGroundModel_, &data[Under]);      

    //真下の法線を調べる
    CheckUnderNormal(data);

    //ステージが2Dなら2D用の関数,3Dなら3D用の関数を呼ぶ
    !pstage_->GetthreeDflag() ? MovingOperation2D()
                              : MovingOperation(data);

    //Playerをステージに合わせて回転
    RotationInStage();

    //ステージが2Dなら2D用の関数,3Dなら3D用の関数を呼ぶ
    !pstage_->GetthreeDflag() ? StageRayCast2D()
                              : StageRayCast(data);

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
void Player::CheckUnderNormal(RayCastData* data)
{
    //法線を調べるかどうかのFlagがtrueなら
    if (normalFlag_)
    {
        //レイが当たっていてかつ少しでも上ベクトルとvNormal_の値が違うのなら
        if (data[Under].hit && (XMVectorGetX(vNormal_) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&data[Under].normal))) || XMVectorGetY(-vNormal_) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&data[Under].normal))) || XMVectorGetZ(-vNormal_) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&data[Under].normal)))))
        {
            //元のキャラの上ベクトルvNormalと下の法線の内積を求める
            float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&data[Under].normal)), XMVector3Normalize(vNormal_)));

            //角度が50度以内に収まっていたら(壁とかに上らせないため)
            if (acos(dotX) < XMConvertToRadians(MAX_NORMAL_RADIANS) && acos(dotX) > XMConvertToRadians(-MAX_NORMAL_RADIANS))
            {
                //ちょっと補間
                vNormal_ = XMVector3Normalize((XMVectorLerp( XMVector3Normalize(vNormal_), XMLoadFloat3(&data[Under].normal), NORMAL_INTERPOLATION_FACTOR)));
                down_ = -vNormal_;
            }

        }
    }
}

//ステージに合わせてPlayerを回転
void Player::RotationInStage()
{
    //Xのベクトルを抜き取る
    float dotX = 0;

    //自キャラまでのベクトルと自キャラの真上のベクトルが少しでも違うなら
    if (XMVectorGetX(up_) != XMVectorGetX(vNormal_) || XMVectorGetY(up_) != XMVectorGetY(vNormal_) || XMVectorGetZ(up_) != XMVectorGetZ(vNormal_))
    {
        //自キャラまでのベクトルと自キャラの真上のベクトルの内積を求める
        dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(up_), XMVector3Normalize(vNormal_)));
    }

    //外積を求める(この結果の軸を横軸にする)
    XMVECTOR cross = XMVector3Cross(up_, vNormal_);

    if (!pstage_->GetthreeDflag())
    {
        XMVECTOR TwoDUp = { 0, 1, 0, 0 };

        totalMx_ = XMMatrixIdentity();
        transform_.mmRotate_ = totalMx_;

        transform_.mmRotate_ *= XMMatrixRotationAxis(TwoDUp, angle_);

        //Playerが回転しているなら
        if (isJampRotation_ || isRotation_) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(TwoDUp, jampRotationPreviousAngle_));
    }
    else
    {
        if (dotX != 0 && dotX <= 1 && dotX >= -1)
        {
            totalMx_ *= XMMatrixRotationAxis(cross, acos(dotX));

            transform_.mmRotate_ = totalMx_;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);

            //Playerが回転しているなら
            if (isJampRotation_ || isRotation_) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(cross, acos(dotX))) * XMMatrixRotationAxis(vNormal_, jampRotationPreviousAngle_);

            camMat_ = totalMx_;
        }
        else
        {
            transform_.mmRotate_ = totalMx_;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);

            //Playerが回転しているなら
            if (isJampRotation_ || isRotation_) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(vNormal_, jampRotationPreviousAngle_));
        }
    }

    //自キャラまでのベクトルと自キャラの真上のベクトルが少しでも違うなら
    if (XMVectorGetX(up_) != XMVectorGetX(vNormal_) || XMVectorGetY(up_) != XMVectorGetY(vNormal_) || XMVectorGetZ(up_) != XMVectorGetZ(vNormal_))
        up_ = vNormal_;
}

//プレイヤー操作(円用)
void Player::MovingOperation(RayCastData* data)
{
    XMFLOAT3 moveL = { 0, 0, 0};

    XMVECTOR moveY = vNormal_/40;

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;

    //少しでも動いたなら
    if(PadLx > 0 || padLy > 0 || PadLx < 0 || padLy < 0)
    {

        //もしPlayerが何もしていないのならアニメーション開始
        !isJampRotation_ && !isRotation_ && !isFly_  ? Model::SetAnimFlag(hModel_, true)
                                                  : Model::SetAnimFlag(hModel_, false);

        //ジャンプ回転をしていないなら
        if (!isJampRotation_ && !isRotation_)
        {
            angle_ = atan2(PadLx, padLy) + camAngle_;

            jampRotationPreviousAngle_ = angle_;
        }
        else
            jampRotationPreviousAngle_ = atan2(PadLx, padLy) + camAngle_;

        //Playerの移動
        {

            //移動するときにLトリガーを押していたらダッシュをする
            if (Input::GetPadTrrigerL())
            {
                Model::SetAnimSpeed(hModel_, 2);
                front_ = XMVector3Normalize(front_) * 1.5;
            }
            else
                Model::SetAnimSpeed(hModel_, 1);

            //ジャンプ回転をしているかによってPlayerの動く方向を決め,moveLに格納
            !isJampRotation_ && !isRotation_ ? XMStoreFloat3(&moveL,XMVector3TransformCoord(front_ / 10, transform_.mmRotate_))
                                           : XMStoreFloat3(&moveL,XMVector3TransformCoord(front_ / 10, mPreviousAngle_));

            //Player移動
            transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };

            //前ベクトルの初期化
            front_ = XMVector3Normalize(front_);
        }
    }
    else
        Model::SetAnimFlag(hModel_, false);

    //空を飛んでいないのなら
    if (!isFly_)
    {
        //当たった距離が0.9fより小さいなら
        if (data[Under].dist < 0.9f)
        {
            XMStoreFloat3(&transform_.position_, XMLoadFloat3(&data[Under].pos) + vNormal_);
            acceleration_ = 1;        //重力初期化
            isJampRotation_ = false;  //回転オフ
            isFly_ = false;
        }
    }

    //もしジャンプをしていない状態でAボタンを押したなら
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) && !isFly_)
    {
        //ジャンプのベクトルに値を代入
        vJamp_ = (vNormal_)/2;
        keepJamp_ = vJamp_;

        //移動した分dist足す
        data[Under].dist++;   

        //ジャンプしている状態にする
        isJamp_ = true;
        isFly_ = true;
    }

    //もしジャンプをしていて回転をしていなくてTrrigerRを押していたら
    if (Input::GetPadTrrigerR() && !isJampRotation_ && isJamp_)
    {
        //ジャンプのベクトルにたす
        vJamp_ = (vNormal_) / 2;
        keepJamp_ = vJamp_;

        //回転FlagをOnにする
        isJampRotation_ = true;
    }

    //もしジャンプをしていたら
    if (isJamp_)
    {
        //アニメーション解除
        Model::SetAnimFlag(hModel_, false);
       
        //符号が同じなら
        if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
        {
            //どんどんベクトルを小さくしていく
            XMStoreFloat3(&moveL, vJamp_ - moveY);
            vJamp_ = vJamp_ - moveY;

            //Transformにたす
            transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
        }
    }

    //もしジャンプをしていなくてtriggerRを押していたら
    if (Input::GetPadTrrigerR() && !isFly_ && !isRotation_) isRotation_ = true;

    //回転FlagがTrue1なら自信を回転させる
    if (isJampRotation_)
    {
        //エフェクトの表示
        RotationEffect();

        angle_ += 0.5;

        //360まで行ったら0に戻す
        if (angle_ >= TWOPI_DEGREES)
            angle_ = ZEROPI_DEGREES;
    }

    //もし回転FlagがTrueなら自身を回転させる
    if (isRotation_)
    {
        //エフェクトの表示
        RotationEffect();

        //回転させる
        angle_ += 1 - (rotationCount_ * 0.015f);

        //もし回転を始めてから60フレーム以上が経過しているなら
        if (rotationCount_ >= 60)
        {
            //回転停止
            isRotation_ = false;
            rotationCount_ = 0;
        }

        //rotationCount1ずつ増やす
        rotationCount_++;
    }

    //Bを押したらカメラの位置変更
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
    {
        //カメラの状態変更
        camStatus_ = camStatus_ == LONG ? SHORT
                                        : LONG;
    }

    //左ショルダーを押したら角度変更
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_LEFT_SHOULDER)) camAngle_ += 0.5f;
    
    //右ショルダーを押したら角度変更
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_RIGHT_SHOULDER)) camAngle_ -= 0.5f;

    //右スティックでカメラの角度かえる
    if (Input::GetPadStickR().x) camAngle_ += 0.03f * Input::GetPadStickR().x;
}

//プレイヤー操作(2D用)
void Player::MovingOperation2D()
{
    XMFLOAT3 moveL = { 0, 0, 0 };

    XMVECTOR moveY = { 0,1.0f / 60.0f,0,0 };

    XMVECTOR TwoDUp = { 0,1,0,0 };

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;

    if (PadLx > 0 || PadLx < 0)
    {
        //もしPlayerが何もしていないのならアニメーション開始
        !isJampRotation_ && !isRotation_ && !isFly_  ? Model::SetAnimFlag(hModel_, true)
                                                  : Model::SetAnimFlag(hModel_, false);

        //ジャンプ回転をしていないなら
        if (!isJampRotation_ && !isRotation_)
        {
            angle_ = -atan2(PadLx, -padLy);

            jampRotationPreviousAngle_ = angle_;
        }
        else
            jampRotationPreviousAngle_ = -atan2(PadLx, padLy);


        //Playerの移動
        {

            //移動するときにLトリガーを押していたらダッシュをする
            if (Input::GetPadTrrigerL())
            {
                Model::SetAnimSpeed(hModel_, 2);
                front_ = XMVector3Normalize(front_) * 1.5;
            }
            else
                Model::SetAnimSpeed(hModel_, 1);

            //回転をしているかによってPlayerの動く方向を決め,moveLに格納
            !isJampRotation_ && !isRotation_ ? XMStoreFloat3(&moveL, XMVector3TransformCoord(front_ / 10, transform_.mmRotate_))
                                           : XMStoreFloat3(&moveL, XMVector3TransformCoord(front_ / 10, mPreviousAngle_));

            //自身のポジションに移動の値を加算する
            transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z };

            front_ = XMVector3Normalize(front_);
        }
    }
    else
        Model::SetAnimFlag(hModel_, false);

    //空を飛んでいないのなら
    if (!isFly_)
    {
        RayCastData dataNormal;
        dataNormal.start = transform_.position_;         //レイの発射位置
        XMFLOAT3 moveY2 = { 0,-1,0};
        dataNormal.dir = moveY2;
        Model::RayCast(hGroundModel_, &dataNormal);      //レイを発射(All)

        //当たった距離が1.0fより小さいなら
        if (dataNormal.dist < 1.0f)
        {
            dataNormal.pos.y += 1.0f;
            transform_.position_ = dataNormal.pos;
            acceleration_ = 1;
            isJampRotation_ = false;
            isFly_ = false;
        }
    }

    //もしジャンプをしていない状態でAボタンを押したなら
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) && !isFly_)
    {
        //ジャンプのベクトルに値を代入
        vJamp_ = (TwoDUp) / 2;

        //ジャンプしている状態,空飛んでる状態にする
        isJamp_ = true;
        isFly_ =  true;
    }

    //もしジャンプをしていたら
    if (isJamp_)
    {
        Model::SetAnimFlag(hModel_, false);

        //ジャンプするベクトルがプラスだったら
        if (XMVectorGetY(vJamp_) >= 0)
        {
            //どんどんベクトルを小さくしていく
            XMStoreFloat3(&moveL, vJamp_ - moveY);
            vJamp_ = vJamp_ - moveY;

            //Transformにたす
            transform_.position_ = { transform_.position_.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
        }
    }

    //もしジャンプをしていて回転をしていなくてTrrigerRを押していたら
    if (Input::GetPadTrrigerR() && !isJampRotation_ && isJamp_)
    {
        //ジャンプのベクトルにたす
        vJamp_ = (TwoDUp) / 2;

        //回転FlagをOnにする
        isJampRotation_ = true;

        //ジャンプ回転FlagをOffにする
        isRotation_ = false;
    }

    //もし浮いていなくてtriggerRを押していたら
    if (Input::GetPadTrrigerR() && !isFly_ && !isRotation_) isRotation_ = true;


    //ジャンプ回転FlagがTrueなら自身を回転させる
    if (isJampRotation_)
    {
        //エフェクトの表示
        RotationEffect();

        //回転
        angle_ += 0.5;
    }

    //もし回転FlagがTrueなら自身を回転させる
    if (isRotation_)
    {
        //エフェクトの表示
        RotationEffect();

        //回転させる
        angle_ += 1 - (rotationCount_ * 0.015f);

        //もし回転を始めてから60フレーム以上が経過しているなら
        if (rotationCount_ >= 60)
        {
            //回転停止
            isRotation_ = false;
            rotationCount_ = 0;
        }

        //rotationCount1ずつ増やす
        rotationCount_++;
    }
}

//回転エフェクト
void Player::RotationEffect()
{
    XMFLOAT3 Right = Model::GetBonePosition(hModel_, "Right2");//右
    XMFLOAT3 Left = Model::GetBonePosition(hModel_, "Left2"); //左

    EmitterData data;
    data.textureFileName = "Cloud.png";
    data.position = Right;
    data.positionErr = XMFLOAT3(0.3, 0.2, 0.3);
    data.delay = 0;
    data.number = 5;
    data.lifeTime = 50;
    data.speed = 0.04f;
    data.speedErr = 0.8;
    data.size = XMFLOAT2(0.6, 0.6);
    data.sizeErr = XMFLOAT2(0.4, 0.4);
    data.scale = XMFLOAT2(1.00, 1.00);
    data.color = XMFLOAT4(0, 1, 1, 1);
    data.deltaColor = XMFLOAT4(0, -0.1, 0, -0.1);
    pParticle_->Start(data);


    data.position = Left;
    pParticle_->Start(data);
}

//落下エフェクト
void Player::FallEffect()
{
    EmitterData data;
    data.textureFileName = "Cloud.png";
    data.position = transform_.position_;
    data.position.y -= 4;
    data.delay = 0;
    data.number = 180;
    data.lifeTime = 50;
    data.dir = XMFLOAT3(0, 0, 1);
    data.dirErr = XMFLOAT3(0, 360, 0);
    data.speed = 0.2f;
    data.speedErr = 0.45;
    data.size = XMFLOAT2(1, 1);
    data.sizeErr = XMFLOAT2(0.4, 0.4);
    data.scale = XMFLOAT2(1.05, 1.05);
    data.color = XMFLOAT4(1, 1, 1, 0.2);
    data.deltaColor = XMFLOAT4(0, 0, 0, -0.004);
    pParticle_->Start(data);
}

//レイ(円用)
void Player::StageRayCast(RayCastData* data)
{

    //右
    data[Right].start = transform_.position_;        //レイの発射位置
    XMVECTOR moveX = { 1,0,0 };                      //動かす値
    moveX = XMVector3TransformCoord(moveX, transform_.mmRotate_);
    XMStoreFloat3(&data[Right].dir, moveX);
    Model::BlockRayCast(hGroundModel_, &data[Right]);     //レイを発射

    //左
    data[Left].start = transform_.position_;         //レイの発射位置
    XMVECTOR moveX2 = { -1,0,0 };                    //動かす値
    moveX2 = XMVector3TransformCoord(moveX2, transform_.mmRotate_);
    XMStoreFloat3(&data[Left].dir, moveX2);
    Model::BlockRayCast(hGroundModel_, &data[Left]);      //レイを発射

    //前
    data[Straight].start = transform_.position_;     //レイの発射位置
    XMVECTOR moveZ = { 0,0,1 };                      //動かす値
    moveZ = XMVector3TransformCoord(moveZ, transform_.mmRotate_);
    XMStoreFloat3(&data[Straight].dir, moveZ);
    Model::BlockRayCast(hGroundModel_, &data[Straight]);  //レイを発射s

    //上
    data[Top].start = transform_.position_;         //レイの発射位置]
    XMVECTOR moveY = { 0,1,0 };                    //動かす値
    moveY = XMVector3TransformCoord(moveY, transform_.mmRotate_);
    XMStoreFloat3(&data[Top].dir, moveY);
    Model::BlockRayCast(hGroundModel_,&data[Top]);      //レイを発射


    //////////////////////////////はみ出した分下げる//////////////////////////////////////

    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    if (data[Right].dist <= 1)
    {
        XMVECTOR dis = { data[Right].dist,0,0 };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveX - dis));
    }
    if (data[Left].dist <= 1)
    {
        XMVECTOR dis = { -data[Left].dist,0,0 };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveX2 - dis));
    }
    if (data[Straight].dist <= 1)
    {
        XMVECTOR dis = { 0,0,data[Straight].dist };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveZ - dis));
    }

    if (data[Top].dist <= 1)
    {
        isJamp_ = false;

        XMVECTOR dis = { 0,data[Top].dist,0 };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveY - dis));
    }

    if (data[Under].dist >= 1)//3
    {
        XMFLOAT3 moveL;

        if (isJamp_)
        {
            XMStoreFloat3(&moveL, (-vNormal_) / 10 * acceleration_);
        }
        else
        {
            XMStoreFloat3(&moveL, (-vNormal_) / 20 * acceleration_);
        }

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z};

        acceleration_ += 0.03;
    }
    else
    {
        isJamp_ = false;
        isFly_ = false;
        isJampRotation_ = false;
        acceleration_ = 1;
    }
}

//レイ(2D用)
void Player::StageRayCast2D()
{
    //ブロックとの当たり判定をするためにトランスフォームを保存
    XMFLOAT3 Colpos = transform_.position_;
    Colpos.x -= 0.5;

    //右
    if (pstage_->IsBlock(&Colpos,0))
    {
        transform_.position_ = Colpos;
    }

    Colpos = transform_.position_;
    Colpos.x += 0.5;

    //左
    if (pstage_->IsBlock(&Colpos,1))
    {
        transform_.position_ = Colpos;
    }

    Colpos = transform_.position_;
    Colpos.y -= 1;

    //下
    if (pstage_->IsBlock(&Colpos,2))
    {
        transform_.position_ = Colpos;
        isJamp_ = false;
        isFly_ = false;
        isJampRotation_ = false;
        acceleration_ = 1;
    }

    Colpos = transform_.position_;
    Colpos.y += 1;

    //上
    if (pstage_->IsBlock(&Colpos,3))
    {
        transform_.position_ = Colpos;
        isJamp_ = false;
        acceleration_ = 1;
    }

    RayCastData data[MAX_RAY_SIZE];                  //レイの個数分作成

    //右
    data[Right].start = transform_.position_;        //レイの発射位置
    XMVECTOR moveX = { 1,0,0 };                      //動かす値
    XMStoreFloat3(&data[Right].dir, moveX);
    Model::RayCast(hGroundModel_, &data[Right]);     //レイを発射

    //左
    data[Left].start = transform_.position_;         //レイの発射位置
    XMVECTOR moveX2 = { -1,0,0 };                    //動かす値
    XMStoreFloat3(&data[Left].dir, moveX2);
    Model::RayCast(hGroundModel_, &data[Left]);      //レイを発射

    //上
    data[Top].start = transform_.position_;         //レイの発射位置]
    XMVECTOR moveY = { 0,1,0 };                    //動かす値
    XMStoreFloat3(&data[Top].dir, moveY);
    Model::RayCast(hGroundModel_, &data[Top]);      //レイを発射

    //下
    data[Under].start = transform_.position_;         //レイの発射位置
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, -vNormal_);//動かす値
    data[Under].dir = moveY2;
    Model::RayCast(hGroundModel_, &data[Under]);      //レイを発射

    //////////////////////////////はみ出した分下げる//////////////////////////////////////

    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    if (data[Right].dist <= 1)
    {
        XMVECTOR dis = { data[Right].dist,0,0 };
        XMStoreFloat3(&transform_.position_, pos - (moveX - dis));
    }
    if (data[Left].dist <= 1)
    {
        XMVECTOR dis = { -data[Left].dist,0,0 };
        XMStoreFloat3(&transform_.position_, pos - (moveX2 - dis));
    }

    if (data[Top].dist <= 1)
    {
        isJamp_ = false;

        XMVECTOR dis = { 0,data[Top].dist,0 };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveY - dis));
    }

    if (data[Under].dist >= 0.9)//3
    {
        XMFLOAT3 moveL;
        XMVECTOR twoDUp = { 0,1,0,0 };

        XMStoreFloat3(&moveL, ((-twoDUp) / 10) * acceleration_);

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };

        acceleration_ += 0.03;
    }
    else
    {
        isJamp_ = false;
        isFly_ = false;
        isJampRotation_ = false;
        acceleration_ = 1;
    }

}

//継承先用の指定した時間で呼ばれるメソッド
void Player::TimeMethod()
{
    Enter();
}

//何かに当たった
void Player::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Warp")
    {
        isJamp_ = true;
        isJampRotation_ = false;
        isRotation_ = false;
        acceleration_ = 1;
    }
}