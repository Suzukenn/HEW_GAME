#ifndef _FAIRY_H_
#define _FAIRY_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Item.h"
#include "Model.h"

#define	VALUE_MOVE_FAIRY	(2.0F)					// 移動速度

class FAIRY final : public  GAMEOBJECT
{
	private:
        LPDIRECT3DTEXTURE9 Texture;	//テクスチャへのポインタ
        LPD3DXMESH Mesh;		    //メッシュ情報へのポインタ
        LPD3DXBUFFER MaterialBuffer;//マテリアル情報へのポインタ
        DWORD MaterialValue;	    //マテリアル情報の数
        D3DXVECTOR3			Move;	// 移動
		bool				m_stat;	// 状態
		int					m_shadow;
		float				m_tar;
		ITEM*				Item;
		int					m_num;		//アイテムの添え字用
		LPD3DXVECTOR3		m_itemPos;
		LPD3DXVECTOR3		m_itemDistance;

	public:
        FAIRY(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);

		HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void OnCollision(COLLISION*);

		void TakeUpItem(LPD3DXVECTOR3);
		D3DXVECTOR3 GetPos(void);
		bool Check(void);
};
#endif
