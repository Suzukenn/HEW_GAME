//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <vector>
#include "Main.h"
#include "WavController.h"

/////////////////////////////////////////////
//�֐����FLoad
//
//�@�\�F�f�[�^�̃��[�h
//
//�����F(TCHAR)�t�@�C���p�X,(UINT32)���[�v
//
//�߂�l�F(bool)�����̐���
/////////////////////////////////////////////
bool WAVCONTROLLER::Load(LPCTSTR filepath, UINT32 loop)
{
    //---�e��錾---//
    LONG lSize;
    MMRESULT mResult;

    //---�ǂݎ����---//
    //�t�@�C���I�[�v��
    Mmio = mmioOpen((PTCHAR)filepath, &MmioInfo, MMIO_READ);
    if (!Mmio)
    {
        MessageBox(nullptr, TEXT("���y�t�@�C�����J���܂���ł���"), filepath, MB_ICONSTOP | MB_OK);
        return false;
    }

    //RIFF�`�����N�̌���
    RiffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    mResult = mmioDescend(Mmio, &RiffChunk, nullptr, MMIO_FINDRIFF);
    if (mResult != MMSYSERR_NOERROR)
    {
        MessageBox(nullptr, TEXT("RIFF�`�����N��������܂���ł���"), filepath, MB_ICONSTOP | MB_OK);
        mmioClose(Mmio, 0);
        return false;
    }

    //�t�H�[�}�b�g�`�����N����
    FormatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
    mResult = mmioDescend(Mmio, &FormatChunk, &RiffChunk, MMIO_FINDCHUNK);
    if (mResult != MMSYSERR_NOERROR)
    {
        MessageBox(nullptr, TEXT("�t�H�[�}�b�g�`�����N��������܂���ł���"), filepath, MB_ICONSTOP | MB_OK);
        mmioClose(Mmio, 0);
        return false;
    }

    //WAVEFORMATEX�\���̂Ƀf�[�^��ǂݍ���
    lSize = mmioRead(Mmio, (HPSTR)&WaveFormat, FormatChunk.cksize);

    switch (lSize)
    {
        //�ǂݍ��݌��E
    case 0:
        MessageBox(nullptr, TEXT("����ȏ�ǂݍ��߂܂���ł���"), filepath, MB_ICONSTOP | MB_OK);
        break;

        //�ǂݎ�莸�s
    case -1:
        MessageBox(nullptr, TEXT("�ǂݎ��Ɏ��s���܂���"), filepath, MB_ICONSTOP | MB_OK);
        break;

        //�ǂݎ�萬��
    default:
        //�f�[�^�T�C�Y�̊m�F
        if (lSize != FormatChunk.cksize)
        {
            MessageBox(nullptr, TEXT("�f�[�^�T�C�Y����v���܂���ł���"), filepath, MB_ICONSTOP | MB_OK);
            mmioClose(Mmio, 0);
            return false;
        }
    }

    //�ǂݍ��݈ʒu��擪�ɖ߂�
    mmioAscend(Mmio, &FormatChunk, 0);

    //�f�[�^�`�����N����
    DataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
    mResult = mmioDescend(Mmio, &DataChunk, &RiffChunk, MMIO_FINDCHUNK);
    if (mResult != MMSYSERR_NOERROR)
    {
        MessageBox(nullptr, TEXT("�f�[�^�`�����N��������܂���ł���"), filepath, MB_ICONSTOP | MB_OK);
        mmioClose(Mmio, 0);
        return false;
    }

    //�����f�[�^��ǂݍ���
    WaveData.resize(DataChunk.cksize);
    if (mmioRead(Mmio, (HPSTR)WaveData.data(), DataChunk.cksize) != DataChunk.cksize)
    {
        MessageBox(nullptr, TEXT("���y�f�[�^��ǂݍ��߂܂���ł���"), filepath, MB_ICONSTOP | MB_OK);
        mmioClose(Mmio, 0);
        return false;
    }
    WaveData.shrink_to_fit();

    //�t�@�C�������
    mmioClose(Mmio, 0);

    LoopCount = loop;

    return true;
}

/////////////////////////////////////////////
//�֐����FGetFormat
//
//�@�\�F�t�H�[�}�b�g�̎擾
//
//�����F�Ȃ�
//
//�߂�l�F(const WAVEFORMATEX&)�t�H�[�}�b�g�̃A�h���X
/////////////////////////////////////////////
const WAVEFORMATEX& WAVCONTROLLER::GetFormat(void)
{
    return WaveFormat;
}

/////////////////////////////////////////////
//�֐����FGetLoop
//
//�@�\�F���[�v���̎擾
//
//�����F�Ȃ�
//
//�߂�l�F(UINT32)�t�H�[�}�b�g�̃A�h���X
/////////////////////////////////////////////
UINT32 WAVCONTROLLER::GetLoop(void)
{
    return LoopCount;
}

/////////////////////////////////////////////
//�֐����FGetWaveData
//
//�@�\�FWav�f�[�^�̎擾
//
//�����F�Ȃ�
//
//�߂�l�F(BYTE)Wav�f�[�^�̃A�h���X
/////////////////////////////////////////////
const BYTE& WAVCONTROLLER::GetWaveData(void)
{
    return WaveData.at(0);
}

/////////////////////////////////////////////
//�֐����FGetWaveSize
//
//�@�\�F�f�[�^�T�C�Y�̎擾
//
//�����F�Ȃ�
//
//�߂�l�F(size_t)�f�[�^�T�C�Y�̃A�h���X
/////////////////////////////////////////////
std::size_t WAVCONTROLLER::GetWaveSize(void)
{
    return WaveData.size();
}