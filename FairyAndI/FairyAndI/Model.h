#ifndef _MODEL_H_
#define _MODEL_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <vector>
#include "Main.h"

//�������O���錾������//
class MODELMANAGER;
class SHADER;

//�������N���X�錾������//
class MODEL
{
    private:
        DWORD MaterialValue;			                //�}�e���A�����̐�
        DWORD AttributeValue;		                    //������(�T�u�Z�b�g��)

        std::vector<D3DMATERIAL9> Material;	            //�}�e���A���z��
        std::vector<LPDIRECT3DTEXTURE9>	Texture;	    //�e�N�X�`���ւ̃|�C���^
        std::vector<LPD3DXATTRIBUTERANGE> Attribute;    //�����z��

        LPD3DXMESH Mesh;		                        //���b�V�����ւ̃|�C���^
        LPD3DXBUFFER MaterialBuffer;	                //�}�e���A�����ւ̃|�C���^

    public:
        void Draw(bool);
        void MODEL::Draw(std::weak_ptr<SHADER>&, LPCTSTR, UINT, D3DXMATRIX&);

        friend MODELMANAGER;
};

#endif