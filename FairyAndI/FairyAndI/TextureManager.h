#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include <unordered_map>
#include "Main.h"
#include "TextureParameter.h"

//＝＝＝クラス宣言＝＝＝//
class TEXTUREMANAGER
{
    private:
        static std::unordered_map<tstring, LPDIRECT3DTEXTURE9> Texture;          	// WAVE 音楽データ

        static HRESULT Create(TEXTUREPARAMETER);
        static HRESULT Load(std::vector<TEXTUREPARAMETER>&, LPCTSTR);

    public:
        static HRESULT Initialize(LPCTSTR);
        static void Uninitialize(void);

        static LPDIRECT3DTEXTURE9 GetTexture(LPCTSTR);
};

#endif