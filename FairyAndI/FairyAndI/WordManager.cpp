//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <fstream>
#include "TextureManager.h"
#include "WordManager.h"

//�������O���[�o���錾������//
std::unordered_map<tstring, bool> WORDMANAGER::NounLock;
std::unordered_map<tstring, bool> WORDMANAGER::AdjectiveLock;
std::unordered_map<tstring, bool> WORDMANAGER::SkillLock;
std::unordered_map<tstring, tstring> WORDMANAGER::NounToAdjective;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FCreateWord
//
//�@�\�F���t�̍쐬
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WORDMANAGER::CreateWord(void)
{
    //---�e��錾---//
    std::string szAdjective;
    std::string szNoun;
    std::wstring wszAdjective;
    std::wstring wszNoun;
    std::ifstream file;

    //---����������---//
    NounToAdjective.clear();

    //---�t�@�C���̓ǂݍ���---//
    file.open("Data/GameScene/Word/WordPair.txt");
    if (file.fail())
    {
        MessageBox(nullptr, TEXT("���[�h�y�A���X�g���J���܂���ł���"), TEXT("Data/GameScene/Word/WordPair.txt"), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return E_FAIL;
    }

    //---�f�[�^�̒��o---//
    while (!file.eof())
    {
        //�f�[�^�̓ǂݎ��
        file >> szNoun >> szAdjective;

        //�f�[�^�̍쐬
#ifdef _UNICODE
        wszNoun = std::wstring(szNoun.begin(), szNoun.end());
        wszNoun.shrink_to_fit();
        wszAdjective = std::wstring(szAdjective.begin(), szAdjective.end());
        wszAdjective.shrink_to_fit();

        NounToAdjective.emplace(std::make_pair(wszNoun, wszAdjective));
        NounLock.insert(std::make_pair(wszNoun, false));
        AdjectiveLock.insert(std::make_pair(wszAdjective, false));

#else
        NounToAdjective.emplace(std::make_pair(szNoun, szAdjective));
        NounLock.insert(std::make_pair(szNoun, false));
        AdjectiveLock.insert(std::make_pair(szAdjective, false));
#endif

    }

    file.close();

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
    //���[�h�̏���
    hResult = CreateWord();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���[�h�y�A�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //�����A�C�e���e�N�X�`�����X�g�̍쐬
    for (auto& Noun : NounLock)
    {
        for (auto& Adjective : AdjectiveLock)
        {
            SkillLock.insert(std::make_pair(Adjective.first + Noun.first, false));
        }
    }

    return hResult;
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
    //�������b�N�̔j��
    NounLock.clear();

    //�`�e�����b�N�̔j��
    AdjectiveLock.clear();

    //�X�L�����b�N�̔j��
    SkillLock.clear();

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

    //---���b�N����---//
    if (NounToAdjective.find(word) != NounToAdjective.end())
    {
        //�����ƌ`�e���̉���
        NounLock.at(word) = true;
        AdjectiveLock.at(NounToAdjective.at(word)) = true;

        //�����A�C�e���̉���
        for (auto& noun : NounLock)
        {
            if (!noun.second || noun.first == TEXT("EMPTY"))
            {
                continue;
            }
            for (auto& adjective : AdjectiveLock)
            {
                if (SkillLock.find(adjective.first + noun.first) == SkillLock.end())
                {
                    continue;
                }
                SkillLock.at(adjective.first + noun.first) = adjective.second ? true : false;
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
HRESULT WORDMANAGER::GetWordLock(LPCTSTR word, bool& lock)
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
            MessageBox(nullptr, TEXT("�P�ꂪ���݂��܂���"), TEXT("�擾�G���["), MB_ICONSTOP | MB_OK);
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
//�����F(tstring)���t,(std::weak_ptr<TEXTURE>)�i�[�A�h���X
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WORDMANAGER::GetWordTexture(LPCTSTR word, std::weak_ptr<TEXTURE>& address)
{
    try
    {
        if (FAILED(TEXTUREMANAGER::GetTexture(NounLock.at(word) ? word : TEXT("EMPTY"), address)))
        {
            MessageBox(nullptr, TEXT("�����e�N�X�`�������݂��܂���"), word, MB_ICONSTOP | MB_OK);
            return E_FAIL;
        }
    }
    catch (const std::out_of_range&)
    {
        try
        {
            if (FAILED(TEXTUREMANAGER::GetTexture(AdjectiveLock.at(word) ? word : TEXT("EMPTY"), address)))
            {
                MessageBox(nullptr, TEXT("�`�e���e�N�X�`�������݂��܂���"), word, MB_ICONSTOP | MB_OK);
                return E_FAIL;
            }
        }
        catch (const std::out_of_range&)
        {
            try
            {
                if (FAILED(TEXTUREMANAGER::GetTexture(SkillLock.at(word) ? word : TEXT("EMPTY"), address)))
                {
                    MessageBox(nullptr, TEXT("�X�L���e�N�X�`�������݂��܂���"), word, MB_ICONSTOP | MB_OK);
                    return E_FAIL;
                }
            }
            catch (const std::out_of_range&)
            {
                try
                {
                    if (FAILED(TEXTUREMANAGER::GetTexture(TEXT("EMPTY"), address)))
                    {
                        MessageBox(nullptr, TEXT("�G���v�e�B�e�N�X�`�������݂��܂���"), word, MB_ICONSTOP | MB_OK);
                        return E_FAIL;
                    }
                }
                catch (const std::out_of_range&)
                {
                    MessageBox(nullptr, TEXT("�\���\�Ȍ��t�̃e�N�X�`�������݂��܂���"), word, MB_ICONSTOP | MB_OK);
                    return E_FAIL;
                }
            }
        }
    }
    return S_OK;
}