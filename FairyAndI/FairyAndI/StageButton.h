#ifndef _STAGE_BUTTON_H_
#define _STAGE_BUTTON_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Button.h"
#include "Main.h"
#include "SceneManager.h"

//�������N���X�錾������//
class STAGEBUTTON final : public BUTTON
{
	private:
		SCENE Stage;
	public:
		virtual void Behavior(void) final;
		void SetSelectStage(SCENE);
};

#endif