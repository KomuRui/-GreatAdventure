#include "Image.h"
#include "Input.h"
#include "ImGuiSet.h"
#include "Model.h"
#include "SphereCollider.h"
#include "..\imgui\\imgui.h"
#include "..\imgui\\imgui_impl_win32.h"
#include "..\imgui\\imgui_impl_dx11.h"
#include "../Mob.h"
#include "../Gimmick/Signboard.h"
#include "../Image/ImageBase.h"
#include "SceneManager.h"
#include <fstream>
#include <vector>

//定数
namespace
{
    static const int MAX_DEBUG_LOG_NUM = 1000; //デバッグログの最大個数
}

/// <summary>
/// Debug用のUIを表示する
/// </summary>
namespace ImGuiSet
{
    ////////////////////////////////////ステージ作成用ImGui///////////////////////////////////////

    //表示させたオブジェクトを格納する場所
    //first->モデル番号
    //second->モデル番号ごとのトランスフォーム
    std::vector<std::pair<int, Transform>>obj_;

    //first->作ったかどうか
    //second->何個作ったか
    std::pair<bool, int> create3D_;               //3Dオブジェクト
    std::pair<bool, int> createSigeboard_;        //看板
    std::pair<bool, int> createCameraTransition_; //カメラ遷移
    std::pair<bool, int> createImage_;            //画像

    //各シーンのステージ情報が入ってるファイルのパス
    const char* stageInfoFilePath_[SCENE_ID_MAX];

    //////////////////////////////ステージのオブジェクトのトランスフォーム表示////////////////////////////

    //オブジェクトの数
    int objectCount_;

    //////////////////////////////////////ログ表示///////////////////////////////////////

    /// <summary>
    ///ログ表示するためのvector
    /// </summary>
    ///first->変数の名前
    ///second->値
    std::vector<std::pair<std::string, std::string>> variable_;

    //初期化
    void ImGuiSet::Initialize()
    {
        //各オブジェ作るのに必要な初期化
        ARGUMENT_INITIALIZE(create3D_.first, false);
        ARGUMENT_INITIALIZE(create3D_.second, ZERO);
        ARGUMENT_INITIALIZE(createSigeboard_.first, false);
        ARGUMENT_INITIALIZE(createSigeboard_.second, ZERO);
        ARGUMENT_INITIALIZE(createCameraTransition_.first, false);
        ARGUMENT_INITIALIZE(createCameraTransition_.second, ZERO);
        ARGUMENT_INITIALIZE(createImage_.first, false);
        ARGUMENT_INITIALIZE(createImage_.second, ZERO);
        ARGUMENT_INITIALIZE(objectCount_, ZERO);

        //各シーンのステージ情報が入ってるファイルのパス設定
        stageInfoFilePath_[SCENE_ID_TITLE] = "Stage/Title/StageInformation/TitleScene1.txt";
        stageInfoFilePath_[SCENE_ID_USER_SELECT] = "Stage/UserSelect/StageInformation/UserSelectScene1.txt";
        stageInfoFilePath_[SCENE_ID_TUTORIAL1] = "Stage/Tutorial/StageInformation/TutorialStage1.txt";
        stageInfoFilePath_[SCENE_ID_TUTORIAL2] = "Stage/Tutorial/StageInformation/TutorialStage2.txt";
        stageInfoFilePath_[SCENE_ID_HOME] = "Stage/Home/StageInformation/HomeStage.txt";
        stageInfoFilePath_[SCENE_ID_WORLD1] = "Stage/World/World1/StageInformation/WorldStage1.txt";
    }

    //描画
    void ImGuiSet::Draw()
    {
        {
            //Imguiスタート
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
        }

        //ステージ作成用UI
        StageCreater();

        //ステージオブジェのトランスフォームすべて表示するImGuiを表示
        StageObjImGuiDisplay();

        //デバッグ用のログ表示
        DebugLogManager();

        {
            ImGui::Render();
            //描画
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        }
    }

    ////////////////////////////////////ステージ作成用ImGui///////////////////////////////////////

    //ステージ作成するImGuiのUIを出してくれる
    void ImGuiSet::StageCreater()
    {
        //window作る
        ImGui::Begin("StageCreater");

        //3Dを作るボタン
        if (ImGui::Button("Create3D"))
        {
            create3D_.first = true;
            create3D_.second++;
        }

        //看板を作るボタン
        if (ImGui::Button("CreateSigeboard"))
        {
            createSigeboard_.first = true;
            createSigeboard_.second++;
        }

        //カメラボタン
        if (ImGui::Button("CreateCameraTransition"))
        {
            createCameraTransition_.first = true;
            createCameraTransition_.second++;
        }

        //画像ボタン
        if (ImGui::Button("CreateImage"))
        {
            createImage_.first = true;
            createImage_.second++;
        }

        //flagがtrueなら関数を呼び出す
        if (create3D_.first)
        {
            Create3D();
        }

        //flagがtrueなら関数を呼び出す
        if (createSigeboard_.first)
        {
            CreateSigeboard();
        }

        //flagがtrueなら関数を呼び出す
        if (createCameraTransition_.first)
        {
            CreateCameraTransition();
        }

        //flagがtrueなら関数を呼び出す
        if (createImage_.first)
        {
            CreateImage();
        }

        ImGui::End();
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
        for (int i = 0; i < create3D_.second; i++)
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
                            pos[i] = XMFLOAT3(0, 0, 0);
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

                        pNewObject[i] = new Mob(GameManager::GetpSceneManager(), text1[i], "");
                        if (GameManager::GetpSceneManager()->GetParent() != nullptr)
                        {
                            GameManager::GetpSceneManager()->PushBackChild(pNewObject[i]);
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

                            const char* fileName = stageInfoFilePath_[GameManager::GetpSceneManager()->GetSceneId()];
                            std::ofstream ofs;
                            ofs.open(fileName, std::ios::app);

                            ofs << std::endl;

                            ofs << text1[i] << "," << text2[i] << "," << pos[i].x << "," << pos[i].y << "," << pos[i].z << ","
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
        for (int i = 0; i < createSigeboard_.second; i++)
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

                        SpNewObject[i] = new Signboard(GameManager::GetpSceneManager(), Stext1[i], "");
                        if (GameManager::GetpSceneManager()->GetParent() != nullptr)
                        {
                            GameManager::GetpSceneManager()->PushBackChild(SpNewObject[i]);
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

                            const char* fileName = stageInfoFilePath_[GameManager::GetpSceneManager()->GetSceneId()];
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
        for (int i = 0; i < createCameraTransition_.second; i++)
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

                        CpNewObject[i] = new Mob(GameManager::GetpSceneManager(), text1[i], "");
                        if (GameManager::GetpSceneManager()->GetParent() != nullptr)
                        {
                            GameManager::GetpSceneManager()->PushBackChild(CpNewObject[i]);
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

                            const char* fileName = stageInfoFilePath_[GameManager::GetpSceneManager()->GetSceneId()];
                            std::ofstream ofs;
                            ofs.open(fileName, std::ios::app);

                            ofs << std::endl;

                            ofs << text1[i] << "," << text2[i] << "," << Cpos[i].x << "," << Cpos[i].y << "," << Cpos[i].z << ","
                                << CcameraTar[i].x << "," << CcameraTar[i].y << "," << CcameraTar[i].z << ","
                                << CcolliderSize[i].x * 2 << "," << CcolliderSize[i].y * 2 << "," << CcolliderSize[i].z * 2 << ","
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
        //各画像の状態
        static int Istatus[MAX_OBJECT_SIZE] = {};
        static ImageBase* IpNewObject[MAX_OBJECT_SIZE];
        static XMFLOAT3 Ipos[MAX_OBJECT_SIZE];
        static XMFLOAT3 Irotate[MAX_OBJECT_SIZE];
        static XMFLOAT3 Iscale[MAX_OBJECT_SIZE];

        //Create3Dを押した分ウィンドウを作る　
        for (int i = 0; i < createImage_.second; i++)
        {
            if (Istatus[i] == 1 || Istatus[i] == 0)
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
                    if (Istatus[i] == 0)
                    {

                        //ロードしたオブジェクトに必要なトランスフォームを用意
                        Transform t;

                        Ipos[i] = XMFLOAT3(0, 0, 0);
                        Irotate[i] = XMFLOAT3(0, 0, 0);
                        Iscale[i] = XMFLOAT3(1, 1, 1);

                        //プッシュするためにpair型を作る
                        //first->ロードしたモデル番号
                        //second->ロードしたモデルのtransform
                        std::pair<int, Transform> a(Image::Load(text1[i]), t);
                        assert(a.first > 0);

                        //vectorに格納する
                        obj_.push_back(a);

                        IpNewObject[i] = new ImageBase(GameManager::GetpSceneManager(), text1[i], "");
                        if (GameManager::GetpSceneManager()->GetParent() != nullptr)
                        {
                            GameManager::GetpSceneManager()->PushBackChild(IpNewObject[i]);
                        }
                        IpNewObject[i]->Initialize();

                        //statusプラス
                        Istatus[i]++;

                    }
                }

                //一回ロードしていたら
                if (Istatus[i] == 1)
                {

                    //Positionの木
                    if (ImGui::TreeNode("position")) {

                        //Positionセット
                        ImGui::SliderFloat("x", &Ipos[i].x, -200.0f, 200.0f);
                        ImGui::SliderFloat("y", &Ipos[i].y, -200.0f, 200.0f);
                        ImGui::SliderFloat("z", &Ipos[i].z, -200.0f, 200.0f);

                        if (ImGui::TreeNode("InputPosition")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &Ipos[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &Ipos[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &Ipos[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //Scaleの木
                    if (ImGui::TreeNode("scale")) {

                        //Scaleセット
                        ImGui::SliderFloat("x", &Iscale[i].x, -20.0f, 20.0f);
                        ImGui::SliderFloat("y", &Iscale[i].y, -20.0f, 20.0f);
                        ImGui::SliderFloat("z", &Iscale[i].z, -20.0f, 20.0f);

                        if (ImGui::TreeNode("InputScale")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &Iscale[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &Iscale[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &Iscale[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //rotateの木
                    if (ImGui::TreeNode("rotate")) {

                        //Rotateセット
                        ImGui::SliderFloat("x", &Irotate[i].x, 0.0f, 360.0f);
                        ImGui::SliderFloat("y", &Irotate[i].y, 0.0f, 360.0f);
                        ImGui::SliderFloat("z", &Irotate[i].z, 0.0f, 360.0f);

                        if (ImGui::TreeNode("rotate")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &Irotate[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &Irotate[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &Irotate[i].z, -20.0f, 20.0f);

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

                            const char* fileName = stageInfoFilePath_[GameManager::GetpSceneManager()->GetSceneId()];
                            std::ofstream ofs;
                            ofs.open(fileName, std::ios::app);

                            ofs << std::endl;

                            ofs << text1[i] << "," << text2[i] << "," << Ipos[i].x << "," << Ipos[i].y << "," << Ipos[i].z << ","
                                << Irotate[i].x << "," << Irotate[i].y << "," << Irotate[i].z << ","
                                << Iscale[i].x << "," << Iscale[i].y << "," << Iscale[i].z;

                            ofs.close();
                        }
                        ImGui::TreePop();
                    }

                    //ウィンドウ削除
                    if (ImGui::Button("close"))
                    {
                        Istatus[i]++;
                    }
                }

                ImGui::End();
            }

            //描画される
            if (Istatus[i] >= 1)
            {
                IpNewObject[i]->SetPosition(Ipos[i]);
                IpNewObject[i]->SetScale(Iscale[i]);
            }
        }

    }

    //////////////////////////////ステージのオブジェクトのトランスフォーム表示////////////////////////////

    //ステージオブジェのトランスフォームすべて表示するImGuiを表示
    void ImGuiSet::StageObjImGuiDisplay()
    {
        //window作る
        ImGui::Begin("StageObjTransformDisplay");

        //ステージオブジェのトランスフォームすべて表示
        StageObjTransformDisplay(GameManager::GetpSceneManager());

        //オブジェクトの数0に初期化
        ARGUMENT_INITIALIZE(objectCount_, ZERO);

        //終わり
        ImGui::End();
    }

    //ステージオブジェのトランスフォームすべて表示
    void ImGuiSet::StageObjTransformDisplay(GameObject* pObj)
    {
        //もしnullなら抜ける
        if (pObj == nullptr) return;

        //オブジェクトの数増やす
        objectCount_++;

        //オブジェクトの名前をもともとの名前プラスobjectCount_した名前にする
        std::string objName = pObj->GetObjectName() + std::to_string(objectCount_);

        //オブジェクトの名前で名前表示する
        if (ImGui::TreeNode(objName.c_str()))
        {
            //位置
            XMFLOAT3 pos = { pObj->GetPosition().x,pObj->GetPosition().y ,pObj->GetPosition().z };
            ImGui::InputFloat("x", &pos.x, -2000.0f, 2000.0f);
            ImGui::InputFloat("y", &pos.y, -2000.0f, 2000.0f);
            ImGui::InputFloat("z", &pos.z, -2000.0f, 2000.0f);
            pObj->SetPosition(pos);

            //回転
            XMFLOAT3 rotate = { pObj->GetRotate().x,pObj->GetRotate().y ,pObj->GetRotate().z };
            ImGui::InputFloat("x", &rotate.x, -2000.0f, 2000.0f);
            ImGui::InputFloat("y", &rotate.y, -2000.0f, 2000.0f);
            ImGui::InputFloat("z", &rotate.z, -2000.0f, 2000.0f);
            pObj->SetRotate(rotate);

            //拡大・縮小
            XMFLOAT3 scale = { pObj->GetScale().x,pObj->GetScale().y ,pObj->GetScale().z };
            ImGui::InputFloat("x", &scale.x, -2000.0f, 2000.0f);
            ImGui::InputFloat("y", &scale.y, -2000.0f, 2000.0f);
            ImGui::InputFloat("z", &scale.z, -2000.0f, 2000.0f);
            pObj->SetScale(scale);


            ImGui::TreePop();
        }

        for (auto itr = pObj->GetChildList()->begin(); itr != pObj->GetChildList()->end(); itr++)
        {
            StageObjTransformDisplay(*itr);
        }
    }

    //////////////////////////////////////ログ表示///////////////////////////////////////

    //デバッグログを管理する(ImGuiはここで表示する)
    void ImGuiSet::DebugLogManager()
    {
        //window作る
        ImGui::Begin("DebugLog");

        //ログ表示
        for (auto i = variable_.rbegin(); i != variable_.rend(); i++)
        {
            ImGui::Text((*i).first.c_str());
            ImGui::SameLine();
            ImGui::Text((*i).second.c_str());
        }

        //サイズが1000以上言ったら削除
        if (variable_.size() >= MAX_DEBUG_LOG_NUM)
            variable_.clear();

        //終わり
        ImGui::End();
    }

    //任意の値を表示してくれる
    void ImGuiSet::DebugLog(std::string text, int num)
    {
        std::pair<std::string, std::string> a;

        ARGUMENT_INITIALIZE(a.first, text);
        ARGUMENT_INITIALIZE(a.second, std::to_string(num));

        variable_.push_back(a);
    }
    void ImGuiSet::DebugLog(std::string text, float num)
    {
        std::pair<std::string, std::string> a;

        ARGUMENT_INITIALIZE(a.first, text);
        ARGUMENT_INITIALIZE(a.second, std::to_string(num));

        variable_.push_back(a);
    }
    void ImGuiSet::DebugLog(std::string text, bool num)
    {
        std::pair<std::string, std::string> a;

        ARGUMENT_INITIALIZE(a.first, text);

        //true,falseで変える
        if (num)
        {
            ARGUMENT_INITIALIZE(a.second, "true");
        }
        else
            ARGUMENT_INITIALIZE(a.second, "false");

        
        variable_.push_back(a);
    }
    void ImGuiSet::DebugLog(std::string text, XMFLOAT3 num)
    {
        std::pair<std::string, std::string> a;

        ARGUMENT_INITIALIZE(a.first, text);
        ARGUMENT_INITIALIZE(a.second, "x " + std::to_string(num.x) + " y " + std::to_string(num.y) + " z " + std::to_string(num.z));

        variable_.push_back(a);
    }
    void ImGuiSet::DebugLog(std::string text, std::string str)
    {
        std::pair<std::string, std::string> a;

        ARGUMENT_INITIALIZE(a.first, text);
        ARGUMENT_INITIALIZE(a.second, str);

        variable_.push_back(a);
    }


    //開放
    void ImGuiSet::Release()
    {
    }
}