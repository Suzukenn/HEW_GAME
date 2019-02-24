//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <fstream>
#include <string>
#include <vector>
#include "Main.h"
#include "Texture.h"
#include "TextureManager.h"

//�������O���[�o���ϐ�������//
std::unordered_map<tstring, std::shared_ptr<TEXTURE>> TEXTUREMANAGER::Texture;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FCreate
//
//�@�\�F�e�N�X�`���̍쐬
//
//�����F(FILEPARAMETER)�Q�ƃf�[�^
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT TEXTUREMANAGER::Create(const FILEPARAMETER& data)
{
    //---�e��錾---//
    TEXTURE tTexture;

    //---����������---//

    //---�f�[�^�̓W�J---//
    //�t�@�C���̎w��m�F
    if (!data.FileName.data())
    {
        MessageBox(nullptr, TEXT("�J���e�N�X�`���t�@�C����������܂���"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //�e�N�X�`���̍쐬
    if (SUCCEEDED(D3DXCreateTextureFromFile(GetDevice(), data.FileName.data(), &tTexture.Image)))
    {
        tTexture.Image->GetLevelDesc(0, &tTexture.Descriptor);
        Texture.emplace(std::make_pair(data.CallKey, std::make_shared<TEXTURE>(tTexture)));
    }
    else
    {
        MessageBox(nullptr, TEXT("�e�N�X�`���̍쐬�Ɏ��s���܂���"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    return S_OK;
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
HRESULT TEXTUREMANAGER::Initialize(LPCTSTR filename)
{
    //---�e��錾---//
    HRESULT hResult;

    std::vector<FILEPARAMETER> conList;

    //---����������---//

    //---�I�u�W�F�N�g����---//
    //�t�@�C���̐ݒ�
    hResult = Load(conList, filename);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�e�N�X�`�����X�g�̓ǂݍ��݂Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //�e�N�X�`���f�[�^�̍쐬
    for (auto& data : conList)
    {
        if (FAILED(Create(data)))
        {
            MessageBox(nullptr, TEXT("�e�N�X�`���f�[�^�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
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
//�����F(std::vector<FILEPARAMETER>&)�e�N�X�`�����X�g,(LPCTSTR)�t�@�C����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT TEXTUREMANAGER::Load(std::vector<FILEPARAMETER>& list, LPCTSTR filename)
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
    if (file.fail())
    {
        MessageBox(nullptr, TEXT("�e�N�X�`�����X�g���J���܂���ł���"), filename, MB_ICONSTOP | MB_OK);
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
    list.shrink_to_fit();

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
void TEXTUREMANAGER::Uninitialize(void)
{
    //---�J��---//
    //�e�N�X�`���̔j��
    for (auto& data : Texture)
    {
        SAFE_RELEASE(data.second->Image);
    }
    Texture.clear();
}

/////////////////////////////////////////////
//�֐����FGetTexture
//
//�@�\�F�e�N�X�`���̎擾
//
//�����F(LPCTSTR)�e�N�X�`����,(LPDIRECT3DTEXTURE9)�i�[�A�h���X
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT TEXTUREMANAGER::GetTexture(LPCTSTR texturename, std::weak_ptr<TEXTURE>& address)
{
    try
    {
        address = Texture.at(texturename);
    }
    catch (const std::out_of_range&)
    {
        MessageBox(nullptr, TEXT("�e�N�X�`�������݂��܂���"), texturename, MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }
    return S_OK;
}