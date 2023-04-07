#include "../ResourceManager/Image.h"
#include "../ResourceManager/CreateStage.h"
#include "../DirectX/Input.h"
#include "ImGuiSet.h"
#include "../ResourceManager/Model.h"
#include "../Collider/SphereCollider.h"
#include "imgui/imgui.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "../../Mob/Mob.h"
#include "../../Gimmick/Signboard.h"
#include "../../UI/ImageBase.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Manager/AudioManager/OtherAudioManager/OtherAudioManager.h"
#include "../ResourceManager/VFX.h"
#include "../GameObject/Camera.h"
#include <fstream>
#include <vector>
#include <windows.h>
#include <psapi.h>

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

    //各オブジェクトの必要な変数
    int objectStatus_[MAX_OBJECT_SIZE] = {};
    Mob* pNewObject_[MAX_OBJECT_SIZE];
    XMFLOAT3 objectPos_[MAX_OBJECT_SIZE];
    XMFLOAT3 objectRotate_[MAX_OBJECT_SIZE];
    XMFLOAT3 objectScale_[MAX_OBJECT_SIZE];

    //各看板の必要な変数
    int sigeboardStatus_[MAX_OBJECT_SIZE] = {};
    Signboard* pNewSigeboard_[MAX_OBJECT_SIZE];
    XMFLOAT3 sigeboardPos_[MAX_OBJECT_SIZE];
    XMFLOAT3 sigeboardRotate_[MAX_OBJECT_SIZE];
    XMFLOAT3 sigeboardScale_[MAX_OBJECT_SIZE];

    //各カメラ遷移の必要な変数
    int cameraTransitionStatus_[MAX_OBJECT_SIZE] = {};
    Mob* pNewCameraTransition_[MAX_OBJECT_SIZE];
    XMFLOAT3 cameraTransitionPos_[MAX_OBJECT_SIZE];
    XMFLOAT3 cameraPos_[MAX_OBJECT_SIZE];
    XMFLOAT3 cameraTar_[MAX_OBJECT_SIZE];
    XMFLOAT3 colliderSize_[MAX_OBJECT_SIZE];

    //各画像の必要な変数
    int imageStatus_[MAX_OBJECT_SIZE] = {};
    ImageBase* pNewImage_[MAX_OBJECT_SIZE];
    XMFLOAT3 imagePos_[MAX_OBJECT_SIZE];
    XMFLOAT3 imageRotate_[MAX_OBJECT_SIZE];
    XMFLOAT3 imageScale_[MAX_OBJECT_SIZE];

    //エフェクトの必要な変数
    std::string textureFileName_ = "Image/Effect/defaultParticle.png";	//画像ファイル名
    XMFLOAT3 position_ = XMFLOAT3(0,0,0);		                        //位置
    XMFLOAT3 positionRnd_ = XMFLOAT3(0, 0, 0);	                        //位置の誤差
    XMFLOAT3 direction_ = XMFLOAT3(0, 0, 0);		                    //パーティクルの移動方向
    XMFLOAT3 directionRnd_ = XMFLOAT3(0, 0, 0);	                        //移動方向の誤差（各軸の角度）
    float	 speed_ = 0.1f;			                                    //1フレームの速度
    float	 speedRnd_ = 0.0f;	                                        //速度誤差（0～1）
    float	 accel_ = 1.0f;			                                    //加速度
    float	 gravity_ = 0.0f;		                                    //重力
    XMFLOAT4 color_ = XMFLOAT4(1, 1, 1, 1);			                    //色（RGBA 0～1）
    XMFLOAT4 deltaColor_ = XMFLOAT4(0, 0, 0, 0);	                    //色の変化量
    XMFLOAT3 rotate_ = XMFLOAT3(0, 0, 0);	 	                        //各軸での角度
    XMFLOAT3 rotateRnd_ = XMFLOAT3(0, 0, 0);	 		                //角度誤差
    XMFLOAT3 spin_ = XMFLOAT3(0, 0, 0);	 		                        //回転速度
    XMFLOAT2 size_ = XMFLOAT2(1.0f, 1.0f);			                    //サイズ
    XMFLOAT2 sizeRnd_ = XMFLOAT2(0.0f, 0.0f);	                        //サイズ誤差（0～1）
    XMFLOAT2 scale_ = XMFLOAT2(1.0f, 1.0f);			                    //1フレームの拡大率
    float    lifeTime_ = 30.0f;		                                    //パーティクルの寿命（フレーム数）
    int delay_ = 0;			                                            //何フレームおきにパーティクルを発生させるか
    int number_ = 5;				                                    //1度に出すパーティクル量
    bool isBillBoard_ = true;	                                        //ビルボードかどうか

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
    std::pair<bool, int> createEffect_;           //エフェクト

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

    //////////////////////////////////////プロセスメモリ表示///////////////////////////////////////

    float processMemory_[500] = { 0 };

    ///////////////////////////////ゲーム画面設定///////////////////////////////////////

    //0->ゲーム画面 1->シーン画面 2->エフェクトエディタ画面
    int screenMode_;

    //3->スタート 4->ストップ
    int gameMode_;

    //ゲーム画面がフルサイズかどうか
    bool isGameScreenFull_;

    //////////////////////////////////////ファイル(インポート・エクスポート)///////////////////////////////////////
    
    std::string info_;

    //初期化
    void ImGuiSet::Initialize()
    {

        //各変数初期化
        ARGUMENT_INITIALIZE(create3D_.first, false);
        ARGUMENT_INITIALIZE(create3D_.second, (int)ZERO);
        ARGUMENT_INITIALIZE(createSigeboard_.first, false);
        ARGUMENT_INITIALIZE(createSigeboard_.second, (int)ZERO);
        ARGUMENT_INITIALIZE(createCameraTransition_.first, false);
        ARGUMENT_INITIALIZE(createCameraTransition_.second, (int)ZERO);
        ARGUMENT_INITIALIZE(createImage_.first, false);
        ARGUMENT_INITIALIZE(createImage_.second, (int)ZERO);
        ARGUMENT_INITIALIZE(createEffect_.first, false);
        ARGUMENT_INITIALIZE(createEffect_.second, (int)ZERO);
        ARGUMENT_INITIALIZE(objectCount_, (int)ZERO);
        ARGUMENT_INITIALIZE(screenMode_, static_cast<int>(Mode::GAME));
        ARGUMENT_INITIALIZE(gameMode_, static_cast<int>(Mode::STOP));
        ARGUMENT_INITIALIZE(isGameScreenFull_, false);
        ARGUMENT_INITIALIZE(info_,"");

        //各シーンのステージ情報が入ってるファイルのパス設定
        stageInfoFilePath_[SCENE_ID_TITLE] = "Stage/Title/StageInformation/TitleScene1.txt";
        stageInfoFilePath_[SCENE_ID_USER_SELECT] = "Stage/UserSelect/StageInformation/UserGameStartUI.txt";
        stageInfoFilePath_[SCENE_ID_TUTORIAL1] = "Image/Pause/UIInformation/PauseUI.txt";
        stageInfoFilePath_[SCENE_ID_TUTORIAL2] = "Stage/Tutorial/StageInformation/TutorialStage2.txt";
        stageInfoFilePath_[SCENE_ID_STAGE_SELECT] = "Stage/Tutorial/StageInformation/TutorialStage2.txt";
        stageInfoFilePath_[SCENE_ID_MINIGAME] = "Stage/Tutorial/StageInformation/TutorialStage2.txt";
        stageInfoFilePath_[SCENE_ID_MINIGAME_LEVEL_SELECT] = "Stage/MiniGameLevelSelect/StageInformation/MiniGameLevelSelectStage.txt";
        stageInfoFilePath_[SCENE_ID_HOME] = "Stage/Home/StageInformation/HomeStage.txt";
        stageInfoFilePath_[SCENE_ID_WORLD1] = "Stage/World/World1/StageInformation/WorldStage1.txt";
        stageInfoFilePath_[SCENE_ID_WORLD2] = "Stage/World/World2/StageInformation/WorldStage2_Movie.txt";
        stageInfoFilePath_[SCENE_ID_LAST] = "Stage/Last/StageInformation/LastStage.txt";
        stageInfoFilePath_[SCENE_ID_ENDROLES] = "Stage/World/World2/StageInformation/WorldStage2_Movie.txt";
    }

    //ゲーム画面がフルサイズではない時の描画
    void ImGuiSet::GameScreenNotFullDraw()
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

        //シーンチェンジ用のボタン表示
        SceneChangeButton();

        //ゲーム画面設定の表示
        GameScreenNotFullPreference();

        //画面の状態設定の表示
        ScreenStatusPreference();
        
        //プロセスメモリ数表示
        ProcessMemory();

        //ファイル設定
        File();

        {
            ImGui::Render();
            //描画
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        }
    }

    //ゲーム画面がフルサイズの時の描画
    void GameScreenFullDraw()
    {
        {
            //Imguiスタート
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
        }

        //ゲーム画面設定の表示
        GameScreenFullPreference();

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
        ImGui::Begin("StageCreater", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //3Dを作るボタン
        if (ImGui::Button("Create3D", ImVec2(300, 50)))
        {
            create3D_.first = true;
            create3D_.second++;
        }

        //看板を作るボタン
        if (ImGui::Button("CreateSigeboard", ImVec2(300, 50)))
        {
            createSigeboard_.first = true;
            createSigeboard_.second++;
        }

        //カメラボタン
        if (ImGui::Button("CreateCameraTransition", ImVec2(300, 50)))
        {
            createCameraTransition_.first = true;
            createCameraTransition_.second++;
        }

        //画像ボタン
        if (ImGui::Button("CreateImage", ImVec2(300, 50)))
        {
            createImage_.first = true;
            createImage_.second++;
        }

        //エフェクトボタン
        if (ImGui::Button("CreateEffect", ImVec2(300, 50)))
        {
            createEffect_.first = true;
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

        //flagがtrueなら関数を呼び出す
        if (createEffect_.first)
        {
            CreateEffect();
        }

        ImGui::End();
    }

    //3Dオブジェクト作成
    void ImGuiSet::Create3D()
    {

        //Create3Dを押した分ウィンドウを作る　
        for (int i = 0; i < create3D_.second; i++)
        {
            if (objectStatus_[i] == 1 || objectStatus_[i] == 0)
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
                    if (objectStatus_[i] == 0)
                    {

                        //ロードしたオブジェクトに必要なトランスフォームを用意
                        Transform t;

                        if (GameManager::GetpPlayer() != nullptr)
                        {
                            objectPos_[i] = GameManager::GetpPlayer()->GetPosition();
                            objectRotate_[i] = GameManager::GetpPlayer()->GetRotate();
                            objectScale_[i] = GameManager::GetpPlayer()->GetScale();
                        }
                        else
                        {
                            objectPos_[i] = XMFLOAT3(0, 0, 0);
                            objectRotate_[i] = XMFLOAT3(0, 0, 0);
                            objectScale_[i] = XMFLOAT3(1, 1, 1);
                        }

                        //プッシュするためにpair型を作る
                        //first->ロードしたモデル番号
                        //second->ロードしたモデルのtransform
                        std::pair<int, Transform> a(Model::Load(text1[i]), t);
                        assert(a.first > 0);

                        //vectorに格納する
                        obj_.push_back(a);

                        pNewObject_[i] = new Mob(GameManager::GetpSceneManager(), text1[i], "");
                        if (GameManager::GetpSceneManager()->GetParent() != nullptr)
                        {
                            GameManager::GetpSceneManager()->PushBackChild(pNewObject_[i]);
                        }
                        pNewObject_[i]->Initialize();

                        //statusプラス
                        objectStatus_[i]++;

                    }
                }

                //一回ロードしていたら
                if (objectStatus_[i] == 1)
                {

                    //Positionの木
                    if (ImGui::TreeNode("position")) {

                        //Positionセット
                        ImGui::SliderFloat("x", &objectPos_[i].x, -200.0f, 200.0f);
                        ImGui::SliderFloat("y", &objectPos_[i].y, -200.0f, 200.0f);
                        ImGui::SliderFloat("z", &objectPos_[i].z, -200.0f, 200.0f);

                        if (ImGui::TreeNode("InputPosition")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &objectPos_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &objectPos_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &objectPos_[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //Scaleの木
                    if (ImGui::TreeNode("scale")) {

                        //Scaleセット
                        ImGui::SliderFloat("x", &objectScale_[i].x, -20.0f, 20.0f);
                        ImGui::SliderFloat("y", &objectScale_[i].y, -20.0f, 20.0f);
                        ImGui::SliderFloat("z", &objectScale_[i].z, -20.0f, 20.0f);

                        if (ImGui::TreeNode("InputScale")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &objectScale_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &objectScale_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &objectScale_[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //rotateの木
                    if (ImGui::TreeNode("rotate")) {

                        //Rotateセット
                        ImGui::SliderFloat("x", &objectRotate_[i].x, 0.0f, 360.0f);
                        ImGui::SliderFloat("y", &objectRotate_[i].y, 0.0f, 360.0f);
                        ImGui::SliderFloat("z", &objectRotate_[i].z, 0.0f, 360.0f);

                        if (ImGui::TreeNode("rotate")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &objectRotate_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &objectRotate_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &objectRotate_[i].z, -20.0f, 20.0f);

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

                            ofs << text1[i] << "," << text2[i] << "," << objectPos_[i].x << "," << objectPos_[i].y << "," << objectPos_[i].z << ","
                                << objectRotate_[i].x << "," << objectRotate_[i].y << "," << objectRotate_[i].z << ","
                                << objectScale_[i].x << "," << objectScale_[i].y << "," << objectScale_[i].z;

                            ofs.close();
                        }
                        ImGui::TreePop();
                    }

                    //ウィンドウ削除
                    if (ImGui::Button("close"))
                    {
                        objectStatus_[i]++;
                    }
                }

                ImGui::End();
            }

            //描画される
            if (objectStatus_[i] >= 1)
            {
                pNewObject_[i]->SetPosition(objectPos_[i]);
                pNewObject_[i]->SetAngle(objectRotate_[i].y);
                pNewObject_[i]->SetScale(objectScale_[i]);
            }
        }
    }

    //看板作成
    void ImGuiSet::CreateSigeboard()
    {
        //Playerのポジションを保存しておく
        XMFLOAT3 basicPos = GameManager::GetpPlayer()->GetPosition();
        XMFLOAT3 basicRotate = GameManager::GetpPlayer()->GetRotate();
        XMFLOAT3 basicScale = GameManager::GetpPlayer()->GetScale();

        //Create3Dを押した分ウィンドウを作る　
        for (int i = 0; i < createSigeboard_.second; i++)
        {
            if (sigeboardStatus_[i] == 1 || sigeboardStatus_[i] == 0)
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
                    if (sigeboardStatus_[i] == 0)
                    {

                        //ロードしたオブジェクトに必要なトランスフォームを用意
                        Transform t;

                        sigeboardPos_[i] = basicPos;
                        sigeboardRotate_[i] = basicRotate;
                        sigeboardScale_[i] = basicScale;

                        pNewSigeboard_[i] = new Signboard(GameManager::GetpSceneManager(), Stext1[i], "");
                        if (GameManager::GetpSceneManager()->GetParent() != nullptr)
                        {
                            GameManager::GetpSceneManager()->PushBackChild(pNewSigeboard_[i]);
                        }
                        pNewSigeboard_[i]->Initialize();

                        //statusプラス
                        sigeboardStatus_[i]++;

                    }
                }

                //一回ロードしていたら
                if (sigeboardStatus_[i] == 1)
                {

                    //Positionの木
                    if (ImGui::TreeNode("position")) {

                        //Positionセット
                        ImGui::SliderFloat("x", &sigeboardPos_[i].x, -200.0f, 200.0f);
                        ImGui::SliderFloat("y", &sigeboardPos_[i].y, -200.0f, 200.0f);
                        ImGui::SliderFloat("z", &sigeboardPos_[i].z, -200.0f, 200.0f);

                        if (ImGui::TreeNode("InputPosition")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &sigeboardPos_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &sigeboardPos_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &sigeboardPos_[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //Scaleの木
                    if (ImGui::TreeNode("scale")) {

                        //Scaleセット
                        ImGui::SliderFloat("x", &sigeboardScale_[i].x, -20.0f, 20.0f);
                        ImGui::SliderFloat("y", &sigeboardScale_[i].y, -20.0f, 20.0f);
                        ImGui::SliderFloat("z", &sigeboardScale_[i].z, -20.0f, 20.0f);

                        if (ImGui::TreeNode("InputScale")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &sigeboardScale_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &sigeboardScale_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &sigeboardScale_[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //rotateの木
                    if (ImGui::TreeNode("rotate")) {

                        //Rotateセット
                        ImGui::SliderFloat("x", &sigeboardRotate_[i].x, 0.0f, 360.0f);
                        ImGui::SliderFloat("y", &sigeboardRotate_[i].y, 0.0f, 360.0f);
                        ImGui::SliderFloat("z", &sigeboardRotate_[i].z, 0.0f, 360.0f);

                        if (ImGui::TreeNode("rotate")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &sigeboardRotate_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &sigeboardRotate_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &sigeboardRotate_[i].z, -20.0f, 20.0f);

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
                            basicPos = { sigeboardPos_[i] };
                            basicRotate = { sigeboardRotate_[i] };
                            basicScale = { sigeboardScale_[i] };

                            const char* fileName = stageInfoFilePath_[GameManager::GetpSceneManager()->GetSceneId()];
                            std::ofstream ofs;
                            ofs.open(fileName, std::ios::app);

                            ofs << std::endl;

                            ofs << Stext1[i] << "," << Stext2[i] << "," << sigeboardPos_[i].x << "," << sigeboardPos_[i].y << "," << sigeboardPos_[i].z << ","
                                << sigeboardRotate_[i].x << "," << sigeboardRotate_[i].y << "," << sigeboardRotate_[i].z << ","
                                << sigeboardScale_[i].x << "," << sigeboardScale_[i].y << "," << sigeboardScale_[i].z;

                            ofs.close();
                        }
                        ImGui::TreePop();
                    }

                    //ウィンドウ削除
                    if (ImGui::Button("close"))
                    {
                        sigeboardStatus_[i]++;
                    }
                }

                ImGui::End();
            }

            //描画される
            if (sigeboardStatus_[i] >= 1)
            {
                pNewSigeboard_[i]->SetPosition(sigeboardPos_[i]);
                pNewSigeboard_[i]->SetRotate(sigeboardRotate_[i]);
                pNewSigeboard_[i]->SetScale(sigeboardScale_[i]);
            }
        }
    }

    //カメラの遷移作成(コライダーに当たったらカメラのポジション変える機能)
    void ImGuiSet::CreateCameraTransition()
    {
        //Playerのポジションを保存しておく
        XMFLOAT3 basicPos = GameManager::GetpPlayer()->GetPosition();
        XMFLOAT3 basicRotate = GameManager::GetpPlayer()->GetRotate();
        XMFLOAT3 basicScale = GameManager::GetpPlayer()->GetScale();

        //Create3Dを押した分ウィンドウを作る　
        for (int i = 0; i < createCameraTransition_.second; i++)
        {
            if (cameraTransitionStatus_[i] == 1 || cameraTransitionStatus_[i] == 0)
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
                    if (cameraTransitionStatus_[i] == 0)
                    {

                        //ロードしたオブジェクトに必要なトランスフォームを用意
                        Transform t;

                        cameraTransitionPos_[i] = basicPos;
                        cameraTar_[i] = basicRotate;
                        colliderSize_[i] = basicScale;

                        //プッシュするためにpair型を作る
                        //first->ロードしたモデル番号
                        //second->ロードしたモデルのtransform
                        std::pair<int, Transform> a(Model::Load(text1[i]), t);
                        assert(a.first > 0);

                        //vectorに格納する
                        obj_.push_back(a);

                        pNewCameraTransition_[i] = new Mob(GameManager::GetpSceneManager(), text1[i], "");
                        if (GameManager::GetpSceneManager()->GetParent() != nullptr)
                        {
                            GameManager::GetpSceneManager()->PushBackChild(pNewCameraTransition_[i]);
                        }
                        pNewCameraTransition_[i]->Initialize();

                        //statusプラス
                        cameraTransitionStatus_[i]++;

                    }
                }

                //一回ロードしていたら
                if (cameraTransitionStatus_[i] == 1)
                {

                    //Positionの木
                    if (ImGui::TreeNode("position")) {

                        //Positionセット
                        ImGui::SliderFloat("x", &cameraTransitionPos_[i].x, -200.0f, 200.0f);
                        ImGui::SliderFloat("y", &cameraTransitionPos_[i].y, -200.0f, 200.0f);
                        ImGui::SliderFloat("z", &cameraTransitionPos_[i].z, -200.0f, 200.0f);

                        if (ImGui::TreeNode("InputPosition")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &cameraTransitionPos_[i].x, -200.0f, 200.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &cameraTransitionPos_[i].y, -200.0f, 200.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &cameraTransitionPos_[i].z, -200.0f, 200.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //Positionの木
                    if (ImGui::TreeNode("CameraPosition")) {

                        //Positionセット
                        ImGui::SliderFloat("x", &cameraPos_[i].x, -200.0f, 200.0f);
                        ImGui::SliderFloat("y", &cameraPos_[i].y, -200.0f, 200.0f);
                        ImGui::SliderFloat("z", &cameraPos_[i].z, -200.0f, 200.0f);

                        if (ImGui::TreeNode("CameraInputPosition")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &cameraPos_[i].x, -200.0f, 200.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &cameraPos_[i].y, -200.0f, 200.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &cameraPos_[i].z, -200.0f, 200.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //Scaleの木
                    if (ImGui::TreeNode("scale")) {

                        //Scaleセット
                        ImGui::SliderFloat("x", &colliderSize_[i].x, -20.0f, 20.0f);
                        ImGui::SliderFloat("y", &colliderSize_[i].y, -20.0f, 20.0f);
                        ImGui::SliderFloat("z", &colliderSize_[i].z, -20.0f, 20.0f);

                        if (ImGui::TreeNode("InputScale")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &colliderSize_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &colliderSize_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &colliderSize_[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //rotateの木
                    if (ImGui::TreeNode("rotate")) {

                        //Rotateセット
                        ImGui::SliderFloat("x", &cameraTar_[i].x, 0.0f, 360.0f);
                        ImGui::SliderFloat("y", &cameraTar_[i].y, 0.0f, 360.0f);
                        ImGui::SliderFloat("z", &cameraTar_[i].z, 0.0f, 360.0f);

                        if (ImGui::TreeNode("rotate")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &cameraTar_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &cameraTar_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &cameraTar_[i].z, -20.0f, 20.0f);

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
                            basicPos = { cameraTransitionPos_[i] };
                            basicRotate = { cameraTar_[i] };
                            basicScale = { colliderSize_[i] };

                            const char* fileName = stageInfoFilePath_[GameManager::GetpSceneManager()->GetSceneId()];
                            std::ofstream ofs;
                            ofs.open(fileName, std::ios::app);

                            ofs << std::endl;

                            ofs << text1[i] << "," << text2[i] << "," << cameraTransitionPos_[i].x << "," << cameraTransitionPos_[i].y << "," << cameraTransitionPos_[i].z << ","
                                << cameraTar_[i].x << "," << cameraTar_[i].y << "," << cameraTar_[i].z << ","
                                << colliderSize_[i].x * 2 << "," << colliderSize_[i].y * 2 << "," << colliderSize_[i].z * 2 << ","
                                << cameraPos_[i].x << "," << cameraPos_[i].y << "," << cameraPos_[i].z;

                            ofs.close();
                        }
                        ImGui::TreePop();
                    }

                    //ウィンドウ削除
                    if (ImGui::Button("close"))
                    {
                        cameraTransitionStatus_[i]++;
                    }
                }

                ImGui::End();
            }

            //描画される
            if (cameraTransitionStatus_[i] >= 1)
            {
                pNewCameraTransition_[i]->SetPosition(cameraTransitionPos_[i]);
                pNewCameraTransition_[i]->SetRotate(cameraTar_[i]);
                pNewCameraTransition_[i]->SetScale(colliderSize_[i]);
            }
        }
    }

    //画像作成
    void ImGuiSet::CreateImage()
    {

        //Create3Dを押した分ウィンドウを作る　
        for (int i = 0; i < createImage_.second; i++)
        {
            if (imageStatus_[i] == 1 || imageStatus_[i] == 0)
            {
                //iをFBXの後ろにたす
                char name[16];
                sprintf_s(name, "FBX %d", i);

                //window作る
                ImGui::Begin(name);

                //ファイルネーム入力欄
                static char text1[MAX_OBJECT_SIZE][100] = {};

                //入力された文字をtext1に格納
                ImGui::InputText("FBX filename", text1[i], sizeof(text1[i]));

                //ロードボタン
                if (ImGui::Button("Load"))
                {
                    //もしまだ一回もロードしてなかったら
                    if (imageStatus_[i] == 0)
                    {

                        //ロードしたオブジェクトに必要なトランスフォームを用意
                        Transform t;

                        imagePos_[i] = XMFLOAT3(0, 0, 0);
                        imageRotate_[i] = XMFLOAT3(0, 0, 0);
                        imageScale_[i] = XMFLOAT3(1, 1, 1);

                        //プッシュするためにpair型を作る
                        //first->ロードしたモデル番号
                        //second->ロードしたモデルのtransform
                        std::pair<int, Transform> a(Image::Load(text1[i]), t);
                        assert(a.first > 0);

                        //vectorに格納する
                        obj_.push_back(a);

                        pNewImage_[i] = new ImageBase(GameManager::GetpSceneManager(), text1[i], "");
                        if (GameManager::GetpSceneManager()->GetParent() != nullptr)
                        {
                            GameManager::GetpSceneManager()->PushBackChild(pNewImage_[i]);
                        }
                        pNewImage_[i]->Initialize();

                        //statusプラス
                        imageStatus_[i]++;

                    }
                }

                //一回ロードしていたら
                if (imageStatus_[i] == 1)
                {

                    //Positionの木
                    if (ImGui::TreeNode("position")) {

                        //Positionセット
                        ImGui::SliderFloat("x", &imagePos_[i].x, -200.0f, 200.0f);
                        ImGui::SliderFloat("y", &imagePos_[i].y, -200.0f, 200.0f);
                        ImGui::SliderFloat("z", &imagePos_[i].z, -200.0f, 200.0f);

                        if (ImGui::TreeNode("InputPosition")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &imagePos_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &imagePos_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &imagePos_[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //Scaleの木
                    if (ImGui::TreeNode("scale")) {

                        //Scaleセット
                        ImGui::SliderFloat("x", &imageScale_[i].x, -20.0f, 20.0f);
                        ImGui::SliderFloat("y", &imageScale_[i].y, -20.0f, 20.0f);
                        ImGui::SliderFloat("z", &imageScale_[i].z, -20.0f, 20.0f);

                        if (ImGui::TreeNode("InputScale")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &imageScale_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &imageScale_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &imageScale_[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //rotateの木
                    if (ImGui::TreeNode("rotate")) {

                        //Rotateセット
                        ImGui::SliderFloat("x", &imageRotate_[i].x, 0.0f, 360.0f);
                        ImGui::SliderFloat("y", &imageRotate_[i].y, 0.0f, 360.0f);
                        ImGui::SliderFloat("z", &imageRotate_[i].z, 0.0f, 360.0f);

                        if (ImGui::TreeNode("rotate")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &imageRotate_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &imageRotate_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &imageRotate_[i].z, -20.0f, 20.0f);

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

                            ofs << text1[i] << "," << text2[i] << "," << imagePos_[i].x << "," << imagePos_[i].y << "," << imagePos_[i].z << ","
                                << imageRotate_[i].x << "," << imageRotate_[i].y << "," << imageRotate_[i].z << ","
                                << imageScale_[i].x << "," << imageScale_[i].y << "," << imageScale_[i].z;

                            ofs.close();
                        }
                        ImGui::TreePop();
                    }

                    //ウィンドウ削除
                    if (ImGui::Button("close"))
                    {
                        imageStatus_[i]++;
                    }
                }

                ImGui::End();
            }

            //描画される
            if (imageStatus_[i] >= 1)
            {
                pNewImage_[i]->SetPosition(imagePos_[i]);
                pNewImage_[i]->SetScale(imageScale_[i]);
            }
        }

    }

    //エフェクト作成
    void ImGuiSet::CreateEffect()
    {

        //window作る
        ImGui::Begin("Effect");

        //エフェクトの各情報設定用
        if (ImGui::TreeNode("textureFileName")) {

            ImGui::InputText("textureFileName", const_cast<char*>(textureFileName_.c_str()), sizeof(textureFileName_.c_str()));
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("position")) {

            //Positionセット
            ImGui::SliderFloat("x", &position_.x, -200.0f, 200.0f);
            ImGui::SliderFloat("y", &position_.y, -200.0f, 200.0f);
            ImGui::SliderFloat("z", &position_.z, -200.0f, 200.0f);

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("positionRnd")) {

            //Positionセット
            ImGui::SliderFloat("x", &positionRnd_.x, -200.0f, 200.0f);
            ImGui::SliderFloat("y", &positionRnd_.y, -200.0f, 200.0f);
            ImGui::SliderFloat("z", &positionRnd_.z, -200.0f, 200.0f);

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("direction")) {

            ImGui::SliderFloat("x", &direction_.x, -200.0f, 200.0f);
            ImGui::SliderFloat("y", &direction_.y, -200.0f, 200.0f);
            ImGui::SliderFloat("z", &direction_.z, -200.0f, 200.0f);

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("directionRnd")) {

            ImGui::SliderFloat("x", &directionRnd_.x, 0.0f, 360.0f);
            ImGui::SliderFloat("y", &directionRnd_.y, 0.0f, 360.0f);
            ImGui::SliderFloat("z", &directionRnd_.z, 0.0f, 360.0f);

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("speed")) {

            ImGui::SliderFloat("speed", &speed_, 0.0f, 50.0f);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("speedRnd")) {

            ImGui::SliderFloat("speed", &speedRnd_, 0.0f, 50.0f);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("accel")) {

            ImGui::SliderFloat("accel", &accel_, 0.0f, 50.0f);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("gravity")) {

            ImGui::SliderFloat("gravity", &gravity_, 0.0f, 50.0f);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("color")) {

            float color[4] = { color_.x, color_.y, color_.z, color_.w };
            ImGui::ColorPicker3("Color", color, ImGuiColorEditFlags_PickerHueWheel);
            color_ = XMFLOAT4(color[0], color[1], color[2], color[3]);

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("deltaColor")) {

            float deltaColor[4] = { deltaColor_.x, deltaColor_.y, deltaColor_.z, deltaColor_.w };
            ImGui::ColorPicker3("deltaColor", deltaColor, ImGuiColorEditFlags_PickerHueWheel);
            deltaColor_ = XMFLOAT4(deltaColor[0], deltaColor[1], deltaColor[2], deltaColor[3]);

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("rotate")) {

            ImGui::SliderFloat("x", &rotate_.x, 0.0f, 360.0f);
            ImGui::SliderFloat("y", &rotate_.y, 0.0f, 360.0f);
            ImGui::SliderFloat("z", &rotate_.z, 0.0f, 360.0f);

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("rotateRnd")) {

            ImGui::SliderFloat("x", &rotateRnd_.x, 0.0f, 360.0f);
            ImGui::SliderFloat("y", &rotateRnd_.y, 0.0f, 360.0f);
            ImGui::SliderFloat("z", &rotateRnd_.z, 0.0f, 360.0f);

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("spin")) {

            ImGui::SliderFloat("x", &spin_.x, 0.0f, 360.0f);
            ImGui::SliderFloat("y", &spin_.y, 0.0f, 360.0f);
            ImGui::SliderFloat("z", &spin_.z, 0.0f, 360.0f);

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("size")) {

            ImGui::SliderFloat("x", &size_.x, 0.0f, 100.0f);
            ImGui::SliderFloat("y", &size_.y, 0.0f, 100.0f);

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("sizeRnd")) {

            ImGui::SliderFloat("x", &sizeRnd_.x, 0.0f, 100.0f);
            ImGui::SliderFloat("y", &sizeRnd_.y, 0.0f, 100.0f);

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("scale")) {

            ImGui::SliderFloat("x", &scale_.x, 0.0f, 100.0f);
            ImGui::SliderFloat("y", &scale_.y, 0.0f, 100.0f);

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("lifeTime")) {

            ImGui::SliderFloat("lifeTime", &lifeTime_, 0.0f, 3000.0f);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("delay")) {

            ImGui::SliderInt("delay", &delay_, 0.0f, 600.0f);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("number")) {

            ImGui::SliderInt("number", &number_, 0.0f, 100.0f);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("isBillBoard")) {

            ImGui::Checkbox("GameScreenFull", &isBillBoard_);
            ImGui::TreePop();
        }

        //各情報代入
        if (ImGui::Button("START"))
        {
            EmitterData data;
            ARGUMENT_INITIALIZE(data.textureFileName, textureFileName_);
            ARGUMENT_INITIALIZE(data.position, position_);
            ARGUMENT_INITIALIZE(data.positionRnd, positionRnd_);
            ARGUMENT_INITIALIZE(data.direction, direction_);
            ARGUMENT_INITIALIZE(data.directionRnd, directionRnd_);
            ARGUMENT_INITIALIZE(data.speed, speed_);
            ARGUMENT_INITIALIZE(data.speedRnd, speedRnd_);
            ARGUMENT_INITIALIZE(data.accel, accel_);
            ARGUMENT_INITIALIZE(data.gravity, gravity_);
            ARGUMENT_INITIALIZE(data.color, color_);
            ARGUMENT_INITIALIZE(data.deltaColor, deltaColor_);
            ARGUMENT_INITIALIZE(data.rotate, rotate_);
            ARGUMENT_INITIALIZE(data.rotateRnd, rotateRnd_);
            ARGUMENT_INITIALIZE(data.spin, spin_);
            ARGUMENT_INITIALIZE(data.size, size_);
            ARGUMENT_INITIALIZE(data.sizeRnd, sizeRnd_);
            ARGUMENT_INITIALIZE(data.scale, scale_);
            ARGUMENT_INITIALIZE(data.lifeTime, lifeTime_);
            ARGUMENT_INITIALIZE(data.delay, delay_);
            ARGUMENT_INITIALIZE(data.number, number_);
            ARGUMENT_INITIALIZE(data.isBillBoard, isBillBoard_);
            VFX::Start(data);
        }

        ImGui::End();
    }

    //////////////////////////////ステージのオブジェクトのトランスフォーム表示////////////////////////////

    //ステージオブジェのトランスフォームすべて表示するImGuiを表示
    void ImGuiSet::StageObjImGuiDisplay()
    {
        //window作る
        ImGui::Begin("StageObjTransformDisplay", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //ステージオブジェのトランスフォームすべて表示
        StageObjTransformDisplay(GameManager::GetpSceneManager());

        //オブジェクトの数0に初期化
        ARGUMENT_INITIALIZE(objectCount_, (int)ZERO);

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
            float pos[3] = { pObj->GetPosition().x,pObj->GetPosition().y ,pObj->GetPosition().z };
            ImGui::DragFloat3("position", pos);
            pObj->SetPosition({ pos[0], pos[1], pos[2] });

            //回転
            float rotate[3] = { pObj->GetRotate().x,pObj->GetRotate().y ,pObj->GetRotate().z };
            ImGui::DragFloat3("rotation", rotate);
            pObj->SetRotate({ rotate[0],rotate[1],rotate[2] });

            //拡大率
            float scale[3] = { pObj->GetScale().x,pObj->GetScale().y ,pObj->GetScale().z };
            ImGui::DragFloat3("scale", scale);
            pObj->SetScale({ scale[0],scale[1],scale[2] });

            //削除ボタン
            if (ImGui::Button("Kill")) { pObj->KillMe(); }

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
        ImGui::Begin("DebugLog", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

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

    ///////////////////////////////シーン変更表示///////////////////////////////////////

    /// <summary>
    /// シーン変更用ボタン表示
    /// </summary>
    void ImGuiSet::SceneChangeButton()
    {
        //window作る
        ImGui::Begin("SceneChangeButton", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //ボタン作成
        if (ImGui::Button("TITLE", ImVec2(300, 50)))                 { GameManager::GetpSceneManager()->SetLoadDrawFlag(false); GameManager::GetpSceneManager()->SameSceneInitializ(SCENE_ID_TITLE); }
        if (ImGui::Button("USER_SELECT", ImVec2(300, 50)))           { GameManager::GetpSceneManager()->SetLoadDrawFlag(false); GameManager::GetpSceneManager()->SameSceneInitializ(SCENE_ID_USER_SELECT); }
        if (ImGui::Button("TUTORIAL1", ImVec2(300, 50)))             { GameManager::GetpSceneManager()->SameSceneInitializ(SCENE_ID_TUTORIAL1); }
        if (ImGui::Button("TUTORIAL2", ImVec2(300, 50)))             { GameManager::GetpSceneManager()->SameSceneInitializ(SCENE_ID_TUTORIAL2); }
        if (ImGui::Button("STAGE_SELECT", ImVec2(300, 50)))          { GameManager::GetpSceneManager()->SameSceneInitializ(SCENE_ID_STAGE_SELECT); }
        if (ImGui::Button("MINIGAME", ImVec2(300, 50)))              { GameManager::GetpSceneManager()->SameSceneInitializ(SCENE_ID_MINIGAME); }
        if (ImGui::Button("MINIGAME_LEVEL_SELECT", ImVec2(300, 50))) { GameManager::GetpSceneManager()->SameSceneInitializ(SCENE_ID_MINIGAME_LEVEL_SELECT); }
        if (ImGui::Button("HOME", ImVec2(300, 50)))                  { GameManager::GetpSceneManager()->SameSceneInitializ(SCENE_ID_HOME); }
        if (ImGui::Button("WORLD1", ImVec2(300, 50)))                { GameManager::GetpSceneManager()->SameSceneInitializ(SCENE_ID_WORLD1); }
        if (ImGui::Button("WORLD2", ImVec2(300, 50)))                { GameManager::GetpSceneManager()->SameSceneInitializ(SCENE_ID_WORLD2); }
        if (ImGui::Button("LASTMOVIE", ImVec2(300, 50)))             { GameManager::GetpSceneManager()->SameSceneInitializ(SCENE_ID_LAST); }
        if (ImGui::Button("ENDROLES", ImVec2(300, 50)))              { GameManager::GetpSceneManager()->SameSceneInitializ(SCENE_ID_ENDROLES); }

        //終わり
        ImGui::End();
    }

    ///////////////////////////////ゲーム画面設定///////////////////////////////////////

    /// <summary>
    /// ゲーム画面設定
    /// </summary>
    void ImGuiSet::GameScreenNotFullPreference()
    {
        //window作る
        ImGui::Begin("GameScreenNotFullPreference", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //ラジオボタンのサイズを2倍に変更
        ImGuiStyle& style = ImGui::GetStyle();
        ARGUMENT_INITIALIZE(style.FramePadding, ImVec2(8, 8));

        //モード状態を記録しておく
        int beforeMode = gameMode_;

        //ラジオボタン作成
        ImGui::RadioButton("Start", &gameMode_, static_cast<int>(Mode::START));
        ImGui::SameLine();
        ImGui::RadioButton("Stop", &gameMode_, static_cast<int>(Mode::STOP));
        ImGui::SameLine();

        //もしStop状態からStart状態に変わったのなら
        if (beforeMode == static_cast<int>(Mode::STOP) && gameMode_ == static_cast<int>(Mode::START))
        {
            Direct3D::SetTimeScale(false);
        }
        //もしStart状態からStop状態に変わったのなら
        else if (beforeMode == static_cast<int>(Mode::START) && gameMode_ == static_cast<int>(Mode::STOP))
        {
            Direct3D::SetTimeScale(true);
        }

        //前の状態を保存しておく
        bool beforeflag = isGameScreenFull_;

        //チェックボックス表示
        ImGui::Checkbox("GameScreenFull", &isGameScreenFull_);

        //フルサイズに変更していたら
        if (!beforeflag && isGameScreenFull_)
            Direct3D::SetGameFull(true);

        //サイズを元に戻す
        ARGUMENT_INITIALIZE(style.FramePadding, ImVec2(4, 4));

        //終わり
        ImGui::End();
    }

    /// <summary>
    /// ゲーム画面がフルサイズの時の設定
    /// </summary>
    void ImGuiSet::GameScreenFullPreference()
    {
        //window作る
        ImGui::Begin("GameScreenFullPreference", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //ラジオボタンのサイズを2倍に変更
        ImGuiStyle& style = ImGui::GetStyle();
        ARGUMENT_INITIALIZE(style.FramePadding, ImVec2(8, 8));

        //モード状態を記録しておく
        int beforeMode = gameMode_;

        //ラジオボタン作成
        ImGui::RadioButton("Start", &gameMode_, static_cast<int>(Mode::START));
        ImGui::SameLine();
        ImGui::RadioButton("Stop", &gameMode_, static_cast<int>(Mode::STOP));
        ImGui::SameLine();

        //もしStop状態からStart状態に変わったのなら
        if (beforeMode == static_cast<int>(Mode::STOP) && gameMode_ == static_cast<int>(Mode::START))
        {
            Direct3D::SetTimeScale(false);
        }
        //もしStart状態からStop状態に変わったのなら
        else if (beforeMode == static_cast<int>(Mode::START) && gameMode_ == static_cast<int>(Mode::STOP))
        {
            Direct3D::SetTimeScale(true);
        }

        //前の状態を保存しておく
        bool beforeflag = isGameScreenFull_;

        //チェックボックス表示
        ImGui::Checkbox("GameScreenFull", &isGameScreenFull_);

        //フルサイズから変更していたら
        if(beforeflag && !isGameScreenFull_)
            Direct3D::SetGameFull(false);

        //サイズを元に戻す
        ARGUMENT_INITIALIZE(style.FramePadding, ImVec2(4, 4));

        //終わり
        ImGui::End();
    }

    /// <summary>
    /// 画面の状態設定
    /// </summary>
    void ImGuiSet::ScreenStatusPreference()
    {
        //window作る
        ImGui::Begin("ScreenStatus", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //ラジオボタンのサイズを2倍に変更
        ImGuiStyle& style = ImGui::GetStyle();
        ARGUMENT_INITIALIZE(style.FramePadding,ImVec2(8, 8));

        //モード状態を記録しておく
        int beforeMode = screenMode_;

        //ラジオボタン作成
        ImGui::RadioButton("Game", &screenMode_, static_cast<int>(Mode::GAME));
        ImGui::SameLine();
        ImGui::RadioButton("Scene", &screenMode_, static_cast<int>(Mode::SCENE));
        ImGui::SameLine();
        ImGui::RadioButton("EffectEdit", &screenMode_, static_cast<int>(Mode::EFFECT_EDIT));

        //もしゲーム画面に切り替わったのなら
        if (beforeMode != static_cast<int>(Mode::GAME) && screenMode_ == static_cast<int>(Mode::GAME))
        {
            ARGUMENT_INITIALIZE(gameMode_, static_cast<int>(Mode::START));
            Direct3D::SetTimeScale(false);
            Direct3D::SetScreenGameStatus(true);
        }
        //もしシーン画面に切り替わったのなら
        else if(beforeMode != static_cast<int>(Mode::SCENE) && screenMode_ == static_cast<int>(Mode::SCENE))
        {
            ARGUMENT_INITIALIZE(gameMode_, static_cast<int>(Mode::STOP));
            Direct3D::SetTimeScale(true);
            Direct3D::SetScreenGameStatus(false);
            Camera::FrameCameraInitialize();
        }
        //もしエフェクトエディタ画面に切り替わったのなら
        else if (beforeMode != static_cast<int>(Mode::EFFECT_EDIT) && screenMode_ == static_cast<int>(Mode::EFFECT_EDIT))
        {
            ARGUMENT_INITIALIZE(gameMode_, static_cast<int>(Mode::STOP));
            Direct3D::SetTimeScale(true);
            Direct3D::SetScreenGameStatus(false);
        }

        //サイズを元に戻す
        ARGUMENT_INITIALIZE(style.FramePadding,ImVec2(4, 4));

        //終わり
        ImGui::End();
    }

    //各セット関数
    void ImGuiSet::SetScreenMode(int mode) { screenMode_ = mode; }
    void ImGuiSet::SetGameMode(int mode) { gameMode_ = mode; }

    //各ゲット関数
    int ImGuiSet::GetScreenMode() { return screenMode_; }

    ///////////////////////////////プロセスメモリ表示///////////////////////////////////////

    void ImGuiSet::ProcessMemory()
    {
        //window作る
        ImGui::Begin("ProcessMemory", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //プロセスメモリ取得
        HANDLE processHandle = GetCurrentProcess();
        PROCESS_MEMORY_COUNTERS_EX pmc;

        for (int i = 0; i < 499; i++)
        {
            processMemory_[i] = processMemory_[i + 1];
        }

        if (GetProcessMemoryInfo(processHandle, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
            processMemory_[499] = (pmc.PrivateUsage / 1024) / 1024;
        }

        //グラフ表示
        ImGui::PlotLines("", processMemory_, 500, 0, NULL, 1, 1000, ImVec2(580, 200));

        //終わり
        ImGui::End();
    }

    ///////////////////////////////ファイル(インポート・エクスポート)///////////////////////////////////////

    void ImGuiSet::File()
    {
        //window作る
        ImGui::Begin("File", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //ボタン作成
        if (ImGui::Button("Import", ImVec2(240, 55)))
        {
            Direct3D::SetTimeScale(true);
            Import();
        }
        ImGui::SameLine();

        if (ImGui::Button("Export", ImVec2(240, 55)))
        {
            Direct3D::SetTimeScale(true);
            Export();
        }
        ImGui::SameLine();

        //終わり
        ImGui::End();
    }

    //ステージインポート
    void ImGuiSet::Import()
    {
        //現在のカレントディレクトリを覚えておく
        char defaultCurrentDir[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

        //ファイル名を入れる変数
        char fileName[MAX_PATH] = "無題.map"; 

        //「ファイルを保存」ダイアログの設定
        OPENFILENAME ofn;                                          //名前をつけて保存ダイアログの設定用構造体
        ZeroMemory(&ofn, sizeof(ofn));                             //構造体初期化
        ofn.lStructSize = sizeof(OPENFILENAME);                    //構造体のサイズ
        ofn.lpstrFilter = TEXT("すべてのファイル(*.*)\0*.*\0\0");  //ファイルの種類
        ofn.lpstrFile = fileName;               	               //ファイル名
        ofn.nMaxFile = MAX_PATH;                 	               //パスの最大文字数
        ofn.Flags = OFN_FILEMUSTEXIST;   		                   //フラグ（同名ファイルが存在したら上書き確認）
        ofn.lpstrDefExt = "map";                  	               //デフォルト拡張子

        //「ファイルを保存」ダイアログ
        BOOL selFile;
        selFile = GetOpenFileName(&ofn);

        //キャンセルしたら中断
        if (selFile == FALSE) return;

        //カレントディレクトリを元の位置に戻す
        SetCurrentDirectory(defaultCurrentDir);

        //ステージ作成
        CreateStage* p = new CreateStage;
        p->LoadFileCreateStage((*GameManager::GetpSceneManager()->GetChildList()->begin()), fileName);
    }

    //ステージオブジェインポートするための関数
    void ImGuiSet::ExportStageObjTransform(GameObject* pObj)
    {

        //シーンマネージャーかつシーンでないのなら
        if (pObj != GameManager::GetpSceneManager() && pObj->GetObjectName().find("Scene") != std::string::npos)
        {
            info_ += pObj->GetPathName() + ",";
            info_ += pObj->GetObjectName() + ",";
            info_ += std::to_string(pObj->GetPosition().x) + ",";
            info_ += std::to_string(pObj->GetPosition().y) + ",";
            info_ += std::to_string(pObj->GetPosition().z) + ",";
            info_ += std::to_string(pObj->GetRotate().x) + ",";
            info_ += std::to_string(pObj->GetRotate().y) + ",";
            info_ += std::to_string(pObj->GetRotate().z) + ",";
            info_ += std::to_string(pObj->GetScale().x) + ",";
            info_ += std::to_string(pObj->GetScale().y) + ",";
            info_ += std::to_string(pObj->GetScale().z) + "\r\n";
     
        }

        //子供の分だけ回す
        for (auto itr = pObj->GetChildList()->begin(); itr != pObj->GetChildList()->end(); itr++)
        {
            ExportStageObjTransform(*itr);
        }
    }

    //ステージエクスポート
    void ImGuiSet::Export()
    {
        char fileName[MAX_PATH] = "無題.txt";  //ファイル名を入れる変数

        //「ファイルを保存」ダイアログの設定
        OPENFILENAME ofn;                         	               //名前をつけて保存ダイアログの設定用構造体
        ZeroMemory(&ofn, sizeof(ofn));            	               //構造体初期化
        ofn.lStructSize = sizeof(OPENFILENAME);   	               //構造体のサイズ
        ofn.lpstrFilter = TEXT("すべてのファイル(*.*)\0*.*\0\0");  //ファイルの種類
        ofn.lpstrFile = fileName;               	               //ファイル名
        ofn.nMaxFile = MAX_PATH;                 	               //パスの最大文字数
        ofn.Flags = OFN_OVERWRITEPROMPT;   		                   //フラグ（同名ファイルが存在したら上書き確認）
        ofn.lpstrDefExt = "txt";                  	               //デフォルト拡張子

        //「ファイルを保存」ダイアログ
        BOOL selFile;
        selFile = GetSaveFileName(&ofn);

        //キャンセルしたら中断
        if (selFile == FALSE) return;

        HANDLE hFile_;
        hFile_ = CreateFile(
            fileName,
            GENERIC_WRITE,
            0,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

        //初期化状態にしておく
        ARGUMENT_INITIALIZE(info_, "");

        //ステージ情報をinfoに格納
        ExportStageObjTransform(GameManager::GetpSceneManager());

        DWORD byte = 0;
        WriteFile(
            hFile_,
            info_.c_str(),
            info_.length(),
            &byte,
            NULL
        );

        CloseHandle(hFile_);
    }

    //開放
    void ImGuiSet::Release()
    {
    }
}