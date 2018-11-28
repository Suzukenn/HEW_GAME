//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <list>
#include "Main.h"
#include "CollisionManager.h"

//＝＝＝グローバル変数＝＝＝//
std::list<COLLISION*> COLLISIONMANAGER::Collision;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Initialize
//
//機能：マネージャーの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT COLLISIONMANAGER::Initialize(void)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    Collision.clear();
    hResult = S_OK;

    return hResult;
}

/////////////////////////////////////////////
//関数名：Instantiate
//
//機能：マネージャーの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void COLLISIONMANAGER::Instantiate(tstring objectname)
{
    //Collision.emplace_back(objectname);
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：マネージャーの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void COLLISIONMANAGER::Uninitialize(void)
{
    //---解放---//
    Collision.clear();
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：テクスチャの取得
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void COLLISIONMANAGER::Update(void)
{

}