#ifndef _WOODGIMMICK_H_
#define _WOODGIMMICK_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//＝＝＝前方宣言＝＝＝//
class OBB;

//＝＝＝クラス宣言＝＝＝//
class WOODGIMMICK final : public GAMEOBJECT
{
	private:
		std::unique_ptr<MODEL> Model;
		OBB* Collision;

	public:

		WOODGIMMICK(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		~WOODGIMMICK();

		HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void OnCollision(COLLISION*);

		D3DXVECTOR3 GetPos(void);
};
#endif