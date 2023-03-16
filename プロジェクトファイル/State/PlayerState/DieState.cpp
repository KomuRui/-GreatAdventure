#include "DieState.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Player/PlayerBase.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Manager/MiniGameManager/MiniGameManager.h"
#include "../../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../../Engine/ResourceManager/Time.h"

//�萔
namespace
{
    static const float PLAYER_ANIM_SPEED = 1.0f;  //�A�j���[�V�����̍Đ����x
    static const float SCENE_CHANGE_TIME = 3.0f;  //�V�[���ύX����
}

//3D�p�X�V
void DieState::Update3D(PlayerBase* player)
{
    //�A�j���[�V���������S�Ɏ��S������ԂȂ�
    if (130 == Model::GetAnimFrame(player->GethModel()))
    {
        //�A�j���[�V������~
        Model::SetAnimFrame(player->GethModel(), 130, 130, ZERO);

        //�t�F�[�h�̃X�e�[�^�X��GAME_OVER��Ԃ���Ȃ����~�j�Q�[���V�[������Ȃ��̂Ȃ�
        if (Fade::GetFadeStatus() != FADE_GAME_OVER && GameManager::GetpSceneManager()->GetSceneId() != SCENE_ID_MINIGAME)
            Fade::SetFadeStatus(FADE_GAME_OVER);
        //�t�F�[�h�̃X�e�[�^�X��CIRCLE_OUT��Ԃ���Ȃ����~�j�Q�[���V�[���Ȃ�
        else if(Fade::GetFadeStatus() != FADE_CIRCLE_OUT && GameManager::GetpSceneManager()->GetSceneId() == SCENE_ID_MINIGAME)
            Fade::SetFadeStatus(FADE_CIRCLE_OUT);

        //�^�C�}�[�X�^�[�g
        Time::UnLock(hTime_);
    }

    //�萔�b�ȏ�o�����̂Ȃ�
    if (Time::GetTimef(hTime_) > SCENE_CHANGE_TIME && GameManager::GetpSceneManager()->GetSceneId() == SCENE_ID_MINIGAME)
        GameManager::PlayerDie();
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void DieState::Enter(PlayerBase* player)
{
    //�~�j�Q�[���̏�Ԃ�END��Ԃɂ���
    if (GameManager::GetpSceneManager()->GetSceneId() == SCENE_ID_MINIGAME)
    {
        MiniGameManager::ChangeMiniGameStatus(MiniGameStatus::END);
        MiniGameManager::SetResultDis(player->GetPosition().z);
    }

    //�^�C�}�[�ԍ�
    hTime_ = Time::Add();

    //�G�t�F�N�g
    PlayerEffectManager::DieEffect(player->GetPosition(), player->GetNormal());

    //�A�j���[�V����
    Model::SetAnimFrame(player->GethModel(), 70, 130, PLAYER_ANIM_SPEED);
    Model::SetAnimFlag(player->GethModel(), true);
}