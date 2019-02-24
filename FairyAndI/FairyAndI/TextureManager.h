#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include <unordered_map>
#include "FileParameter.h"
#include "Main.h"


class TEXTURE;

//�������N���X�錾������//
class TEXTUREMANAGER
{
    private:
        static std::unordered_map<tstring, std::shared_ptr<TEXTURE>> Texture;

        static HRESULT Create(const FILEPARAMETER&);
        static HRESULT Load(std::vector<FILEPARAMETER>&, LPCTSTR);

    public:
        static HRESULT Initialize(LPCTSTR);
        static void Uninitialize(void);

        static HRESULT GetTexture(LPCTSTR, std::weak_ptr<TEXTURE>&);
};

#endif