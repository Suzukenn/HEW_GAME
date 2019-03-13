#ifndef _GAME_SCENE_03_H_
#define _GAME_SCENE_03_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BaseScene.h"
#include "BackGround.h"
#include "Canvas.h"
#include "Field.h"
#include "FlexibleCamera.h"
#include "Ground.h"
#include "Main.h"

//�������N���X�錾������//
class GAME03 final : public BASE_SCENE
{
private:
	BACKGROUND Back;
	BACKGROUND Back_Front;
	CANVAS Canvas;
	FIELD Field;
	GROUND Ground;
	FLEXIBLECAMERA FlexibleCamera;

	bool Mode;

public:
	void Draw(void);
	void Uninitialize(void);
	HRESULT Initialize(void);
	void Update(void);
};

#endif