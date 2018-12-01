#ifndef _TRAININGSCENE_H_
#define _TRAININGSCENE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "BaseScene.h"
#include "Canvas.h"
#include "Fairy.h"
#include "Field.h"
#include "FlexibleCamera.h"
#include "Item.h"
#include "Main.h"
#include "Player.h"

//＝＝＝クラス宣言＝＝＝//
class TRAINING final : public BASE_SCENE
{
    private:
        CANVAS Canvas;
        FIELD Field;
        FLEXIBLECAMERA FlexibleCamera;
        int					m_num;		//アイテムの添え字用
        LPD3DXVECTOR3		m_itemPos;
        LPD3DXVECTOR3		m_itemDistance;

        bool Mode;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif