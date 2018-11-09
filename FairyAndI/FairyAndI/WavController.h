#ifndef _WAV_CONTROLLER_H_
#define _WAV_CONTROLLER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <vector>
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class WAVCONTROLLER
{
	private:
		HMMIO				Mmio;		    //MMIOハンドル
		MMIOINFO			MmioInfo;	    //MMIO情報構造体
		MMCKINFO			RiffChunk;	    //RIFFチャンク
		MMCKINFO			FormatChunk;	//フォーマットチャンク
		MMCKINFO			DataChunk;	    //DATA チャンク
		WAVEFORMATEX		WaveFormat;	    //WAVフォーマット構造体	
		std::vector<BYTE>	WaveData;		//音楽データ	
        UINT32			    LoopCount;		//ループ再生
		
	public:
		bool Load(LPCTSTR);

		const WAVEFORMATEX* GetFormat(void);
        const UINT32 GetLoop(void);
		const BYTE* GetWaveData(void);
		const std::size_t GetWaveSize(void);
};

#endif