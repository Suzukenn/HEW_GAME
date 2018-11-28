//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <fstream>
#include "WordManager.h"

//�������O���[�o���錾������//
std::unordered_map<tstring, LPDIRECT3DTEXTURE9> WORDMANAGER::NounTexture;
std::unordered_map<tstring, LPDIRECT3DTEXTURE9> WORDMANAGER::AdjectiveTexture;
std::unordered_map<tstring, bool> WORDMANAGER::NounLock;
std::unordered_map<tstring, bool> WORDMANAGER::AdjectiveLock;
std::unordered_map<tstring, tstring> WORDMANAGER::NounToAdjective;
std::unordered_map<tstring, LPDIRECT3DTEXTURE9> WORDMANAGER::ItemTexture;
std::unordered_map<tstring, bool> WORDMANAGER::ItemLock;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FCreatePair
//
//�@�\�F�y�A�̍쐬
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WORDMANAGER::CreatePair(void)
{
    //---�e��錾---//
    std::string szAdjective;
    std::string szNoun;
    std::wstring wszAdjective;
    std::wstring wszNoun;
    std::ifstream file(TEXT("Data/Common/Word/WordPair.txt"));

    //---����������---//
    NounToAdjective.clear();

    //---�t�@�C���̓ǂݍ���---//
    if (!file.is_open())
    {
        MessageBox(nullptr, TEXT("���[�h�y�A���X�g���J���܂���ł���"), TEXT("Data/Common/Word/WordPair.txt"), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return E_FAIL;
    }

    //---�f�[�^�̒��o---//
    while (!file.eof())
    {
        file >> szNoun >> szAdjective;

#ifdef _UNICODE
        wszNoun = std::wstring(szNoun.begin(), szNoun.end());
        wszNoun.shrink_to_fit();
        wszAdjective = std::wstring(szAdjective.begin(), szAdjective.end());
        wszAdjective.shrink_to_fit();
#endif
        NounToAdjective.insert(std::make_pair(wszNoun, wszAdjective));
    }

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FCreateTexture
//
//�@�\�F�e�N�X�`���̍쐬
//
//�����F(std::unordered_map<tstring, LPDIRECT3DTEXTURE9>)�i�[���X�g,(FILEPARAMETER)�Q�ƃf�[�^
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WORDMANAGER::CreateTexture(std::unordered_map<tstring, LPDIRECT3DTEXTURE9>& list, const FILEPARAMETER& data)
{
    //---�e��錾---//
    std::unique_ptr<LPDIRECT3DTEXTURE9> pTexture;

    //---����������---//
    pTexture.reset(new LPDIRECT3DTEXTURE9());

    //---�f�[�^�̓W�J---//
    //�t�@�C���̎w��m�F
    if (!data.FileName.data())
    {
        MessageBox(nullptr, TEXT("�J���e�N�X�`���t�@�C����������܂���"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //�e�N�X�`���̍쐬
    if (SUCCEEDED(D3DXCreateTextureFromFile(GetDevice(), data.FileName.data(), pTexture.get())))
    {
        list.insert(std::make_pair(data.CallKey, *pTexture));
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
//�@�\�F���[�h�}�l�[�W���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WORDMANAGER::Initialize(void)
{
    //---�e��錾---//
    HRESULT hResult;

    std::vector<FILEPARAMETER> conList;

    //---�I�u�W�F�N�g����---//
    //�����e�N�X�`�����X�g�̓ǂݍ���
    hResult = LoadTexture(conList, TEXT("Data/Common/Word/NounList.txt"));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�����e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //�����e�N�X�`���̍쐬
    for (auto& data : conList)
    {
        if (FAILED(CreateTexture(NounTexture, data)))
        {
            MessageBox(nullptr, TEXT("�����e�N�X�`���f�[�^�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
            Uninitialize();
            return hResult;
        }
        NounLock.insert(std::make_pair(data.CallKey, false));
    }

    //�`�e���e�N�X�`�����X�g�̓ǂݍ���
    hResult = LoadTexture(conList, TEXT("Data/Common/Word/AdjectiveList.txt"));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�`�e���e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //�`�e���e�N�X�`���̍쐬
    for (auto& data : conList)
    {
        if (FAILED(CreateTexture(AdjectiveTexture, data)))
        {
            MessageBox(nullptr, TEXT("�`�e���e�N�X�`���f�[�^�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
            Uninitialize();
            return hResult;
        }
        AdjectiveLock.insert(std::make_pair(data.CallKey, false));
    }

    //���[�h�y�A�̍쐬
    hResult = CreatePair();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���[�h�y�A�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //�����A�C�e���e�N�X�`�����X�g�̓ǂݍ���
    hResult = LoadTexture(conList, TEXT("Data/Common/Word/ItemList.txt"));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�����A�C�e���e�N�X�`�����X�g�̓ǂݍ��݂Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //�����A�C�e���e�N�X�`���̍쐬
    for (auto& data : conList)
    {
        if (FAILED(CreateTexture(ItemTexture, data)))
        {
            MessageBox(nullptr, TEXT("�����A�C�e���e�N�X�`���f�[�^�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
            Uninitialize();
            return hResult;
        }
        ItemLock.insert(std::make_pair(data.CallKey, false));
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FLoadTexture
//
//�@�\�F���[�h�e�N�X�`���̓ǂݍ���
//
//�����F(FILEPARAMETER)�e�N�X�`�����X�g,(LPCTSTR)���X�g�t�@�C��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WORDMANAGER::LoadTexture(std::vector<FILEPARAMETER>& list, LPCTSTR filename)
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

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F���[�h�}�l�[�W���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WORDMANAGER::Uninitialize(void)
{
    //---�J��---//
    //�����e�N�X�`���̔j��
    for (auto& data : NounTexture)
    {
        SAFE_RELEASE(data.second);
    }
    NounTexture.clear();

    //�`�e���e�N�X�`���̔j��
    for (auto& data : AdjectiveTexture)
    {
        SAFE_RELEASE(data.second);
    }
    AdjectiveTexture.clear();

    //�������b�N�̔j��
    NounLock.clear();

    //�`�e�����b�N�̔j��
    AdjectiveLock.clear();

    //�y�A�����̔j��
    NounToAdjective.clear();
}

/////////////////////////////////////////////
//�֐����FUnLockWord
//
//�@�\�F���[�h���b�N�̉���
//
//�����F(LPCTSTR)���t
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WORDMANAGER::UnLockWord(LPCTSTR word)
{
    //---�e��錾---//
    std::vector<tstring> conList;
    std::string s = ",a,b,,c,";
    std::string buf;
    if (NounToAdjective.find(word) != NounToAdjective.end())
    {
        //�����ƌ`�e���̉���
        NounLock.at(word) = true;
        AdjectiveLock.at(NounToAdjective.at(word)) = true;

        //�����A�C�e���̉���
        for (auto& noun : NounLock)
        {
            if (!noun.second || noun.first == TEXT("LOCK"))
            {
                continue;
            }
            for (auto& adjective : AdjectiveLock)
            {
                if (ItemLock.find(adjective.first + noun.first) == ItemLock.end())
                {
                    continue;
                }
                ItemLock.at(adjective.first + noun.first) = adjective.second ? true : false;
            }
        }
    }
    else
    {
        MessageBox(nullptr, TEXT("�P�ꂪ���݂��܂���"), word, MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }
    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F���[�h�}�l�[�W���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WORDMANAGER::Update(void)
{

}

/////////////////////////////////////////////
//�֐����FGetWordLock
//
//�@�\�F���t�̃��b�N��Ԃ̎擾
//
//�����F(tstring)���t,(LPDIRECT3DTEXTURE9)�i�[�A�h���X
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WORDMANAGER::GetWordLock(tstring word, bool& lock)
{
    try
    {
        lock = NounLock.at(word);
    }
    catch (const std::out_of_range&)
    {
        try
        {
            lock = AdjectiveLock.at(word);
        }
        catch (const std::out_of_range&)
        {
            MessageBox(nullptr, TEXT("�P�ꂪ�����݂��܂���"), TEXT("�擾�G���["), MB_ICONSTOP | MB_OK);
            return E_FAIL;
        }
    }
    return S_OK;
}

/////////////////////////////////////////////
//�֐����FGetWordTexture
//
//�@�\�F�e�N�X�`���̎擾
//
//�����F(tstring)���t,(LPDIRECT3DTEXTURE9)�i�[�A�h���X
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WORDMANAGER::GetWordTexture(tstring word, LPDIRECT3DTEXTURE9& address)
{
    try
    {
        address = NounLock.at(word) ? NounTexture.at(word) : NounTexture.at(TEXT("LOCK"));
        if (!address)
        {
            MessageBox(nullptr, TEXT("�e�N�X�`�������݂��܂���"), TEXT("�擾�G���["), MB_ICONSTOP | MB_OK);
            return E_FAIL;
        }
    }
    catch (const std::out_of_range&)
    {
        try
        {
            address = AdjectiveLock.at(word) ? AdjectiveTexture.at(word) : AdjectiveTexture.at(TEXT("LOCK"));
            if (!address)
            {
                MessageBox(nullptr, TEXT("�e�N�X�`�������݂��܂���"), TEXT("�擾�G���["), MB_ICONSTOP | MB_OK);
                return E_FAIL;
            }
        }
        catch (const std::out_of_range&)
        {
            try
            {
                address = ItemLock.at(word) ? ItemTexture.at(word) : ItemTexture.at(TEXT("UNKNOWN"));
                if (!address)
                {
                    MessageBox(nullptr, TEXT("�e�N�X�`�������݂��܂���"), TEXT("�擾�G���["), MB_ICONSTOP | MB_OK);
                    return E_FAIL;
                }
            }
            catch (const std::out_of_range&)
            {
                MessageBox(nullptr, TEXT("�e�N�X�`�������݂��܂���"), TEXT("�擾�G���["), MB_ICONSTOP | MB_OK);
                return E_FAIL;
            }
        }
    }
    return S_OK;
}