//�������w�b�_�t�@�C���ǂݍ��݁�����//
#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include "AnimationModelContainer.h"
#include "AnimationModelFrame.h"
#include "AnimationModelHierarchy.h"
#include "Main.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FANIMATIONMODELHIERARCHY
//
//�@�\�F�R���X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
ANIMATIONMODELHIERARCHY::ANIMATIONMODELHIERARCHY(void)
{
    FileDirectory.assign(0);
}

/////////////////////////////////////////////
//�֐����F~ANIMATIONMODELHIERARCHY
//
//�@�\�F�f�X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
ANIMATIONMODELHIERARCHY::~ANIMATIONMODELHIERARCHY(void)
{

}

/////////////////////////////////////////////
//�֐����FCreateFrame
//
//�@�\�F�t���[���̍쐬
//
//�����F(LPCTSTR)�t���[����,(LPD3DXFRAME)�V�t���[����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ANIMATIONMODELHIERARCHY::CreateFrame(LPCSTR Name, LPD3DXFRAME* ppNewFrame)
{
    //---�e��錾---//
    ANIMATIONMODELFREAM* pFrame;

    //---����������---//
    *ppNewFrame = nullptr;            //�V�����t���[���A�h���X�i�[�p�ϐ���������
    pFrame = new ANIMATIONMODELFREAM; //�t���[���̗̈�m��

    //�̈�m�ۂ̎��s���̏���
    if (pFrame)
    {
        memset(pFrame, 0, sizeof(ANIMATIONMODELFREAM));
    }
    else
    {
        return E_OUTOFMEMORY;
    }

    //---�t���[�����i�[---//
    if (Name)
    {
        //�t���[�����i�[�p�̈�m��
        pFrame->Name = new char[lstrlenA(Name) + 1];

        //�̈�m�ۂ̎��s���̏���
        if (pFrame->Name)
        {
            //�t���[�����i�[
            lstrcpyA(pFrame->Name, Name);
        }
        else
        {
            delete pFrame;
            return E_OUTOFMEMORY;
        }
    }
    else
    {
        pFrame->Name = nullptr;
    }

    //�s��̏�����
    D3DXMatrixIdentity(&pFrame->TransformationMatrix);
    D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);
    
    //�O���̐V�K�t���[���A�h���X�i�[�p�ϐ��ɁA�쐬�����t���[���̃A�h���X���i�[
    *ppNewFrame = pFrame;

    return D3D_OK;
}

/////////////////////////////////////////////
//�֐����FCreateMeshContainer
//
//�@�\�F���b�V���R���e�i�[�̍쐬
//
//�����F(LPCSTR)���b�V����,(D3DXMESHDATA*)���b�V���f�[�^,(D3DXMATERIAL*)�}�e���A��,(D3DXEFFECTINSTANCE*)�G�t�F�N�g,(DWORD)�}�e���A����,(DWORD*)�אڗv�f,(LPD3DXSKININFO)�X�L�����,(LPD3DXMESHCONTAINER*)�i�[�R���e�i
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ANIMATIONMODELHIERARCHY::CreateMeshContainer(THIS_ LPCSTR Name, CONST D3DXMESHDATA* pMeshData, CONST D3DXMATERIAL* pMaterials, CONST D3DXEFFECTINSTANCE* pEffectInstances, DWORD NumMaterials, CONST DWORD* pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER* ppMeshContainer)
{
    //---�e��錾---//
    DWORD dwFacesAmount;
    DWORD dwCounter;
    DWORD dwMaterial;
    DWORD dwBoneValue;
    std::string strTexturePath;
    std::wstring strTexturePathW;

    TCHAR szCurrentDirectory[_MAX_DIR];
    char szTexturePath[_MAX_DIR];

    LPDIRECT3DDEVICE9 pDevice;
    LPD3DXMESH pMesh;                           //�ꎞ�I�ȃ��b�V���f�[�^�i�[�p
    ANIMATIONMODELCONTAINER* pMeshContainer;    //�ꎞ�i�[���b�V���R���e�i

    //---����������---//
    pMesh = pMeshData->pMesh;      //pMesh�ɊO�������̃��b�V���A�h���X���i�[
    *ppMeshContainer = nullptr;    //���b�V���R���e�i�i�[�p�ϐ�������
    pDevice = GetDevice();
    pMeshContainer = new ANIMATIONMODELCONTAINER;    //���b�V���R���e�i�̈�̓��I�m��

    //����ȃ��b�V���ȊO�̓G���[�Ŗ߂�
    if (pMeshData->Type != D3DXMESHTYPE_MESH || !pMeshData->pMesh->GetFVF())
    {
        return E_FAIL;
    }

    //���b�V���R���e�i��������
    memset(pMeshContainer, 0, sizeof(ANIMATIONMODELCONTAINER));

    //---���b�V�����̃R�s�[---//
    if (Name)
    {
        //���b�V���R���e�i�̖��O�i�[�p�̈�𓮓I�m��
        pMeshContainer->Name = new char[lstrlenA(Name) + 1];

        if (pMeshContainer->Name)
        {
            lstrcpyA(pMeshContainer->Name, Name);
        }
        else
        {
            delete pMeshContainer;
            return E_OUTOFMEMORY;
        }
    }
    else
    {
        pMeshContainer->Name = nullptr;
    }

    //---���f���f�[�^�̊i�[---//
    pMesh->GetDevice(&pDevice);                                //DirectX�f�o�C�X�擾
    dwFacesAmount = pMesh->GetNumFaces();                      //���b�V���̖ʂ̐����擾

    if (pMesh->GetFVF() & D3DFVF_NORMAL)
    {
        pMeshContainer->MeshData.pMesh = pMesh;
        pMesh->AddRef();
    }
    else
    {
        // �@���������Ȃ��ꍇ�͒ǉ�
        if (FAILED(pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF() | D3DFVF_NORMAL, pDevice, &pMeshContainer->MeshData.pMesh))) 
        {
            pDevice->Release();
            DestroyMeshContainer(pMeshContainer);
            return E_FAIL;
        }
        pMesh = pMeshContainer->MeshData.pMesh;
        D3DXComputeNormals(pMesh, nullptr);
    }

    //---���b�V���̃}�e���A���ݒ�----//
    pMeshContainer->NumMaterials = max(1, NumMaterials);                                //���b�V���̃}�e���A�������i�[(�ő��1��)
    pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];        //���b�V���R���e�i�́A�}�e���A���f�[�^�i�[�̈�𓮓I�m��
    pMeshContainer->Textures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];    //���b�V���R���e�i�́A�e�N�X�`���f�[�^�i�[�̈�𓮓I�m��
    pMeshContainer->pAdjacency = new DWORD[dwFacesAmount * 3];                          //���b�V���R���e�i�́A�ʂ��ƂɎ���3�̗אڐ���񂪊i�[���ꂽDWORD�^�̃A�h���X�i�[�p(�|�C���^)�ϐ�
    if (!pMeshContainer->pAdjacency || !pMeshContainer->Textures || !pMeshContainer->pMaterials)
    {
        DestroyMeshContainer(pMeshContainer);
        pDevice->Release();
        return E_OUTOFMEMORY;
    }

    //�e�N�X�`���f�[�^�i�[�p�̈��������(memset���g�p����0�Œ��g�𖄂߂�)
    memset(pMeshContainer->Textures, 0, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

    //�O�������̗אڐ��������b�V���R���e�i�Ɋi�[
    memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * dwFacesAmount * 3);

    //---�}�e���A���̊i�[---//
    //�}�e���A������
    if (NumMaterials > 0)
    {
        if (FileDirectory.at(0))
        {
            GetCurrentDirectory(_MAX_PATH, szCurrentDirectory);
            SetCurrentDirectory(FileDirectory.begin()._Ptr);
        }

        //�O�������̃}�e���A���f�[�^�A�h���X�����b�V���R���e�i�Ɋi�[
        memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);

        //�}�e���A���������[�v������
        for (dwMaterial = 0; dwMaterial < NumMaterials; ++dwMaterial)
        {
            pMeshContainer->pMaterials[dwMaterial].MatD3D.Ambient = pMeshContainer->pMaterials[dwMaterial].MatD3D.Diffuse;

            //�e�N�X�`���f�[�^�������
            if (pMeshContainer->pMaterials[dwMaterial].pTextureFilename)
            {
                //�e�N�X�`���̃t�@�C���p�X��ۑ�(�ēǂݍ��ݎ��ɕK�v)
                _splitpath(pMeshContainer->pMaterials[dwMaterial].pTextureFilename, nullptr, szTexturePath, nullptr, nullptr);
                strTexturePath = pMeshContainer->pMaterials[dwMaterial].pTextureFilename;
                strTexturePathW = std::wstring(strTexturePath.begin(), strTexturePath.end());

                //�e�N�X�`�����̓ǂݍ���
                if (FAILED(D3DXCreateTextureFromFile(pDevice, strTexturePathW.data(), &pMeshContainer->Textures[dwMaterial])))
                {
                    pMeshContainer->Textures[dwMaterial] = nullptr;
                }
            }
        }

        //�J�����g�f�B���N�g�������ɖ߂�
        if (FileDirectory.at(0))
        {
            SetCurrentDirectory(szCurrentDirectory);
        }   
    }
    else
    {
        //�}�e���A���Ȃ�
        memset(&pMeshContainer->pMaterials, 0, sizeof(D3DXMATERIAL));   //�}�e���A���f�[�^������(memset���g�p���Ē��g��0�Ŗ��߂�)
        pMeshContainer->pMaterials->pTextureFilename = nullptr;         //�e�N�X�`���t�@�C������nullptr��

        //�}�e���A���J���[��0.5�ɐݒ�
        pMeshContainer->pMaterials->MatD3D.Diffuse.r = 0.5F;
        pMeshContainer->pMaterials->MatD3D.Diffuse.g = 0.5F;
        pMeshContainer->pMaterials->MatD3D.Diffuse.b = 0.5F;

        //�������g�U���Ɠ��l�ɐݒ�(��Őݒ肵���}�e���A���J���[��0.5�̐ݒ���R�s�[)
        pMeshContainer->pMaterials->MatD3D.Ambient = pMeshContainer->pMaterials->MatD3D.Diffuse;
    }

    //---�����e�[�u���̎擾---//
    if (FAILED(pMeshContainer->MeshData.pMesh->CloneMeshFVF(D3DXMESH_MANAGED, pMeshContainer->MeshData.pMesh->GetFVF(), pDevice, &pMesh)))
    {
        pDevice->Release();
        return E_FAIL;
    }
    SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
    pMeshContainer->MeshData.pMesh = pMesh;

    if (FAILED(pMesh->GetAttributeTable(nullptr, &pMeshContainer->AttributeGroupValue)))
    {
        pDevice->Release();
        return E_FAIL;
    }
    pMeshContainer->AttributeTable = new D3DXATTRIBUTERANGE[pMeshContainer->AttributeGroupValue];
    if (!pMeshContainer->AttributeTable)
    {
        pMeshContainer->AttributeGroupValue = 0;
        pDevice->Release();
        return E_OUTOFMEMORY;
    }
    if (FAILED(pMesh->GetAttributeTable(pMeshContainer->AttributeTable, nullptr)))
    {
        pDevice->Release();
        return E_FAIL;
    }

    //---�X�L�����̎擾---//
    if (pSkinInfo)
    {
        pMeshContainer->pSkinInfo = pSkinInfo;                              //���b�V�������i�[(����͒ʏ탁�b�V���Ɗ��S�ɕ����Ă��邽�߂��ׂăX�L�����b�V�����ƂȂ�)
        pSkinInfo->AddRef();                                                //�Q�ƃJ�E���^
        dwBoneValue = pSkinInfo->GetNumBones();                             //�{�[���̐����擾
        pMeshContainer->BoneOffsetMatrix = new D3DXMATRIX[dwBoneValue];     //�t���[��(�{�[��)�P�ʂł̃��[���h�s��i�[�p�̈�̓��I�m��
        if (!pMeshContainer->BoneOffsetMatrix)
        {
            return E_OUTOFMEMORY;
        }

        //�{�[���̐��������[�v������
        for (dwCounter = 0; dwCounter < dwBoneValue; ++dwCounter)
        {
            //�p�t���[��(�{�[��)�̃I�t�Z�b�g�s����擾���Ċi�[
            memcpy(&pMeshContainer->BoneOffsetMatrix[dwCounter], pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(dwCounter), sizeof(D3DMATRIX));
        }

        //---�Œ�p�C�v���C���`��p�ɕϊ�---//
        if (FAILED(pMeshContainer->pSkinInfo->ConvertToBlendedMesh(pMesh, 0, pMeshContainer->pAdjacency, nullptr, nullptr, nullptr, &pMeshContainer->Weight, &pMeshContainer->BoneValue, &pMeshContainer->BoneBuffer, &pMeshContainer->MeshData.pMesh)))
        {
            return E_FAIL;
        }
    }

    //���[�J���ɐ����������b�V���R���e�i�[���Ăяo�����ɃR�s�[����
    *ppMeshContainer = pMeshContainer;
    
    return D3D_OK;
}

/////////////////////////////////////////////
//�֐����FDestroyFrame
//
//�@�\�F�t���[���̔j��
//
//�����F(LPD3DXFRAME)�p���t���[��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ANIMATIONMODELHIERARCHY::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
    //---�e��錾---//
    ANIMATIONMODELFREAM* pFrame;

    //---����������---//
    pFrame = (ANIMATIONMODELFREAM*)pFrameToFree;

    //---�J������---//
    SAFE_DELETE_ARRAY(pFrame->Name);
    SAFE_DELETE(pFrame);

    return D3D_OK;
}

/////////////////////////////////////////////
//�֐����FDestroyFrame
//
//�@�\�F���b�V���R���e�i�[�̔j��
//
//�����F(LPD3DXMESHCONTAINER)�p���R���e�i
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ANIMATIONMODELHIERARCHY::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
{
    //---�e��錾---//
    DWORD dwMaterial;

    ANIMATIONMODELCONTAINER* pMeshContainer;

    //---����������---//
    pMeshContainer = (ANIMATIONMODELCONTAINER*)pMeshContainerBase;

    //---�J������---//
    SAFE_DELETE_ARRAY(pMeshContainer->Name);
    SAFE_RELEASE(pMeshContainer->pSkinInfo);
    SAFE_DELETE_ARRAY(pMeshContainer->pAdjacency);
    SAFE_DELETE_ARRAY(pMeshContainer->pMaterials);
    SAFE_DELETE_ARRAY(pMeshContainer->BoneMatrix);

    //�e�N�X�`�����
    if (pMeshContainer->Textures)
    {
        for (dwMaterial = 0; dwMaterial < pMeshContainer->NumMaterials; ++dwMaterial)
        {
            SAFE_RELEASE(pMeshContainer->Textures[dwMaterial]);
        }
    }
    SAFE_DELETE_ARRAY(pMeshContainer->Textures);
    SAFE_RELEASE(pMeshContainer->MeshData.pMesh);

    //�{�[���J��
    if (pMeshContainer->BoneBuffer)
    {
        SAFE_RELEASE(pMeshContainer->BoneBuffer);
        SAFE_DELETE_ARRAY(pMeshContainer->BoneOffsetMatrix);
    }
    SAFE_DELETE(pMeshContainer);
    pMeshContainerBase = nullptr;
    return D3D_OK;
}

/////////////////////////////////////////////
//�֐����FSetDirectory
//
//�@�\�FX�t�@�C���̂���f�B���N�g���̐ݒ�
//
//�����F(LPCTSTR)�f�B���N�g���p�X
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ANIMATIONMODELHIERARCHY::SetDirectory(LPCTSTR directory)
{
    if (directory)
    {
        lstrcpy(FileDirectory.data(), directory);
    }
    else
    {
        FileDirectory.at(0) = 0;
    }
}