//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "Main.h"
#include "SoundManager.h"

//�������O���[�o���ϐ�������//
std::unique_ptr<IXAudio2*> SOUNDMANAGER::Manager;                                              //�Ǘ��I�u�W�F�N�g
std::unique_ptr<IXAudio2MasteringVoice*> SOUNDMANAGER::MasterVoice;                            //�}�X�^�[�{�C�X
std::unordered_map<tstring, IXAudio2SourceVoice*> SOUNDMANAGER::SourceVoice;  //�\�[�X�{�C�X
std::unordered_map<tstring, WAVCONTROLLER> SOUNDMANAGER::WaveSound;           //WAVE ���y�f�[�^

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FCreateSound
//
//�@�\�F�\�[�X�{�C�X�̍쐬
//
//�����F(SOUNDPARAM)���f�[�^,(int)�i�[�z��ԍ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT SOUNDMANAGER::CreateSound(SOUNDPARAMETER data, int nCounter)
{
    //---�e��錾---//
    WAVCONTROLLER wavBuffer;

    std::unique_ptr<IXAudio2SourceVoice*> pVoice;

    //---����������---//
    pVoice.reset(new IXAudio2SourceVoice*);

    //---�f�[�^�̓W�J---//
    //�t�@�C���̎w��m�F
    if (!data.FileName.data())
    {
        MessageBox(nullptr, TEXT("�J�����y�t�@�C����������܂���"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //�f�[�^�̃��[�h
    if (wavBuffer.Load(data.FileName.c_str()))
    {
        WaveSound.insert(std::make_pair(data.CallKey, wavBuffer));
    }
    else
    {
        MessageBox(nullptr, TEXT("�f�[�^�̃��[�h�Ɏ��s���܂���"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //�\�[�X�{�C�X�̍쐬
    if (SUCCEEDED((*Manager)->CreateSourceVoice(pVoice.get(), &WaveSound.at(data.CallKey).GetFormat())))
    {
        SourceVoice.insert(std::make_pair(data.CallKey, (*pVoice)));
    }
    else
    {
        MessageBox(nullptr, TEXT("�\�[�X�{�C�X�̍쐬�Ɏ��s���܂���"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�}�l�[�W���[�̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT SOUNDMANAGER::Initialize(void)
{
    //---�e��錾---//
    HRESULT hResult;

    std::vector<SOUNDPARAMETER> conList;

    //---����������---//
    Manager.reset(new IXAudio2*);
    MasterVoice.reset(new IXAudio2MasteringVoice*);

    //---�I�u�W�F�N�g����---//
    //XAudio2�I�u�W�F�N�g�̍쐬
    hResult = XAudio2Create(Manager.get());
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //�}�X�^�[�{�C�X�̐���
    hResult = (*Manager)->CreateMasteringVoice(MasterVoice.get());
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�}�X�^�[�{�C�X�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        SAFE_RELEASE((*Manager));
        return hResult;
    }

    //�t�@�C���̐ݒ�
    hResult = Load(conList);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�g���b�N���X�g�̓ǂݍ��݂Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        SAFE_RELEASE((*Manager));
        return hResult;
    }

    //�T�E���h�f�[�^�̍쐬
    for (auto& data : conList)
    {
        if (FAILED(CreateSound(data, 0)))
        {
            MessageBox(nullptr, TEXT("�T�E���h�f�[�^�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
            SAFE_RELEASE((*Manager));
            return hResult;
        }
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FLoad
//
//�@�\�F�ǂݍ��݃f�[�^�̊i�[
//
//�����F(SOUNDPARAM*)�y�ȃ��X�g
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT SOUNDMANAGER::Load(std::vector<SOUNDPARAMETER>& list)
{
    //---�e��錾---//
    int nCounter;
    std::string szFileName;
    std::string szKeyName;
    UINT32 nLoop;
    std::ifstream file(TEXT("Data/Sound/tracklist.txt"));

    //---����������---//
    nCounter = 0;
    list.resize(999);

    //---�t�@�C���̓ǂݍ���---//
    if (file.fail())
    {
        MessageBox(nullptr, TEXT("�g���b�N���X�g���J���܂���ł���"), TEXT("Data/Sound/tracklist.txt"), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //---�f�[�^�̒��o---//
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
//�֐����FUninitialize
//
//�@�\�F�}�l�[�W���[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SOUNDMANAGER::Uninitialize(void)
{
    //---���---//
    //�\�[�X�{�C�X�̔j��
    for (auto& data : SourceVoice)
    {
        data.second->Stop(0);
        data.second->DestroyVoice();
        data.second = nullptr;
    }

    //�}�X�^�[�{�C�X�̔j��
    (*MasterVoice)->DestroyVoice();
    (*MasterVoice) = nullptr;

    //XAudio2�I�u�W�F�N�g�̔j��
    SAFE_RELEASE((*Manager));
}

/////////////////////////////////////////////
//�֐����FPlay
//
//�@�\�F�T�E���h�̍Đ�
//
//�����F(tstring)�T�E���h��
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SOUNDMANAGER::Play(tstring label)
{
    //---�e��錾---//
    XAUDIO2_VOICE_STATE sState;
    XAUDIO2_BUFFER bBuffer;

    //---�o�b�t�@�̒l�ݒ�---//
    memset(&bBuffer, 0, sizeof(XAUDIO2_BUFFER));
    bBuffer.AudioBytes = (UINT)WaveSound.at(label).GetWaveSize();
    bBuffer.pAudioData = &WaveSound.at(label).GetWaveData();
    bBuffer.Flags = XAUDIO2_END_OF_STREAM;
    bBuffer.LoopCount = XAUDIO2_LOOP_INFINITE * WaveSound.at(label).GetLoop();

    //---��Ԏ擾---//
    SourceVoice.at(label)->GetState(&sState);

    //---�Đ�����---//
    if (sState.BuffersQueued)
    {
        //�ꎞ��~
        SourceVoice.at(label)->Stop(0);

        //�I�[�f�B�I�o�b�t�@�̍폜
        SourceVoice.at(label)->FlushSourceBuffers();
    }

    //---�I�[�f�B�I�o�b�t�@�̓o�^---//
    SourceVoice.at(label)->SubmitSourceBuffer(&bBuffer);

    //---�Đ�---//
    SourceVoice.at(label)->Start(0);
}

/////////////////////////////////////////////
//�֐����FStop
//
//�@�\�F�T�E���h�̈ꎞ��~
//
//�����F(tstring)�T�E���h��
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SOUNDMANAGER::Pause(tstring label)
{
    //---�e��錾---//
    XAUDIO2_VOICE_STATE sState;

    //---�Đ�����---//
    SourceVoice.at(label)->GetState(&sState);

    //---�Đ�����---//
    if (sState.BuffersQueued)
    {
        //---�ꎞ��~---//
        SourceVoice.at(label)->Stop(0);
    }
}

/////////////////////////////////////////////
//�֐����FStop
//
//�@�\�F�T�E���h�̒�~
//
//�����F(tstring)�T�E���h��
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SOUNDMANAGER::Stop(tstring label)
{
    //---�e��錾---//
    XAUDIO2_VOICE_STATE sState;

    //��Ԏ擾
    SourceVoice.at(label)->GetState(&sState);

    //---�Đ�����---//
    if (sState.BuffersQueued)
    {
        //�ꎞ��~
        SourceVoice.at(label)->Stop(0);

        //�I�[�f�B�I�o�b�t�@�̍폜
        SourceVoice.at(label)->FlushSourceBuffers();
    }
}

/////////////////////////////////////////////
//�֐����FVolume
//
//�@�\�F�T�E���h�̃{�����[���ݒ�
//
//�����F(tstring)�T�E���h��,(float)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SOUNDMANAGER::Volume(tstring label, float volume)
{
    //---���ʒ���---//
    if (SourceVoice.at(label))
    {
        SourceVoice.at(label)->SetVolume(volume);
    }
}