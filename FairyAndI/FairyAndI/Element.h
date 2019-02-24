#ifndef _ELEMENT_H_
#define _ELEMENT_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//＝＝＝前方宣言＝＝＝//
class SPHERE;

//＝＝＝クラス宣言＝＝＝//
class ELEMENT final : public GAMEOBJECT
{
	private:
        bool Gray;
        tstring Type;

        std::weak_ptr<MODEL> Model;
        SPHERE* Collision;
        LPCTSTR Name;

	public:
        ELEMENT(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
        ~ELEMENT(void);

        void Draw(void);
		HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);

        void OnCollision(COLLISION*);
};

#endif