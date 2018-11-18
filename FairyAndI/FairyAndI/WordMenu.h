#ifndef _WORDMENU_H_
#define _WORDMENU_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include <vector>
#include "BackGround.h"
#include "Main.h"
#include "SelectMarker.h"
#include "WordList.h"
#include "WordPlate.h"

//�������񋓌^��`������//
enum
{
    SETTING_STATE_ADJECTIVELIST,
    SETTING_STATE_NOUN,
    SETTING_STATE_SELECT,
    SETTING_STATE_MAX
};

//�������N���X�錾������//
class WORDMENU
{
    private:
        int State;
        BACKGROUND Back;
        SELECTMARKER SelectMarker;
        std::array<WORDPLATE, 2> SelectWord;
        std::array<WORDLIST, 2> List;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif