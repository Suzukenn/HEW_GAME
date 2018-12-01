//�������w�b�_�t�@�C���ǂݍ��݁�����//
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <memory>
#include <string>
#include <tchar.h>
#include <unordered_map>
#include <vector>
#include "Main.h"
#include "ModelManager.h"

//�������O���[�o���ϐ�������//
std::unordered_map<tstring, MODEL*> MODELMANAGER::Model;           //�e�N�X�`��

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FCreate
//
//�@�\�F���f���̍쐬
//
//�����F(FILEPARAMETER)�Q�ƃf�[�^
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT MODELMANAGER::Create(const FILEPARAMETER& data)
{
    //---�e��錾---//
    HRESULT hResult;
    DWORD nCounter;

    TCHAR szDirectory[_MAX_DIR];
    TCHAR szCurrentDirectory[_MAX_PATH];

    LPDIRECT3DDEVICE9 pDevice;
    LPD3DXMATERIAL pMaterial;
    MODEL* pModel;

    //---����������---//
    pDevice = GetDevice();
    pModel = new MODEL();

    //---�f�[�^�̓W�J---//
    //�t�@�C���̎w��m�F
    if (data.FileName.data())
    {
        //�t�H���_���𒊏o
        _tsplitpath(data.FileName.data(), nullptr, szDirectory, nullptr, nullptr);
    }
    else
    {
        MessageBox(nullptr, TEXT("�J�����f���t�@�C����������܂���"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        delete pModel;
        return E_FAIL;
    }

    //X�t�@�C���̓ǂݍ���
    hResult = D3DXLoadMeshFromX(data.FileName.data(), D3DXMESH_SYSTEMMEM, pDevice, nullptr, &pModel->MaterialBuffer, nullptr, &pModel->MaterialValue, &pModel->Mesh);
    if(FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���f���̍쐬�Ɏ��s���܂���"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //�����e�[�u���擾
    pModel->Mesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT, 0, 0, 0, 0);
    pModel->AttributeValue = 0;
    pModel->Mesh->GetAttributeTable(nullptr, &pModel->AttributeValue);
    pModel->Attribute = new D3DXATTRIBUTERANGE[pModel->AttributeValue];
    pModel->Mesh->GetAttributeTable(pModel->Attribute, &pModel->AttributeValue);

    //�J�����g�f�B���N�g����ύX
    if (szDirectory[0])
    {
        GetCurrentDirectory(_MAX_PATH, szCurrentDirectory);
        SetCurrentDirectory(szDirectory);
    }

    //�}�e���A���ǂݍ���
    pMaterial = (LPD3DXMATERIAL)pModel->MaterialBuffer->GetBufferPointer();
    pModel->Material = new D3DMATERIAL9[pModel->MaterialValue];
    pModel->Texture = new LPDIRECT3DTEXTURE9[pModel->MaterialValue];
    for (nCounter = 0; nCounter < pModel->MaterialValue; ++nCounter)
    {
        pModel->Material[nCounter] = pMaterial[nCounter].MatD3D;
        pModel->Material[nCounter].Ambient = pModel->Material[nCounter].Diffuse;
        pModel->Texture[nCounter] = nullptr;
        if (pMaterial[nCounter].pTextureFilename && pMaterial[nCounter].pTextureFilename[0])
        {
            // �e�N�X�`���t�@�C����ǂݍ���
            hResult = D3DXCreateTextureFromFile(pDevice, (LPCWSTR)pMaterial[nCounter].pTextureFilename, &pModel->Texture[nCounter]);
            if (FAILED(hResult))
            {
                pModel->Texture[nCounter] = nullptr;
                Uninitialize();
                return hResult;
            }
        }
    }

    //�J�����g�f�B���N�g�������ɖ߂�
    if (szDirectory[0])
    {
        SetCurrentDirectory(szCurrentDirectory);
    }

    Model.insert(std::make_pair(data.CallKey, pModel));

    return hResult;
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�}�l�[�W���[�̏�����
//
//�����F(LPCTSTR)�t�@�C����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT MODELMANAGER::Initialize(LPCTSTR filename)
{
    //---�e��錾---//
    HRESULT hResult;

    std::vector<FILEPARAMETER> conList;

    //---����������---//
    Model.clear();

    //---�I�u�W�F�N�g����---//
    //�t�@�C���̐ݒ�
    hResult = Load(conList, filename);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�I�u�W�F�N�g���X�g�̓ǂݍ��݂Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //���f���f�[�^�̍쐬
    for (auto& data : conList)
    {
        if (FAILED(Create(data)))
        {
            MessageBox(nullptr, TEXT("�I�u�W�F�N�g�f�[�^�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
            Uninitialize();
            return hResult;
        }
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FLoad
//
//�@�\�F�ǂݍ��݃f�[�^�̊i�[
//
//�����F(TEXTUREPARAMETER)�e�N�X�`�����X�g,(LPCTSTR)�t�@�C����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT MODELMANAGER::Load(std::vector<FILEPARAMETER>& list, LPCTSTR filename)
{
    //---�e��錾---//
    int nCounter;
    std::string szFileName;
    std::string szKeyName;
    std::ifstream file(filename);

    //---����������---//
    nCounter = 0;
    list.resize(999);

    //---�t�@�C���̓ǂݍ���---//
    if (!file.is_open())
    {
        MessageBox(nullptr, TEXT("���f�����X�g���J���܂���ł���"), filename, MB_ICONSTOP | MB_OK);
        Uninitialize();
        return E_FAIL;
    }

    //---�f�[�^�̒��o---//
    while (!file.eof())
    {
        file >> szFileName >> szKeyName;

#ifdef _UNICODE
        list.at(nCounter).FileName.resize(szFileName.size());
        list.at(nCounter).FileName = std::wstring(szFileName.begin(), szFileName.end());
        list.at(nCounter).CallKey.resize(szKeyName.size());
        list.at(nCounter).CallKey = std::wstring(szKeyName.begin(), szKeyName.end());
#else
        list.at(nCounter).FileName = szFileName;
        list.at(nCounter).CallKey = szKeyName;
#endif

        ++nCounter;
    }

    list.resize(nCounter);

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�}�l�[�W���[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void MODELMANAGER::Uninitialize(void)
{
    //---���---//
    //���f���̔j��
    for (auto& data : Model)
    {
        SAFE_RELEASE((*data.second->Texture));
        SAFE_RELEASE((data.second->Mesh));
        SAFE_RELEASE((data.second->MaterialBuffer));
    }
    Model.clear();
}

/////////////////////////////////////////////
//�֐����FGetTexture
//
//�@�\�F�e�N�X�`���̎擾
//
//�����F(tstring)�e�N�X�`����,(MODEL*)�i�[�A�h���X
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT MODELMANAGER::GetModel(tstring modelname, MODEL& address)
{
    try
    {
        address = *Model.at(modelname);
        //if (!address)
        //{
        //    MessageBox(nullptr, TEXT("���f�������݂��܂���"), TEXT("�G���["), MB_ICONSTOP | MB_OK);
        //    return E_FAIL;
        //}
    }
    catch (const std::out_of_range&)
    {
        MessageBox(nullptr, TEXT("���f�������݂��܂���"), TEXT("�G���["), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }
    return S_OK;
}