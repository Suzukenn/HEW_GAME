#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include <unordered_map>
#include <xaudio2.h>
#include "Main.h"
#include "SoundParameter.h"
#include "WavController.h"

//＝＝＝クラス宣言＝＝＝//
class SOUNDMANAGER
{
    private:
        static std::unique_ptr<IXAudio2*> Manager;                                                   //管理オブジェクト
        static std::unique_ptr<IXAudio2MasteringVoice*> MasterVoice;                                 //マスターボイス
        static std::unordered_map<tstring, IXAudio2SourceVoice*> SourceVoice;  //ソースボイス
        static std::unordered_map<tstring, WAVCONTROLLER> WaveSound;          	// WAVE 音楽データ

        static HRESULT CreateSound(SOUNDPARAMETER, int);
        static HRESULT Load(std::vector<SOUNDPARAMETER>&);

    public:
        static HRESULT Initialize(void);
        static void Play(tstring);
        static void Pause(tstring);
        static void Stop(tstring);
        static void Uninitialize(void);
        static void Volume(tstring, float);
};

#endif