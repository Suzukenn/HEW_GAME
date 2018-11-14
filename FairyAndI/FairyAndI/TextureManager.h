#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include <unordered_map>
#include "Main.h"
#include "TextureParameter.h"

//�������N���X�錾������//
class TEXTUREMANAGER
{
    private:
        static std::unordered_map<tstring, LPDIRECT3DTEXTURE9> Texture;

        static HRESULT Create(const TEXTUREPARAMETER&);
        static HRESULT Load(std::vector<TEXTUREPARAMETER>&, LPCTSTR);

    public:
        static HRESULT Initialize(LPCTSTR);
        static void Uninitialize(void);

        static HRESULT GetTexture(LPCTSTR, LPDIRECT3DTEXTURE9&);
};

#endif