#ifndef _TITLE_H_
#define _TITLE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include "AnimationbackImage.h"
#include "BackImage.h"
#include "BaseScene.h"
#include "Fade.h"
#include "FirstButton.h"
#include "Main.h"
#include "StartButton.h"
#include "TrainingButton.h"

#define TITLE_BUTTON	(2)

//�������񋓌^��`������//
typedef enum 
{
	MODE_FIRST,
	MODE_SELECT,
	MODE_MANUAL,
	MODE_MAX
}TITLE_MODE;

//�������N���X�錾������//
class TITLE final : public BASE_SCENE
{
    private:
        ANIMATIONBACKIMAGE AnimationBack;
        BACKIMAGE Back;
        ANIMATIONBACKIMAGE Logo;
		FIRSTBUTTON FirstButton;
		std::array<SPRITE, TITLE_BUTTON> SelectButton;
		ANIMATIONSPRITE Cursor;

		// �_�Ő���p
		DWORD dwTicks;
		DWORD dwMask;

		unsigned int LogoAlpha;
		TITLE_MODE Mode;
		int Select;
		D3DXVECTOR2 CursorPos;

		void ChooseStage(void);

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif