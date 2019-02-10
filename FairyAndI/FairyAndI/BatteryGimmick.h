#ifndef _BATTERYGIMMICK_H_
#define _BATTERYGIMMICK_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//＝＝＝前方宣言＝＝＝//
class SPHERE;
//class OBB;
//＝＝＝クラス宣言＝＝＝//
class BATTERYGIMMICK final : public GAMEOBJECT
{
	private:

		std::weak_ptr<MODEL> Model;
		SPHERE* Collision;
		//OBB* Collision;

	public:

		BATTERYGIMMICK(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
		~BATTERYGIMMICK(void);

		HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void OnCollision(COLLISION*);

		D3DXVECTOR3 GetPos(void);
};
#endif