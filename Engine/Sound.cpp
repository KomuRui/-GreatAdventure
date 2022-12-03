#include<cassert>
#include "Sound.h"


//コンストラクタ
Sound::Sound() :
    pDSound_(nullptr),
    pPrimary_(nullptr)
{
}


//デストラクタ
Sound::~Sound()
{
    Release();
}

//初期化
void Sound::Initialize(const HWND hWnd)
{
    // COMの初期化
    CoInitialize(nullptr);

    // DirectSound8を作成
    HRESULT ret = DirectSoundCreate8(nullptr, &pDSound_, nullptr);
    assert(SUCCEEDED(ret));


    // 強調モード
    ret = pDSound_->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE | DSSCL_PRIORITY);
    assert(SUCCEEDED(ret));

    //プライマリサウンドバッファの作成
    CreatePrimaryBuffer();
}



//プライマリサウンドバッファの作成
void Sound::CreatePrimaryBuffer()
{
    WAVEFORMATEX wf;

    // プライマリサウンドバッファの作成
    DSBUFFERDESC dsDesc;
    ZeroMemory(&dsDesc, sizeof(DSBUFFERDESC));
    dsDesc.dwSize = sizeof(DSBUFFERDESC);
    dsDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
    dsDesc.dwBufferBytes = 0;
    dsDesc.lpwfxFormat = nullptr;

    HRESULT ret = pDSound_->CreateSoundBuffer(&dsDesc, &pPrimary_, nullptr);

    assert(SUCCEEDED(ret));

    // プライマリバッファのステータスを決定
    wf.cbSize = sizeof(WAVEFORMATEX);
    wf.wFormatTag = WAVE_FORMAT_PCM;
    wf.nChannels = 2;
    wf.nSamplesPerSec = 44100;
    wf.wBitsPerSample = 16;
    wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
    wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
    ret = pPrimary_->SetFormat(&wf);
    assert(SUCCEEDED(ret));
}


//ファイルのロード
HRESULT Sound::Load(LPDIRECTSOUNDBUFFER* dsb, const std::string& fileName) const
{
    MMCKINFO mSrcWaveFile;
    MMCKINFO mSrcWaveFmt;
    MMCKINFO mSrcWaveData;

    const HMMIO hSrc = mmioOpenA(const_cast<LPSTR>(fileName.c_str()), nullptr, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);

    if (!hSrc)
    {
        return E_FAIL;
    }

    // 'WAVE'チャンクチェック
    ZeroMemory(&mSrcWaveFile, sizeof(mSrcWaveFile));
    HRESULT ret = mmioDescend(hSrc, &mSrcWaveFile, nullptr, MMIO_FINDRIFF);
    assert(mSrcWaveFile.fccType == mmioFOURCC('W', 'A', 'V', 'E'));

    // 'fmt 'チャンクチェック
    ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
    ret = mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK);
    assert(mSrcWaveFmt.ckid == mmioFOURCC('f', 'm', 't', ' '));

    // ヘッダサイズの計算
    int iSrcHeaderSize = mSrcWaveFmt.cksize;
    if (iSrcHeaderSize < sizeof(WAVEFORMATEX))
        iSrcHeaderSize = sizeof(WAVEFORMATEX);

    // ヘッダメモリ確保
    const auto wf = static_cast<LPWAVEFORMATEX>(malloc(iSrcHeaderSize));

    assert(wf);
    ZeroMemory(wf, iSrcHeaderSize);

    // WAVEフォーマットのロード
    ret = mmioRead(hSrc, reinterpret_cast<char*>(wf), mSrcWaveFmt.cksize);
    assert(SUCCEEDED(ret));


    // fmtチャンクに戻る
    mmioAscend(hSrc, &mSrcWaveFmt, 0);

    // dataチャンクを探す
    while (true)
    {
        // 検索
        ret = mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, 0);
        assert(SUCCEEDED(ret));

        if (mSrcWaveData.ckid == mmioStringToFOURCCA("data", 0))
            break;

        // 次のチャンクへ
        ret = mmioAscend(hSrc, &mSrcWaveData, 0);
    }

    // サウンドバッファの作成
    DSBUFFERDESC dsDesc;
    ZeroMemory(&dsDesc, sizeof(DSBUFFERDESC));
    dsDesc.dwSize = sizeof(DSBUFFERDESC);
    dsDesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER;
    dsDesc.dwBufferBytes = mSrcWaveData.cksize;
    dsDesc.lpwfxFormat = wf;
    dsDesc.guid3DAlgorithm = DS3DALG_DEFAULT;
    ret = pDSound_->CreateSoundBuffer(&dsDesc, dsb, nullptr);
    assert(SUCCEEDED(ret));

    // ロック開始
    LPVOID pMem1, pMem2;
    DWORD dwSize1, dwSize2;
    ret = (*dsb)->Lock(0, mSrcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0);
    assert(SUCCEEDED(ret));

    // データ書き込み
    mmioRead(hSrc, static_cast<char*>(pMem1), dwSize1);
    mmioRead(hSrc, static_cast<char*>(pMem2), dwSize2);

    // ロック解除
    (*dsb)->Unlock(pMem1, dwSize1, pMem2, dwSize2);

    // ヘッダ用メモリを開放
    free(wf);

    // WAVを閉じる
    mmioClose(hSrc, 0);

    return S_OK;

}

//再生
void Sound::Play(LPDIRECTSOUNDBUFFER* dsb)
{

    (*dsb)->SetCurrentPosition(0);
    (*dsb)->Play(0, 0, 0);
}

void Sound::PlayLoop(LPDIRECTSOUNDBUFFER* dsb) {

    (*dsb)->SetCurrentPosition(0);
    (*dsb)->Play(0, 0, DSBPLAY_LOOPING);
}

//停止
void Sound::Stop(LPDIRECTSOUNDBUFFER* dsb)
{
    (*dsb)->Stop();
}

//開放
void Sound::Release() const
{
    pPrimary_->Release();
    pDSound_->Release();

    // COMの終了
    CoUninitialize();
}
