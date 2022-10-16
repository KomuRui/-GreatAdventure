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
    JampRotationPreviousAngle(0),

    ///////////////////カメラ///////////////////////

    CAM_VEC(XMVectorSet(0.0f, 6.0f, -6.0f, 0.0f)),
    cameraPos_(transform_.rotate_.x,transform_.rotate_.y, transform_.rotate_.z),
    CamMat(XMMatrixIdentity())
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

	///////////////transform///////////////////

	transform_.position_.y = 33;
    //transform_.position_.y = 3;

    ///////////////Stageの各データ取得///////////////////

    //モデル番号取得
    pstage_ = (Stage*)FindObject("Stage");
    hGroundModel_ = pstage_->GethModel();

    //ステージのPosition取得
    StagePotision = pstage_->GetPosition();

    ///////////////元となる上ベクトルの初期化///////////////////

    Up = { 0, 1, 0, 0 };

    ///////////////Playerは元々あるTransform.Rotateを使わないためFlagをTrueにする///////////////////

    transform_.mFlag_ = true;

}

//更新
void Player::Update()
{
    #pragma region Playerの下にレイを打ってそこの法線を求める

    //RayCastData dataNormal;
    //dataNormal.start = transform_.position_;         //レイの発射位置
    //XMFLOAT3 moveY2;
    //XMStoreFloat3(&moveY2, -vNormal);//動かす値
    //dataNormal.dir = moveY2;
    //Model::RayCast(hGroundModel_, &dataNormal);      //レイを発射

    //XMVECTOR vdataNormal = XMLoadFloat3(&dataNormal.normal);

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

    //プレイヤー操作
    MovingOperation();

    //Playerをステージに合わせて回転
    RotationInStage();

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

//更新の前に一回呼ばれる関数
void Player::StartUpdate()
{
}

/////////////////////関数//////////////////////

//カメラの処理
void Player::CameraBehavior()
{
    XMFLOAT3 camPos;                                         //最終的なカメラの位置を入れる変数
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);     //transform_.position_のVector型
    XMVECTOR vCam = CAM_VEC;                                 //Playerからカメラのベクトルを作成
    vCam = XMVector3TransformCoord(vCam, CamMat);            //vCamを回す

    vPos += vCam;                    //PlayerのPosにPlayerからカメラのベクトルをたす
    XMStoreFloat3(&camPos, vPos);    //camPosにvPosをXMFLOAT3に変えていれる

    //カメラの上方向を求めるためにStagePotisionを引いて上方向のベクトルを作成
    XMFLOAT3 UpDirection = { camPos.x - StagePotision.x ,camPos.y - StagePotision.y , camPos.z - StagePotision.z };

    //カメラのいろいろ設定
    Camera::SetUpDirection(XMLoadFloat3(&UpDirection));
    Camera::SetPosition(camPos);
    Camera::SetTarget(XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z));

}

//ステージに合わせてPlayerを回転
void Player::RotationInStage()
{
    //ステージから自キャラまでのベクトルを求める
    XMFLOAT3 Normal = { transform_.position_.x - StagePotision.x ,transform_.position_.y - StagePotision.y , transform_.position_.z - StagePotision.z };
    XMVECTOR vNormal = XMLoadFloat3(&Normal);
    vNormal = XMVector3Normalize(vNormal);

    //ライトの方向をステージから自キャラまでのベクトルの下方向に設定
    Light::SetDirection(XMFLOAT4(-Normal.x, -Normal.y, -Normal.z, 0));

    //Xのベクトルを抜き取る
    float dotX = 0;

    //自キャラまでのベクトルと自キャラの真上のベクトルが少しでも違うなら
    if (XMVectorGetX(Up) != XMVectorGetX(vNormal) || XMVectorGetY(Up) != XMVectorGetY(vNormal) || XMVectorGetZ(Up) != XMVectorGetZ(vNormal))
    {
        //自キャラまでのベクトルと自キャラの真上のベクトルの内積を求める
        XMVECTOR vecDot = XMVector3Dot(Up, vNormal);

        //Xのベクトルを抜き取る
        dotX = XMVectorGetX(vecDot);
    }

    XMVECTOR cross = XMVector3Cross(Up, vNormal);

    if (dotX != 0)
    {
        transform_.mmRotate_ = XMMatrixRotationAxis(cross, acos(dotX));
        transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal, Angle);

        if (JampRotationPreviousAngle)
            mPreviousAngle = XMMatrixRotationAxis(cross, acos(dotX)) * XMMatrixRotationAxis(vNormal, JampRotationPreviousAngle);

        CamMat = XMMatrixRotationAxis(cross, acos(dotX));
    }
    else
    {
        transform_.mmRotate_ = XMMatrixRotationAxis(vNormal, Angle);
    }
}

//プレイヤー操作
void Player::MovingOperation()
{
    static float beforeRotate = 0;
    static bool  flag = false;

    XMVECTOR front = { 0, 0, 1, 0 };
    XMFLOAT3 moveL = {0,0,0};

    //ステージから自キャラまでのベクトルを求める
    XMFLOAT3 Normal = { transform_.position_.x - StagePotision.x ,transform_.position_.y - StagePotision.y , transform_.position_.z - StagePotision.z };
    XMVECTOR vNormal = XMLoadFloat3(&Normal);
    vNormal = XMVector3Normalize(vNormal);

    XMVECTOR moveY = vNormal/40;


    if(Input::GetPadStickL().x > 0 || Input::GetPadStickL().y > 0 || Input::GetPadStickL().x < 0 || Input::GetPadStickL().y < 0)
    {
        
        if (!isJampRotation)
        {
            beforeRotate = Angle;

            float afterRotate = atan2(Input::GetPadStickL().x, Input::GetPadStickL().y);

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
            JampRotationPreviousAngle = atan2(Input::GetPadStickL().x, Input::GetPadStickL().y);

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

            XMFLOAT3 moveL;
            front = front / 10;
            XMStoreFloat3(&moveL, front);

            transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
        }
    }

    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) && !isJamp)
    {
            vJamp = (vNormal)/2;

            isJamp = true;
    }

    if (isJamp)
    {
        if (XMVectorGetY(vJamp) >= 0)
        {
            XMStoreFloat3(&moveL, vJamp - moveY);
            vJamp = vJamp - moveY;

            transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
        }
    }

    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B) && !isJampRotation && isJamp)
    {
        vJamp += (vNormal) / 2;
        isJampRotation = true;
    }

    if (isJampRotation)
    {
        Angle += 0.5;
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

//レイ
void Player::StageRayCast()
{
    RayCastData data[MAX_RAY_SIZE];                  //レイの個数分作成

    //右
    data[Right].start = transform_.position_;        //レイの発射位置
    XMFLOAT3 moveX = { 1,0,0 };                      //動かす値
    data[Right].dir = moveX;
    Model::RayCast(hGroundModel_, &data[Right]);     //レイを発射

    //左
    data[Left].start = transform_.position_;         //レイの発射位置
    XMFLOAT3 moveX2 = { -1,0,0 };                    //動かす値
    data[Left].dir = moveX2;
    Model::RayCast(hGroundModel_, &data[Left]);      //レイを発射

    //前
    data[Straight].start = transform_.position_;     //レイの発射位置
    XMFLOAT3 moveZ = { 0,0,1 };                      //動かす値
    data[Straight].dir = moveZ;
    Model::RayCast(hGroundModel_, &data[Straight]);  //レイを発射s

    //後
    data[Back].start = transform_.position_;         //レイの発射位置
    XMFLOAT3 moveZ2 = { 0,0,-1 };                    //動かす値
    data[Back].dir = moveZ2;
    Model::RayCast(hGroundModel_, &data[Back]);      //レイを発射

    //上
    data[Top].start = transform_.position_;          //レイの発射位置
    XMFLOAT3 moveY = { 0,1,0 };                      //動かす値
    data[Top].dir = moveY;
    Model::RayCast(hGroundModel_, &data[Top]);       //レイを発射

    XMFLOAT3 Normal = { transform_.position_.x - StagePotision.x ,transform_.position_.y - StagePotision.y , transform_.position_.z - StagePotision.z };
    XMVECTOR vNormal = XMLoadFloat3(&Normal);
    vNormal = XMVector3Normalize(vNormal);

    //下
    data[Under].start = transform_.position_;         //レイの発射位置
    XMFLOAT3 moveY2;   
    XMStoreFloat3(&moveY2, -vNormal);//動かす値
    data[Under].dir = moveY2;
    Model::RayCast(hGroundModel_, &data[Under]);      //レイを発射

    //////////////////////////////はみ出した分下げる//////////////////////////////////////

    if (data[Right].dist <= 1)
    {
        transform_.position_.x -= 1 - data[Right].dist;
    }
    if (data[Left].dist <= 1)
    {
        transform_.position_.x += 1 - data[Left].dist;
    }
    if (data[Straight].dist <= 1)
    {
        transform_.position_.z -= 1 - data[Straight].dist;
    }
    if (data[Back].dist <= 1)
    {
        transform_.position_.z += 1 - data[Back].dist;
    }
    if (data[Top].dist <= 1)
    {
        transform_.position_.y -= 1 - data[Top].dist;
    }
    if (data[Under].dist >= 1)//3
    {
        XMFLOAT3 moveL;

        if (isJamp)
        {
            vNormal = (-vNormal) / 10;
            XMStoreFloat3(&moveL, vNormal);
        }
        else
        {
            vNormal = (-vNormal) / 40;
            XMStoreFloat3(&moveL, vNormal);
        }

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z};
       // transform_.position_.y += (0.8 - data[Under].dist) / 5;
    }
    else
    {
        isJamp = false;
        isJampRotation = false;
    }
}
