#ifndef _ITEM_H_
#define _ITEM_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//＝＝＝クラス宣言＝＝＝//
class ITEM final : private GAMEOBJECT
{
	private:
        LPCTSTR Name;

	public:
        void Draw(void);
		HRESULT Initialize(LPCTSTR);
		void Uninitialize(void);
		void Update(void);

        void OnCollision(COLLISION*);
};

#endif