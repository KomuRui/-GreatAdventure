#include <vector>
#include "Audio.h"

//3D画像を管理する
namespace Audio
{
    //サウンドクラスのオブジェクト
    Sound* pSound_;

    //ロード済みの画像データ一覧
    std::vector<AudioData*>	data_;
    int isPlaySe_ = 1;
    int isPlayBgm_ = 1;


    //初期化
    void Initialize(const HWND hWnd)
    {
        pSound_ = new Sound;
        pSound_->Initialize(hWnd);

        AllRelease();
    }


    //サウンドファイルをロード
    int Load(const std::string& fileName)
    {
        auto* pData = new AudioData;

        //開いたファイル一覧から同じファイル名のものが無いか探す
        bool isExist = false;

        for (auto& index : data_)
        {
            //すでに開いている場合
            if (index != nullptr && index->fileName == fileName)
            {
                pData->pSoundBuffer = index->pSoundBuffer;
                isExist = true;
                break;
            }
        }

        //新たにファイルを開く
        if (isExist == false)
        {
            pData->pSoundBuffer = new LPDIRECTSOUNDBUFFER;

            if (FAILED(pSound_->Load(pData->pSoundBuffer, fileName)))
            {
                //開けなかった
                SAFE_DELETE(pData)
                    return -1;
            }

            //無事開けた
            pData->fileName = fileName;
        }


        //使ってない番号が無いか探す
        for (int index = 0; index < data_.size(); ++index)
        {
            if (data_[index] == nullptr)
            {
                data_[index] = pData;
                return index;
            }
        }

        //新たに追加
        data_.push_back(pData);
        return static_cast<int>(data_.size()) - 1;
    }



    //再生
    void Play(const int handle)
    {
        if (handle < 0 || handle >= data_.size() || data_[handle] == nullptr)
        {
            return;
        }

        if (isPlaySe_)
            Sound::Play(data_[handle]->pSoundBuffer);
    }

    void PlayLoop(const int handle)
    {
        if (handle < 0 || handle >= data_.size() || data_[handle] == nullptr) {
            return;
        }

        if (isPlayBgm_)
            Sound::PlayLoop(data_[handle]->pSoundBuffer);
    }


    //停止
    void Stop(const int handle)
    {
        if (handle < 0 || handle >= data_.size() || data_[handle] == nullptr)
        {
            return;
        }

        Sound::Stop(data_[handle]->pSoundBuffer);
    }



    //任意のサウンドを開放
    void Release(const int handle)
    {
        if (handle < 0 || handle >= data_.size())
        {
            return;
        }

        //同じサウンドを他でも使っていないか
        bool isExist = false;

        for (int index = 0; index < data_.size(); ++index)
        {
            //すでに開いている場合
            if (data_[index] != nullptr && index != handle && data_[index]->pSoundBuffer == data_[handle]->pSoundBuffer)
            {
                isExist = true;
                break;
            }
        }

        //使ってなければモデル解放
        if (isExist == false)
        {
            SAFE_DELETE(data_[handle]->pSoundBuffer)
        }


        SAFE_DELETE(data_[handle])
    }



    //全てのサウンドを解放
    void AllRelease()
    {
        for (int index = 0; index < data_.size(); ++index)
        {
            Release(index);
        }
        data_.clear();
    }


    //ゲーム終了時に行う処理
    void ReleaseDirectSound()
    {
        SAFE_DELETE(pSound_)
    }
}
