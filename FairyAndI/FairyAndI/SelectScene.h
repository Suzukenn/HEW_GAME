#ifndef _SELECTSCENE_H_
#define _SELECTSCENE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include "BackImage.h"
#include "BaseScene.h"
#include "Main.h"
#include "StageButton.h"

//�������萔�E�}�N����`������//
#define MAX_SELECTBUTTON (3)

//�������N���X�錾������//
class SELECTSCENE final : public BASE_SCENE
{
    private:
        BACKIMAGE Back;
		std::array<STAGEBUTTON, MAX_SELECTBUTTON> Button;
		int Select;
		// �_�Ő���p
		DWORD dwTicks;
		DWORD dwMask;

		void ChooseStage(void);

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif