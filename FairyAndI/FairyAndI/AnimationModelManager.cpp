//�������w�b�_�t�@�C���ǂݍ��݁�����//
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <tchar.h>
#include <vector>
#include "AnimationModelManager.h"
#include "Main.h"

//�������O���[�o���ϐ�������//
std::unordered_map<tstring, std::shared_ptr<ANIMATIONMODEL>> ANIMATIONMODELMANAGER::Model;

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
HRESULT ANIMATIONMODELMANAGER::Create(const FILEPARAMETER& data)
{
    //---�e��錾---//
    HRESULT hResult;
    ANIMATIONMODEL mModel;

    //---���f���f�[�^�̓ǂݍ���---//
    hResult = mModel.Initialize(data.FileName.data(), 1.0F);
    if (SUCCEEDED(hResult))
    {
        Model.emplace(std::make_pair(data.CallKey, std::make_shared<ANIMATIONMODEL>(mModel)));
    }
    else
    {
        MessageBox(nullptr, TEXT("���f���̍쐬�Ɏ��s���܂���"), data.FileName.data(), MB_ICONSTOP | MB_OK);
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
HRESULT ANIMATIONMODELMANAGER::Initialize(LPCTSTR filename)
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
HRESULT ANIMATIONMODELMANAGER::Load(std::vector<FILEPARAMETER>& list, LPCTSTR filename)
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
void ANIMATIONMODELMANAGER::Uninitialize(void)
{
    //---���---//
    //���f���̔j��
    for (auto& data : Model)
    {
        data.second->Uninitialize();
    }
    Model.clear();
}

/////////////////////////////////////////////
//�֐����FGetTexture
//
//�@�\�F�e�N�X�`���̎擾
//
//�����F(LPCTSTR)�e�N�X�`����,(std::shared_ptr<ANIMATIONMODEL>)�i�[�A�h���X
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ANIMATIONMODELMANAGER::GetModel(LPCTSTR modelname, std::shared_ptr<ANIMATIONMODEL>& address)
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