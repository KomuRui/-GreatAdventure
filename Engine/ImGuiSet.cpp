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
#include "../Gimmick/Signboard.h"


//コンストラクタ
ImGuiSet::ImGuiSet(GameObject* parent)
	: GameObject(parent, "ImGuiSet"), create3Dflag_(false), objectCount_(0), createSigeboardflag_(false),sigeboardCount_(0), createCameraTransitionflag_(false),cameraTransitionCount_(0)
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

    /*Player* pPlayer = (Player*)FindObject("Player");
    XMFLOAT3 pos = { pPlayer->GetPosition().x,pPlayer->GetPosition().y,pPlayer->GetPosition().z };

    ImGui::Text("x");
    ImGui::InputFloat("x", &pos.x, -2000000.0f, 2000000.0f);
    ImGui::Text("y");
    ImGui::InputFloat("y", &pos.y, -2000000.0f, 2000000.0f);
    ImGui::Text("z");
    ImGui::InputFloat("z", &pos.z, -2000000.0f, 2000000.0f);*/

    //3Dを作るボタン
    if (ImGui::Button("Create3D"))
    {
        create3Dflag_ = true;
        objectCount_++;
    }

    //看板を作るボタン
    if (ImGui::Button("CreateSigeboard"))
    {
        createSigeboardflag_ = true;
        sigeboardCount_++;
    }

    //カメラボタン
    if (ImGui::Button("CreateCameraTransition"))
    {
        createCameraTransitionflag_ = true;
        cameraTransitionCount_++;
    }


    //flagがtrueなら関数を呼び出す
    if (create3Dflag_)
    {
        Create3D();
    }

    //flagがtrueなら関数を呼び出す
    if (createSigeboardflag_)
    {
        CreateSigeboard();
    }

    //flagがtrueなら関数を呼び出す
    if (createCameraTransitionflag_)
    {
        CreateCameraTransition();
    }

    ImGui::End();

    ImGui::Render();
    //描画
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

//3Dオブジェクト作成
void ImGuiSet::Create3D()
{
    //各オブジェクトの状態
    static int status[MAX_OBJECT_SIZE] = {};
    static Mob* pNewObject[MAX_OBJECT_SIZE];
    static XMFLOAT3 pos[MAX_OBJECT_SIZE];
    static XMFLOAT3 rotate[MAX_OBJECT_SIZE];
    static XMFLOAT3 scale[MAX_OBJECT_SIZE];
      
    //Create3Dを押した分ウィンドウを作る　
    for (int i = 0; i < objectCount_; i++)
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

                    if (GameManager::GetpPlayer() != nullptr)
                    {
                        pos[i] = GameManager::GetpPlayer()->GetPosition();
                        rotate[i] = GameManager::GetpPlayer()->GetRotate();
                        scale[i] = GameManager::GetpPlayer()->GetScale();
                    }
                    else
                    {
                        pos[i] = XMFLOAT3(0,0,0);
                        rotate[i] = XMFLOAT3(0, 0, 0);
                        scale[i] = XMFLOAT3(1, 1, 1);
                    }

                    //プッシュするためにpair型を作る
                    //first->ロードしたモデル番号
                    //second->ロードしたモデルのtransform
                    std::pair<int, Transform> a(Model::Load(text1[i]), t);
                    assert(a.first > 0);

                    //vectorに格納する
                    obj_.push_back(a);

                    pNewObject[i] = new Mob(this, text1[i],"");
                    if (GetParent() != nullptr)
                    {
                        this->PushBackChild(pNewObject[i]);
                    }
                    pNewObject[i]->Initialize();

                    //statusプラス
                    status[i]++;

                }
            }

            //一回ロードしていたら
            if (status[i] == 1)
            {

                //Positionの木
                if (ImGui::TreeNode("position")) {

                    //Positionセット
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

                //Scaleの木
                if (ImGui::TreeNode("scale")) {

                    //Scaleセット
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

                //rotateの木
                if (ImGui::TreeNode("rotate")) {

                    //Rotateセット
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

                    //ファイルネーム入力欄
                    static char text2[MAX_OBJECT_SIZE][50] = {};

                    //入力された文字をtext1に格納
                    ImGui::InputText("ObjName", text2[i], sizeof(text2[i]));

                    if (ImGui::Button("Save"))
                    {

                        const char* fileName = "Stage/World/World1/StageInformation/WorldStage1.txt";
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
            pNewObject[i]->SetPosition(pos[i]);
            pNewObject[i]->SetAngle(rotate[i].y);
            pNewObject[i]->SetScale(scale[i]);
        }
    }
}

//看板作成
void ImGuiSet::CreateSigeboard()
{
    //各オブジェクトの状態
    static int Sstatus[MAX_OBJECT_SIZE] = {};
    static Signboard* SpNewObject[MAX_OBJECT_SIZE];
    static XMFLOAT3 Spos[MAX_OBJECT_SIZE];
    static XMFLOAT3 Srotate[MAX_OBJECT_SIZE];
    static XMFLOAT3 Sscale[MAX_OBJECT_SIZE];
    static XMFLOAT3 SBasicPos = GameManager::GetpPlayer()->GetPosition();
    static XMFLOAT3 SBasicRotate = GameManager::GetpPlayer()->GetRotate();
    static XMFLOAT3 SBasicScale = GameManager::GetpPlayer()->GetScale();

    //Create3Dを押した分ウィンドウを作る　
    for (int i = 0; i < sigeboardCount_; i++)
    {
        if (Sstatus[i] == 1 || Sstatus[i] == 0)
        {
            //iをFBXの後ろにたす
            char name[16];
            sprintf_s(name, "FBX %d", i);

            //window作る
            ImGui::Begin(name);

            //ファイルネーム入力欄
            static char Stext1[MAX_OBJECT_SIZE][50] = {};

            //入力された文字をtext1に格納
            ImGui::InputText("FBX filename", Stext1[i], sizeof(Stext1[i]));

            //ロードボタン
            if (ImGui::Button("Load"))
            {
                //もしまだ一回もロードしてなかったら
                if (Sstatus[i] == 0)
                {

                    //ロードしたオブジェクトに必要なトランスフォームを用意
                    Transform t;

                    Spos[i] = SBasicPos;
                    Srotate[i] = SBasicRotate;
                    Sscale[i] = SBasicScale;

                    ////プッシュするためにpair型を作る
                    ////first->ロードしたモデル番号
                    ////second->ロードしたモデルのtransform
                    //std::pair<int, Transform> a(Model::Load(text1[i]), t);
                    //assert(a.first > 0);

                    ////vectorに格納する
                    //obj.push_back(a);

                    SpNewObject[i] = new Signboard(this, Stext1[i], "");
                    if (GetParent() != nullptr)
                    {
                        this->PushBackChild(SpNewObject[i]);
                    }
                    SpNewObject[i]->Initialize();

                    //statusプラス
                    Sstatus[i]++;

                }
            }

            //一回ロードしていたら
            if (Sstatus[i] == 1)
            {

                //Positionの木
                if (ImGui::TreeNode("position")) {

                    //Positionセット
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

                //Scaleの木
                if (ImGui::TreeNode("scale")) {

                    //Scaleセット
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

                //rotateの木
                if (ImGui::TreeNode("rotate")) {

                    //Rotateセット
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

                    //ファイルネーム入力欄
                    static char Stext2[MAX_OBJECT_SIZE][50] = {};

                    //入力された文字をtext1に格納
                    ImGui::InputText("ObjName", Stext2[i], sizeof(Stext2[i]));

                    if (ImGui::Button("Save"))
                    {
                        SBasicPos = { Spos[i] };
                        SBasicRotate = { Srotate[i] };
                        SBasicScale = { Sscale[i] };

                        const char* fileName = "Stage/World/World1/StageInformation/WorldStage1.txt";
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

                //ウィンドウ削除
                if (ImGui::Button("close"))
                {
                    Sstatus[i]++;
                }
            }

            ImGui::End();
        }

        //描画される
        if (Sstatus[i] >= 1)
        {
            SpNewObject[i]->SetPosition(Spos[i]);
            SpNewObject[i]->SetRotate(Srotate[i]);
            SpNewObject[i]->SetScale(Sscale[i]);
        }
    }
}

//カメラの遷移作成(コライダーに当たったらカメラのポジション変える機能)
void ImGuiSet::CreateCameraTransition()
{
    //各オブジェクトの状態
    static int Cstatus[MAX_OBJECT_SIZE] = {};
    static Mob* CpNewObject[MAX_OBJECT_SIZE];
    static XMFLOAT3 Cpos[MAX_OBJECT_SIZE];
    static XMFLOAT3 CcameraPos[MAX_OBJECT_SIZE];
    static XMFLOAT3 CcameraTar[MAX_OBJECT_SIZE];
    static XMFLOAT3 CcolliderSize[MAX_OBJECT_SIZE];
    static XMFLOAT3 CBasicPos = GameManager::GetpPlayer()->GetPosition();
    static XMFLOAT3 CBasicRotate = GameManager::GetpPlayer()->GetRotate();
    static XMFLOAT3 CBasicScale = GameManager::GetpPlayer()->GetScale();

    //Create3Dを押した分ウィンドウを作る　
    for (int i = 0; i < cameraTransitionCount_; i++)
    {
        if (Cstatus[i] == 1 || Cstatus[i] == 0)
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
                if (Cstatus[i] == 0)
                {

                    //ロードしたオブジェクトに必要なトランスフォームを用意
                    Transform t;

                    Cpos[i] = CBasicPos;
                    CcameraTar[i] = CBasicRotate;
                    CcolliderSize[i] = CBasicScale;

                    //プッシュするためにpair型を作る
                    //first->ロードしたモデル番号
                    //second->ロードしたモデルのtransform
                    std::pair<int, Transform> a(Model::Load(text1[i]), t);
                    assert(a.first > 0);

                    //vectorに格納する
                    obj_.push_back(a);

                    CpNewObject[i] = new Mob(this, text1[i], "");
                    if (GetParent() != nullptr)
                    {
                        this->PushBackChild(CpNewObject[i]);
                    }
                    CpNewObject[i]->Initialize();

                    //statusプラス
                    Cstatus[i]++;

                }
            }

            //一回ロードしていたら
            if (Cstatus[i] == 1)
            {

                //Positionの木
                if (ImGui::TreeNode("position")) {

                    //Positionセット
                    ImGui::SliderFloat("x", &Cpos[i].x, -200.0f, 200.0f);
                    ImGui::SliderFloat("y", &Cpos[i].y, -200.0f, 200.0f);
                    ImGui::SliderFloat("z", &Cpos[i].z, -200.0f, 200.0f);

                    if (ImGui::TreeNode("InputPosition")) {

                        ImGui::Text("x");
                        ImGui::InputFloat("x", &Cpos[i].x, -200.0f, 200.0f);
                        ImGui::Text("y");
                        ImGui::InputFloat("y", &Cpos[i].y, -200.0f, 200.0f);
                        ImGui::Text("z");
                        ImGui::InputFloat("z", &Cpos[i].z, -200.0f, 200.0f);

                        ImGui::TreePop();
                    }

                    ImGui::TreePop();
                }

                //Positionの木
                if (ImGui::TreeNode("CameraPosition")) {

                    //Positionセット
                    ImGui::SliderFloat("x", &CcameraPos[i].x, -200.0f, 200.0f);
                    ImGui::SliderFloat("y", &CcameraPos[i].y, -200.0f, 200.0f);
                    ImGui::SliderFloat("z", &CcameraPos[i].z, -200.0f, 200.0f);

                    if (ImGui::TreeNode("CameraInputPosition")) {

                        ImGui::Text("x");
                        ImGui::InputFloat("x", &CcameraPos[i].x, -200.0f, 200.0f);
                        ImGui::Text("y");
                        ImGui::InputFloat("y", &CcameraPos[i].y, -200.0f, 200.0f);
                        ImGui::Text("z");
                        ImGui::InputFloat("z", &CcameraPos[i].z, -200.0f, 200.0f);

                        ImGui::TreePop();
                    }

                    ImGui::TreePop();
                }

                //Scaleの木
                if (ImGui::TreeNode("scale")) {

                    //Scaleセット
                    ImGui::SliderFloat("x", &CcolliderSize[i].x, -20.0f, 20.0f);
                    ImGui::SliderFloat("y", &CcolliderSize[i].y, -20.0f, 20.0f);
                    ImGui::SliderFloat("z", &CcolliderSize[i].z, -20.0f, 20.0f);

                    if (ImGui::TreeNode("InputScale")) {

                        ImGui::Text("x");
                        ImGui::InputFloat("x", &CcolliderSize[i].x, -20.0f, 20.0f);
                        ImGui::Text("y");
                        ImGui::InputFloat("y", &CcolliderSize[i].y, -20.0f, 20.0f);
                        ImGui::Text("z");
                        ImGui::InputFloat("z", &CcolliderSize[i].z, -20.0f, 20.0f);

                        ImGui::TreePop();
                    }

                    ImGui::TreePop();
                }

                //rotateの木
                if (ImGui::TreeNode("rotate")) {

                    //Rotateセット
                    ImGui::SliderFloat("x", &CcameraTar[i].x, 0.0f, 360.0f);
                    ImGui::SliderFloat("y", &CcameraTar[i].y, 0.0f, 360.0f);
                    ImGui::SliderFloat("z", &CcameraTar[i].z, 0.0f, 360.0f);

                    if (ImGui::TreeNode("rotate")) {

                        ImGui::Text("x");
                        ImGui::InputFloat("x", &CcameraTar[i].x, -20.0f, 20.0f);
                        ImGui::Text("y");
                        ImGui::InputFloat("y", &CcameraTar[i].y, -20.0f, 20.0f);
                        ImGui::Text("z");
                        ImGui::InputFloat("z", &CcameraTar[i].z, -20.0f, 20.0f);

                        ImGui::TreePop();
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
                        CBasicPos = { Cpos[i] };
                        CBasicRotate = { CcameraTar[i] };
                        CBasicScale = { CcolliderSize[i] };

                        const char* fileName = "Stage/World/World1/StageInformation/WorldStage1.txt";
                        std::ofstream ofs;
                        ofs.open(fileName, std::ios::app);

                        ofs << std::endl;

                        ofs << text1[i] << "," << text2[i] << "," << Cpos[i].x << "," << Cpos[i].y << "," << Cpos[i].z << ","
                            << CcameraTar[i].x << "," << CcameraTar[i].y << "," << CcameraTar[i].z << ","
                            << CcolliderSize[i].x * 2 << "," << CcolliderSize[i].y * 2<< "," << CcolliderSize[i].z * 2<< ","
                            << CcameraPos[i].x << "," << CcameraPos[i].y << "," << CcameraPos[i].z;

                        ofs.close();
                    }
                    ImGui::TreePop();
                }

                //ウィンドウ削除
                if (ImGui::Button("close"))
                {
                    Cstatus[i]++;
                }
            }

            ImGui::End();
        }

        //描画される
        if (Cstatus[i] >= 1)
        {
            CpNewObject[i]->SetPosition(Cpos[i]);
            CpNewObject[i]->SetRotate(CcameraTar[i]);
            CpNewObject[i]->SetScale(CcolliderSize[i]);
        }
    }
}

//画像作成
void ImGuiSet::CreateImage()
{

}

//開放
void ImGuiSet::Release()
{
}

void ImGuiSet::StartUpdate()
{
}
