#ifndef _SHADER_H_
#define _SHADER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <unordered_map>
#include "Main.h"

//�������N���X�錾������//
class SHADER
{
    public:
        LPD3DXEFFECT Effect;
        std::unordered_map<tstring, D3DXHANDLE> Technic;
        std::unordered_map<tstring, D3DXTECHNIQUE_DESC> Dectriptor;

    public:
        //HRESULT SetUP();
};

#endif