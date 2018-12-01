//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <algorithm>
#include <list>
#include "Main.h"
#include "ActorManager.h"
#include "Bullet.h"
#include "Player.h"
#include "Fairy.h"
#include "Wall.h"

//＝＝＝グローバル変数＝＝＝//
std::list<GAMEOBJECT*> ACTORMANAGER::GameObject;
std::list<GAMEOBJECT*> ACTORMANAGER::DestroyObject;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Destroy
//
//機能：オブジェクトの削除
//
//引数：(GAMEOBJECT*)削除オブジェクト
//
//戻り値：なし
/////////////////////////////////////////////
void ACTORMANAGER::Destroy(GAMEOBJECT* object)
{
    //---廃棄リストへ登録---//
    DestroyObject.emplace_back(object);
}

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

    GameObject.emplace_back(new PLAYER(TEXT("PLAYER"), TEXT("PLAYER"), D3DXVECTOR3(0.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, -D3DX_PI * 0.5F, 0.0F)));
    GameObject.emplace_back(new FAIRY(TEXT("FAIRY"), TEXT("FAIRY"), D3DXVECTOR3(0.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, -D3DX_PI * 0.5F, 0.0F)));

    hResult = S_OK;

    return hResult;
}

/////////////////////////////////////////////
//関数名：Instantiate
//
//機能：アイテムの生成
//
//引数：(tstring)オブジェクト名,(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void ACTORMANAGER::Instantiate(tstring gameobject, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    tstring strInstance;
    std::vector<tstring> conObjectName = {TEXT("BULLET"), TEXT("WALL")};
    
    //for (auto& data : conObjectName)
    //{
    //    if (gameobject.find(data))
    //    {
    //        strInstance = data;
    //        break;
    //    }
    //}

    if (gameobject.find(TEXT("ICE")))
    {
        GameObject.emplace_back(new BULLET(TEXT("ICE"), TEXT("BULLET"), position, rotation));
    }
    else if (gameobject.find(TEXT("WALL")))
    {
        GameObject.emplace_back(new WALL(gameobject.data(), TEXT("WALL"), position, rotation));
    }
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
    for (auto& data : DestroyObject)
    {
        data->Uninitialize();
    }

    GameObject.clear();
    DestroyObject.clear();
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
    //---現存オブジェクトの更新
    for (auto& data : GameObject)
    {
        data->Update();
    }

    //---廃棄の実行---//
    for (auto& data : DestroyObject)
    {
        GameObject.remove(data);
    }
}