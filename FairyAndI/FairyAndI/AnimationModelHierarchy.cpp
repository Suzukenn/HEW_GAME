//�������w�b�_�t�@�C���ǂݍ��݁�����//
#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include "AnimationModelContainer.h"
#include "AnimationModelFrame.h"
#include "AnimationModelHierarchy.h"
#include "Main.h"

//�������֐���`������//
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
    memset(pFrame, 0, sizeof(ANIMATIONMODELFREAM));

    //---�t���[�����i�[---//
    if (Name)
    {
        //�t���[�����i�[
        pFrame->Name = new char[lstrlenA(Name) + 1];
        lstrcpyA(pFrame->Name, Name);
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

    return S_OK;
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
    HRESULT hResult;
    DWORD dwFacesAmount;
    DWORD dwCounter;
    DWORD dwMaterial;
    DWORD dwBoneValue;
    std::string strTexturePath;
    std::wstring strTexturePathW;

    TCHAR szCurrentDirectory[_MAX_PATH];
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
        //���b�V���R���e�i�̖��O�i�[
        pMeshContainer->Name = new char[lstrlenA(Name) + 1];
        lstrcpyA(pMeshContainer->Name, Name);
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
        hResult = pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF() | D3DFVF_NORMAL, pDevice, &pMeshContainer->MeshData.pMesh);
        if (FAILED(hResult)) 
        {
            MessageBox(nullptr, TEXT("���b�V���̒��_���`���̕����Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
            DestroyMeshContainer(pMeshContainer);
            return hResult;
        }
        pMesh = pMeshContainer->MeshData.pMesh;
        hResult = D3DXComputeNormals(pMesh, nullptr);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("���b�V���̖@���̌v�Z�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
            DestroyMeshContainer(pMeshContainer);
            return hResult;
        }
    }

    //---���b�V���̃}�e���A���ݒ�----//
    pMeshContainer->NumMaterials = max(1, NumMaterials);                                //���b�V���̃}�e���A�������i�[(�ő��1��)
    pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];        //���b�V���R���e�i�́A�}�e���A���f�[�^�i�[�̈�𓮓I�m��
    pMeshContainer->Texture.resize(pMeshContainer->NumMaterials);                       //���b�V���R���e�i�́A�e�N�X�`���f�[�^�i�[�̈�𓮓I�m��
    pMeshContainer->pAdjacency = new DWORD[dwFacesAmount * 3];                          //���b�V���R���e�i�́A�ʂ��ƂɎ���3�̗אڐ���񂪊i�[���ꂽDWORD�^�̃A�h���X�i�[�p(�|�C���^)�ϐ�
    if (!pMeshContainer->pAdjacency || pMeshContainer->Texture.empty() || !pMeshContainer->pMaterials)
    {
        MessageBox(nullptr, TEXT("���b�V���̃}�e���A����񂪑���܂���"), TEXT("�������G���["), MB_OK);
        DestroyMeshContainer(pMeshContainer);
        return E_OUTOFMEMORY;
    }

    //�O�������̗אڐ��������b�V���R���e�i�Ɋi�[
    memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * dwFacesAmount * 3);

    //---�}�e���A���̊i�[---//
    //�}�e���A������
    if (NumMaterials)
    {
        if (lstrlenA((LPCSTR)FileDirectory.begin()._Ptr))
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
                hResult = D3DXCreateTextureFromFile(pDevice, strTexturePathW.data(), &pMeshContainer->Texture.at(dwMaterial));
                if (FAILED(hResult))
                {
                    MessageBox(nullptr, TEXT("���b�V���̃e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
                    pMeshContainer->Texture.at(dwMaterial) = nullptr;
                    return hResult;
                }
            }
        }

        //�J�����g�f�B���N�g�������ɖ߂�
        if (lstrlenA((LPCSTR)FileDirectory.begin()._Ptr))
        {
            SetCurrentDirectory(szCurrentDirectory);
        }
    }
    else
    {
        //�}�e���A���Ȃ�
        memset(&pMeshContainer->pMaterials, 0, sizeof(D3DXMATERIAL));   //�}�e���A���f�[�^������
        pMeshContainer->pMaterials->pTextureFilename = nullptr;         //�e�N�X�`���t�@�C������nullptr��

        //�}�e���A���J���[��0.5�ɐݒ�
        pMeshContainer->pMaterials->MatD3D.Diffuse.r = 0.5F;
        pMeshContainer->pMaterials->MatD3D.Diffuse.g = 0.5F;
        pMeshContainer->pMaterials->MatD3D.Diffuse.b = 0.5F;

        //�������g�U���Ɠ��l�ɐݒ�(��Őݒ肵���}�e���A���J���[��0.5�̐ݒ���R�s�[)
        pMeshContainer->pMaterials->MatD3D.Ambient = pMeshContainer->pMaterials->MatD3D.Diffuse;
    }

    //---�����e�[�u���̎擾---//
    hResult = pMeshContainer->MeshData.pMesh->CloneMeshFVF(D3DXMESH_MANAGED, pMeshContainer->MeshData.pMesh->GetFVF(), pDevice, &pMesh);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���b�V���̒��_���`���̓ǂݍ��݂Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }
    SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
    pMeshContainer->MeshData.pMesh = pMesh;

    hResult = pMesh->GetAttributeTable(nullptr, &pMeshContainer->AttributeGroupValue);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���b�V���̑����e�[�u���̃G���g�����̓ǂݍ��݂Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }
    pMeshContainer->AttributeTable.resize(pMeshContainer->AttributeGroupValue);
    hResult = pMesh->GetAttributeTable(pMeshContainer->AttributeTable.begin()._Ptr, &pMeshContainer->AttributeGroupValue);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���b�V���̑����e�[�u���̓ǂݍ��݂Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    //---�X�L�����̎擾---//
    if (pSkinInfo)
    {
        pMeshContainer->pSkinInfo = pSkinInfo;                  //���b�V�������i�[(����͒ʏ탁�b�V���Ɗ��S�ɕ����Ă��邽�߂��ׂăX�L�����b�V�����ƂȂ�)
        pSkinInfo->AddRef();                                    //�Q�ƃJ�E���^
        dwBoneValue = pSkinInfo->GetNumBones();                 //�{�[���̐����擾
        pMeshContainer->BoneOffsetMatrix.resize(dwBoneValue);   //�t���[��(�{�[��)�P�ʂł̃��[���h�s��i�[�p�̈�̓��I�m��

        //�{�[���̐��������[�v������
        for (dwCounter = 0; dwCounter < dwBoneValue; ++dwCounter)
        {
            //�p�t���[��(�{�[��)�̃I�t�Z�b�g�s����擾���Ċi�[
            pMeshContainer->BoneOffsetMatrix.at(dwCounter) = *pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(dwCounter);
        }

        //---�Œ�p�C�v���C���`��p�ɕϊ�---//
        hResult = pMeshContainer->pSkinInfo->ConvertToBlendedMesh(pMesh, 0, pMeshContainer->pAdjacency, nullptr, nullptr, nullptr, &pMeshContainer->Weight, &pMeshContainer->BoneValue, &pMeshContainer->BoneBuffer, &pMeshContainer->MeshData.pMesh);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("���b�V�����Œ�p�C�v���C���p�ɕϊ��ł��܂���ł���"), TEXT("�������G���["), MB_OK);
            return hResult;
        }
    }

    //���[�J���ɐ����������b�V���R���e�i�[���Ăяo�����ɃR�s�[����
    *ppMeshContainer = pMeshContainer;
    
    return hResult;
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

    return S_OK;
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
    ANIMATIONMODELCONTAINER* pMeshContainer;

    //---����������---//
    pMeshContainer = (ANIMATIONMODELCONTAINER*)pMeshContainerBase;

    //---�J������---//
    SAFE_DELETE_ARRAY(pMeshContainer->Name);
    SAFE_RELEASE(pMeshContainer->pSkinInfo);
    SAFE_DELETE_ARRAY(pMeshContainer->pAdjacency);
    SAFE_DELETE_ARRAY(pMeshContainer->pMaterials);
    for (auto& data : pMeshContainer->BoneMatrix)
    {
        SAFE_DELETE(data);
    }
    pMeshContainer->BoneMatrix.clear();

    //�e�N�X�`�����
    if (!pMeshContainer->Texture.empty())
    {
        for (auto& data : pMeshContainer->Texture)
        {
            SAFE_RELEASE(data);
        }
    }
    pMeshContainer->Texture.clear();
    SAFE_RELEASE(pMeshContainer->MeshData.pMesh);

    //�{�[���J��
    if (pMeshContainer->BoneBuffer)
    {
        SAFE_RELEASE(pMeshContainer->BoneBuffer);
        pMeshContainer->BoneOffsetMatrix.clear();
    }

    SAFE_DELETE(pMeshContainer);
    pMeshContainerBase = nullptr;
    return S_OK;
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
    directory? lstrcpy(FileDirectory.data(), directory): FileDirectory.assign(0);
}