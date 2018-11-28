////�������w�b�_�t�@�C���ǂݍ��݁�����//
//#define _CRT_SECURE_NO_WARNINGS
//#include <fstream>
//#include <memory>
//#include <string>
//#include <tchar.h>
//#include <unordered_map>
//#include <vector>
//#include "Main.h"
//#include "ItemManager.h"
//
////�������O���[�o���ϐ�������//
//std::unordered_map<int, MODEL*> ITEMMANAGER::Item;           //�e�N�X�`��
//
////�������֐���`������//
///////////////////////////////////////////////
////�֐����FCreate
////
////�@�\�F���f���̍쐬
////
////�����F(FILEPARAMETER)�Q�ƃf�[�^
////
////�߂�l�F(HRESULT)�����̐���
///////////////////////////////////////////////
//HRESULT ITEMMANAGER::Create(const FILEPARAMETER& data)
//{
//    //---�e��錾---//
//    HRESULT hResult;
//    DWORD nCounter;
//
//    TCHAR szDirectory[_MAX_DIR];
//    TCHAR szCurrentDirectory[_MAX_PATH];
//
//    LPDIRECT3DDEVICE9 pDevice;
//    LPD3DXBUFFER pMaterialBuffer;
//    LPD3DXMATERIAL pMaterial;
//    MODEL* pModel;
//
//    //---����������---//
//    pDevice = GetDevice();
//    pMaterialBuffer = nullptr;
//    pModel = new MODEL();
//
//    //---�f�[�^�̓W�J---//
//    //�t�@�C���̎w��m�F
//    if (data.FileName.data())
//    {
//        //�t�H���_���𒊏o
//        _tsplitpath(data.FileName.data(), nullptr, szDirectory, nullptr, nullptr);
//    }
//    else
//    {
//        MessageBox(nullptr, TEXT("�J�����f���t�@�C����������܂���"), data.FileName.data(), MB_ICONSTOP | MB_OK);
//        delete pModel;
//        return E_FAIL;
//    }
//
//    //X�t�@�C���̓ǂݍ���
//    hResult = D3DXLoadMeshFromX(data.FileName.data(), D3DXMESH_SYSTEMMEM, pDevice, nullptr, &pMaterialBuffer, nullptr, &pModel->MaterialValue, &pModel->Mesh);
//    if (FAILED(hResult))
//    {
//        MessageBox(nullptr, TEXT("���f���̍쐬�Ɏ��s���܂���"), data.FileName.data(), MB_ICONSTOP | MB_OK);
//        Uninitialize();
//        return hResult;
//    }
//
//    //�����e�[�u���擾
//    pModel->Mesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT, 0, 0, 0, 0);
//    pModel->AttributeValue = 0;
//    pModel->Mesh->GetAttributeTable(nullptr, &pModel->AttributeValue);
//    pModel->Attribute = new D3DXATTRIBUTERANGE[pModel->AttributeValue];
//    pModel->Mesh->GetAttributeTable(pModel->Attribute, &pModel->AttributeValue);
//
//    //�J�����g�f�B���N�g����ύX
//    if (szDirectory[0])
//    {
//        GetCurrentDirectory(_MAX_PATH, szCurrentDirectory);
//        SetCurrentDirectory(szDirectory);
//    }
//
//    //�}�e���A���ǂݍ���
//    pMaterial = (LPD3DXMATERIAL)pMaterialBuffer->GetBufferPointer();
//    pModel->Material = new D3DMATERIAL9[pModel->MaterialValue];
//    pModel->Texture = new LPDIRECT3DTEXTURE9[pModel->MaterialValue];
//    for (nCounter = 0; nCounter < pModel->MaterialValue; ++nCounter)
//    {
//        pModel->Material[nCounter] = pMaterial[nCounter].MatD3D;
//        pModel->Material[nCounter].Ambient = pModel->Material[nCounter].Diffuse;
//        pModel->Texture[nCounter] = nullptr;
//        if (pMaterial[nCounter].pTextureFilename && pMaterial[nCounter].pTextureFilename[0])
//        {
//            // �e�N�X�`���t�@�C����ǂݍ���
//            hResult = D3DXCreateTextureFromFile(pDevice, (LPCWSTR)pMaterial[nCounter].pTextureFilename, &pModel->Texture[nCounter]);
//            if (FAILED(hResult))
//            {
//                pModel->Texture[nCounter] = nullptr;
//                Uninitialize();
//                return hResult;
//            }
//        }
//    }
//
//    SAFE_RELEASE(pMaterialBuffer);
//
//    // �J�����g�f�B���N�g�������ɖ߂�
//    if (szDirectory[0])
//    {
//        SetCurrentDirectory(szCurrentDirectory);
//    }
//
//    Item.insert(std::make_pair(data.CallKey, pModel));
//
//    return hResult;
//}
//
///////////////////////////////////////////////
////�֐����FInitialize
////
////�@�\�F�}�l�[�W���[�̏�����
////
////�����F(LPCTSTR)�t�@�C����
////
////�߂�l�F(HRESULT)�����̐���
///////////////////////////////////////////////
//HRESULT ITEMMANAGER::Initialize(LPCTSTR filename)
//{
//    //---�e��錾---//
//    HRESULT hResult;
//
//    std::vector<FILEPARAMETER> conList;
//
//    //---����������---//
//    Item.clear();
//
//    //---�I�u�W�F�N�g����---//
//    //�t�@�C���̐ݒ�
//    hResult = Load(conList, filename);
//    if (FAILED(hResult))
//    {
//        MessageBox(nullptr, TEXT("�A�C�e�����X�g�̓ǂݍ��݂Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
//        Uninitialize();
//        return hResult;
//    }
//
//    //���f���f�[�^�̍쐬
//    for (auto& data : conList)
//    {
//        if (FAILED(Create(data)))
//        {
//            MessageBox(nullptr, TEXT("�A�C�e���f�[�^�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
//            Uninitialize();
//            return hResult;
//        }
//    }
//
//    return hResult;
//}
//
///////////////////////////////////////////////
////�֐����FLoad
////
////�@�\�F�ǂݍ��݃f�[�^�̊i�[
////
////�����F(TEXTUREPARAMETER)�e�N�X�`�����X�g,(LPCTSTR)�t�@�C����
////
////�߂�l�F(HRESULT)�����̐���
///////////////////////////////////////////////
//HRESULT ITEMMANAGER::Load(std::vector<FILEPARAMETER>& list, LPCTSTR filename)
//{
//    //---�e��錾---//
//    int nCounter;
//    std::string szFileName;
//    std::string szKeyName;
//    std::ifstream file(TEXT("Data/Common/Word/ItemList.txt"));
//
//    //---����������---//
//    nCounter = 0;
//    list.resize(999);
//
//    //---�t�@�C���̓ǂݍ���---//
//    if (!file.is_open())
//    {
//        MessageBox(nullptr, TEXT("�A�C�e�����X�g���J���܂���ł���"), TEXT("Data/Common/Word/ItemList.txt"), MB_ICONSTOP | MB_OK);
//        Uninitialize();
//        return E_FAIL;
//    }
//
//    //---�f�[�^�̒��o---//
//    while (!file.eof())
//    {
//        file >> szFileName >> szKeyName;
//
//#ifdef _UNICODE
//        list.at(nCounter).FileName.resize(szFileName.size());
//        list.at(nCounter).FileName = std::wstring(szFileName.begin(), szFileName.end());
//        list.at(nCounter).CallKey.resize(szKeyName.size());
//        list.at(nCounter).CallKey = std::wstring(szKeyName.begin(), szKeyName.end());
//#else
//        list.at(nCounter).FileName = szFileName.c_str();;
//        list.at(nCounter).CallKey = szKeyName.c_str();
//#endif
//
//        ++nCounter;
//    }
//
//    list.resize(nCounter);
//
//    return S_OK;
//}
//
///////////////////////////////////////////////
////�֐����FUninitialize
////
////�@�\�F�}�l�[�W���[�̏I��
////
////�����F�Ȃ�
////
////�߂�l�F�Ȃ�
///////////////////////////////////////////////
//void ITEMMANAGER::Uninitialize(void)
//{
//    //---���---//
//    //���f���̔j��
//    for (auto& data : Item)
//    {
//        SAFE_RELEASE((*data.second->Texture));
//        SAFE_RELEASE((data.second->Mesh));
//        SAFE_RELEASE((data.second->MaterialBuffer));
//    }
//    Item.clear();
//}
//
///////////////////////////////////////////////
////�֐����FGetTexture
////
////�@�\�F�e�N�X�`���̎擾
////
////�����F(LPCTSTR)�e�N�X�`����,(LPDIRECT3DTEXTURE9)�i�[�A�h���X
////
////�߂�l�F(HRESULT)�����̐���
///////////////////////////////////////////////
//HRESULT ITEMMANAGER::Instantiate(LPCTSTR itemname, MODEL* address)
//{
//    try
//    {
//        address = Item.at(itemname);
//        if (!address)
//        {
//            MessageBox(nullptr, TEXT("���f�������݂��܂���"), itemname, MB_ICONSTOP | MB_OK);
//            return E_FAIL;
//        }
//    }
//    catch (const std::out_of_range&)
//    {
//        MessageBox(nullptr, TEXT("���f�������݂��܂���"), itemname, MB_ICONSTOP | MB_OK);
//        return E_FAIL;
//    }
//    return S_OK;
//}