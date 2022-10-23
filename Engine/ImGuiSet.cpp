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

//コンストラクタ
ImGuiSet::ImGuiSet(GameObject* parent)
	: GameObject(parent, "ImGuiSet"), Create3Dflag(false), ObjectCount(0)
{
}

//初期化
void ImGuiSet::Initialize()
{
}

//更新
void ImGuiSet::Update()
{
}

//描画
void ImGuiSet::Draw()
{
    //Imguiスタート
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    //window作る
    ImGui::Begin("StagePosition");

    /*XMFLOAT3 pos = { pStage->GetPosition().x,pStage->GetPosition().y,pStage->GetPosition().z };*/

   /* ImGui::Text("x");
    ImGui::InputFloat("x", &pos.x, -2000000.0f, 2000000.0f);
    ImGui::Text("y");
    ImGui::InputFloat("y", &pos.y, -2000000.0f, 2000000.0f);
    ImGui::Text("z");
    ImGui::InputFloat("z", &pos.z, -2000000.0f, 2000000.0f);*/

    //3Dを作るボタン
    if (ImGui::Button("Create3D"))
    {
        Create3Dflag = true;
        ObjectCount++;
    }

    //カメラボタン
    if (ImGui::Button("Camera"))
    {
    }

    //flagがtrueなら関数を呼び出す
    if (Create3Dflag)
    {
        Create3D();
    }

    ImGui::End();

    ImGui::Render();
    //描画
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiSet::Create3D()
{
    //各オブジェクトの状態
    static int status[MAX_OBJECT_SIZE] = {};

    //Create3Dを押した分ウィンドウを作る
    for (int i = 0; i < ObjectCount; i++)
    {
        if (status[i] == 1 || status[i] == 0)
        {
            //iをFBXの後ろにたす
            char name[16];
            sprintf_s(name, "FBX %d", i);

            //window作る
            ImGui::Begin(name);

            //ファイルネーム入力欄
            static char text1[MAX_OBJECT_SIZE][50] = {};

            //入力された文字をtext1に格納
            ImGui::InputText("FBX filename", text1[i], sizeof(text1[i]));

            //ロードボタン
            if (ImGui::Button("Load"))
            {
                //もしまだ一回もロードしてなかったら
                if (status[i] == 0)
                {

                    //ロードしたオブジェクトに必要なトランスフォームを用意
                    Transform t;

                    //プッシュするためにpair型を作る
                    //first->ロードしたモデル番号
                    //second->ロードしたモデルのtransform
                    std::pair<int, Transform> a(Model::Load(text1[i]), t);
                    assert(a.first > 0);

                    //vectorに格納する
                    obj.push_back(a);

                    //statusプラス
                    status[i]++;
                }
            }

            //一回ロードしていたら
            if (status[i] == 1)
            {
                SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.2f);
                static XMFLOAT3 pos = { 0,0,0 };
                static XMFLOAT3 pos2 = { 0,0,0 };

                //Positionの木
                if (ImGui::TreeNode("position")) {

                    //Positionセット
                    ImGui::SliderFloat("x", &obj[i].second.position_.x, -20.0f, 20.0f);
                    ImGui::SliderFloat("y", &obj[i].second.position_.y, -20.0f, 20.0f);
                    ImGui::SliderFloat("z", &obj[i].second.position_.z, -20.0f, 20.0f);

                    ImGui::TreePop();
                }

                //Scaleの木
                if (ImGui::TreeNode("scale")) {

                    //Scaleセット
                    ImGui::SliderFloat("x", &obj[i].second.scale_.x, -20.0f, 20.0f);
                    ImGui::SliderFloat("y", &obj[i].second.scale_.y, -20.0f, 20.0f);
                    ImGui::SliderFloat("z", &obj[i].second.scale_.z, -20.0f, 20.0f);

                    ImGui::TreePop();
                }

                //rotateの木
                if (ImGui::TreeNode("rotate")) {

                    //Rotateセット
                    ImGui::SliderFloat("x", &obj[i].second.rotate_.x, 0.0f, 360.0f);
                    ImGui::SliderFloat("y", &obj[i].second.rotate_.y, 0.0f, 360.0f);
                    ImGui::SliderFloat("z", &obj[i].second.rotate_.z, 0.0f, 360.0f);

                    ImGui::TreePop();
                }

                if (ImGui::Button("Collsion"))
                {
                    AddCollider(collision);
                }

                //当たり判定の追加
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

                    //ファイルネーム入力欄
                    static char text2[MAX_OBJECT_SIZE][50] = {};

                    //入力された文字をtext1に格納
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

                //ウィンドウ削除
                if (ImGui::Button("close"))
                {
                    status[i]++;
                }
            }

            ImGui::End();
        }

        //描画される
        if (status[i] >= 1)
        {
            //描画
            Model::Draw(obj[i].first);
            Model::SetTransform(obj[i].first, obj[i].second);
        }
    }
}

//開放
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

