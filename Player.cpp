#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include <cmath>
#include "Engine/Light.h"
#include "Engine/BoxCollider.h"

//コンストラクタ
Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), hModel_(-1), hGroundModel_(0), Angle(0), isJamp(false), vJamp(XMVectorSet(0, 0, 0, 0)), isJampRotation(false),
    JampRotationPreviousAngle(0), acceleration(1), isRotation(false), camStatus_(LONG), camAngle_(1),

    ///////////////////カメラ///////////////////////
    CamMat(XMMatrixIdentity()),
    TotalMx(XMMatrixIdentity()),
    vNormal(XMVectorSet(0,-1,0,0)),
    Up(XMVectorSet(0, 1, 0, 0)),
    Down(XMVectorSet(0, -1, 0, 0)),
    front(XMVectorSet(0,0,1,0))
{
    CAM_VEC[LONG] = XMVectorSet(0.0f, 15, -15, 0.0f);
    CAM_VEC[SHORT] = XMVectorSet(0.0f, 4, -4, 0.0f);
}

/////////////////////オーバーライドする関数//////////////////////

//初期化
void Player::Initialize()
{

	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load("Star_Main_Character.fbx");
	assert(hModel_ >= 0);

    ///////////////Playerは元々あるTransform.Rotateを使わないためFlagをTrueにする///////////////////

    transform_.mFlag_ = true;

    ///////////////Playerの当たり判定設定///////////////////

    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0.3, 0), XMFLOAT3(2, 2.2, 2));
    AddCollider(collision);


    ///////////////エフェクトとアニメーション設定///////////////////

    //エフェクト出すために必要なクラス
    pParticle_ = Instantiate<Particle>(this);

    //アニメーション
    Model::SetAnimFrame(hModel_, 1, 60, 1);

}

//更新の前に一回呼ばれる関数
void Player::StartUpdate()
{
    ///////////////Stageのデータ取得///////////////////

    //モデル番号取得
    pstage_ = (TutorialStage*)FindObject("TutorialStage");
    hGroundModel_ = pstage_->GethModel();

    transform_.position_ = pstage_->GetPos();

    RayCastData dataNormal;
    dataNormal.start = transform_.position_;         //レイの発射位置
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, Down);//動かす値
    dataNormal.dir = moveY2;
    Model::RayCast(hGroundModel_, &dataNormal);      //レイを発射

    vNormal = XMLoadFloat3(&dataNormal.normal);
}

//更新
void Player::Update()
{

    #pragma region Playerの下にレイを打ってそこの法線を求める

    RayCastData data[MAX_RAY_SIZE];                  //レイの個数分作成
    data[Under].start = transform_.position_;         //レイの発射位置
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, Down);//動かす値
    data[Under].dir = moveY2;
    Model::RayCast(hGroundModel_, &data[Under]);      //レイを発射(All)

    if (data[Under].hit && (XMVectorGetX(vNormal) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&data[Under].normal))) || XMVectorGetY(-vNormal) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&data[Under].normal))) || XMVectorGetZ(-vNormal) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&data[Under].normal)))))
    {
        //元のキャラの上ベクトルvNormalと下の法線の内積を求める
        float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&data[Under].normal)), XMVector3Normalize(vNormal)));

        //角度が40度以内に収まっていたら(壁とかに上らせないため)
        if (acos(dotX) < XMConvertToRadians(50) && acos(dotX) > XMConvertToRadians(-50))
        {
            //ちょっと補間
            vNormal = XMVector3Normalize((XMLoadFloat3(&data[Under].normal) + vNormal) + vNormal * 20);
            Down = -vNormal;
        }

    }

#pragma endregion

    #pragma region コントローラーが無い時に使うキーボード操作

    if (Input::IsKey(DIK_A))
    {
        Angle -= 0.1;

        if (-360 >= Angle)
            Angle = 0;
    }

    if (Input::IsKey(DIK_D))
    {
        Angle += 0.1;

        if (360 <= Angle)
            Angle = 0;
    }


    if (Input::IsKey(DIK_W))
    {
        XMVECTOR front = { 0, 0, 1, 0 };

        front = XMVector3TransformCoord(front, transform_.mmRotate_);//vCamを回す

        XMFLOAT3 moveL;
        front = front / 10;
        XMStoreFloat3(&moveL, front);

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
    }

#pragma endregion


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
        XMVECTOR vCam = CAM_VEC[camStatus_];                     //Playerからカメラのベクトルを作成
        vCam = XMVector3TransformCoord(vCam, CamMat);            //vCamを回す
        vCam = XMVector3TransformCoord(vCam, XMMatrixRotationAxis(vNormal, camAngle_));

        vPos += vCam;                    //PlayerのPosにPlayerからカメラのベクトルをたす
        XMStoreFloat3(&camPos, vPos);    //camPosにvPosをXMFLOAT3に変えていれる

        //カメラの上方向を求めるためにStagePotisionを引いて上方向のベクトルを作成
        XMFLOAT3 UpDirection = { XMVectorGetX(-vNormal), XMVectorGetY(-vNormal), XMVectorGetZ(-vNormal) };

        XMStoreFloat3(&camTar, XMVectorLerp(XMLoadFloat3(&camTar), XMLoadFloat3(&transform_.position_), 0.08));
        XMStoreFloat3(&campos, XMVectorLerp(XMLoadFloat3(&campos), XMLoadFloat3(&camPos), 0.08));

        //カメラのいろいろ設定
        Camera::SetUpDirection(vNormal);
        Camera::SetPosition(campos);
        Camera::SetTarget(camTar);

        //ライト設定
        XMFLOAT3 lightPos;
        XMStoreFloat3(&lightPos, vNormal + XMLoadFloat3(&transform_.position_));

        Light::SetDirection(XMFLOAT4(0, 0,0, 0));
        Light::SetPosition(XMFLOAT4(lightPos.x, lightPos.y, lightPos.z, 0));
    }
    else
    {

        XMFLOAT3 camTar2 = { transform_.position_.x,transform_.position_.y + 1,transform_.position_.z };
        XMFLOAT3 camPos2 = { transform_.position_.x, transform_.position_.y, transform_.position_.z + 20 };

        XMStoreFloat3(&camTar, XMVectorLerp(XMLoadFloat3(&camTar), XMLoadFloat3(&camTar2), 0.08));
        XMStoreFloat3(&campos, XMVectorLerp(XMLoadFloat3(&campos), XMLoadFloat3(&camPos2), 0.08));

        //カメラのいろいろ設定
        Camera::SetPosition(campos);
        Camera::SetTarget(camTar);
       

        Light::SetDirection(XMFLOAT4(0 ,0 ,0 , 0));
        Light::SetPosition(XMFLOAT4(transform_.position_.x, transform_.position_.y, transform_.position_.z + 2, 0));
    }

}

//ステージに合わせてPlayerを回転
void Player::RotationInStage()
{
    //Xのベクトルを抜き取る
    float dotX = 0;

    //自キャラまでのベクトルと自キャラの真上のベクトルが少しでも違うなら
    if (XMVectorGetX(Up) != XMVectorGetX(vNormal) || XMVectorGetY(Up) != XMVectorGetY(vNormal) || XMVectorGetZ(Up) != XMVectorGetZ(vNormal))
    {
        //自キャラまでのベクトルと自キャラの真上のベクトルの内積を求める
        dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(Up), XMVector3Normalize(vNormal)));
    }

    //外積を求める(この結果の軸を横軸にする)
    XMVECTOR cross = XMVector3Cross(Up, vNormal);

    if (!pstage_->GetthreeDflag())
    {
        XMVECTOR TwoDUp = { 0, 1, 0, 0 };

        TotalMx = XMMatrixIdentity();
        transform_.mmRotate_ = TotalMx;

        transform_.mmRotate_ *= XMMatrixRotationAxis(TwoDUp, Angle);

        //Playerが回転しているなら
        if (isJampRotation || isRotation) mPreviousAngle = (TotalMx * XMMatrixRotationAxis(TwoDUp, JampRotationPreviousAngle));
    }
    else
    {
        if (dotX != 0 && dotX <= 1 && dotX >= -1)
        {
            TotalMx *= XMMatrixRotationAxis(cross, acos(dotX));

            transform_.mmRotate_ = TotalMx;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal, Angle);

            //Playerが回転しているなら
            if (isJampRotation || isRotation) mPreviousAngle = (TotalMx * XMMatrixRotationAxis(cross, acos(dotX))) * XMMatrixRotationAxis(vNormal, JampRotationPreviousAngle);

            CamMat = TotalMx;
        }
        else
        {
            transform_.mmRotate_ = TotalMx;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal, Angle);

            //Playerが回転しているなら
            if (isJampRotation || isRotation) mPreviousAngle = (TotalMx * XMMatrixRotationAxis(vNormal, JampRotationPreviousAngle));
        }
    }

    //自キャラまでのベクトルと自キャラの真上のベクトルが少しでも違うなら
    if (XMVectorGetX(Up) != XMVectorGetX(vNormal) || XMVectorGetY(Up) != XMVectorGetY(vNormal) || XMVectorGetZ(Up) != XMVectorGetZ(vNormal))
        Up = vNormal;
}

//プレイヤー操作(円用)
void Player::MovingOperation(RayCastData* data)
{
    XMFLOAT3 moveL = { 0, 0, 0};

    XMVECTOR moveY = vNormal/40;

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;

    //少しでも動いたなら
    if(PadLx > 0 || padLy > 0 || PadLx < 0 || padLy < 0)
    {

        //もしPlayerが何もしていないのならアニメーション開始
        !isJampRotation && !isRotation && !isJamp ? Model::SetAnimFlag(hModel_, true)
                                                  : Model::SetAnimFlag(hModel_, false);

        //ジャンプ回転をしていないなら
        if (!isJampRotation && !isRotation)
        {
            Angle = atan2(PadLx, padLy) + camAngle_;

            JampRotationPreviousAngle = Angle;
        }
        else
            JampRotationPreviousAngle = atan2(PadLx, padLy) + camAngle_;

        //Playerの移動
        {

            //移動するときにLトリガーを押していたらダッシュをする
            if (Input::GetPadTrrigerL())
            {
                Model::SetAnimSpeed(hModel_, 2);
                front = XMVector3Normalize(front) * 1.5;
            }
            else
                Model::SetAnimSpeed(hModel_, 1);

            //ジャンプ回転をしているかによってPlayerの動く方向を決め,moveLに格納
            !isJampRotation && !isRotation ? XMStoreFloat3(&moveL,XMVector3TransformCoord(front / 10, transform_.mmRotate_))
                                           : XMStoreFloat3(&moveL,XMVector3TransformCoord(front / 10, mPreviousAngle));

            //Player移動
            transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };

            //前ベクトルの初期化
            front = XMVector3Normalize(front);
        }
    }
    else
        Model::SetAnimFlag(hModel_, false);

    //ジャンプをしていないなら
    if (!isJamp)
    {
        //当たった距離が0.9fより小さいなら
        if (data[Under].dist < 0.9f)
        {
            XMStoreFloat3(&transform_.position_, XMLoadFloat3(&data[Under].pos) + vNormal);
            acceleration = 1;        //重力初期化
            isJampRotation = false;  //回転オフ
        }
    }

    //もしジャンプをしていない状態でAボタンを押したなら
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) && !isJamp)
    {
        //ジャンプのベクトルに値を代入
        vJamp = (vNormal)/2;
        KeepJamp = vJamp;

        //移動した分dist足す
        data[Under].dist++;     

        //ジャンプしている状態にする
        isJamp = true;
    }

    //もしジャンプをしていて回転をしていなくてTrrigerRを押していたら
    if (Input::GetPadTrrigerR() && !isJampRotation && isJamp)
    {
        //ジャンプのベクトルにたす
        vJamp = (vNormal) / 2;
        KeepJamp = vJamp;

        //回転FlagをOnにする
        isJampRotation = true;
    }

    //もしジャンプをしていたら
    if (isJamp)
    {
        //アニメーション解除
        Model::SetAnimFlag(hModel_, false);
       
        //符号が同じなら
        if (signbit(XMVectorGetY(vJamp)) == signbit(XMVectorGetY(KeepJamp)))
        {
            //どんどんベクトルを小さくしていく
            XMStoreFloat3(&moveL, vJamp - moveY);
            vJamp = vJamp - moveY;

            //Transformにたす
            transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
        }
    }

    //もしジャンプをしていなくてtriggerRを押していたら
    if (Input::GetPadTrrigerR() && !isJamp && !isRotation) isRotation = true;

    //回転FlagがTrue1なら自信を回転させる
    if (isJampRotation)
    {
        //エフェクトの表示
        RotationEffect();

        Angle += 0.5;

        //360まで行ったら0に戻す
        if (Angle >= TWOPI_DEGREES)
            Angle = ZEROPI_DEGREES;
    }

    //もし回転FlagがTrueなら自身を回転させる
    if (isRotation)
    {
        //エフェクトの表示
        RotationEffect();

        //回転させる
        Angle += 1 - (rotationCount * 0.015f);

        //もし回転を始めてから60フレーム以上が経過しているなら
        if (rotationCount >= 60)
        {
            //回転停止
            isRotation = false;
            rotationCount = 0;
        }

        //rotationCount1ずつ増やす
        rotationCount++;
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
        !isJampRotation && !isRotation && !isJamp ? Model::SetAnimFlag(hModel_, true) 
                                                  : Model::SetAnimFlag(hModel_, false);

        //ジャンプ回転をしていないなら
        if (!isJampRotation && !isRotation)
        {
            Angle = -atan2(PadLx, -padLy);

            JampRotationPreviousAngle = Angle;
        }
        else
            JampRotationPreviousAngle = -atan2(PadLx, padLy);


        //Playerの移動
        {

            //移動するときにLトリガーを押していたらダッシュをする
            if (Input::GetPadTrrigerL())
            {
                Model::SetAnimSpeed(hModel_, 2);
                front = XMVector3Normalize(front) * 1.5;
            }
            else
                Model::SetAnimSpeed(hModel_, 1);

            //回転をしているかによってPlayerの動く方向を決め,moveLに格納
            !isJampRotation && !isRotation ? XMStoreFloat3(&moveL, XMVector3TransformCoord(front / 10, transform_.mmRotate_))
                                           : XMStoreFloat3(&moveL, XMVector3TransformCoord(front / 10, mPreviousAngle));

            //自身のポジションに移動の値を加算する
            transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z };

            front = XMVector3Normalize(front);
        }
    }
    else
        Model::SetAnimFlag(hModel_, false);

    //ジャンプをしていないなら
    if (!isJamp)
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
            acceleration = 1;
            isJampRotation = false;
        }
    }

    //もしジャンプをしていない状態でAボタンを押したなら
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) && !isJamp && !isRotation)
    {
        //ジャンプのベクトルに値を代入
        vJamp = (TwoDUp) / 2;

        //ジャンプしている状態にする
        isJamp = true;
    }

    //もしジャンプをしていたら
    if (isJamp)
    {
        Model::SetAnimFlag(hModel_, false);

        //ジャンプするベクトルがプラスだったら
        if (XMVectorGetY(vJamp) >= 0)
        {
            //どんどんベクトルを小さくしていく
            XMStoreFloat3(&moveL, vJamp - moveY);
            vJamp = vJamp - moveY;

            //Transformにたす
            transform_.position_ = { transform_.position_.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
        }
    }

    //もしジャンプをしていて回転をしていなくてBを押していたら
    if (Input::GetPadTrrigerR() && !isJampRotation && isJamp)
    {
        //ジャンプのベクトルにたす
        vJamp = (TwoDUp) / 2;

        //回転FlagをOnにする
        isJampRotation = true;

        //ジャンプ回転FlagをOffにする
        isRotation = false;
    }

    //もしジャンプをしていなくてtriggerRを押していたら
    if (Input::GetPadTrrigerR() && !isJamp && !isRotation) isRotation = true;


    //ジャンプ回転FlagがTrueなら自身を回転させる
    if (isJampRotation)
    {
        //エフェクトの表示
        RotationEffect();

        //回転
        Angle += 0.5;
    }

    //もし回転FlagがTrueなら自身を回転させる
    if (isRotation)
    {
        //エフェクトの表示
        RotationEffect();

        //回転させる
        Angle += 1 - (rotationCount * 0.015f);

        //もし回転を始めてから60フレーム以上が経過しているなら
        if (rotationCount >= 60)
        {
            //回転停止
            isRotation = false;
            rotationCount = 0;
        }

        //rotationCount1ずつ増やす
        rotationCount++;
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

//ゆっくりと次の角度に向く
void Player::FaceOrientationSlowly(float afterRotate,bool &flag)
{
    if (afterRotate < 0)
        afterRotate += XMConvertToRadians(360);

    if (Angle < afterRotate)
        Angle += fabs(afterRotate - Angle) / 10;
    else
        Angle -= fabs(afterRotate - Angle) / 10;

    if (fabs(afterRotate - Angle) <= XMConvertToRadians(60))
    {
        flag = false;
    }
}

//レイ(円用)
void Player::StageRayCast(RayCastData* data)
{

    //右
    data[Right].start = transform_.position_;        //レイの発射位置
    XMVECTOR moveX = { 1,0,0 };                      //動かす値
    moveX = XMVector3TransformCoord(moveX, transform_.mmRotate_);
    XMStoreFloat3(&data[Right].dir, moveX);
    Model::RayCast(hGroundModel_, &data[Right]);     //レイを発射

    //左
    data[Left].start = transform_.position_;         //レイの発射位置
    XMVECTOR moveX2 = { -1,0,0 };                    //動かす値
    moveX2 = XMVector3TransformCoord(moveX2, transform_.mmRotate_);
    XMStoreFloat3(&data[Left].dir, moveX2);
    Model::RayCast(hGroundModel_, &data[Left]);      //レイを発射

    //前
    data[Straight].start = transform_.position_;     //レイの発射位置
    XMVECTOR moveZ = { 0,0,1 };                      //動かす値
    moveZ = XMVector3TransformCoord(moveZ, transform_.mmRotate_);
    XMStoreFloat3(&data[Straight].dir, moveZ);
    Model::RayCast(hGroundModel_, &data[Straight]);  //レイを発射s

    //上
    data[Top].start = transform_.position_;         //レイの発射位置]
    XMVECTOR moveY = { 0,1,0 };                    //動かす値
    moveY = XMVector3TransformCoord(moveY, transform_.mmRotate_);
    XMStoreFloat3(&data[Top].dir, moveY);
    Model::RayCast(hGroundModel_,&data[Top]);      //レイを発射

    //ブロックとの当たり判定
    XMFLOAT3 Colpos;
    XMStoreFloat3(&Colpos, XMLoadFloat3(&transform_.position_) + (moveZ / 2));

    //前
    if (pstage_->IsBlock3D(&Colpos, moveZ, transform_.mmRotate_,2))
    {
        transform_.position_ = Colpos;
    }

    XMStoreFloat3(&Colpos, XMLoadFloat3(&transform_.position_) + (moveX / 2));

    //右
    if (pstage_->IsBlock3D(&Colpos, moveX, transform_.mmRotate_,0))
    {
        transform_.position_ = Colpos;
    }

    XMStoreFloat3(&Colpos, XMLoadFloat3(&transform_.position_) + (moveX2 / 2));

    //左
    if (pstage_->IsBlock3D(&Colpos, moveX2, transform_.mmRotate_, 1))
    {
        transform_.position_ = Colpos;
    }

    XMStoreFloat3(&Colpos, XMLoadFloat3(&transform_.position_) + XMVector3Normalize (vNormal));

    //下
    if (pstage_->IsBlock3D(&Colpos, XMVector3Normalize(vNormal), transform_.mmRotate_, 4))
    {
        transform_.position_ = Colpos;
        isJamp = false;
        isJampRotation = false;
        acceleration = 1;
    }

    XMStoreFloat3(&Colpos, XMLoadFloat3(&transform_.position_) + XMVector3Normalize(-vNormal));

    //上
    if (pstage_->IsBlock3D(&Colpos, XMVector3Normalize(-vNormal), transform_.mmRotate_,5))
    {
        transform_.position_ = Colpos;
        isJamp = false;
        isJampRotation = false;
        acceleration = 1;
    }

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
        isJamp = false;

        XMVECTOR dis = { 0,data[Top].dist,0 };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveY - dis));
    }

    if (data[Under].dist >= 1)//3
    {
        XMFLOAT3 moveL;

        if (isJamp)
        {
            XMStoreFloat3(&moveL, (-vNormal) / 10 * acceleration);
        }
        else
        {
            XMStoreFloat3(&moveL, (-vNormal) / 20 * acceleration);
        }

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z};

        acceleration += 0.03;
    }
    else
    {
        isJamp = false;
        isJampRotation = false;
        acceleration = 1;
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
        isJamp = false;
        isJampRotation = false;
        acceleration = 1;
    }

    Colpos = transform_.position_;
    Colpos.y += 1;

    //上
    if (pstage_->IsBlock(&Colpos,3))
    {
        transform_.position_ = Colpos;
        isJamp = false;
        acceleration = 1;
    }

    RayCastData data[MAX_RAY_SIZE];                  //レイの個数分作成

    //右
    data[Right].start = transform_.position_;        //レイの発射位置
    XMVECTOR moveX = { 0.5,0,0 };                      //動かす値
    XMStoreFloat3(&data[Right].dir, moveX);
    Model::RayCast(hGroundModel_, &data[Right]);     //レイを発射

    //左
    data[Left].start = transform_.position_;         //レイの発射位置
    XMVECTOR moveX2 = { -0.5,0,0 };                    //動かす値
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
    XMStoreFloat3(&moveY2, -vNormal);//動かす値
    data[Under].dir = moveY2;
    Model::RayCast(hGroundModel_, &data[Under]);      //レイを発射

    //////////////////////////////はみ出した分下げる//////////////////////////////////////

    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    if (data[Right].dist <= 0.5)
    {
        XMVECTOR dis = { data[Right].dist,0,0 };
        XMStoreFloat3(&transform_.position_, pos - (moveX - dis));
    }
    if (data[Left].dist <= 0.5)
    {
        XMVECTOR dis = { -data[Left].dist,0,0 };
        XMStoreFloat3(&transform_.position_, pos - (moveX2 - dis));
    }

    if (data[Top].dist <= 1)
    {
        isJamp = false;

        XMVECTOR dis = { 0,data[Top].dist,0 };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveY - dis));
    }

    if (data[Under].dist >= 0.9)//3
    {
        XMFLOAT3 moveL;
        XMVECTOR twoDUp = { 0,1,0,0 };

        XMStoreFloat3(&moveL, ((-twoDUp) / 10) * acceleration);

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };

        acceleration += 0.03;
    }
    else
    {
        isJamp = false;
        isJampRotation = false;
        acceleration = 1;
    }

}

//何かに当たった
void Player::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Warp")
    {
        isJamp = true;
        isJampRotation = false;
        isRotation = false;
        acceleration = 1;
    }
}