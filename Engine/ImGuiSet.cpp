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

//�R���X�g���N�^
ImGuiSet::ImGuiSet(GameObject* parent)
	: GameObject(parent, "ImGuiSet"), Create3Dflag(false), ObjectCount(0)
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

    /*XMFLOAT3 pos = { pStage->GetPosition().x,pStage->GetPosition().y,pStage->GetPosition().z };*/

   /* ImGui::Text("x");
    ImGui::InputFloat("x", &pos.x, -2000000.0f, 2000000.0f);
    ImGui::Text("y");
    ImGui::InputFloat("y", &pos.y, -2000000.0f, 2000000.0f);
    ImGui::Text("z");
    ImGui::InputFloat("z", &pos.z, -2000000.0f, 2000000.0f);*/

    //3D�����{�^��
    if (ImGui::Button("Create3D"))
    {
        Create3Dflag = true;
        ObjectCount++;
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

    ImGui::End();

    ImGui::Render();
    //�`��
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiSet::Create3D()
{
    //�e�I�u�W�F�N�g�̏��
    static int status[MAX_OBJECT_SIZE] = {};

    //Create3D�����������E�B���h�E�����
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

                    //�v�b�V�����邽�߂�pair�^�����
                    //first->���[�h�������f���ԍ�
                    //second->���[�h�������f����transform
                    std::pair<int, Transform> a(Model::Load(text1[i]), t);
                    assert(a.first > 0);

                    //vector�Ɋi�[����
                    obj.push_back(a);

                    //status�v���X
                    status[i]++;
                }
            }

            //��񃍁[�h���Ă�����
            if (status[i] == 1)
            {
                SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.2f);
                static XMFLOAT3 pos = { 0,0,0 };
                static XMFLOAT3 pos2 = { 0,0,0 };

                //Position�̖�
                if (ImGui::TreeNode("position")) {

                    //Position�Z�b�g
                    ImGui::SliderFloat("x", &obj[i].second.position_.x, -20.0f, 20.0f);
                    ImGui::SliderFloat("y", &obj[i].second.position_.y, -20.0f, 20.0f);
                    ImGui::SliderFloat("z", &obj[i].second.position_.z, -20.0f, 20.0f);

                    ImGui::TreePop();
                }

                //Scale�̖�
                if (ImGui::TreeNode("scale")) {

                    //Scale�Z�b�g
                    ImGui::SliderFloat("x", &obj[i].second.scale_.x, -20.0f, 20.0f);
                    ImGui::SliderFloat("y", &obj[i].second.scale_.y, -20.0f, 20.0f);
                    ImGui::SliderFloat("z", &obj[i].second.scale_.z, -20.0f, 20.0f);

                    ImGui::TreePop();
                }

                //rotate�̖�
                if (ImGui::TreeNode("rotate")) {

                    //Rotate�Z�b�g
                    ImGui::SliderFloat("x", &obj[i].second.rotate_.x, 0.0f, 360.0f);
                    ImGui::SliderFloat("y", &obj[i].second.rotate_.y, 0.0f, 360.0f);
                    ImGui::SliderFloat("z", &obj[i].second.rotate_.z, 0.0f, 360.0f);

                    ImGui::TreePop();
                }

                if (ImGui::Button("Collsion"))
                {
                    AddCollider(collision);
                }

                //�����蔻��̒ǉ�
                if (ImGui::TreeNode("CollisionPos")) {

                    ImGui::SliderFloat("x", &pos.x, -20.0f, 20.0f);
                    ImGui::SliderFloat("y", &pos.y, -20.0f, 20.0f);
                    ImGui::SliderFloat("z", &pos.z, -20.0f, 20.0f);

                    if (ImGui::TreeNode("InputCollisionPos")) {

                        ImGui::Text("x");
                        ImGui::InputFloat("x", &pos2.x, -20.0f, 20.0f);
                        ImGui::Text("y");
                        ImGui::InputFloat("y", &pos2.y, -20.0f, 20.0f);
                        ImGui::Text("z");
                        ImGui::InputFloat("z", &pos2.z, -20.0f, 20.0f);

                        if (ImGui::Button("Save"))
                        pos = pos2;

                        ImGui::TreePop();
                    }

                    if (collision->GetColliderPos().x != pos.x || collision->GetColliderPos().y != pos.y || collision->GetColliderPos().z != pos.z)
                    {
                        collision->SetColliderPos(pos);
                        KillCollider(collision);
                        SphereCollider* collision = new SphereCollider(XMFLOAT3(pos), 1.2f);
                        AddCollider(collision);
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
                        const char* fileName = "TutorialStage1.txt";
                        std::ofstream ofs;
                        ofs.open(fileName, std::ios::app);

                        ofs << std::endl;

                        ofs << text1[i] << "," <<text2[i] << "," << obj[i].second.position_.x << "," << obj[i].second.position_.y << "," << obj[i].second.position_.z << ","
                            << obj[i].second.rotate_.x << "," << obj[i].second.rotate_.y << "," << obj[i].second.rotate_.z << ","
                            << obj[i].second.scale_.x << "," << obj[i].second.scale_.y << "," << obj[i].second.scale_.z;

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
            //�`��
            Model::Draw(obj[i].first);
            Model::SetTransform(obj[i].first, obj[i].second);
        }
    }
}

//�J��
void ImGuiSet::Release()
{
}

void ImGuiSet::StartUpdate()
{
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

        XMFLOAT3 pos = { std::stof(data[2]),std::stof(data[3]),std::stof(data[4]) };
        XMFLOAT3 rotate = { std::stof(data[5]),std::stof(data[6]),std::stof(data[7]) };
        XMFLOAT3 scale = { std::stof(data[8]),std::stof(data[9]),std::stof(data[10]) };

        InstantiateString(ModelPathName,Name, pos, rotate, scale);

        for (int i = 0; i < 11; i++)
        {
            data[i] = "";
        }
        sum = 0;
    }

    
}

void ImGuiSet::InstantiateString(std::string ModelPathName, std::string inName, XMFLOAT3 pos, XMFLOAT3 rotate, XMFLOAT3 scale)
{
    if (inName == "Mob")
    {
        Mob* pNewObject = new Mob(this, ModelPathName);
        if (GetParent() != nullptr)
        {
            this->PushBackChild(pNewObject);
        }
        pNewObject->Initialize();
        pNewObject->SetPosition(pos);
        pNewObject->SetRotate(rotate);
        pNewObject->SetScale(scale);
    }
}

