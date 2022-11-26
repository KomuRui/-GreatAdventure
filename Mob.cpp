#include "Mob.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Engine/GameManager.h"

//�R���X�g���N�^
Mob::Mob(GameObject* parent, std::string modelPath,std::string name)
	: GameObject(parent, name), hModel_(-1), ModelNamePath_(modelPath), hGroundModel_(0), Angle(0),

    ///////////////////�J����///////////////////////
    TotalMx(XMMatrixIdentity()),
    vNormal(XMVectorSet(0, -1, 0, 0)),
    Up(XMVectorSet(0, 1, 0, 0)),
    Down(XMVectorSet(0, -1, 0, 0))
{
}

//������
void Mob::Initialize()
{
	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= 0);

	////////////////////�p����ŐV���ɏ������̓��e�ǉ�����p///////////////////////

	ChildInitialize();

}

//�X�V�̑O�Ɉ�񂾂��Ă΂��֐�
void Mob::StartUpdate()
{

    ///////////////Stage�̃f�[�^�擾///////////////////

    //���f���ԍ��擾
    pstage_ = GameManager::GetpStage();
    int polyModel = pstage_->GetPolyModell();

    //3D�Ȃ�
    if (pstage_->GetthreeDflag())
    {
        //�߂��̃|���S���𒲂ׂ�
        NearPolyData dataNormal;
        dataNormal.start = transform_.position_;
        Model::NearPolyNormal(polyModel, &dataNormal);

        //�@����ǉ�
        vNormal = XMLoadFloat3(&dataNormal.normal);
    }
    else
        vNormal = { 0,1,0,0 };

    ///////////////���X����Transform.Rotate���g��Ȃ�����Flag��True�ɂ���///////////////////

    transform_.mFlag_ = true;

    //�p�����StartUpdate
	ChildStartUpdate();
}

//�X�V
void Mob::Update()
{
    //null�Ȃ珈�������Ȃ�
    if (pstage_ == nullptr) return;

    //�X�e�[�W�ɍ��킹��Mob����]������
    RotationInStage();

    //�p���悲�Ƃɓ�����ς����
    ChildUpdate();
}

//�X�e�[�W�ɍ��킹��Mob����]
void Mob::RotationInStage()
{
    //X�̃x�N�g���𔲂����
    float dotX = 0;

    //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���������ł��Ⴄ�Ȃ�
    if (XMVectorGetX(Up) != XMVectorGetX(vNormal) || XMVectorGetY(Up) != XMVectorGetY(vNormal) || XMVectorGetZ(Up) != XMVectorGetZ(vNormal))
    {
        //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���̓��ς����߂�
        XMVECTOR vecDot = XMVector3Dot(XMVector3Normalize(Up), XMVector3Normalize(vNormal));

        //X�̃x�N�g���𔲂����
        dotX = XMVectorGetX(vecDot);
    }

    XMVECTOR cross = XMVector3Cross(Up, vNormal);

    if (!pstage_->GetthreeDflag())
    {
        XMVECTOR TwoDUp = { 0, 1, 0, 0 };

        TotalMx = XMMatrixIdentity();
        transform_.mmRotate_ = TotalMx;

        transform_.mmRotate_ *= XMMatrixRotationAxis(TwoDUp, Angle);
    }
    else
    {
        if (dotX != 0 && dotX <= 1 && dotX >= -1)
        {
            TotalMx *= XMMatrixRotationAxis(cross, acos(dotX));

            transform_.mmRotate_ = TotalMx;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal, Angle);
        }
        else
        {
            transform_.mmRotate_ = TotalMx;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal, Angle);
        }
    }

    //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���������ł��Ⴄ�Ȃ�
    if (XMVectorGetX(Up) != XMVectorGetX(vNormal) || XMVectorGetY(Up) != XMVectorGetY(vNormal) || XMVectorGetZ(Up) != XMVectorGetZ(vNormal))
        Up = vNormal;
}

//�`��
void Mob::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	ChildDraw();
}

//�J��
void Mob::Release()
{
    ChildRelease();
}




