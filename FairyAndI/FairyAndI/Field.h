#ifndef _FIELD_H_
#define _FIELD_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "Main.h"
#include "Model.h"
#include "Transform.h"

//＝＝＝クラス宣言＝＝＝//
class FIELD
{
    private:
        TRANSFORM Transform;
        LPDIRECT3DTEXTURE9 Texture;
        static LPD3DXMESH Mesh;
        LPD3DXBUFFER MaterialBuffer;
        DWORD MaterialValue;

    public:
        static bool CheckField(LPD3DXVECTOR3, LPD3DXVECTOR3, float&);
        void Draw(void);
        HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
        void Uninitialize(void);
        void Update(void);
};

#endif