#ifndef _ICEGIMMICK_H_
#define _ICEGIMMICK_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//＝＝＝定数・マクロ定義＝＝＝//

//＝＝＝前方宣言＝＝＝//
class SPHERE;

//＝＝＝クラス宣言＝＝＝//
class ICEGIMMICK final : public GAMEOBJECT
{
	private:

		std::unique_ptr<MODEL> Model;
		SPHERE* Collision;

	public:

		ICEGIMMICK(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		~ICEGIMMICK();

		HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void OnCollision(COLLISION*);

		D3DXVECTOR3 GetPos(void);
};
#endif