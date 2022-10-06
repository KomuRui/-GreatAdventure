#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include <cmath>

//コンストラクタ
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1), hGroundModel_(0),

    ///////////////////カメラ///////////////////////

    CAM_VEC(XMVectorSet(0.0f, 3.0f, -5.0f, 0.0f)),
    cameraPos_(transform_.rotate_.x,transform_.rotate_.y, transform_.rotate_.z)
{
}

/////////////////////オーバーライドする関数//////////////////////

//初期化
void Player::Initialize()
{

	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load("Star_Main_Character.fbx");
	assert(hModel_ >= 0);

	///////////////transform///////////////////

	transform_.position_.y = 33;

    pstage_ = (Stage*)FindObject("Stage");
    hGroundModel_ = pstage_->GethModel();
}

//更新
void Player::Update()
{

    //カメラの回転
    cameraPos_.y += Input::GetPadStickR().x * 3;
    cameraPos_.x += Input::GetPadStickR().y;

    //プレイヤー操作
    MovingOperation();

    //カメラの挙動
    CameraBehavior();

    //ステージとの当たり判定
    StageRayCast();
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
    XMFLOAT3 camPos;
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(cameraPos_.y));
    XMMATRIX mRotateX4 = XMMatrixRotationX(XMConvertToRadians(cameraPos_.x));
    XMMATRIX mRotateZ1 = XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));
    XMVECTOR vCam = CAM_VEC;
    vCam = XMVector3TransformCoord(vCam, mRotateZ1);//vCamを回す
    vCam = XMVector3TransformCoord(vCam, mRotateX4);//vCamを回す
    vCam = XMVector3TransformCoord(vCam, mRotateY);//vCamを回す

    vPos += vCam;
    XMStoreFloat3(&camPos, vPos);

    Camera::SetPosition(camPos);
    Camera::SetTarget(XMFLOAT3(transform_.position_.x, transform_.position_.y + 1, transform_.position_.z));
}

//プレイヤー操作
void Player::MovingOperation()
{
    XMFLOAT3     cam = { Camera::GetPosition().x,transform_.position_.y,Camera::GetPosition().z };
    XMVECTOR     vCam = XMLoadFloat3(&cam);
    XMVECTOR     vPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR     distance = XMVector3Normalize(vPos - vCam);
    static float beforeRotate = 0;
    static bool  flag = false;

    if(Input::GetPadStickL().x > 0 || Input::GetPadStickL().y > 0 || Input::GetPadStickL().x < 0 || Input::GetPadStickL().y < 0)
    {
        beforeRotate = transform_.rotate_.y;

        XMMATRIX mRotate90 = XMMatrixRotationY(atan2(Input::GetPadStickL().x , Input::GetPadStickL().y));
        distance = XMVector3TransformCoord(distance, mRotate90);

        float afterRotate = cameraPos_.y + (atan2(Input::GetPadStickL().x, Input::GetPadStickL().y)) * 180.0 / 3.14159265;

        if (beforeRotate != afterRotate)
        {
            flag = true;
            FaceOrientationSlowly(afterRotate, flag);
        }
        else
            transform_.rotate_.y = afterRotate;

        if (!flag)
        {
            XMFLOAT3 move;
            if (fabs(Input::GetPadStickL().x) != 0 && fabs(Input::GetPadStickL().y) != 0)
            {
                float avg = (fabs(Input::GetPadStickL().x) + fabs(Input::GetPadStickL().y));

                if (avg > 1)
                {
                    avg = 1;
                }
                XMStoreFloat3(&move, ((distance / 10) * avg));
            }
            else if(fabs(Input::GetPadStickL().x) != 0)
            {
                XMStoreFloat3(&move, ((distance / 10) * fabs(Input::GetPadStickL().x)));
            }
            else
            {
                XMStoreFloat3(&move, ((distance / 10) * fabs(Input::GetPadStickL().y)));
            }

            transform_.position_ = { transform_.position_.x + move.x,transform_.position_.y + move.y,transform_.position_.z + move.z };
        }
    }

}

//ゆっくりと次の角度に向く
void Player::FaceOrientationSlowly(float afterRotate,bool &flag)
{
    if (afterRotate < 0)
        afterRotate += 360;

    if (transform_.rotate_.y < afterRotate)
        transform_.rotate_.y += fabs(afterRotate - transform_.rotate_.y) / 10;
    else
        transform_.rotate_.y -= fabs(afterRotate - transform_.rotate_.y) / 10;

    if (fabs(afterRotate - transform_.rotate_.y) <= 60)
    {
        flag = false;
    }
}

//レイ
void Player::StageRayCast()
{
    RayCastData data[MAX_RAY_SIZE];          //レイの個数分作成

    //右
    data[Right].start = transform_.position_;    //レイの発射位置
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

    //下
    data[Under].start = transform_.position_;         //レイの発射位置
    XMFLOAT3 moveY2 = { 0,-1,0 };                     //動かす値
    data[Under].dir = moveY2;
    Model::RayCast(hGroundModel_, &data[Under]);      //レイを発射

    //////////////////////////////はみ出した分下げる//////////////////////////////////////

    if (data[Right].dist <= 0.5)
    {
        transform_.position_.x -= 0.5 - data[Right].dist;
    }
    if (data[Left].dist <= 0.5)
    {
        transform_.position_.x += 0.5 - data[Left].dist;
    }
    if (data[Straight].dist <= 0.5)
    {
        transform_.position_.z -= 0.5 - data[Straight].dist;
    }
    if (data[Back].dist <= 0.5)
    {
        transform_.position_.z += 0.5 - data[Back].dist;
    }
    if (data[Top].dist <= 0.5)
    {
        transform_.position_.y -= 0.5 - data[Top].dist;
    }
    if (data[Under].dist <= 3)
    {
        transform_.position_.y += (0.8 - data[Under].dist) / 5;
    }
}
