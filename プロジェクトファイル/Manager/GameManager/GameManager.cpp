#include "GameManager.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/Component/EasingMove.h"
#include "../../Engine/ResourceManager/Easing.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../LifeManager/LifeManager.h"
#include "../CoinManager/CoinManager.h"
#include "../TextManager/TextManager.h"
#include "../MiniGameManager/MiniGameManager.h"
#include "../ButtonManager/ButtonManager.h"
#include "../AudioManager/CoinAudioManager/CoinAudioMAnager.h"
#include "../AudioManager/PlayerAudioManager/PlayerAudioManager.h"
#include "../AudioManager/OtherAudioManager/OtherAudioManager.h"
#include "../../OtherObject/UserInfomation.h"
#include "../../OtherObject/SelectPlanetController.h"
#include "../../UI/Pause/PauseUI.h"
#include <cmath>

//�Q�[���̂��낢��ȊǗ�������
namespace GameManager
{
	///////////////////////////////�ϐ�//////////////////////////////////

	//���ݎg�p����Ă���v���C���[�̃|�C���^�i�[�p
	PlayerBase* pNowPlayer_;

	//���݂̎g�p����Ă���X�e�[�W�̃|�C���^�i�[�p
	Stage* pNowStage_;

	//���݂̎g�p����Ă��郏�[�v�̃|�C���^�i�[�p
	Warp* pNowWarp_;

	//�V�[���}�l�[�W���[�̃|�C���^�i�[�p
	SceneManager* pSceneManager_;

	//�|�[�Y�̎��ɕ\������UI
	PauseUI* pPauseUI_;

	///////////////////////////////�֐�//////////////////////////////////

	//������
	void GameManager::Initialize()
	{
		//���[�U�[���̏�����
		UserInfomation::Initialize();

		//���[�U�[�I���V�[���Ǘ��̏�����
		SelectPlanetController::Initialize();

		CoinAudioManager::Initialize();
		OtherAudioManager::Initialize();
		PlayerAudioManager::Initialize();

		//���C�t�}�l�[�W���[�̏�����
		LifeManager::Initialize();

		//�R�C���}�l�[�W���[�̏�����
		CoinManager::Initialize();

		//�e�L�X�g�}�l�[�W���̏�����
		TextManager::Initialize();

		//�~�j�Q�[���}�l�[�W���[�̏�����
		MiniGameManager::Initialize();

		//�t�F�C�h�̏�����
		Fade::Initialize();

		//�e�ϐ�������
		ARGUMENT_INITIALIZE(pNowPlayer_, nullptr);
		ARGUMENT_INITIALIZE(pNowStage_, nullptr);
		ARGUMENT_INITIALIZE(pNowWarp_, nullptr);
		ARGUMENT_INITIALIZE(pSceneManager_, nullptr);
		ARGUMENT_INITIALIZE(pPauseUI_, new PauseUI);
	}

	//�V�[���J�ڂ̎��̏�����
	void GameManager::SceneTransitionInitialize()
	{
		//���낢�돉������Ԃɂ��Ă���
		Light::Initialize();
		Fade::SceneTransitionInitialize();
		MiniGameManager::Initialize();
		CoinManager::SceneTransitionInitialize();
		LifeManager::SceneTransitionInitialize();
		CoinAudioManager::SceneTransitionInitialize();
		OtherAudioManager::SceneTransitionInitialize();
		PlayerAudioManager::SceneTransitionInitialize();
		ARGUMENT_INITIALIZE(pPauseUI_, new PauseUI);
		CoinManager::KeepCoinUpdate();
	}

	//Player�����S��������LifeManager����Ă΂��
	void GameManager::PlayerDie()
	{
		//���C�t���ʂ��
		LifeManager::ResetLife();

		//�����{�X�̃V�[���Ȃ�R�C������������Ԃ�
		if (pSceneManager_->GetSceneId() == SCENE_ID_WORLD2) CoinManager::SetCoinKeep();

		//�������񂾃V�[�����`���[�g���A���V�[���Ȃ�
		if(pSceneManager_->GetSceneId() == SCENE_ID_TUTORIAL1 || pSceneManager_->GetSceneId() == SCENE_ID_TUTORIAL2)
			pSceneManager_->SameSceneInitializ(SCENE_ID_TUTORIAL1);
		//�~�j�Q�[���ɂ������V�[���Ȃ�
		else if(pSceneManager_->GetSceneId() == SCENE_ID_MINIGAME || pSceneManager_->GetSceneId() == SCENE_ID_MINIGAME_LEVEL_SELECT)
			pSceneManager_->SameSceneInitializ(SCENE_ID_MINIGAME_LEVEL_SELECT);
		//����ȊO�Ȃ�
		else
			pSceneManager_->SameSceneInitializ(SCENE_ID_HOME);
	}

	//�X�V
	void GameManager::Update()
	{
		//�X�^�[�g�{�^�������������܂��|�[�Y��ʂ�`�悵�Ă��Ȃ����C�ӂ̃V�[������Ȃ��̂Ȃ�|�[�Y��ʂ�UI�쐬
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START) && !pPauseUI_->isDrawUI()
			&& pSceneManager_->GetSceneId() != SCENE_ID_ENDROLES
			&& pSceneManager_->GetSceneId() != SCENE_ID_MINIGAME
			&& pSceneManager_->GetSceneId() != SCENE_ID_TITLE
			&& pSceneManager_->GetSceneId() != SCENE_ID_USER_SELECT) {
			pPauseUI_->CreateUI(); 
			Direct3D::SetTimeScale(true);
			OtherAudioManager::ClickAudio();
		}

		//�|�[�Y��ʂ̍X�V���Ă�
		pPauseUI_->Update();

		//�{�^���}�l�[�W���̍X�V���Ă�
		ButtonManager::Update();
	}

	//�`��(�R�C���̎擾����Player���C�t�̕\��)
	void GameManager::Draw()
	{
		//�����~�j�Q�[���Ȃ�
		if (pSceneManager_->GetSceneId() == SCENE_ID_MINIGAME)
		{
			//�~�j�Q�[���̊e����`��
			MiniGameManager::Draw();

			//�R�C���̎擾���̕\��
			CoinManager::Draw();
		}
		//����Play�V�[���Ȃ�
		else if (pSceneManager_->GetSceneId() != SCENE_ID_TITLE && pSceneManager_->GetSceneId() != SCENE_ID_USER_SELECT)
		{
			//Player���C�t�̕\��
			LifeManager::Draw();

			//�R�C���̎擾���̕\��
			CoinManager::Draw();
		}

		//Ui�Ȃǂ�\��
		Image::UiDraw();
		
		//�|�[�Y��ʂ̕`��
		pPauseUI_->Draw();

		//�t�F�[�h�p�̕`��
		Fade::Draw();
	}

	/// <summary>
	/// �|�[�Y��ʂ��폜
	/// </summary>
	void GameManager::PauseDelete()
	{
		pPauseUI_->AllRelease();
		Direct3D::SetTimeScale(false);
	}

	///////////////////////////////�Z�b�g�Q�b�g�֐�//////////////////////////////////
	
	//�v���C���[�̃|�C���^�Z�b�g
	void GameManager::SetpPlayer(PlayerBase* player) { pNowPlayer_ = player; }

	//�v���C���[�̃|�C���^�Q�b�g
	PlayerBase* GameManager::GetpPlayer() { return pNowPlayer_; }

	//�X�e�[�W�̃|�C���^�Z�b�g
	void GameManager::SetpStage(Stage* stage) { pNowStage_ = stage; }

	//�X�e�[�W�̃|�C���^�Q�b�g
	Stage* GameManager::GetpStage() { return pNowStage_; }

	//���[�v�̃|�C���^�Z�b�g
	void GameManager::SetpWarp(Warp* warp) { pNowWarp_ = warp; }

	//���[�v�̃|�C���^�Q�b�g
	Warp* GameManager::GetpWarp() { return pNowWarp_; }

	//�V�[���}�l�[�W���[�̃|�C���^�Z�b�g
	void GameManager::SetpSceneManager(SceneManager* scene) { pSceneManager_ = scene; }

	//�V�[���}�l�[�W���[�̃|�C���^�Q�b�g
	SceneManager* GameManager::GetpSceneManager() { return pSceneManager_; }

}