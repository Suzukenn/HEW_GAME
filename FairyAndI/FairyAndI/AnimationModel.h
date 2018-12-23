#ifndef _ANIMATION_MODEL_H_
#define _ANIMATION_MODEL_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <vector>
#include "AnimationModelHierarchy.h"
#include "Main.h"

//�������O���錾������//
class ANIMATIONMODELFREAM;
class ANIMATIONMODELCONTAINER;

//�������N���X�錾������//
class ANIMATIONMODEL
{
    private:
        float PlaySpeed;                        //�A�j���[�V�����X�s�[�h
        DWORD CurrentTrack;                     //���݂̃A�j���[�V�����g���b�N
        D3DXTRACK_DESC CurrentTrackDescription; //���݂̃A�j���[�V�����f�[�^�g���b�N
        UINT AnimationSetValue;                 //�A�j���[�V�����Z�b�g
        D3DXMATRIX World;                       //���[���h�}�g���N�X
        ANIMATIONMODELHIERARCHY Hierarchy;      //�q�G�����L�[�N���X�ϐ�

        std::vector<LPD3DXANIMATIONSET> AnimationData;

        LPD3DXFRAME FrameRoot;                          //�{�[�����
        LPD3DXANIMATIONCONTROLLER AnimationController;  //�A�j���[�V�����R���g���[��

        HRESULT AllocateAllBoneMatrices(LPD3DXFRAME);
        HRESULT AllocateBoneMatrix(LPD3DXMESHCONTAINER);
        void DrawFrame(LPD3DXFRAME);
        void SetTime(double);
        void RenderMeshContainer(LPD3DXMESHCONTAINER, LPD3DXFRAME);
        void UpdateFrameMatrices(LPD3DXFRAME, LPD3DXMATRIX);

    public:
        ANIMATIONMODEL(void);
        ~ANIMATIONMODEL(void);

        void ChangeAnimation(DWORD);
        void Draw(D3DXMATRIX);
        HRESULT Initialize(LPCTSTR);
        void Uninitialize(void);
};

#endif