#include "DieState.h"
#include "../../Engine/Model.h"
#include "../../Player/PlayerBase.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/Time.h"
#include "../../Manager/MiniGameManager/MiniGameManager.h"
#include "../../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"

//�萔
namespace
{
    static const float PLAYER_ANIM_SPEED = 1.0f;  //�A�j���[�V�����̍Đ����x
}

//3D�p�X�V
void DieState::Update3D(PlayerBase* player)
{
    //�A�j���[�V���������S�Ɏ��S������ԂȂ�
    if (130 == Model::GetAnimFrame(player->GethModel()))
    {
        //�A�j���[�V������~
        Model::SetAnimFrame(player->GethModel(), 130, 130, ZERO);

        //�t�F�[�h�̃X�e�[�^�X��FADE_OUT��Ԃ���Ȃ�������
        if (GameManager::GetStatus() != FADE_OUT)
            GameManager::SetStatus(FADE_OUT, "Image/Fade/BaseFade.png");
    }
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

    //�G�t�F�N�g
    PlayerEffectManager::DieEffect(player->GetPosition(), player->GetNormal());

    //�A�j���[�V����
    Model::SetAnimFrame(player->GethModel(), 70, 130, PLAYER_ANIM_SPEED);
    Model::SetAnimFlag(player->GethModel(), true);
}