#ifndef _WOODGIMMICK_H_
#define _WOODGIMMICK_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//＝＝＝前方宣言＝＝＝//
class SPHERE;

//＝＝＝クラス宣言＝＝＝//
class WOODGIMMICK final : public GAMEOBJECT
{
	private:
        bool Gray;
        bool Small;

		std::weak_ptr<MODEL> Model;
        std::weak_ptr<SHADER> Shader;
        SPHERE* Collision;

	public:
		WOODGIMMICK(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
		~WOODGIMMICK(void);

		HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void OnCollision(COLLISION*);
};
#endif