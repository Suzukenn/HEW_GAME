//�������w�b�_�t�@�C���ǂݍ��݁�����//
#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include "AnimationModel.h"
#include "AnimationModelContainer.h"
#include "AnimationModelFrame.h"
#include "AnimationModelHierarchy.h"
#include "InputManager.h"
#include "Main.h"

//�������萔�E�}�N����`������//
#define SKIN_ANIME_SPEED 0.000125F    //�A�j���[�V�����R���g���[���[�̃X�s�[�h

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FAllocateBoneMatrix
//
//�@�\�F�{�[���s��̃A���P�[�g
//
//�����F(LPD3DXFRAME)�����t���[��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ANIMATIONMODEL::AllocateAllBoneMatrices(LPD3DXFRAME frame)
{
    //---�e��錾---//
    HRESULT hResult;

    ANIMATIONMODELFREAM* pFrame;

    //---����������---//
    pFrame = (ANIMATIONMODELFREAM*)frame;

    //�K�w�̑���(���������m�ۂ������b�V���R���e�i�̈��T������)
    if (frame->pMeshContainer)
    {
        //�{�[���s��̏���������
        hResult = AllocateBoneMatrix(frame->pMeshContainer);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("�{�[���s��̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
            return hResult;
        }
    }

    //�ċA���f����
    if (frame->pFrameSibling)
    {
        hResult = AllocateAllBoneMatrices(frame->pFrameSibling);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("�Z��t���[���̃{�[���s��̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
            return hResult;
        }
    }
    if (frame->pFrameFirstChild)
    {
        hResult = AllocateAllBoneMatrices(frame->pFrameFirstChild);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("�q�t���[���̃{�[���s��̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
            return hResult;
        }
    }
    return S_OK;
}

/////////////////////////////////////////////
//�֐����FAllocateBoneMatrix
//
//�@�\�F�{�[���}�g���N�X�̐���
//
//�����F(LPD3DXMESHCONTAINER)���b�V���R���e�i
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ANIMATIONMODEL::AllocateBoneMatrix(LPD3DXMESHCONTAINER meshcontainer)
{
    //---�e��錾---//
    DWORD dwBoneValue;
    DWORD dwCounter;

    ANIMATIONMODELFREAM* pFrame;
    ANIMATIONMODELCONTAINER* pMeshContainer;

    //---����������---//
    pMeshContainer = (ANIMATIONMODELCONTAINER*)meshcontainer;

    //�X�L�����b�V���łȂ���΂Ȃɂ����Ȃ�
    if (!pMeshContainer->pSkinInfo)
    {
        return S_OK;
    }

    dwBoneValue = pMeshContainer->pSkinInfo->GetNumBones();     //�{�[���̐��擾
    pMeshContainer->BoneMatrix.resize(dwBoneValue); //�e�{�[���̃��[���h�s��i�[�p�̈���m��

    //---�{�[���̃|�C���^�̊i�[---//
    for (dwCounter = 0; dwCounter < dwBoneValue; ++dwCounter)
    {
        //�q�t���[��(�{�[��)�̃A�h���X���������Ċi�[
        pFrame = (ANIMATIONMODELFREAM*)D3DXFrameFind(FrameRoot, pMeshContainer->pSkinInfo->GetBoneName(dwCounter));

        if (pFrame)
        {
            //�e�{�[���̃��[���h�s��i�[�p�ϐ��ɍŏI�s����i�[
            pMeshContainer->BoneMatrix.at(dwCounter) = &pFrame->CombinedTransformationMatrix;
        }
        else
        {
            return E_FAIL;
        }
    }
    return S_OK;
}

/////////////////////////////////////////////
//�֐����FChangeAnimation
//
//�@�\�F�Đ��A�j���[�V�����̕ύX
//
//�����F(DWORD)�Đ��A�j���[�V�����ԍ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ANIMATIONMODEL::ChangeAnimation(DWORD animationnumber)
{
    //�w��l�̋��E�`�F�b�N
    if (animationnumber >= AnimationData.size())
    {
        return;
    }
    else if (CurrentTrack == animationnumber)
    {
        return;
    }
    else
    {
        CurrentTrack = animationnumber;

        //�A�j���[�V�������ŏ��̈ʒu����Đ�������
        if (FAILED(AnimationController->SetTrackAnimationSet(0, AnimationData.at(animationnumber))))
        {
            MessageBox(nullptr, TEXT("�A�j���[�V�����̕ύX�Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
            exit(EXIT_FAILURE);
        }

    }
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F���f���̕`��
//
//�����F(D3DXMATRIX)���[���h�}�g���N�X,(bool)�G�t�F�N�g�̗L�����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ANIMATIONMODEL::Draw(D3DXMATRIX worldmatrix, bool effect)
{
    // �A�j���[�V�����X�V
    if (AnimationController)
    {
        //�A�j���[�V�������ԃf�[�^�̍X�V
        if (FAILED(AnimationController->AdvanceTime(SKIN_ANIME_SPEED * PlaySpeed, nullptr)))
        {
            MessageBox(nullptr, TEXT("���b�V���A�j���[�V�����̍Đ��Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
            exit(EXIT_FAILURE);
        }
    }

    //�t���[���̍X�V
    if (FrameRoot)
    {
        //�A�j���[�V�����f�[�^���X�V
        UpdateFrameMatrices(FrameRoot, &worldmatrix);

        //�A�j���[�V�����`��
        DrawFrame(FrameRoot, effect);
    }
}

/////////////////////////////////////////////
//�֐����FDrawFrame
//
//�@�\�F�t���[���̃����_�����O
//
//�����F(LPD3DXFRAME)���[�g�t���[��,(bool)�G�t�F�N�g�̗L�����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ANIMATIONMODEL::DrawFrame(LPD3DXFRAME framebase, bool effect)
{
    //---�e��錾---//
    LPD3DXMESHCONTAINER pMeshContainer;

    //---����������---//
    pMeshContainer = framebase->pMeshContainer;

    //---�����_�����O---//
    while (pMeshContainer)
    {
        //���b�V���̃����_�����O
        RenderMeshContainer(pMeshContainer, framebase, effect);

        //���̃��b�V���R���e�i�փA�N�e�B�u���ڂ�
        pMeshContainer = pMeshContainer->pNextMeshContainer;
    }

    //�Z��t���[���̃����_�����O
    if (framebase->pFrameSibling)
    {
        DrawFrame(framebase->pFrameSibling, effect);
    }

    //�q�t���[���̃����_�����O
    if (framebase->pFrameFirstChild)
    {
        DrawFrame(framebase->pFrameFirstChild, effect);
    }
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F���f���̏�����
//
//�����F(LPCTSTR)�t�@�C����,(float)�Đ����x
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ANIMATIONMODEL::Initialize(LPCTSTR filename, float speed)
{
    //---�e��錾---//
    DWORD dwCounter;
    HRESULT hResult;

    TCHAR szDirectory[_MAX_DIR];
    TCHAR szWork[_MAX_DIR];

    //---����������---//
    PlaySpeed = speed;
    CurrentTrack = 0;
    CurrentTrackDescription = { D3DXPRIORITY_LOW, 1.0F, 1.0F, 0.0, TRUE };
    AnimationData.clear();

    //---�f�B���N�g���̒��o---//
    if (filename)
    {
        //�t�H���_���𒊏o
        _tsplitpath(filename, szDirectory, szWork, nullptr, nullptr);
        lstrcat(szDirectory, szWork);
        Hierarchy.SetDirectory(szDirectory);
    }
    else
    {
        MessageBox(nullptr, TEXT("�J�����f���t�@�C����������܂���"), filename, MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //---�K�w�\�����b�V���̓ǂݍ���---//
    hResult = D3DXLoadMeshHierarchyFromX(filename, D3DXMESH_MANAGED, GetDevice(), &Hierarchy, nullptr, &FrameRoot, &AnimationController);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�A�j���[�V�����t��X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���"), filename, MB_OK);
        return hResult;
    }

    //---�{�[���s�񏉊���---//
    hResult = AllocateAllBoneMatrices(FrameRoot);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�{�[���s��̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    //---�A�j���[�V�����g���b�N�̎擾---//
    if (AnimationController)
    {
        AnimationData.resize(AnimationController->GetNumAnimationSets());
        for (dwCounter = 0; dwCounter < AnimationData.size(); ++dwCounter)
        {
            //�A�j���[�V�����擾
            hResult = AnimationController->GetAnimationSet(dwCounter, &AnimationData.at(dwCounter));
            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("�A�j���[�V�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
                return hResult;
            }
        }
    }

    //---�}�g���N�X�̍X�V---//
    if (FrameRoot)
    {
        SetTime(0.0);
        UpdateFrameMatrices(FrameRoot, &World);
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FRenderMeshContainer
//
//�@�\�F�t���[�����̃��b�V���̃����_�����O
//
//�����F(LPD3DXMESHCONTAINER)���b�V���R���e�i,(LPD3DXFRAME)�����_�����O�t���[��,(bool)�G�t�F�N�g�̗L�����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
void ANIMATIONMODEL::RenderMeshContainer(LPD3DXMESHCONTAINER meshcontainer, LPD3DXFRAME frame, bool effect)
{
    //---�e��錾---//
    HRESULT hResult;
    DWORD dwAttribute;
    DWORD dwBoneCounter;
    DWORD dwWeightCounter;
    DWORD dwBlendMatrixNumber;
    DWORD dwPreviewBoneID;
    DWORD dwMatrixID;
    D3DMATERIAL9 matEffect;

    volatile DWORD dwAttributeCounter;

    LPDIRECT3DDEVICE9 pDevice;
    LPD3DXBONECOMBINATION pBoneCombination;
    ANIMATIONMODELCONTAINER* pMeshContainer;
    ANIMATIONMODELFREAM* pFrame;

    //---����������---//
    pMeshContainer = (ANIMATIONMODELCONTAINER*)meshcontainer;
    pFrame = (ANIMATIONMODELFREAM*)frame;
    pDevice = GetDevice();

    //---�`��---//
    //�X�L�����b�V���̕`��
    if (meshcontainer->pSkinInfo)
    {
        //�{�[���e�[�u������o�b�t�@�̐擪�A�h���X���擾
        pBoneCombination = (LPD3DXBONECOMBINATION)pMeshContainer->BoneBuffer->GetBufferPointer();

        //dwPrevBoneID��������
        dwPreviewBoneID = UINT_MAX;

        //�X�L�j���O�v�Z
        for (dwBoneCounter = 0; dwBoneCounter < pMeshContainer->BoneValue; ++dwBoneCounter)
        {
            dwBlendMatrixNumber = 0;
            //�e�����Ă���s�񐔎擾
            for (dwWeightCounter = 0; dwWeightCounter < pMeshContainer->Weight; ++dwWeightCounter)
            {
                //�e�����������l������
                if (pBoneCombination[dwBoneCounter].BoneId[dwWeightCounter] != UINT_MAX)
                {
                    //���݉e�����󂯂Ă���{�[���̐�
                    dwBlendMatrixNumber = dwWeightCounter;
                }
            }

            //�W�I���g���u�����f�B���O���g�p���邽�߂ɍs��̌����w��
            hResult = pDevice->SetRenderState(D3DRS_VERTEXBLEND, dwBlendMatrixNumber);
            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("�e�N�X�`���̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
            }

            //�e�����Ă���s��̌���
            for (dwWeightCounter = 0; dwWeightCounter < pMeshContainer->Weight; ++dwWeightCounter)
            {
                //nMatrixIndex��1�x�̌Ăяo���ŕ`��o����e�{�[�������ʂ���l���i�[
                dwMatrixID = pBoneCombination[dwBoneCounter].BoneId[dwWeightCounter];

                //�s��̏�񂪂����
                if (dwMatrixID != UINT_MAX)
                {
                    //�s��X�^�b�N�Ɋi�[
                    hResult = pDevice->SetTransform(D3DTS_WORLDMATRIX(dwWeightCounter), &(pMeshContainer->BoneOffsetMatrix[dwMatrixID] * (*pMeshContainer->BoneMatrix[dwMatrixID])));
                    if (FAILED(hResult))
                    {
                        MessageBox(nullptr, TEXT("�s��X�^�b�N�ւ̊i�[�Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
                    }
                }
            }

            //�}�e���A���̐ݒ�
            if (effect)
            {
                matEffect = pMeshContainer->pMaterials[pBoneCombination[dwBoneCounter].AttribId].MatD3D;
                matEffect.Diffuse = { 0.5F, 0.5F, 0.5F, 1.0F };
                hResult = pDevice->SetMaterial(&matEffect);
            }
            else
            {
                hResult = pDevice->SetMaterial(&pMeshContainer->pMaterials[pBoneCombination[dwBoneCounter].AttribId].MatD3D);
            }

            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("�}�e���A���̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
            }

            hResult = pDevice->SetTexture(0, pMeshContainer->Texture.at(pBoneCombination[dwBoneCounter].AttribId));
            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("�e�N�X�`���̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
            }

            //�����e�[�u���̎��ʎq���i�[
            dwPreviewBoneID = pBoneCombination[dwBoneCounter].AttribId;

            //���b�V���̕`��
            hResult = pMeshContainer->MeshData.pMesh->DrawSubset(dwBoneCounter);
            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("���b�V���̕`��Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
            }
        }
    }

    //�ʏ탁�b�V���̕`��
    else
    {
        hResult = pDevice->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);
        for (dwAttributeCounter = 0; dwAttributeCounter < pMeshContainer->NumMaterials; ++dwAttributeCounter)
        {
            //�����e�[�u���̎擾
            dwAttribute = pMeshContainer->AttributeTable.at(dwAttributeCounter).AttribId;

            //�}�e���A���̐ݒ�
            hResult = pDevice->SetMaterial(&pMeshContainer->pMaterials[dwAttribute].MatD3D);
            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("�}�e���A���̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
            }

            //�e�N�X�`���̐ݒ�
            hResult = pDevice->SetTexture(0, pMeshContainer->Texture.at(dwAttribute));
            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("�e�N�X�`���̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
            }

            //���b�V���̕`��
            hResult = pMeshContainer->MeshData.pMesh->DrawSubset(dwAttribute);
            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("���b�V���̕`��Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
            }
        }
    }
}

/////////////////////////////////////////////
//�֐����FSetTime
//
//�@�\�F�Đ��ʒu�̐ݒ�
//
//�����F(double)�Đ��ʒu
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ANIMATIONMODEL::SetTime(double time)
{
    //---�e��錾---//
    UINT nCounter;

    if (!AnimationController)
    {
        return;
    }
    
    for (nCounter = 0; nCounter < AnimationController->GetMaxNumTracks(); ++nCounter)
    {
        AnimationController->SetTrackPosition(nCounter, 0.0);
    }

    AnimationController->ResetTime();
    AnimationController->AdvanceTime(time, nullptr);
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F���f���̍폜
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ANIMATIONMODEL::Uninitialize(void)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;

    //�A�j���[�V�����R���g���[���[���
    if (AnimationController)
    {
        for (nCounter = 0; nCounter < AnimationData.size(); ++nCounter)
        {
            SAFE_RELEASE(AnimationData.at(nCounter));
        }
    }
    AnimationData.clear();
    SAFE_RELEASE(AnimationController);

    //�{�[���J��
    if (FrameRoot)
    {
        hResult = D3DXFrameDestroy(FrameRoot, &Hierarchy);
        if (SUCCEEDED(hResult))
        {
            //�{�[���t���[���֌W���
            FrameRoot = nullptr;
        }
    }
}

/////////////////////////////////////////////
//�֐����FUpdateFrameMatrices
//
//�@�\�F�t���[�����̃��b�V�����Ƃ̃��[���h�ϊ��s��̍X�V
//
//�����F(LPD3DXFRAME)�X�V�t���[��,(LPD3DXMATRIX)�e�}�g���N�X
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ANIMATIONMODEL::UpdateFrameMatrices(LPD3DXFRAME framebase, LPD3DXMATRIX parentmatrix)
{
    //---�e��錾---//
    ANIMATIONMODELFREAM* pFrame;

    //---����������---//
    pFrame = (ANIMATIONMODELFREAM*)framebase;

    //CombinedTransformationMatrix�ɍŏI�s����i�[
    pFrame->CombinedTransformationMatrix = parentmatrix ? pFrame->TransformationMatrix * *parentmatrix : pFrame->TransformationMatrix;

    // �Z��t���[��������΃}�g���b�N�X���X�V
    if (pFrame->pFrameSibling)
    {
        UpdateFrameMatrices(pFrame->pFrameSibling, parentmatrix);
    }

    // �q�t���[��������΃}�g���b�N�X���X�V
    if (pFrame->pFrameFirstChild)
    {
        UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
    }
}