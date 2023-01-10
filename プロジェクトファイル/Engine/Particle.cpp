#include "Particle.h"
#include "Camera.h"

Particle::Particle(GameObject* parent)
{
}

Particle::~Particle()
{
}

void Particle::Initialize()
{
}

//更新
void Particle::Update()
{
    //各エミッターの処理
    EmitterUpdate();

    //各パーティクルの処理
    ParticleUpdate();
}


//発生中のパーティクルの更新
void Particle::ParticleUpdate()
{
    for (auto particle = particleList_.begin(); particle != particleList_.end();)
    {
        //寿命が尽きたので消す
        if ((*particle)->life == 0)
        {
            (*particle)->pEmitter->particleNum--;
            (*particle)->pEmitter->isDead = true;
            delete (*particle);
            particle = particleList_.erase(particle);
        }

        //まだ生きてる
        else
        {
            (*particle)->life--;
            (*particle)->now.position.x += (*particle)->delta.position.x;
            (*particle)->now.position.y += (*particle)->delta.position.y;
            (*particle)->now.position.z += (*particle)->delta.position.z;
            (*particle)->delta.position.x *= (*particle)->accel;
            (*particle)->delta.position.y *= (*particle)->accel;
            (*particle)->delta.position.z *= (*particle)->accel;
            (*particle)->delta.position.y -= (*particle)->gravity;


            (*particle)->now.scale.x *= (*particle)->delta.scale.x;
            (*particle)->now.scale.y *= (*particle)->delta.scale.y;
            (*particle)->now.color.x += (*particle)->delta.color.x; //R
            (*particle)->now.color.y += (*particle)->delta.color.y; //G
            (*particle)->now.color.z += (*particle)->delta.color.z; //B
            (*particle)->now.color.w += (*particle)->delta.color.w; //A

            (*particle)->now.Angle += (*particle)->delta.Angle;

            particle++;
        }
    }
}


//各エミッタの更新
void Particle::EmitterUpdate()
{
    for (auto emitter = emitterList_.begin(); emitter != emitterList_.end();)
    {
        //もう死んでるエミッター
        if ((*emitter)->isDead)
        {
            //そのエミッターから出たパーティクルが全部消えてたらエミッターも削除
            if ((*emitter)->particleNum <= 0)
            {
                (*emitter)->pBillBoard->Release();
                delete ((*emitter)->pBillBoard);
                delete (*emitter);
                emitter = emitterList_.erase(emitter);
            }
            else
            {
                emitter++;
            }
        }

        //まだ生きてる
        else
        {
            //パーティクルを発生させるタイミングなら
            if ((*emitter)->data.delay == 0 || (*emitter)->frameCount % (*emitter)->data.delay == 0)
            {
                //指定個数分
                for (int i = 0; i < (*emitter)->data.number; i++)
                {
                    //パーティクル発生
                    ParticleData* pParticle = new ParticleData;

                    //初期
                    {
                        //位置
                        pParticle->now.position = (*emitter)->data.position;

                        if((*emitter)->data.positionErr.x < 0.01 && (*emitter)->data.positionErr.x > 0) (*emitter)->data.positionErr.x = 0;
                        if((*emitter)->data.positionErr.y < 0.01 && (*emitter)->data.positionErr.y > 0) (*emitter)->data.positionErr.y = 0;
                        if((*emitter)->data.positionErr.z < 0.01 && (*emitter)->data.positionErr.z > 0) (*emitter)->data.positionErr.z = 0;

                        float dx = (float)((*emitter)->data.positionErr.x == 0 ? 0 : rand() % (int)((*emitter)->data.positionErr.x * 201) - ((*emitter)->data.positionErr.x * 100)) / 100.0f;
                        float dy = (float)((*emitter)->data.positionErr.y == 0 ? 0 : rand() % (int)((*emitter)->data.positionErr.y * 201) - ((*emitter)->data.positionErr.y * 100)) / 100.0f;
                        float dz = (float)((*emitter)->data.positionErr.z == 0 ? 0 : rand() % (int)((*emitter)->data.positionErr.z * 201) - ((*emitter)->data.positionErr.z * 100)) / 100.0f;
                        pParticle->now.position.x += dx;
                        pParticle->now.position.y += dy;
                        pParticle->now.position.z += dz;

                        //色
                        pParticle->now.color = (*emitter)->data.color;

                        //拡大率
                        dx = (float)((*emitter)->data.sizeErr.x == 0 ? 0 : rand() % (int)((*emitter)->data.sizeErr.x * 201) - ((*emitter)->data.sizeErr.x * 100)) / 100.0f + 1.0f;
                        dy = (float)((*emitter)->data.sizeErr.y == 0 ? 0 : rand() % (int)((*emitter)->data.sizeErr.y * 201) - ((*emitter)->data.sizeErr.y * 100)) / 100.0f + 1.0f;
                        pParticle->now.scale.x = (*emitter)->data.size.x * dx;
                        pParticle->now.scale.y = (*emitter)->data.size.y * dy;

                        pParticle->now.Angle += (*emitter)->data.Angle;
                    }

                    //変化量
                    {
                        //移動方向
                        XMVECTOR vecDir = XMLoadFloat3(&(*emitter)->data.dir);

                        //軸回転なら
                        if ((*emitter)->data.axisFlag)
                        {
                            vecDir = XMVector3TransformCoord(vecDir, XMMatrixTranslation((*emitter)->data.axisPosMove.x,
                                (*emitter)->data.axisPosMove.y, (*emitter)->data.axisPosMove.z) * XMMatrixRotationAxis((*emitter)->data.axisAngle,
                                    XMConvertToRadians(rand() % (int)200)));
                        }
                        //普通の回転なら
                        else
                        {
                            float dx = (float)((*emitter)->data.dirErr.x == 0 ? 0 : rand() % (int)((*emitter)->data.dirErr.x * 201) - ((*emitter)->data.dirErr.x * 100)) / 100.0f;
                            float dy = (float)((*emitter)->data.dirErr.y == 0 ? 0 : rand() % (int)((*emitter)->data.dirErr.y * 201) - ((*emitter)->data.dirErr.y * 100)) / 100.0f;
                            float dz = (float)((*emitter)->data.dirErr.z == 0 ? 0 : rand() % (int)((*emitter)->data.dirErr.z * 201) - ((*emitter)->data.dirErr.z * 100)) / 100.0f;
                            XMMATRIX matRotX = XMMatrixRotationX(XMConvertToRadians(dx));
                            XMMATRIX matRotY = XMMatrixRotationY(XMConvertToRadians(dy));
                            XMMATRIX matRotZ = XMMatrixRotationZ(XMConvertToRadians(dz));
                            vecDir = XMVector3TransformCoord(vecDir, matRotX * matRotY * matRotZ);
                        }

                        float s = (float)((*emitter)->data.speedErr == 0 ? 0 : rand() % (int)((*emitter)->data.speedErr * 201) - ((*emitter)->data.speedErr * 100)) / 100.0f + 1.0f;
                        vecDir = XMVector3Normalize(vecDir) * ((*emitter)->data.speed * s);
                        XMStoreFloat3(&pParticle->delta.position, vecDir);

                        //拡大率
                        pParticle->delta.scale = (*emitter)->data.scale;

                        //色
                        pParticle->delta.color = (*emitter)->data.deltaColor;

                        pParticle->delta.Angle += (*emitter)->data.Angle;
                    }

                    pParticle->life = (*emitter)->data.lifeTime;    //残り寿命
                    pParticle->gravity = (*emitter)->data.gravity;  //重力
                    pParticle->accel = (*emitter)->data.accel;      //加速

                    pParticle->pEmitter = *emitter; //発生元

                    //発生
                    particleList_.push_back(pParticle);

                    pParticle->pEmitter->particleNum++; //発生元のパーティクル数をカウントアップ

                }
            }

            (*emitter)->frameCount++;


            //delayが0のエミッターは１発出したら削除
            if ((*emitter)->data.delay == 0)
            {
                (*emitter)->isDead = true;

            }

            emitter++;
        }
    }
}

//パーティクル描画
void Particle::Draw()
{
    Direct3D::SetShader(Direct3D::SHADER_BILLBOARD);
    Direct3D::SetBlendMode(Direct3D::BLEND_ADD);


    for (auto particle = particleList_.begin(); particle != particleList_.end(); particle++)
    {
        XMMATRIX matWorld;
        XMMATRIX matTrans = XMMatrixTranslation((*particle)->now.position.x, (*particle)->now.position.y, (*particle)->now.position.z);

        XMMATRIX matScale = XMMatrixScaling((*particle)->now.scale.x, (*particle)->now.scale.y, 1.0f);


        matWorld = matScale * Camera::GetBillboardMatrix() * matTrans;
        (*particle)->pEmitter->pBillBoard->Draw(matWorld, (*particle)->now.color);
    }


}

//解放
void Particle::Release()
{
}


//エミッタの作成
int Particle::Start(EmitterData emitterData)
{
    int handle = 0;
    for (auto i = emitterList_.begin(); i != emitterList_.end(); i++)
    {
        handle++;
    }


    Emitter* pEmitter = new Emitter;

    pEmitter->data = emitterData;
    pEmitter->handle = handle;
    pEmitter->frameCount = 0;

    pEmitter->pBillBoard = new BillBoard;
    pEmitter->pBillBoard->Load(emitterData.textureFileName);

    emitterList_.push_back(pEmitter);

    return handle;
}

//エミッタの削除
void Particle::End(int handle)
{
    for (auto i = emitterList_.begin(); i != emitterList_.end(); i++)
    {
        if ((*i)->handle == handle)
        {
            (*i)->pBillBoard->Release();
            delete ((*i)->pBillBoard);
            delete (*i);
            i = emitterList_.erase(i);

            (*i)->isDead = true;
            break;
        }
    }
}
