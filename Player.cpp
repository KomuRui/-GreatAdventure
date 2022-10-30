#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include <cmath>
#include "Engine/Light.h"

//コンストラクタ
Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), hModel_(-1), hGroundModel_(0), Angle(0), isJamp(false), vJamp(XMVectorSet(0, 0, 0, 0)), isJampRotation(false),
    JampRotationPreviousAngle(0), acceleration(1),

    ///////////////////カメラ///////////////////////

    CAM_VEC(XMVectorSet(0.0f, 25.0f, -30.0f, 0.0f)),
    CamMat(XMMatrixIdentity()),
    TotalMx(XMMatrixIdentity()),
    vNormal(XMVectorSet(0,-1,0,0))
{
}

/////////////////////オーバーライドする関数//////////////////////

//初期化
void Player::Initialize()
{

	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load("Star_Main_Character.fbx");
	assert(hModel_ >= 0);

    Model::SetAmbient(hModel_, 20);

    ///////////////元となる上ベクトルの初期化///////////////////

    Up = { 0, 1, 0, 0 };
    Down = { 0, -1, 0, 0 };

    ///////////////Playerは元々あるTransform.Rotateを使わないためFlagをTrueにする///////////////////

    transform_.mFlag_ = true;

}

//更新の前に一回呼ばれる関数
void Player::StartUpdate()
{
    ///////////////Stageの各データ取得///////////////////

    //モデル番号取得
    pstage_ = (TutorialStage*)FindObject("TutorialStage");
    hGroundModel_ = pstage_->GethModel();

    ///////////////transform///////////////////

    transform_.position_ = pstage_->GetPos();

    RayCastData dataNormal;
    dataNormal.start = transform_.position_;         //レイの発射位置
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, Down);//動かす値
    dataNormal.dir = moveY2;
    Model::AllRayCast(hModel_ ,&dataNormal);      //レイを発射

    vNormal = XMLoadFloat3(&dataNormal.normal);

    //カメラのポジション初期化しておく
    //2Dの時
    if (!pstage_->GetthreeDflag())
        NowCamPos = { transform_.position_.x, transform_.position_.y + 1, transform_.position_.z + 20 };
}


//更新
void Player::Update()
{
    #pragma region Playerの下にレイを打ってそこの法線を求める

    RayCastData dataNormal;
    dataNormal.start = transform_.position_;         //レイの発射位置
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, Down);//動かす値
    dataNormal.dir = moveY2;
    Model::AllRayCast(hModel_, &dataNormal, "Stage/Tutorial/first_Stage.fbx");      //レイを発射(All)

    if (dataNormal.hit && ( XMVectorGetX(vNormal) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&dataNormal.normal))) || XMVectorGetY(-vNormal) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&dataNormal.normal))) || XMVectorGetZ(-vNormal) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&dataNormal.normal)))))
    {
        //元のキャラの上ベクトルvNormalと下の法線の内積を求める
        float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&dataNormal.normal)), XMVector3Normalize(vNormal)));

        //角度が60度以内に収まっていたら(壁とかに上らせないため)
        if (acos(dotX) < XMConvertToRadians(60) && acos(dotX) > XMConvertToRadians(-60))
        {
            //ちょっと補間
            vNormal = XMVector3Normalize((XMLoadFloat3(&dataNormal.normal) + vNormal) + vNormal * 30);
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

    if (!pstage_->GetthreeDflag())
        //プレイヤー操作2D
        MovingOperation2D();
    else
        //プレイヤー操作
        MovingOperation();

    //Playerをステージに合わせて回転
    RotationInStage();

    if (!pstage_->GetthreeDflag())
        //ステージとの当たり判定2D
        StageRayCast2D();
    else
        //ステージとの当たり判定
        StageRayCast();

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
    if (pstage_->GetthreeDflag())
    {
        XMFLOAT3 camPos;                                         //最終的なカメラの位置を入れる変数
        XMVECTOR vPos = XMLoadFloat3(&transform_.position_);     //transform_.position_のVector型
        XMVECTOR vCam = CAM_VEC;                                 //Playerからカメラのベクトルを作成
        vCam = XMVector3TransformCoord(vCam, CamMat);            //vCamを回す

        vPos += vCam;                    //PlayerのPosにPlayerからカメラのベクトルをたす
        XMStoreFloat3(&camPos, vPos);    //camPosにvPosをXMFLOAT3に変えていれる

        //カメラの上方向を求めるためにStagePotisionを引いて上方向のベクトルを作成
        XMFLOAT3 UpDirection = { XMVectorGetX(-vNormal), XMVectorGetY(-vNormal), XMVectorGetZ(-vNormal) };

        //カメラのいろいろ設定
        Camera::SetUpDirection(vNormal);
        Camera::SetPosition(camPos);
        Camera::SetTarget(XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z));

        Light::SetDirection(XMFLOAT4(XMVectorGetX(-vNormal), XMVectorGetY(-vNormal), XMVectorGetZ(-vNormal), 0));
    }
    else
    {
        //今いるカメラのポジションよりYが1より離れているなら
        if (fabs(transform_.position_.y - NowCamPos.y) > 0.5 && !isJamp)
        {
            XMFLOAT3 pos = { transform_.position_.x,transform_.position_.y,transform_.position_.z + 20 };
                
            XMStoreFloat3(&NowCamPos,XMVectorLerp(XMLoadFloat3(&NowCamPos), XMLoadFloat3(&pos), 0.05));
        }

        //カメラのいろいろ設定
        Camera::SetPosition(XMFLOAT3(transform_.position_.x, NowCamPos.y, NowCamPos.z));
        Camera::SetTarget(XMFLOAT3(transform_.position_.x, transform_.position_.y + 1, transform_.position_.z));

        Light::SetDirection(XMFLOAT4(0 ,0, -1, 0));
    }
}

//ステージに合わせてPlayerを回転
void Player::RotationInStage()
{
    float4x4 crs;

    //Xのベクトルを抜き取る
    float dotX = 0;

    //自キャラまでのベクトルと自キャラの真上のベクトルが少しでも違うなら
    if (XMVectorGetX(Up) != XMVectorGetX(vNormal) || XMVectorGetY(Up) != XMVectorGetY(vNormal) || XMVectorGetZ(Up) != XMVectorGetZ(vNormal))
    {
        //自キャラまでのベクトルと自キャラの真上のベクトルの内積を求める
        XMVECTOR vecDot = XMVector3Dot(XMVector3Normalize(Up), XMVector3Normalize(vNormal));

        //Xのベクトルを抜き取る
        dotX = XMVectorGetX(vecDot);
    }

    XMVECTOR cross = XMVector3Cross(Up, vNormal);

    if (!pstage_->GetthreeDflag())
    {
        XMVECTOR TwoDUp = { 0, 1, 0, 0 };

        TotalMx = XMMatrixIdentity();
        transform_.mmRotate_ = TotalMx;

        XMStoreFloat4x4(_Out_ & crs, _In_ XMMatrixRotationAxis(TwoDUp, Angle));
        transform_.mmRotate_ *= transform_.QuaternionToMattrix(make_quaternion_from_rotation_matrix(crs));

        if (isJampRotation)
            mPreviousAngle = (TotalMx * XMMatrixRotationAxis(TwoDUp, JampRotationPreviousAngle));
    }
    else
    {

        if (dotX != 0 && dotX <= 1 && dotX >= -1)
        {

            XMStoreFloat4x4(_Out_ & crs, _In_ XMMatrixRotationAxis(cross, acos(dotX)));
            TotalMx *= transform_.QuaternionToMattrix(make_quaternion_from_rotation_matrix(crs));
            transform_.mmRotate_ = TotalMx;


            XMStoreFloat4x4(_Out_ & crs, _In_ XMMatrixRotationAxis(vNormal, Angle));
            transform_.mmRotate_ *= transform_.QuaternionToMattrix(make_quaternion_from_rotation_matrix(crs));


            if (isJampRotation)
                mPreviousAngle = (TotalMx * XMMatrixRotationAxis(cross, acos(dotX))) * XMMatrixRotationAxis(vNormal, JampRotationPreviousAngle);

            CamMat = TotalMx;
        }
        else
        {
            transform_.mmRotate_ = TotalMx;

            XMStoreFloat4x4(_Out_ & crs, _In_ XMMatrixRotationAxis(vNormal, Angle));
            transform_.mmRotate_ *= transform_.QuaternionToMattrix(make_quaternion_from_rotation_matrix(crs));

            if (isJampRotation)
                mPreviousAngle = (TotalMx * XMMatrixRotationAxis(vNormal, JampRotationPreviousAngle));
        }
    }

    //自キャラまでのベクトルと自キャラの真上のベクトルが少しでも違うなら
    if (XMVectorGetX(Up) != XMVectorGetX(vNormal) || XMVectorGetY(Up) != XMVectorGetY(vNormal) || XMVectorGetZ(Up) != XMVectorGetZ(vNormal))
    {
        Up = vNormal;
    }
}

//プレイヤー操作(円用)
void Player::MovingOperation()
{
    static float beforeRotate = 0;
    static bool  flag = false;

    XMVECTOR front = { 0, 0, 1, 0 };

    XMFLOAT3 moveL = { 0, 0, 0};

    XMVECTOR moveY = vNormal/40;

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;

    if(PadLx > 0 || padLy > 0 || PadLx < 0 || padLy < 0)
    {

        if (!isJampRotation)
        {
            beforeRotate = Angle;

            float afterRotate = atan2(PadLx, padLy);

            /*if (beforeRotate != afterRotate)
            {
                flag = true;
                FaceOrientationSlowly(afterRotate, flag);
            }
            else*/
            Angle = afterRotate;

            JampRotationPreviousAngle = Angle;
        }
        else
            JampRotationPreviousAngle = atan2(PadLx, padLy);

        if (!flag)
        {
            if (!isJampRotation)
            {
                front = XMVector3TransformCoord(front, transform_.mmRotate_);
            }
            else
            {
                front = XMVector3TransformCoord(front, mPreviousAngle);
            }

            front = front / 10;
            XMStoreFloat3(&moveL, front);

            transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
        }
    }

    //もしジャンプをしていない状態でAボタンを押したなら
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) && !isJamp)
    {
        //ジャンプのベクトルに値を代入
        vJamp = (vNormal)/2;

        //ジャンプしている状態にする
        isJamp = true;
    }

    //もしジャンプをしていたら
    if (isJamp)
    {
        //ジャンプするベクトルがプラスだったら
        if (XMVectorGetY(vJamp) >= 0)
        {
            //どんどんベクトルを小さくしていく
            XMStoreFloat3(&moveL, vJamp - moveY);
            vJamp = vJamp - moveY;

            //Transformにたす
            transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
        }
    }

    //もしジャンプをしていて回転をしていなくてBを押していたら
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B) && !isJampRotation && isJamp)
    {
        //ジャンプのベクトルにたす
        vJamp += (vNormal) / 2;

        //回転FlagをOnにする
        isJampRotation = true;
    }

    //回転FlagがTrue1なら自信を回転させる
    if (isJampRotation)
    {
        Angle += 0.5;

        //360まで行ったら0に戻す
        if (Angle >= 360)
            Angle = 0;
    }

}

//プレイヤー操作(2D用)
void Player::MovingOperation2D()
{
    XMVECTOR front = { 0, 0, -1, 0 };

    XMFLOAT3 moveL = { 0, 0, 0 };

    XMVECTOR moveY = { 0,1.0f / 60.0f,0,0 };

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;

    if (PadLx > 0 || PadLx < 0)
    {
        //padLy = 0;

        if (!isJampRotation)
        {
            Angle = -atan2(PadLx, -padLy);

            JampRotationPreviousAngle = Angle;
        }
        else
            JampRotationPreviousAngle = -atan2(PadLx, padLy);


        if (!isJampRotation)
        {
            front = XMVector3TransformCoord(front, transform_.mmRotate_);
        }
        else
        {
            front = XMVector3TransformCoord(front, mPreviousAngle);
        }

        front = front / 10;
        XMStoreFloat3(&moveL, -front);

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z };

    }

    //ジャンプをしていないなら
    if (!isJamp)
    {
        RayCastData dataNormal;
        dataNormal.start = transform_.position_;         //レイの発射位置
        XMFLOAT3 moveY2 = { 0,-1,0};
        dataNormal.dir = moveY2;
        Model::AllRayCast(hModel_, &dataNormal, "Stage/Tutorial/first_Stage.fbx");      //レイを発射(All)

        //当たった距離が1.0fより小さいなら
        if (dataNormal.dist < 1.0f)
        {
            dataNormal.pos.y += 1.0f;
            transform_.position_ = dataNormal.pos;
            acceleration = 1;
        }
    }

    //もしジャンプをしていない状態でAボタンを押したなら
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) && !isJamp)
    {
        XMVECTOR TwoDUp = { 0,1,0,0 };

        //ジャンプのベクトルに値を代入
        vJamp = (TwoDUp) / 2;

        //ジャンプしている状態にする
        isJamp = true;
    }

    //もしジャンプをしていたら
    if (isJamp)
    {
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
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B) && !isJampRotation && isJamp)
    {
        XMVECTOR TwoDUp = { 0,1,0,0 };

        //ジャンプのベクトルにたす
        vJamp += (TwoDUp) / 2;

        //回転FlagをOnにする
        isJampRotation = true;
    }

    //回転FlagがTrue1なら自信を回転させる
    if (isJampRotation)
    {
        Angle += 0.5;

        //360まで行ったら0に戻す
        if (Angle >= 360)
            Angle = 0;
    }

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
void Player::StageRayCast()
{
    RayCastData data[MAX_RAY_SIZE];                  //レイの個数分作成

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

    //後
    data[Back].start = transform_.position_;         //レイの発射位置
    XMVECTOR moveZ2 = { 0,0,-1 };                    //動かす値
    moveZ2 = XMVector3TransformCoord(moveZ2, transform_.mmRotate_);
    XMStoreFloat3(&data[Back].dir, moveZ2);
    Model::RayCast(hGroundModel_, &data[Back]);      //レイを発射

    //上
    data[Top].start = transform_.position_;         //レイの発射位置]
    XMVECTOR moveY = { 0,1,0 };                    //動かす値
    moveY = XMVector3TransformCoord(moveY, transform_.mmRotate_);
    XMStoreFloat3(&data[Top].dir, moveY);
    Model::RayCast(hGroundModel_,&data[Top]);      //レイを発射

    //下
    data[Under].start = transform_.position_;         //レイの発射位置
    XMFLOAT3 moveY2;   
    XMStoreFloat3(&moveY2, -vNormal);//動かす値
    data[Under].dir = moveY2;
    Model::RayCast(hGroundModel_, &data[Under]);      //レイを発射

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
    if (data[Back].dist <= 1)
    {
        XMVECTOR dis = { 0,0,-data[Back].dist };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveZ2 - dis));
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
            XMStoreFloat3(&moveL, (-vNormal) / 10);
        }
        else
        {
            XMStoreFloat3(&moveL, (-vNormal) / 20);
        }

        //XMStoreFloat3(&moveL, (-vNormal) / 10);

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z};
    }
    else
    {
        isJamp = false;
        isJampRotation = false;
    }
}

//レイ(2D用)
void Player::StageRayCast2D()
{
    RayCastData data[MAX_RAY_SIZE];                  //レイの個数分作成

    //右
    data[Right].start = transform_.position_;        //レイの発射位置
    XMVECTOR moveX = { 0.5,0,0 };                      //動かす値
    XMStoreFloat3(&data[Right].dir, moveX);
    Model::AllRayCast(hModel_, &data[Right], "Stage/Tutorial/first_Stage.fbx");     //レイを発射

    //左
    data[Left].start = transform_.position_;         //レイの発射位置
    XMVECTOR moveX2 = { -0.5,0,0 };                    //動かす値
    XMStoreFloat3(&data[Left].dir, moveX2);
    Model::AllRayCast(hModel_, &data[Left], "Stage/Tutorial/first_Stage.fbx");      //レイを発射

    //上
    data[Top].start = transform_.position_;         //レイの発射位置]
    XMVECTOR moveY = { 0,1,0 };                    //動かす値
    XMStoreFloat3(&data[Top].dir, moveY);
    Model::AllRayCast(hModel_, &data[Top], "Stage/Tutorial/first_Stage.fbx");      //レイを発射

    //下
    data[Under].start = transform_.position_;         //レイの発射位置
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, -vNormal);//動かす値
    data[Under].dir = moveY2;
    Model::AllRayCast(hModel_, &data[Under], "Stage/Tutorial/first_Stage.fbx");      //レイを発射

    //////////////////////////////はみ出した分下げる//////////////////////////////////////

    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    if (data[Right].dist <= 0.5)
    {
        XMVECTOR dis = { data[Right].dist,0,0 };
        //dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveX - dis));
    }
    if (data[Left].dist <= 0.5)
    {
        XMVECTOR dis = { -data[Left].dist,0,0 };
        //dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
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
        XMFLOAT3 beforPosition;
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
