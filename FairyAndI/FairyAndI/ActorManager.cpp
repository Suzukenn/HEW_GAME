//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <list>
#include "Main.h"
#include "ActorManager.h"

//＝＝＝グローバル変数＝＝＝//
std::list<GAMEOBJECT*> ACTORMANAGER::GameObject;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：マネージャーの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ACTORMANAGER::Draw(void)
{
    for (auto& data : GameObject)
    {
        data->Draw();
    }
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：マネージャーの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ACTORMANAGER::Initialize(void)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    GameObject.clear();
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
void ACTORMANAGER::Instantiate(tstring gameobject)
{
    //GameObject.emplace_back();
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
void ACTORMANAGER::Uninitialize(void)
{
    //---解放---//
    for (auto& data : GameObject)
    {
        data->Uninitialize();
    }
    GameObject.clear();
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
void ACTORMANAGER::Update(void)
{
    for (auto& data : GameObject)
    {
        data->Update();
    }
}

