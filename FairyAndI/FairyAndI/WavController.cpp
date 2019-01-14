//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <vector>
#include "Main.h"
#include "WavController.h"

/////////////////////////////////////////////
//関数名：Load
//
//機能：データのロード
//
//引数：(TCHAR)ファイルパス,(UINT32)ループ
//
//戻り値：(bool)処理の成否
/////////////////////////////////////////////
bool WAVCONTROLLER::Load(LPCTSTR filepath, UINT32 loop)
{
    //---各種宣言---//
    LONG lSize;
    MMRESULT mResult;

    //---読み取り作業---//
    //ファイルオープン
    Mmio = mmioOpen((PTCHAR)filepath, &MmioInfo, MMIO_READ);
    if (!Mmio)
    {
        MessageBox(nullptr, TEXT("音楽ファイルを開けませんでした"), filepath, MB_ICONSTOP | MB_OK);
        return false;
    }

    //RIFFチャンクの検索
    RiffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    mResult = mmioDescend(Mmio, &RiffChunk, nullptr, MMIO_FINDRIFF);
    if (mResult != MMSYSERR_NOERROR)
    {
        MessageBox(nullptr, TEXT("RIFFチャンクが見つかりませんでした"), filepath, MB_ICONSTOP | MB_OK);
        mmioClose(Mmio, 0);
        return false;
    }

    //フォーマットチャンク検索
    FormatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
    mResult = mmioDescend(Mmio, &FormatChunk, &RiffChunk, MMIO_FINDCHUNK);
    if (mResult != MMSYSERR_NOERROR)
    {
        MessageBox(nullptr, TEXT("フォーマットチャンクが見つかりませんでした"), filepath, MB_ICONSTOP | MB_OK);
        mmioClose(Mmio, 0);
        return false;
    }

    //WAVEFORMATEX構造体にデータを読み込む
    lSize = mmioRead(Mmio, (HPSTR)&WaveFormat, FormatChunk.cksize);

    switch (lSize)
    {
        //読み込み限界
    case 0:
        MessageBox(nullptr, TEXT("これ以上読み込めませんでした"), filepath, MB_ICONSTOP | MB_OK);
        break;

        //読み取り失敗
    case -1:
        MessageBox(nullptr, TEXT("読み取りに失敗しました"), filepath, MB_ICONSTOP | MB_OK);
        break;

        //読み取り成功
    default:
        //データサイズの確認
        if (lSize != FormatChunk.cksize)
        {
            MessageBox(nullptr, TEXT("データサイズが一致しませんでした"), filepath, MB_ICONSTOP | MB_OK);
            mmioClose(Mmio, 0);
            return false;
        }
    }

    //読み込み位置を先頭に戻す
    mmioAscend(Mmio, &FormatChunk, 0);

    //データチャンク検索
    DataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
    mResult = mmioDescend(Mmio, &DataChunk, &RiffChunk, MMIO_FINDCHUNK);
    if (mResult != MMSYSERR_NOERROR)
    {
        MessageBox(nullptr, TEXT("データチャンクが見つかりませんでした"), filepath, MB_ICONSTOP | MB_OK);
        mmioClose(Mmio, 0);
        return false;
    }

    //音声データを読み込む
    WaveData.resize(DataChunk.cksize);
    if (mmioRead(Mmio, (HPSTR)WaveData.data(), DataChunk.cksize) != DataChunk.cksize)
    {
        MessageBox(nullptr, TEXT("音楽データを読み込めませんでした"), filepath, MB_ICONSTOP | MB_OK);
        mmioClose(Mmio, 0);
        return false;
    }
    WaveData.shrink_to_fit();

    //ファイルを閉じる
    mmioClose(Mmio, 0);

    LoopCount = loop;

    return true;
}

/////////////////////////////////////////////
//関数名：GetFormat
//
//機能：フォーマットの取得
//
//引数：なし
//
//戻り値：(const WAVEFORMATEX&)フォーマットのアドレス
/////////////////////////////////////////////
const WAVEFORMATEX& WAVCONTROLLER::GetFormat(void)
{
    return WaveFormat;
}

/////////////////////////////////////////////
//関数名：GetLoop
//
//機能：ループ情報の取得
//
//引数：なし
//
//戻り値：(UINT32)フォーマットのアドレス
/////////////////////////////////////////////
UINT32 WAVCONTROLLER::GetLoop(void)
{
    return LoopCount;
}

/////////////////////////////////////////////
//関数名：GetWaveData
//
//機能：Wavデータの取得
//
//引数：なし
//
//戻り値：(BYTE)Wavデータのアドレス
/////////////////////////////////////////////
const BYTE& WAVCONTROLLER::GetWaveData(void)
{
    return WaveData.at(0);
}

/////////////////////////////////////////////
//関数名：GetWaveSize
//
//機能：データサイズの取得
//
//引数：なし
//
//戻り値：(size_t)データサイズのアドレス
/////////////////////////////////////////////
std::size_t WAVCONTROLLER::GetWaveSize(void)
{
    return WaveData.size();
}