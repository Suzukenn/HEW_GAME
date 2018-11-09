#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include <unordered_map>
#include <xaudio2.h>
#include "Main.h"
#include "SoundParameter.h"
#include "WavController.h"

//�������N���X�錾������//
class SOUNDMANAGER
{
    private:
        static std::unique_ptr<IXAudio2*> Manager;                                                   //�Ǘ��I�u�W�F�N�g
        static std::unique_ptr<IXAudio2MasteringVoice*> MasterVoice;                                 //�}�X�^�[�{�C�X
        static std::unordered_map<tstring, IXAudio2SourceVoice*> SourceVoice;  //�\�[�X�{�C�X
        static std::unordered_map<tstring, WAVCONTROLLER> WaveSound;          	// WAVE ���y�f�[�^

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