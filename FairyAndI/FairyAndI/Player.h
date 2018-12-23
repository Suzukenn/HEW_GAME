#ifndef _PLAYER_H_
#define _PLAYER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "AnimationModel.h"
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//---定数・マクロ定義---//
#define	VALUE_MOVE_PLAYER 5.0F

//＝＝＝前方宣言＝＝＝//
class OBB;

//＝＝＝クラス定義＝＝＝//
class PLAYER final : public GAMEOBJECT
{
	private:
        LPDIRECT3DTEXTURE9 Texture;	//テクスチャへのポインタ
        LPD3DXMESH Mesh;		    //メッシュ情報へのポインタ
        LPD3DXBUFFER MaterialBuffer;//マテリアル情報へのポインタ
        DWORD MaterialValue;	    //マテリアル情報の数
        D3DXVECTOR3 Move;

        ANIMATIONMODEL Model;

        OBB* Collision;

	public:
        PLAYER(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);

        void Draw(void);
		HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);

        void OnCollision(COLLISION*);

		static const D3DXVECTOR3 GetPlayerPosition(void);
		static const D3DXVECTOR3 GetPlayerRotation(void);
};
#endif
