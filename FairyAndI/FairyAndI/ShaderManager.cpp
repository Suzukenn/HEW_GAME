//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <fstream>
#include <string>
#include <vector>
#include "Main.h"
#include "Shader.h"
#include "ShaderManager.h"

//�������O���[�o���ϐ�������//
std::unordered_map<tstring, std::shared_ptr<SHADER>> SHADERMANAGER::Shader;

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
HRESULT SHADERMANAGER::Create(const FILEPARAMETER& data)
{
    //---�e��錾---//
    HRESULT hResult;
    D3DXHANDLE hCurrentHandle;
    D3DXHANDLE hNextHandle;
    D3DXTECHNIQUE_DESC TechnicDiscriptor;
    SHADER sShader;
    std::string strName;
    LPD3DXBUFFER pErrMessage;

    //---����������---//
    hCurrentHandle = nullptr;

    //---�f�[�^�̓W�J---//
    //�t�@�C���̎w��m�F
    if (!data.FileName.data())
    {
        MessageBox(nullptr, TEXT("�J���V�F�[�_�[�t�@�C����������܂���"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //�e�N�X�`���̍쐬
#ifdef _DEBUG
    hResult = D3DXCreateEffectFromFile(GetDevice(), data.FileName.data(), nullptr, nullptr, D3DXSHADER_DEBUG, nullptr, &sShader.Effect, &pErrMessage);
#else
    hResult = D3DXCreateEffectFromFile(GetDevice(), data.FileName.data(), nullptr, nullptr, D3DXSHADER_OPTIMIZATION_LEVEL1, nullptr, &sShader.Effect, &pErrMessage);
#endif // _DEBUG

    if (SUCCEEDED(hResult))
    {
        do
        {
            hResult = sShader.Effect->FindNextValidTechnique(hCurrentHandle, &hNextHandle);
            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("�e�N�j�b�N�̃n���h���̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
                return hResult;
            }
            if (hNextHandle)
            {
                hResult = sShader.Effect->GetTechniqueDesc(hNextHandle, &TechnicDiscriptor);
                if (SUCCEEDED(hResult))
                {
                    strName = std::string(TechnicDiscriptor.Name);
                    sShader.Technic.emplace(std::make_pair(tstring(strName.begin(), strName.end()), hNextHandle));
                    sShader.Dectriptor.emplace(std::make_pair(tstring(strName.begin(), strName.end()), TechnicDiscriptor));
                }
                else
                {
                    MessageBox(nullptr, TEXT("�e�N�j�b�N�̃f�[�^�̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
                    return hResult;
                }
            }

        } while (!hNextHandle);
        Shader.emplace(std::make_pair(data.CallKey, std::make_shared<SHADER>(sShader)));
    }
    else
    {
        MessageBox(nullptr, TEXT("�V�F�[�_�[�̍쐬�Ɏ��s���܂���"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return hResult;
    }

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
HRESULT SHADERMANAGER::Initialize(LPCTSTR filename)
{
    //---�e��錾---//
    HRESULT hResult;

    std::vector<FILEPARAMETER> conList;

    //---����������---//
    Shader.clear();

    //---�I�u�W�F�N�g����---//
    //�t�@�C���̐ݒ�
    hResult = Load(conList, filename);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�V�F�[�_�[���X�g�̓ǂݍ��݂Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //�e�N�X�`���f�[�^�̍쐬
    for (auto& data : conList)
    {
        if (FAILED(Create(data)))
        {
            MessageBox(nullptr, TEXT("�V�F�[�_�[�f�[�^�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
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
HRESULT SHADERMANAGER::Load(std::vector<FILEPARAMETER>& list, LPCTSTR filename)
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
        MessageBox(nullptr, TEXT("�V�F�[�_�[���X�g���J���܂���ł���"), filename, MB_ICONSTOP | MB_OK);
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
void SHADERMANAGER::Uninitialize(void)
{
    //---�J��---//
    //�e�N�X�`���̔j��
    for (auto& data : Shader)
    {
        SAFE_RELEASE(data.second->Effect);
    }
    Shader.clear();
}

/////////////////////////////////////////////
//�֐����FGetTexture
//
//�@�\�F�e�N�X�`���̎擾
//
//�����F(LPCTSTR)�V�F�[�_�[��,(LPDIRECT3DTEXTURE9)�i�[�A�h���X
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT SHADERMANAGER::GetShader(LPCTSTR shadername, std::weak_ptr<SHADER>& address)
{
    try
    {
        address = Shader.at(shadername);
    }
    catch (const std::out_of_range&)
    {
        MessageBox(nullptr, TEXT("�V�F�[�_�[�����݂��܂���"), shadername, MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }
    return S_OK;
}