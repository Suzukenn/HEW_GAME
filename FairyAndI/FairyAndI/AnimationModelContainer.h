#ifndef _ANIMATION_MODEL_CONTAINER_H_
#define _ANIMATION_MODEL_CONTAINER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <vector>
#include "Main.h"

//�������N���X�錾������//
class ANIMATIONMODELCONTAINER : public D3DXMESHCONTAINER
{
    public:
        DWORD AttributeGroupValue;                      //������
        DWORD Weight;                                   //�d�݂̌�
        DWORD BoneValue;                                //�{�[���̐�

        std::vector<LPD3DXMATRIX> BoneMatrix;           //�S�Ẵ{�[���̃��[���h�s��̐擪�|�C���^�[
        std::vector<LPDIRECT3DTEXTURE9> Texture;        //����t����e�N�X�`��
        std::vector<D3DXATTRIBUTERANGE> AttributeTable; //�����e�[�u��
        std::vector<D3DXMATRIX> BoneOffsetMatrix;       //�t���[���Ƃ��Ẵ{�[���̃��[���h�s��

        LPD3DXBUFFER BoneBuffer;                        //�{�[���e�[�u��
};

#endif