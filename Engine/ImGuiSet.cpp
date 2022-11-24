#include "Image.h"
#include "SceneManager.h"
#include "Input.h"
#include "ImGuiSet.h"
#include "Model.h"
#include "SphereCollider.h"
#include "..\imgui\\imgui.h"
#include "..\imgui\\imgui_impl_win32.h"
#include "..\imgui\\imgui_impl_dx11.h"
#include <fstream>
#include "../Mob.h"
#include "../Gimmick/Coin.h"
#include "../Gimmick/Warp.h"
#include "../Block/ItemBlock.h"
#include "../Enemy/Enemy.h"
#include "../Enemy/DropEnemy.h"
#include "../Enemy/PigEnemy.h"
#include "../Block/BrickBlock.h"
#include "../Block/NormalBlock.h"
#include "../Block/TransparentBlock.h"
#include "../Mob/MainMob.h"
#include "../Gimmick/Signboard.h"

//�R���X�g���N�^
ImGuiSet::ImGuiSet(GameObject* parent)
	: GameObject(parent, "ImGuiSet"), Create3Dflag(false), ObjectCount(0), CreateSigeboardflag(false),SigeboardCount(0)
{
}

//������
void ImGuiSet::Initialize()
{
}

//�X�V
void ImGuiSet::Update()
{
}

//�`��
void ImGuiSet::Draw()
{
    //Imgui�X�^�[�g
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    //window���
    ImGui::Begin("StagePosition");

    //3D�����{�^��
    if (ImGui::Button("Create3D"))
    {
        Create3Dflag = true;
        ObjectCount++;
    }

    //�Ŕ����{�^��
    if (ImGui::Button("CreateSigeboard"))
    {
        CreateSigeboardflag = true;
        SigeboardCount++;
    }

    //�J�����{�^��
    if (ImGui::Button("Camera"))
    {
    }


    //flag��true�Ȃ�֐����Ăяo��
    if (Create3Dflag)
    {
        Create3D();
    }

    if (CreateSigeboardflag)
    {
        CreateSigeboard();
    }

    ImGui::End();

    ImGui::Render();
    //�`��
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiSet::Create3D()
{
    //�e�I�u�W�F�N�g�̏��
    static int status[MAX_OBJECT_SIZE] = {};
    static Mob* pNewObject[MAX_OBJECT_SIZE];
    static XMFLOAT3 pos[MAX_OBJECT_SIZE];
    static XMFLOAT3 rotate[MAX_OBJECT_SIZE];
    static XMFLOAT3 scale[MAX_OBJECT_SIZE];
    static XMFLOAT3 BasicPos = pPlayer_->GetPosition();
    static XMFLOAT3 BasicRotate = pPlayer_->GetRotate();
    static XMFLOAT3 BasicScale = pPlayer_->GetScale();
      
    //Create3D�����������E�B���h�E�����@
    for (int i = 0; i < ObjectCount; i++)
    {
        if (status[i] == 1 || status[i] == 0)
        {
            //i��FBX�̌��ɂ���
            char name[16];
            sprintf_s(name, "FBX %d", i);

            //window���
            ImGui::Begin(name);

            //�t�@�C���l�[�����͗�
            static char text1[MAX_OBJECT_SIZE][50] = {};

            //���͂��ꂽ������text1�Ɋi�[
            ImGui::InputText("FBX filename", text1[i], sizeof(text1[i]));

            //���[�h�{�^��
            if (ImGui::Button("Load"))
            {
                //�����܂��������[�h���ĂȂ�������
                if (status[i] == 0)
                {

                    //���[�h�����I�u�W�F�N�g�ɕK�v�ȃg�����X�t�H�[����p��
                    Transform t;

                    pos[i] = BasicPos;
                    rotate[i] = BasicRotate;
                    scale[i] = BasicScale;

                    //�v�b�V�����邽�߂�pair�^�����
                    //first->���[�h�������f���ԍ�
                    //second->���[�h�������f����transform
                    std::pair<int, Transform> a(Model::Load(text1[i]), t);
                    assert(a.first > 0);

                    //vector�Ɋi�[����
                    obj.push_back(a);

                    pNewObject[i] = new Mob(this, text1[i],"");
                    if (GetParent() != nullptr)
                    {
                        this->PushBackChild(pNewObject[i]);
                    }
                    pNewObject[i]->Initialize();

                    //status�v���X
                    status[i]++;

                }
            }

            //��񃍁[�h���Ă�����
            if (status[i] == 1)
            {

                //Position�̖�
                if (ImGui::TreeNode("position")) {

                    //Position�Z�b�g
                    ImGui::SliderFloat("x", &pos[i].x, -200.0f, 200.0f);
                    ImGui::SliderFloat("y", &pos[i].y, -200.0f, 200.0f);
                    ImGui::SliderFloat("z", &pos[i].z, -200.0f, 200.0f);

                    if (ImGui::TreeNode("InputPosition")) {

                        ImGui::Text("x");
                        ImGui::InputFloat("x", &pos[i].x, -20.0f, 20.0f);
                        ImGui::Text("y");
                        ImGui::InputFloat("y", &pos[i].y, -20.0f, 20.0f);
                        ImGui::Text("z");
                        ImGui::InputFloat("z", &pos[i].z, -20.0f, 20.0f);

                        ImGui::TreePop();
                    }

                    ImGui::TreePop();
                }

                //Scale�̖�
                if (ImGui::TreeNode("scale")) {

                    //Scale�Z�b�g
                    ImGui::SliderFloat("x", &scale[i].x, -20.0f, 20.0f);
                    ImGui::SliderFloat("y", &scale[i].y, -20.0f, 20.0f);
                    ImGui::SliderFloat("z", &scale[i].z, -20.0f, 20.0f);

                    if (ImGui::TreeNode("InputScale")) {

                        ImGui::Text("x");
                        ImGui::InputFloat("x", &scale[i].x, -20.0f, 20.0f);
                        ImGui::Text("y");
                        ImGui::InputFloat("y", &scale[i].y, -20.0f, 20.0f);
                        ImGui::Text("z");
                        ImGui::InputFloat("z", &scale[i].z, -20.0f, 20.0f);

                        ImGui::TreePop();
                    }

                    ImGui::TreePop();
                }

                //rotate�̖�
                if (ImGui::TreeNode("rotate")) {

                    //Rotate�Z�b�g
                    ImGui::SliderFloat("x", &rotate[i].x, 0.0f, 360.0f);
                    ImGui::SliderFloat("y", &rotate[i].y, 0.0f, 360.0f);
                    ImGui::SliderFloat("z", &rotate[i].z, 0.0f, 360.0f);

                    if (ImGui::TreeNode("rotate")) {

                        ImGui::Text("x");
                        ImGui::InputFloat("x", &rotate[i].x, -20.0f, 20.0f);
                        ImGui::Text("y");
                        ImGui::InputFloat("y", &rotate[i].y, -20.0f, 20.0f);
                        ImGui::Text("z");
                        ImGui::InputFloat("z", &rotate[i].z, -20.0f, 20.0f);

                        ImGui::TreePop();
                    }

                    ImGui::TreePop();
                }

                if (ImGui::TreeNode("StageSave")) {

                    //�t�@�C���l�[�����͗�
                    static char text2[MAX_OBJECT_SIZE][50] = {};

                    //���͂��ꂽ������text1�Ɋi�[
                    ImGui::InputText("ObjName", text2[i], sizeof(text2[i]));

                    if (ImGui::Button("Save"))
                    {
                        BasicPos = { pos[i] };
                        BasicRotate = { rotate[i] };
                        BasicScale = { scale[i] };

                        const char* fileName = "Stage/Tutorial/StageInformation/TutorialStage1.txt";
                        std::ofstream ofs;
                        ofs.open(fileName, std::ios::app);

                        ofs << std::endl;

                        ofs << text1[i] << "," <<text2[i] << "," << pos[i].x << "," << pos[i].y << "," << pos[i].z << ","
                            << rotate[i].x << "," << rotate[i].y << "," << rotate[i].z << ","
                            << scale[i].x << "," << scale[i].y << "," << scale[i].z;

                        ofs.close();
                    }
                    ImGui::TreePop();
                }

                //�E�B���h�E�폜
                if (ImGui::Button("close"))
                {
                    status[i]++;
                }
            }

            ImGui::End();
        }

        //�`�悳���
        if (status[i] >= 1)
        {
            pNewObject[i]->SetPosition(pos[i]);
            pNewObject[i]->SetRotate(rotate[i]);
            pNewObject[i]->SetScale(scale[i]);
        }
    }
}

void ImGuiSet::CreateSigeboard()
{
    //�e�I�u�W�F�N�g�̏��
    static int Sstatus[MAX_OBJECT_SIZE] = {};
    static Signboard* SpNewObject[MAX_OBJECT_SIZE];
    static XMFLOAT3 Spos[MAX_OBJECT_SIZE];
    static XMFLOAT3 Srotate[MAX_OBJECT_SIZE];
    static XMFLOAT3 Sscale[MAX_OBJECT_SIZE];
    static XMFLOAT3 SBasicPos = pPlayer_->GetPosition();
    static XMFLOAT3 SBasicRotate = pPlayer_->GetRotate();
    static XMFLOAT3 SBasicScale = pPlayer_->GetScale();

    //Create3D�����������E�B���h�E�����@
    for (int i = 0; i < SigeboardCount; i++)
    {
        if (Sstatus[i] == 1 || Sstatus[i] == 0)
        {
            //i��FBX�̌��ɂ���
            char name[16];
            sprintf_s(name, "FBX %d", i);

            //window���
            ImGui::Begin(name);

            //�t�@�C���l�[�����͗�
            static char Stext1[MAX_OBJECT_SIZE][50] = {};

            //���͂��ꂽ������text1�Ɋi�[
            ImGui::InputText("FBX filename", Stext1[i], sizeof(Stext1[i]));

            //���[�h�{�^��
            if (ImGui::Button("Load"))
            {
                //�����܂��������[�h���ĂȂ�������
                if (Sstatus[i] == 0)
                {

                    //���[�h�����I�u�W�F�N�g�ɕK�v�ȃg�����X�t�H�[����p��
                    Transform t;

                    Spos[i] = SBasicPos;
                    Srotate[i] = SBasicRotate;
                    Sscale[i] = SBasicScale;

                    ////�v�b�V�����邽�߂�pair�^�����
                    ////first->���[�h�������f���ԍ�
                    ////second->���[�h�������f����transform
                    //std::pair<int, Transform> a(Model::Load(text1[i]), t);
                    //assert(a.first > 0);

                    ////vector�Ɋi�[����
                    //obj.push_back(a);

                    SpNewObject[i] = new Signboard(this, Stext1[i], "");
                    if (GetParent() != nullptr)
                    {
                        this->PushBackChild(SpNewObject[i]);
                    }
                    SpNewObject[i]->Initialize();

                    //status�v���X
                    Sstatus[i]++;

                }
            }

            //��񃍁[�h���Ă�����
            if (Sstatus[i] == 1)
            {

                //Position�̖�
                if (ImGui::TreeNode("position")) {

                    //Position�Z�b�g
                    ImGui::SliderFloat("x", &Spos[i].x, -200.0f, 200.0f);
                    ImGui::SliderFloat("y", &Spos[i].y, -200.0f, 200.0f);
                    ImGui::SliderFloat("z", &Spos[i].z, -200.0f, 200.0f);

                    if (ImGui::TreeNode("InputPosition")) {

                        ImGui::Text("x");
                        ImGui::InputFloat("x", &Spos[i].x, -20.0f, 20.0f);
                        ImGui::Text("y");
                        ImGui::InputFloat("y", &Spos[i].y, -20.0f, 20.0f);
                        ImGui::Text("z");
                        ImGui::InputFloat("z", &Spos[i].z, -20.0f, 20.0f);

                        ImGui::TreePop();
                    }

                    ImGui::TreePop();
                }

                //Scale�̖�
                if (ImGui::TreeNode("scale")) {

                    //Scale�Z�b�g
                    ImGui::SliderFloat("x", &Sscale[i].x, -20.0f, 20.0f);
                    ImGui::SliderFloat("y", &Sscale[i].y, -20.0f, 20.0f);
                    ImGui::SliderFloat("z", &Sscale[i].z, -20.0f, 20.0f);

                    if (ImGui::TreeNode("InputScale")) {

                        ImGui::Text("x");
                        ImGui::InputFloat("x", &Sscale[i].x, -20.0f, 20.0f);
                        ImGui::Text("y");
                        ImGui::InputFloat("y", &Sscale[i].y, -20.0f, 20.0f);
                        ImGui::Text("z");
                        ImGui::InputFloat("z", &Sscale[i].z, -20.0f, 20.0f);

                        ImGui::TreePop();
                    }

                    ImGui::TreePop();
                }

                //rotate�̖�
                if (ImGui::TreeNode("rotate")) {

                    //Rotate�Z�b�g
                    ImGui::SliderFloat("x", &Srotate[i].x, 0.0f, 360.0f);
                    ImGui::SliderFloat("y", &Srotate[i].y, 0.0f, 360.0f);
                    ImGui::SliderFloat("z", &Srotate[i].z, 0.0f, 360.0f);

                    if (ImGui::TreeNode("rotate")) {

                        ImGui::Text("x");
                        ImGui::InputFloat("x", &Srotate[i].x, -20.0f, 20.0f);
                        ImGui::Text("y");
                        ImGui::InputFloat("y", &Srotate[i].y, -20.0f, 20.0f);
                        ImGui::Text("z");
                        ImGui::InputFloat("z", &Srotate[i].z, -20.0f, 20.0f);

                        ImGui::TreePop();
                    }

                    ImGui::TreePop();
                }

                if (ImGui::TreeNode("StageSave")) {

                    //�t�@�C���l�[�����͗�
                    static char Stext2[MAX_OBJECT_SIZE][50] = {};

                    //���͂��ꂽ������text1�Ɋi�[
                    ImGui::InputText("ObjName", Stext2[i], sizeof(Stext2[i]));

                    if (ImGui::Button("Save"))
                    {
                        SBasicPos = { Spos[i] };
                        SBasicRotate = { Srotate[i] };
                        SBasicScale = { Sscale[i] };

                        const char* fileName = "Stage/Tutorial/StageInformation/TutorialStage1.txt";
                        std::ofstream ofs;
                        ofs.open(fileName, std::ios::app);

                        ofs << std::endl;

                        ofs << Stext1[i] << "," << Stext2[i] << "," << Spos[i].x << "," << Spos[i].y << "," << Spos[i].z << ","
                            << Srotate[i].x << "," << Srotate[i].y << "," << Srotate[i].z << ","
                            << Sscale[i].x << "," << Sscale[i].y << "," << Sscale[i].z;

                        ofs.close();
                    }
                    ImGui::TreePop();
                }

                //�E�B���h�E�폜
                if (ImGui::Button("close"))
                {
                    Sstatus[i]++;
                }
            }

            ImGui::End();
        }

        //�`�悳���
        if (Sstatus[i] >= 1)
        {
            SpNewObject[i]->SetPosition(Spos[i]);
            SpNewObject[i]->SetRotate(Srotate[i]);
            SpNewObject[i]->SetScale(Sscale[i]);
        }
    }
}

//�J��
void ImGuiSet::Release()
{
}

void ImGuiSet::StartUpdate()
{
    pPlayer_ = (Player*)FindObject("Player");
}

void ImGuiSet::CreateStage(std::string filename)
{
    static const char* fileName = filename.c_str();
    static std::ifstream ifs(fileName);

    std::string buf;
    std::string data[11] = {""};

    int sum = 0;

    while (!ifs.eof())
    {
        std::getline(ifs, buf);
        
        for(int i = 0; i < buf.size(); i++)
        {
            if (buf[i] != ',')
            {
                data[sum] += buf[i];
            }
            else
                sum++;
        }

        std::string ModelPathName = data[0];
        std::string Name = data[1];

        Transform t;

        t.position_ = { std::stof(data[2]),std::stof(data[3]),std::stof(data[4]) };
        t.rotate_ = { std::stof(data[5]),std::stof(data[6]),std::stof(data[7]) };
        t.scale_ = { std::stof(data[8]),std::stof(data[9]),std::stof(data[10]) };

        InstantiateString(ModelPathName,Name, t);


        for (int i = 0; i < 11; i++)
        {
            data[i] = "";
        }
        sum = 0;
    }

    
}

void ImGuiSet::InstantiateString(std::string ModelPathName, std::string inName,Transform t)
{

    /////////////////////Mob///////////////////////

    if (inName == "Mob")
    {
        Mob* pNewObject = new Mob(this, ModelPathName,inName);
        if (GetParent() != nullptr)
        {
            this->GetParent()->PushBackChild(pNewObject);
        }
        pNewObject->SetTransform(t);
        pNewObject->Initialize();
    }

    if (inName == "MainMob")
    {
        MainMob* pNewObject = new MainMob(this, ModelPathName, inName);
        if (GetParent() != nullptr)
        {
            this->GetParent()->PushBackChild(pNewObject);
        }
        pNewObject->SetTransform(t);
        pNewObject->Initialize();
    }

    /////////////////////Gimmick///////////////////////

    if (inName == "Coin")
    {
        Coin* pNewObject = new Coin(this, ModelPathName, inName);
        if (GetParent() != nullptr)
        {
            this->GetParent()->PushBackChild(pNewObject);
        }
        pNewObject->SetTransform(t);
        pNewObject->Initialize();
    }
    if (inName == "Warp" || inName == "Warp1")
    {
        Warp* pNewObject = new Warp(this, ModelPathName, "Warp");
        if (GetParent() != nullptr)
        {
            this->GetParent()->PushBackChild(pNewObject);
        }
        pNewObject->SetTransform(t);
        pNewObject->Initialize();

        if (inName == "Warp1")pNewObject->SetNumber(1);
    }
    if (inName == "Signboard")
    {
        Signboard* pNewObject = new Signboard(this, ModelPathName, "Signboard");
        if (GetParent() != nullptr)
        {
            this->GetParent()->PushBackChild(pNewObject);
        }
        pNewObject->SetTransform(t);
        pNewObject->Initialize();
    }

    /////////////////////Block///////////////////////

    if (inName == "ItemBlock" || inName == "ItemBlock1")
    {

        ItemBlock* pNewObject = new ItemBlock(this, ModelPathName, "ItemBlock");
        if (GetParent() != nullptr)
        {
            this->GetParent()->PushBackChild(pNewObject);
        }
        pNewObject->SetTransform(t);
        pNewObject->Initialize();

        //��]����悤�ɐݒ�
        if(inName == "ItemBlock1")pNewObject->SetStatus(1);

        //�u���b�N�Ȃ̂Œǉ�
        tBlock.push_back(pNewObject);
    }
    if (inName == "BrickBlock")
    {

        BrickBlock* pNewObject = new BrickBlock(this, ModelPathName, "BrickBlock");
        if (GetParent() != nullptr)
        {
            this->GetParent()->PushBackChild(pNewObject);
        }
        pNewObject->SetTransform(t);
        pNewObject->Initialize();

        //�u���b�N�Ȃ̂Œǉ�
        tBlock.push_back(pNewObject);
    }
    if (inName == "NormalBlock")
    {

        NormalBlock* pNewObject = new NormalBlock(this, ModelPathName, "NormalBlock");
        if (GetParent() != nullptr)
        {
            this->GetParent()->PushBackChild(pNewObject);
        }
        pNewObject->SetTransform(t);
        pNewObject->Initialize();

        //�u���b�N�Ȃ̂Œǉ�
        tBlock.push_back(pNewObject);
    }
    if (inName == "TransparentBlock")
    {

        TransparentBlock* pNewObject = new TransparentBlock(this, ModelPathName, "TransparentBlock");
        if (GetParent() != nullptr)
        {
            this->GetParent()->PushBackChild(pNewObject);
        }
        pNewObject->SetTransform(t);
        pNewObject->Initialize();

        //�u���b�N�Ȃ̂Œǉ�
        tBlock.push_back(pNewObject);
    }

    /////////////////////Enemy///////////////////////

    if (inName == "Enemy")
    {
        Enemy* pNewObject = new Enemy(this, ModelPathName, inName);
        if (GetParent() != nullptr)
        {
            this->GetParent()->PushBackChild(pNewObject);
        }
        pNewObject->SetTransform(t);
        pNewObject->Initialize();
    }

    if (inName == "DropEnemy")
    {
        DropEnemy* pNewObject = new DropEnemy(this, ModelPathName, inName);
        if (GetParent() != nullptr)
        {
            this->GetParent()->PushBackChild(pNewObject);
        }
        pNewObject->SetTransform(t);
        pNewObject->Initialize();
    }

    if (inName == "PigEnemy")
    {
        PigEnemy* pNewObject = new PigEnemy(this, ModelPathName, inName);
        if (GetParent() != nullptr)
        {
            this->GetParent()->PushBackChild(pNewObject);
        }
        pNewObject->SetTransform(t);
        pNewObject->Initialize();
    }
}

