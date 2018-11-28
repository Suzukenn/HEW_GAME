#ifndef _PLAYER_H_
#define _PLAYER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "Base3Dobject.h"
#include "Main.h"
#include "Model.h"

//---定数・マクロ定義---//
#define	VALUE_MOVE_PLAYER 5.0F

//＝＝＝クラス定義＝＝＝//
class PLAYER final : private BASE3DOBJECT
{
	private:
        LPDIRECT3DTEXTURE9 Texture;	//テクスチャへのポインタ
        LPD3DXMESH Mesh;		    //メッシュ情報へのポインタ
        LPD3DXBUFFER MaterialBuffer;//マテリアル情報へのポインタ
        DWORD MaterialValue;	    //マテリアル情報の数

        D3DXVECTOR3 Move;

	public:
        void Draw(void);
		HRESULT Initialize(LPCTSTR);
		void Uninitialize(void);
		void Update(void);
		const D3DXVECTOR3 GetPlayerPosition(void);
		const LPD3DXVECTOR3 GetPlayerRotation(void);
};
#endif
