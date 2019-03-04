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
std::unordered_map<tstring, std::shared_ptr<MODEL>> MODELMANAGER::Model;           //�e�N�X�`��

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
    MODEL mModel;

    TCHAR szDirectory[_MAX_DIR];
    TCHAR szCurrentDirectory[_MAX_PATH];

    LPDIRECT3DDEVICE9 pDevice;
    LPD3DXMATERIAL pMaterial;
    LPD3DXMESH pTempMesh;

    //---����������---//
    pDevice = GetDevice();

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
        return E_FAIL;
    }

    //X�t�@�C���̓ǂݍ���
    hResult = D3DXLoadMeshFromX(data.FileName.data(), D3DXMESH_SYSTEMMEM, pDevice, nullptr, &mModel.MaterialBuffer, nullptr, &mModel.MaterialValue, &mModel.Mesh);
    if(FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���f���̍쐬�Ɏ��s���܂���"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //�����e�[�u���擾
    mModel.Mesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT, 0, 0, 0, 0);
    mModel.AttributeValue = 0;
    mModel.Mesh->GetAttributeTable(nullptr, &mModel.AttributeValue);
    mModel.Attribute.resize(mModel.AttributeValue);
    mModel.Mesh->GetAttributeTable(mModel.Attribute.at(0), &mModel.AttributeValue);

    //�J�����g�f�B���N�g����ύX
    if (szDirectory[0])
    {
        GetCurrentDirectory(_MAX_PATH, szCurrentDirectory);
        SetCurrentDirectory(szDirectory);
    }

    //�}�e���A���ǂݍ���
    pMaterial = (LPD3DXMATERIAL)mModel.MaterialBuffer->GetBufferPointer();
    mModel.Material.resize(mModel.MaterialValue);
    mModel.Texture.resize(mModel.MaterialValue);
    for (nCounter = 0; nCounter < mModel.MaterialValue; ++nCounter)
    {
        mModel.Material.at(nCounter) = pMaterial[nCounter].MatD3D;
        mModel.Material.at(nCounter).Ambient = mModel.Material.at(nCounter).Diffuse;
        mModel.Texture.at(nCounter) = nullptr;
        if (pMaterial[nCounter].pTextureFilename && pMaterial[nCounter].pTextureFilename[0])
        {
            // �e�N�X�`���t�@�C����ǂݍ���
            hResult = D3DXCreateTextureFromFile(pDevice, (LPCTSTR)pMaterial[nCounter].pTextureFilename, &mModel.Texture[nCounter]);
            if (FAILED(hResult))
            {
                mModel.Texture.at(nCounter) = nullptr;
                Uninitialize();
                return hResult;
            }
        }
    }

    //�@�����Ȃ���Βǉ�
    if (!(mModel.Mesh->GetFVF() & D3DFVF_NORMAL))
    {
        mModel.Mesh->CloneMeshFVF(mModel.Mesh->GetOptions(), mModel.Mesh->GetFVF() | D3DFVF_NORMAL, pDevice, &pTempMesh);
        D3DXComputeNormals(pTempMesh, nullptr);
        SAFE_RELEASE(mModel.Mesh);
        mModel.Mesh = pTempMesh;
    }

    //�J�����g�f�B���N�g�������ɖ߂�
    if (szDirectory[0])
    {
        SetCurrentDirectory(szCurrentDirectory);
    }

    Model.emplace(std::make_pair(data.CallKey, std::make_shared<MODEL>(mModel)));

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
    std::string strFileName;
    std::string strKeyName;
    std::ifstream file;

    //---����������---//
    nCounter = 0;
    list.resize(999);

    //---�t�@�C���̓ǂݍ���---//
    file.open(filename);
    if (file.fail())
    {
        MessageBox(nullptr, TEXT("���f�����X�g���J���܂���ł���"), filename, MB_ICONSTOP | MB_OK);
        Uninitialize();
        return E_FAIL;
    }

    //---�f�[�^�̒��o---//
    while (!file.eof())
    {
        //�f�[�^�ǂݎ��
        file >> strFileName >> strKeyName;

        //�i�[
        list.at(nCounter).FileName = tstring(strFileName.begin(), strFileName.end());
        list.at(nCounter).CallKey = tstring(strKeyName.begin(), strKeyName.end());

        ++nCounter;
    }

    list.resize(nCounter);
    file.close();

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
        SAFE_RELEASE((data.second->Mesh));
        SAFE_RELEASE((data.second->MaterialBuffer));
        for (auto& texture : data.second->Texture)
        {
            SAFE_RELEASE((texture));
        }
    }
    Model.clear();
}

/////////////////////////////////////////////
//�֐����FGetTexture
//
//�@�\�F�e�N�X�`���̎擾
//
//�����F(LPCTSTR)�e�N�X�`����,(MODEL*)�i�[�A�h���X
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT MODELMANAGER::GetModel(LPCTSTR modelname, std::weak_ptr<MODEL>& address)
{
    try
    {
        address = Model.at(modelname);
    }
    catch (const std::out_of_range&)
    {
        MessageBox(nullptr, TEXT("���f�������݂��܂���"), modelname, MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }
    return S_OK;
}