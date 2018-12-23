#ifndef _ANIMATION_MODEL_HIERARCHY_H_
#define _ANIMATION_MODEL_HIERARCHY_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class ANIMATIONMODELHIERARCHY : public ID3DXAllocateHierarchy
{
    private:
        std::array<TCHAR, _MAX_PATH> FileDirectory;	// Xファイルのあるディレクトリ

    public:
        ANIMATIONMODELHIERARCHY(void);
        STDMETHOD(CreateFrame)(THIS_ LPCSTR, LPD3DXFRAME*);
        STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR, CONST D3DXMESHDATA*, CONST D3DXMATERIAL*, CONST D3DXEFFECTINSTANCE*, DWORD, CONST DWORD*, LPD3DXSKININFO, LPD3DXMESHCONTAINER*);
        STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME);
        STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER);

        void SetDirectory(LPCTSTR);
};

#endif