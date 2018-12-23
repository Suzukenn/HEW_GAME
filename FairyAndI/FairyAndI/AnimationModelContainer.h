#ifndef _ANIMATION_MODEL_CONTAINER_H_
#define _ANIMATION_MODEL_CONTAINER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <vector>
#include "Main.h"

//�������N���X�錾������//
class ANIMATIONMODELCONTAINER : public D3DXMESHCONTAINER
{
    public:
        LPDIRECT3DTEXTURE9* Textures;     //����t����e�N�X�`��
        LPD3DXATTRIBUTERANGE AttributeTable;//�����e�[�u��
        DWORD AttributeGroupValue;          //������

        DWORD Weight;                     //�d�݂̌��i�d�݂Ƃ͒��_�ւ̉e���B�j
        DWORD BoneValue;                  //�{�[���̐�
        LPD3DXBUFFER BoneBuffer;          //�{�[���E�e�[�u��
        LPD3DXMATRIX* BoneMatrix;         //�S�Ẵ{�[���̃��[���h�s��̐擪�|�C���^�[
        LPD3DXMATRIX BoneOffsetMatrix;    //�t���[���Ƃ��Ẵ{�[���̃��[���h�s��̃|�C���^�[
};

#endif