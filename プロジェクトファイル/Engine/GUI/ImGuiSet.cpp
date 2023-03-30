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
#include "../GameObject/Camera.h"
#include <fstream>
#include <vector>
#include <windows.h>
#include <psapi.h>

//�萔
namespace
{
    static const int MAX_DEBUG_LOG_NUM = 1000; //�f�o�b�O���O�̍ő��
}

/// <summary>
/// Debug�p��UI��\������
/// </summary>
namespace ImGuiSet
{
    ////////////////////////////////////�X�e�[�W�쐬�pImGui///////////////////////////////////////

    //�\���������I�u�W�F�N�g���i�[����ꏊ
    //first->���f���ԍ�
    //second->���f���ԍ����Ƃ̃g�����X�t�H�[��
    std::vector<std::pair<int, Transform>>obj_;

    //first->��������ǂ���
    //second->���������
    std::pair<bool, int> create3D_;               //3D�I�u�W�F�N�g
    std::pair<bool, int> createSigeboard_;        //�Ŕ�
    std::pair<bool, int> createCameraTransition_; //�J�����J��
    std::pair<bool, int> createImage_;            //�摜

    //�e�V�[���̃X�e�[�W��񂪓����Ă�t�@�C���̃p�X
    const char* stageInfoFilePath_[SCENE_ID_MAX];

    //////////////////////////////�X�e�[�W�̃I�u�W�F�N�g�̃g�����X�t�H�[���\��////////////////////////////

    //�I�u�W�F�N�g�̐�
    int objectCount_;

    //////////////////////////////////////���O�\��///////////////////////////////////////

    /// <summary>
    ///���O�\�����邽�߂�vector
    /// </summary>
    ///first->�ϐ��̖��O
    ///second->�l
    std::vector<std::pair<std::string, std::string>> variable_;

    //////////////////////////////////////�v���Z�X�������\��///////////////////////////////////////

    float processMemory_[500] = { 0 };

    //////////////////////////////////////�t�@�C��(�C���|�[�g�E�G�N�X�|�[�g)///////////////////////////////////////
    
    std::string info_;

    //������
    void ImGuiSet::Initialize()
    {

        //�e�I�u�W�F���̂ɕK�v�ȏ�����
        ARGUMENT_INITIALIZE(create3D_.first, false);
        ARGUMENT_INITIALIZE(create3D_.second, (int)ZERO);
        ARGUMENT_INITIALIZE(createSigeboard_.first, false);
        ARGUMENT_INITIALIZE(createSigeboard_.second, (int)ZERO);
        ARGUMENT_INITIALIZE(createCameraTransition_.first, false);
        ARGUMENT_INITIALIZE(createCameraTransition_.second, (int)ZERO);
        ARGUMENT_INITIALIZE(createImage_.first, false);
        ARGUMENT_INITIALIZE(createImage_.second, (int)ZERO);
        ARGUMENT_INITIALIZE(objectCount_, (int)ZERO);
        ARGUMENT_INITIALIZE(info_,"");

        //�e�V�[���̃X�e�[�W��񂪓����Ă�t�@�C���̃p�X�ݒ�
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

    //�Q�[����ʂ��t���T�C�Y�ł͂Ȃ����̕`��
    void ImGuiSet::GameScreenNotFullDraw()
    {
        {
            //Imgui�X�^�[�g
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
        }

        //�X�e�[�W�쐬�pUI
        StageCreater();

        //�X�e�[�W�I�u�W�F�̃g�����X�t�H�[�����ׂĕ\������ImGui��\��
        StageObjImGuiDisplay();

        //�f�o�b�O�p�̃��O�\��
        DebugLogManager();

        //�V�[���`�F���W�p�̃{�^���\��
        SceneChangeButton();

        //�Q�[����ʐݒ�̕\��
        GameScreenNotFullPreference();

        //��ʂ̏�Ԑݒ�̕\��
        ScreenStatusPreference();
        
        //�v���Z�X���������\��
        ProcessMemory();

        //�t�@�C���ݒ�
        File();

        {
            ImGui::Render();
            //�`��
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        }
    }

    //�Q�[����ʂ��t���T�C�Y�̎��̕`��
    void GameScreenFullDraw()
    {
        {
            //Imgui�X�^�[�g
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
        }

        //�Q�[����ʐݒ�̕\��
        GameScreenFullPreference();

        {
            ImGui::Render();
            //�`��
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        }
    }

    ////////////////////////////////////�X�e�[�W�쐬�pImGui///////////////////////////////////////

    //�X�e�[�W�쐬����ImGui��UI���o���Ă����
    void ImGuiSet::StageCreater()
    {
        //window���
        ImGui::Begin("StageCreater");

        //3D�����{�^��
        if (ImGui::Button("Create3D", ImVec2(300, 50)))
        {
            create3D_.first = true;
            create3D_.second++;
        }

        //�Ŕ����{�^��
        if (ImGui::Button("CreateSigeboard", ImVec2(300, 50)))
        {
            createSigeboard_.first = true;
            createSigeboard_.second++;
        }

        //�J�����{�^��
        if (ImGui::Button("CreateCameraTransition", ImVec2(300, 50)))
        {
            createCameraTransition_.first = true;
            createCameraTransition_.second++;
        }

        //�摜�{�^��
        if (ImGui::Button("CreateImage", ImVec2(300, 50)))
        {
            createImage_.first = true;
            createImage_.second++;
        }

        //flag��true�Ȃ�֐����Ăяo��
        if (create3D_.first)
        {
            Create3D();
        }

        //flag��true�Ȃ�֐����Ăяo��
        if (createSigeboard_.first)
        {
            CreateSigeboard();
        }

        //flag��true�Ȃ�֐����Ăяo��
        if (createCameraTransition_.first)
        {
            CreateCameraTransition();
        }

        //flag��true�Ȃ�֐����Ăяo��
        if (createImage_.first)
        {
            CreateImage();
        }

        ImGui::End();
    }

    //3D�I�u�W�F�N�g�쐬
    void ImGuiSet::Create3D()
    {
        //�e�I�u�W�F�N�g�̏��
        static int status[MAX_OBJECT_SIZE] = {};
        static Mob* pNewObject[MAX_OBJECT_SIZE];
        static XMFLOAT3 pos[MAX_OBJECT_SIZE];
        static XMFLOAT3 rotate[MAX_OBJECT_SIZE];
        static XMFLOAT3 scale[MAX_OBJECT_SIZE];

        //Create3D�����������E�B���h�E�����@
        for (int i = 0; i < create3D_.second; i++)
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

                        //�v�b�V�����邽�߂�pair�^�����
                        //first->���[�h�������f���ԍ�
                        //second->���[�h�������f����transform
                        std::pair<int, Transform> a(Model::Load(text1[i]), t);
                        assert(a.first > 0);

                        //vector�Ɋi�[����
                        obj_.push_back(a);

                        pNewObject[i] = new Mob(GameManager::GetpSceneManager(), text1[i], "");
                        if (GameManager::GetpSceneManager()->GetParent() != nullptr)
                        {
                            GameManager::GetpSceneManager()->PushBackChild(pNewObject[i]);
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
                pNewObject[i]->SetAngle(rotate[i].y);
                pNewObject[i]->SetScale(scale[i]);
            }
        }
    }

    //�Ŕ쐬
    void ImGuiSet::CreateSigeboard()
    {
        //�e�I�u�W�F�N�g�̏��
        static int Sstatus[MAX_OBJECT_SIZE] = {};
        static Signboard* SpNewObject[MAX_OBJECT_SIZE];
        static XMFLOAT3 Spos[MAX_OBJECT_SIZE];
        static XMFLOAT3 Srotate[MAX_OBJECT_SIZE];
        static XMFLOAT3 Sscale[MAX_OBJECT_SIZE];
        static XMFLOAT3 SBasicPos = GameManager::GetpPlayer()->GetPosition();
        static XMFLOAT3 SBasicRotate = GameManager::GetpPlayer()->GetRotate();
        static XMFLOAT3 SBasicScale = GameManager::GetpPlayer()->GetScale();

        //Create3D�����������E�B���h�E�����@
        for (int i = 0; i < createSigeboard_.second; i++)
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

                        SpNewObject[i] = new Signboard(GameManager::GetpSceneManager(), Stext1[i], "");
                        if (GameManager::GetpSceneManager()->GetParent() != nullptr)
                        {
                            GameManager::GetpSceneManager()->PushBackChild(SpNewObject[i]);
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

    //�J�����̑J�ڍ쐬(�R���C�_�[�ɓ���������J�����̃|�W�V�����ς���@�\)
    void ImGuiSet::CreateCameraTransition()
    {
        //�e�I�u�W�F�N�g�̏��
        static int Cstatus[MAX_OBJECT_SIZE] = {};
        static Mob* CpNewObject[MAX_OBJECT_SIZE];
        static XMFLOAT3 Cpos[MAX_OBJECT_SIZE];
        static XMFLOAT3 CcameraPos[MAX_OBJECT_SIZE];
        static XMFLOAT3 CcameraTar[MAX_OBJECT_SIZE];
        static XMFLOAT3 CcolliderSize[MAX_OBJECT_SIZE];
        static XMFLOAT3 CBasicPos = GameManager::GetpPlayer()->GetPosition();
        static XMFLOAT3 CBasicRotate = GameManager::GetpPlayer()->GetRotate();
        static XMFLOAT3 CBasicScale = GameManager::GetpPlayer()->GetScale();

        //Create3D�����������E�B���h�E�����@
        for (int i = 0; i < createCameraTransition_.second; i++)
        {
            if (Cstatus[i] == 1 || Cstatus[i] == 0)
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
                    if (Cstatus[i] == 0)
                    {

                        //���[�h�����I�u�W�F�N�g�ɕK�v�ȃg�����X�t�H�[����p��
                        Transform t;

                        Cpos[i] = CBasicPos;
                        CcameraTar[i] = CBasicRotate;
                        CcolliderSize[i] = CBasicScale;

                        //�v�b�V�����邽�߂�pair�^�����
                        //first->���[�h�������f���ԍ�
                        //second->���[�h�������f����transform
                        std::pair<int, Transform> a(Model::Load(text1[i]), t);
                        assert(a.first > 0);

                        //vector�Ɋi�[����
                        obj_.push_back(a);

                        CpNewObject[i] = new Mob(GameManager::GetpSceneManager(), text1[i], "");
                        if (GameManager::GetpSceneManager()->GetParent() != nullptr)
                        {
                            GameManager::GetpSceneManager()->PushBackChild(CpNewObject[i]);
                        }
                        CpNewObject[i]->Initialize();

                        //status�v���X
                        Cstatus[i]++;

                    }
                }

                //��񃍁[�h���Ă�����
                if (Cstatus[i] == 1)
                {

                    //Position�̖�
                    if (ImGui::TreeNode("position")) {

                        //Position�Z�b�g
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

                    //Position�̖�
                    if (ImGui::TreeNode("CameraPosition")) {

                        //Position�Z�b�g
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

                    //Scale�̖�
                    if (ImGui::TreeNode("scale")) {

                        //Scale�Z�b�g
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

                    //rotate�̖�
                    if (ImGui::TreeNode("rotate")) {

                        //Rotate�Z�b�g
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

                        //�t�@�C���l�[�����͗�
                        static char text2[MAX_OBJECT_SIZE][50] = {};

                        //���͂��ꂽ������text1�Ɋi�[
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

                    //�E�B���h�E�폜
                    if (ImGui::Button("close"))
                    {
                        Cstatus[i]++;
                    }
                }

                ImGui::End();
            }

            //�`�悳���
            if (Cstatus[i] >= 1)
            {
                CpNewObject[i]->SetPosition(Cpos[i]);
                CpNewObject[i]->SetRotate(CcameraTar[i]);
                CpNewObject[i]->SetScale(CcolliderSize[i]);
            }
        }
    }

    //�摜�쐬
    void ImGuiSet::CreateImage()
    {
        //�e�摜�̏��
        static int Istatus[MAX_OBJECT_SIZE] = {};
        static ImageBase* IpNewObject[MAX_OBJECT_SIZE];
        static XMFLOAT3 Ipos[MAX_OBJECT_SIZE];
        static XMFLOAT3 Irotate[MAX_OBJECT_SIZE];
        static XMFLOAT3 Iscale[MAX_OBJECT_SIZE];

        //Create3D�����������E�B���h�E�����@
        for (int i = 0; i < createImage_.second; i++)
        {
            if (Istatus[i] == 1 || Istatus[i] == 0)
            {
                //i��FBX�̌��ɂ���
                char name[16];
                sprintf_s(name, "FBX %d", i);

                //window���
                ImGui::Begin(name);

                //�t�@�C���l�[�����͗�
                static char text1[MAX_OBJECT_SIZE][100] = {};

                //���͂��ꂽ������text1�Ɋi�[
                ImGui::InputText("FBX filename", text1[i], sizeof(text1[i]));

                //���[�h�{�^��
                if (ImGui::Button("Load"))
                {
                    //�����܂��������[�h���ĂȂ�������
                    if (Istatus[i] == 0)
                    {

                        //���[�h�����I�u�W�F�N�g�ɕK�v�ȃg�����X�t�H�[����p��
                        Transform t;

                        Ipos[i] = XMFLOAT3(0, 0, 0);
                        Irotate[i] = XMFLOAT3(0, 0, 0);
                        Iscale[i] = XMFLOAT3(1, 1, 1);

                        //�v�b�V�����邽�߂�pair�^�����
                        //first->���[�h�������f���ԍ�
                        //second->���[�h�������f����transform
                        std::pair<int, Transform> a(Image::Load(text1[i]), t);
                        assert(a.first > 0);

                        //vector�Ɋi�[����
                        obj_.push_back(a);

                        IpNewObject[i] = new ImageBase(GameManager::GetpSceneManager(), text1[i], "");
                        if (GameManager::GetpSceneManager()->GetParent() != nullptr)
                        {
                            GameManager::GetpSceneManager()->PushBackChild(IpNewObject[i]);
                        }
                        IpNewObject[i]->Initialize();

                        //status�v���X
                        Istatus[i]++;

                    }
                }

                //��񃍁[�h���Ă�����
                if (Istatus[i] == 1)
                {

                    //Position�̖�
                    if (ImGui::TreeNode("position")) {

                        //Position�Z�b�g
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

                    //Scale�̖�
                    if (ImGui::TreeNode("scale")) {

                        //Scale�Z�b�g
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

                    //rotate�̖�
                    if (ImGui::TreeNode("rotate")) {

                        //Rotate�Z�b�g
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

                        //�t�@�C���l�[�����͗�
                        static char text2[MAX_OBJECT_SIZE][50] = {};

                        //���͂��ꂽ������text1�Ɋi�[
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

                    //�E�B���h�E�폜
                    if (ImGui::Button("close"))
                    {
                        Istatus[i]++;
                    }
                }

                ImGui::End();
            }

            //�`�悳���
            if (Istatus[i] >= 1)
            {
                IpNewObject[i]->SetPosition(Ipos[i]);
                IpNewObject[i]->SetScale(Iscale[i]);
            }
        }

    }

    //////////////////////////////�X�e�[�W�̃I�u�W�F�N�g�̃g�����X�t�H�[���\��////////////////////////////

    //�X�e�[�W�I�u�W�F�̃g�����X�t�H�[�����ׂĕ\������ImGui��\��
    void ImGuiSet::StageObjImGuiDisplay()
    {
        //window���
        ImGui::Begin("StageObjTransformDisplay");

        //�X�e�[�W�I�u�W�F�̃g�����X�t�H�[�����ׂĕ\��
        StageObjTransformDisplay(GameManager::GetpSceneManager());

        //�I�u�W�F�N�g�̐�0�ɏ�����
        ARGUMENT_INITIALIZE(objectCount_, (int)ZERO);

        //�I���
        ImGui::End();
    }

    //�X�e�[�W�I�u�W�F�̃g�����X�t�H�[�����ׂĕ\��
    void ImGuiSet::StageObjTransformDisplay(GameObject* pObj)
    {
        //����null�Ȃ甲����
        if (pObj == nullptr) return;

        //�I�u�W�F�N�g�̐����₷
        objectCount_++;

        //�I�u�W�F�N�g�̖��O�����Ƃ��Ƃ̖��O�v���XobjectCount_�������O�ɂ���
        std::string objName = pObj->GetObjectName() + std::to_string(objectCount_);

        //�I�u�W�F�N�g�̖��O�Ŗ��O�\������
        if (ImGui::TreeNode(objName.c_str()))
        {
            //�ʒu
            float pos[3] = { pObj->GetPosition().x,pObj->GetPosition().y ,pObj->GetPosition().z };
            ImGui::DragFloat3("position", pos);
            pObj->SetPosition({ pos[0], pos[1], pos[2] });

            //��]
            float rotate[3] = { pObj->GetRotate().x,pObj->GetRotate().y ,pObj->GetRotate().z };
            ImGui::DragFloat3("rotation", rotate);
            pObj->SetRotate({ rotate[0],rotate[1],rotate[2] });

            //�g�嗦
            float scale[3] = { pObj->GetScale().x,pObj->GetScale().y ,pObj->GetScale().z };
            ImGui::DragFloat3("scale", scale);
            pObj->SetScale({ scale[0],scale[1],scale[2] });

            //�폜�{�^��
            if (ImGui::Button("Kill")) { pObj->KillMe(); }

            ImGui::TreePop();
        }

        for (auto itr = pObj->GetChildList()->begin(); itr != pObj->GetChildList()->end(); itr++)
        {
            StageObjTransformDisplay(*itr);
        }
    }

    //////////////////////////////////////���O�\��///////////////////////////////////////

    //�f�o�b�O���O���Ǘ�����(ImGui�͂����ŕ\������)
    void ImGuiSet::DebugLogManager()
    {
        //window���
        ImGui::Begin("DebugLog");

        //���O�\��
        for (auto i = variable_.rbegin(); i != variable_.rend(); i++)
        {
            ImGui::Text((*i).first.c_str());
            ImGui::SameLine();
            ImGui::Text((*i).second.c_str());
        }

        //�T�C�Y��1000�ȏ㌾������폜
        if (variable_.size() >= MAX_DEBUG_LOG_NUM)
            variable_.clear();

        //�I���
        ImGui::End();
    }

    //�C�ӂ̒l��\�����Ă����
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

        //true,false�ŕς���
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

    ///////////////////////////////�V�[���ύX�\��///////////////////////////////////////

    /// <summary>
    /// �V�[���ύX�p�{�^���\��
    /// </summary>
    void ImGuiSet::SceneChangeButton()
    {
        //window���
        ImGui::Begin("SceneChangeButton");

        //�{�^���쐬
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

        //�I���
        ImGui::End();
    }

    ///////////////////////////////�Q�[����ʐݒ�///////////////////////////////////////

    /// <summary>
    /// �Q�[����ʐݒ�
    /// </summary>
    void ImGuiSet::GameScreenNotFullPreference()
    {
        //window���
        ImGui::Begin("GameScreenNotFullPreference");

        //�{�^���쐬
        if (ImGui::Button("START", ImVec2(150, 60)) && Direct3D::GetScreenGameStatus()) Direct3D::SetTimeScale(false);
        ImGui::SameLine();
        if (ImGui::Button("STOP", ImVec2(150, 60)))Direct3D::SetTimeScale(true);
        ImGui::SameLine();
        if (ImGui::Button("GameScreenFull", ImVec2(150, 60)))Direct3D::SetGameFull(true);
        ImGui::SameLine();

        //�I���
        ImGui::End();
    }

    /// <summary>
    /// �Q�[����ʂ��t���T�C�Y�̎��̐ݒ�
    /// </summary>
    void ImGuiSet::GameScreenFullPreference()
    {
        //window���
        ImGui::Begin("GameScreenFullPreference");

        //�{�^���쐬
        if (ImGui::Button("START", ImVec2(150, 40)) && Direct3D::GetScreenGameStatus()) Direct3D::SetTimeScale(false);
        ImGui::SameLine();

        if (ImGui::Button("STOP", ImVec2(150, 40)))Direct3D::SetTimeScale(true);
        ImGui::SameLine();

        if (ImGui::Button("GameScreenNotFull", ImVec2(170, 40)))Direct3D::SetGameFull(false);
        ImGui::SameLine();

        //�I���
        ImGui::End();
    }

    /// <summary>
    /// ��ʂ̏�Ԑݒ�
    /// </summary>
    void ImGuiSet::ScreenStatusPreference()
    {
        //window���
        ImGui::Begin("ScreenStatus");

        //�{�^���쐬
        if (ImGui::Button("Game", ImVec2(230, 60)))
        {
            Direct3D::SetTimeScale(false);
            Direct3D::SetScreenGameStatus(true);
        }
        ImGui::SameLine();

        if (ImGui::Button("Scene", ImVec2(230, 60)))
        {
            Direct3D::SetTimeScale(true);
            Direct3D::SetScreenGameStatus(false);
            Camera::FrameCameraInitialize();
        }
        ImGui::SameLine();

        //�I���
        ImGui::End();
    }

    ///////////////////////////////�v���Z�X�������\��///////////////////////////////////////

    void ImGuiSet::ProcessMemory()
    {
        //window���
        ImGui::Begin("ProcessMemory");

        //�v���Z�X�������擾
        HANDLE processHandle = GetCurrentProcess();
        PROCESS_MEMORY_COUNTERS_EX pmc;

        for (int i = 0; i < 499; i++)
        {
            processMemory_[i] = processMemory_[i + 1];
        }

        if (GetProcessMemoryInfo(processHandle, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
            processMemory_[499] = (pmc.PrivateUsage / 1024) / 1024;
        }

        //�O���t�\��
        ImGui::PlotLines("", processMemory_, 500, 0, NULL, 1, 1000, ImVec2(580, 200));

        //�I���
        ImGui::End();
    }

    ///////////////////////////////�t�@�C��(�C���|�[�g�E�G�N�X�|�[�g)///////////////////////////////////////

    void ImGuiSet::File()
    {
        //window���
        ImGui::Begin("File");

        //�{�^���쐬
        if (ImGui::Button("Import", ImVec2(140, 60)))
        {
            Direct3D::SetTimeScale(true);
            Import();
        }
        ImGui::SameLine();

        if (ImGui::Button("Export", ImVec2(140, 60)))
        {
            Direct3D::SetTimeScale(true);
            Export();
        }
        ImGui::SameLine();

        //�I���
        ImGui::End();
    }

    //�X�e�[�W�C���|�[�g
    void ImGuiSet::Import()
    {
        //���݂̃J�����g�f�B���N�g�����o���Ă���
        char defaultCurrentDir[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

        //�t�@�C����������ϐ�
        char fileName[MAX_PATH] = "����.map"; 

        //�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
        OPENFILENAME ofn;                                          //���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
        ZeroMemory(&ofn, sizeof(ofn));                             //�\���̏�����
        ofn.lStructSize = sizeof(OPENFILENAME);                    //�\���̂̃T�C�Y
        ofn.lpstrFilter = TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");  //�t�@�C���̎��
        ofn.lpstrFile = fileName;               	               //�t�@�C����
        ofn.nMaxFile = MAX_PATH;                 	               //�p�X�̍ő啶����
        ofn.Flags = OFN_FILEMUSTEXIST;   		                   //�t���O�i�����t�@�C�������݂�����㏑���m�F�j
        ofn.lpstrDefExt = "map";                  	               //�f�t�H���g�g���q

        //�u�t�@�C����ۑ��v�_�C�A���O
        BOOL selFile;
        selFile = GetOpenFileName(&ofn);

        //�L�����Z�������璆�f
        if (selFile == FALSE) return;

        //�J�����g�f�B���N�g�������̈ʒu�ɖ߂�
        SetCurrentDirectory(defaultCurrentDir);

        //�X�e�[�W�쐬
        CreateStage* p = new CreateStage;
        p->LoadFileCreateStage((*GameManager::GetpSceneManager()->GetChildList()->begin()), fileName);
    }

    //�X�e�[�W�I�u�W�F�C���|�[�g���邽�߂̊֐�
    void ImGuiSet::ExportStageObjTransform(GameObject* pObj)
    {

        //�V�[���}�l�[�W���[���V�[���łȂ��̂Ȃ�
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

        //�q���̕�������
        for (auto itr = pObj->GetChildList()->begin(); itr != pObj->GetChildList()->end(); itr++)
        {
            ExportStageObjTransform(*itr);
        }
    }

    //�X�e�[�W�G�N�X�|�[�g
    void ImGuiSet::Export()
    {
        char fileName[MAX_PATH] = "����.txt";  //�t�@�C����������ϐ�

        //�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
        OPENFILENAME ofn;                         	               //���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
        ZeroMemory(&ofn, sizeof(ofn));            	               //�\���̏�����
        ofn.lStructSize = sizeof(OPENFILENAME);   	               //�\���̂̃T�C�Y
        ofn.lpstrFilter = TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");  //�t�@�C���̎��
        ofn.lpstrFile = fileName;               	               //�t�@�C����
        ofn.nMaxFile = MAX_PATH;                 	               //�p�X�̍ő啶����
        ofn.Flags = OFN_OVERWRITEPROMPT;   		                   //�t���O�i�����t�@�C�������݂�����㏑���m�F�j
        ofn.lpstrDefExt = "txt";                  	               //�f�t�H���g�g���q

        //�u�t�@�C����ۑ��v�_�C�A���O
        BOOL selFile;
        selFile = GetSaveFileName(&ofn);

        //�L�����Z�������璆�f
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

        //��������Ԃɂ��Ă���
        ARGUMENT_INITIALIZE(info_, "");

        //�X�e�[�W����info�Ɋi�[
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

    //�J��
    void ImGuiSet::Release()
    {
    }
}