//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "Main.h"
#include "SoundManager.h"

//＝＝＝グローバル変数＝＝＝//
std::unique_ptr<IXAudio2*> SOUNDMANAGER::Manager;                                              //管理オブジェクト
std::unique_ptr<IXAudio2MasteringVoice*> SOUNDMANAGER::MasterVoice;                            //マスターボイス
std::unordered_map<tstring, IXAudio2SourceVoice*> SOUNDMANAGER::SourceVoice;  //ソースボイス
std::unordered_map<tstring, WAVCONTROLLER> SOUNDMANAGER::WaveSound;           //WAVE 音楽データ

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：CreateSound
//
//機能：ソースボイスの作成
//
//引数：(SOUNDPARAM)元データ,(int)格納配列番号
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SOUNDMANAGER::CreateSound(SOUNDPARAMETER data, int nCounter)
{
    //---各種宣言---//
    WAVCONTROLLER wavBuffer;

    std::unique_ptr<IXAudio2SourceVoice*> pVoice;

    //---初期化処理---//
    pVoice.reset(new IXAudio2SourceVoice*);

    //---データの展開---//
    //ファイルの指定確認
    if (!data.FileName.data())
    {
        MessageBox(nullptr, TEXT("開く音楽ファイルが見つかりません"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //データのロード
    if (wavBuffer.Load(data.FileName.c_str()))
    {
        WaveSound.insert(std::make_pair(data.CallKey, wavBuffer));
    }
    else
    {
        MessageBox(nullptr, TEXT("データのロードに失敗しました"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //ソースボイスの作成
    if (SUCCEEDED((*Manager)->CreateSourceVoice(pVoice.get(), &WaveSound.at(data.CallKey).GetFormat())))
    {
        SourceVoice.insert(std::make_pair(data.CallKey, (*pVoice)));
    }
    else
    {
        MessageBox(nullptr, TEXT("ソースボイスの作成に失敗しました"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    return S_OK;
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：マネージャーの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SOUNDMANAGER::Initialize(void)
{
    //---各種宣言---//
    HRESULT hResult;

    std::vector<SOUNDPARAMETER> conList;

    //---初期化処理---//
    Manager.reset(new IXAudio2*);
    MasterVoice.reset(new IXAudio2MasteringVoice*);

    //---オブジェクト準備---//
    //XAudio2オブジェクトの作成
    hResult = XAudio2Create(Manager.get());
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("XAudio2オブジェクトの作成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //マスターボイスの生成
    hResult = (*Manager)->CreateMasteringVoice(MasterVoice.get());
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("マスターボイスの作成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        SAFE_RELEASE((*Manager));
        return hResult;
    }

    //ファイルの設定
    hResult = Load(conList);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("トラックリストの読み込みに失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        SAFE_RELEASE((*Manager));
        return hResult;
    }

    //サウンドデータの作成
    for (auto& data : conList)
    {
        if (FAILED(CreateSound(data, 0)))
        {
            MessageBox(nullptr, TEXT("サウンドデータの作成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
            SAFE_RELEASE((*Manager));
            return hResult;
        }
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：Load
//
//機能：読み込みデータの格納
//
//引数：(SOUNDPARAM*)楽曲リスト
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SOUNDMANAGER::Load(std::vector<SOUNDPARAMETER>& list)
{
    //---各種宣言---//
    int nCounter;
    std::string szFileName;
    std::string szKeyName;
    UINT32 nLoop;
    std::ifstream file(TEXT("Data/Sound/tracklist.txt"));

    //---初期化処理---//
    nCounter = 0;
    list.resize(999);

    //---ファイルの読み込み---//
    if (file.fail())
    {
        MessageBox(nullptr, TEXT("トラックリストを開けませんでした"), TEXT("Data/Sound/tracklist.txt"), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //---データの抽出---//
    while (!file.eof())
    {
        file >> szFileName >> nLoop >> szKeyName;

#ifdef _UNICODE
        list.at(nCounter).FileName.resize(szFileName.size());
        list.at(nCounter).FileName = std::wstring(szFileName.begin(), szFileName.end());
        list.at(nCounter).LoopCount = nLoop;
        list.at(nCounter).CallKey.resize(szKeyName.size());
        list.at(nCounter).CallKey = std::wstring(szKeyName.begin(), szKeyName.end());
#else
        list.at(nCounter).FileName = szFileName.c_str();;
        list.at(nCounter).LoopCount = nLoop;
        list.at(nCounter).CallKey = szKeyName.c_str();
#endif

        nCounter++;
    }
    list.resize(nCounter);

    return S_OK;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：マネージャーの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SOUNDMANAGER::Uninitialize(void)
{
    //---解放---//
    //ソースボイスの破棄
    for (auto& data : SourceVoice)
    {
        data.second->Stop(0);
        data.second->DestroyVoice();
        data.second = nullptr;
    }

    //マスターボイスの破棄
    (*MasterVoice)->DestroyVoice();
    (*MasterVoice) = nullptr;

    //XAudio2オブジェクトの破棄
    SAFE_RELEASE((*Manager));
}

/////////////////////////////////////////////
//関数名：Play
//
//機能：サウンドの再生
//
//引数：(tstring)サウンド名
//
//戻り値：なし
/////////////////////////////////////////////
void SOUNDMANAGER::Play(tstring label)
{
    //---各種宣言---//
    XAUDIO2_VOICE_STATE sState;
    XAUDIO2_BUFFER bBuffer;

    //---バッファの値設定---//
    memset(&bBuffer, 0, sizeof(XAUDIO2_BUFFER));
    bBuffer.AudioBytes = (UINT)WaveSound.at(label).GetWaveSize();
    bBuffer.pAudioData = &WaveSound.at(label).GetWaveData();
    bBuffer.Flags = XAUDIO2_END_OF_STREAM;
    bBuffer.LoopCount = XAUDIO2_LOOP_INFINITE * WaveSound.at(label).GetLoop();

    //---状態取得---//
    SourceVoice.at(label)->GetState(&sState);

    //---再生判定---//
    if (sState.BuffersQueued)
    {
        //一時停止
        SourceVoice.at(label)->Stop(0);

        //オーディオバッファの削除
        SourceVoice.at(label)->FlushSourceBuffers();
    }

    //---オーディオバッファの登録---//
    SourceVoice.at(label)->SubmitSourceBuffer(&bBuffer);

    //---再生---//
    SourceVoice.at(label)->Start(0);
}

/////////////////////////////////////////////
//関数名：Stop
//
//機能：サウンドの一時停止
//
//引数：(tstring)サウンド名
//
//戻り値：なし
/////////////////////////////////////////////
void SOUNDMANAGER::Pause(tstring label)
{
    //---各種宣言---//
    XAUDIO2_VOICE_STATE sState;

    //---再生判定---//
    SourceVoice.at(label)->GetState(&sState);

    //---再生判定---//
    if (sState.BuffersQueued)
    {
        //---一時停止---//
        SourceVoice.at(label)->Stop(0);
    }
}

/////////////////////////////////////////////
//関数名：Stop
//
//機能：サウンドの停止
//
//引数：(tstring)サウンド名
//
//戻り値：なし
/////////////////////////////////////////////
void SOUNDMANAGER::Stop(tstring label)
{
    //---各種宣言---//
    XAUDIO2_VOICE_STATE sState;

    //状態取得
    SourceVoice.at(label)->GetState(&sState);

    //---再生判定---//
    if (sState.BuffersQueued)
    {
        //一時停止
        SourceVoice.at(label)->Stop(0);

        //オーディオバッファの削除
        SourceVoice.at(label)->FlushSourceBuffers();
    }
}

/////////////////////////////////////////////
//関数名：Volume
//
//機能：サウンドのボリューム設定
//
//引数：(tstring)サウンド名,(float)音量
//
//戻り値：なし
/////////////////////////////////////////////
void SOUNDMANAGER::Volume(tstring label, float volume)
{
    //---音量調整---//
    if (SourceVoice.at(label))
    {
        SourceVoice.at(label)->SetVolume(volume);
    }
}