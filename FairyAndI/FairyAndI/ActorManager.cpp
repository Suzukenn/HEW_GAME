//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <algorithm>
#include <list>
#include "ActorManager.h"
#include "Bullet.h"
#include "Main.h"
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
//関数名：FindObject
//
//機能：指定オブジェクトの検索・リストの生成
//
//引数：(std::vector<GAMEOBJECT*>)格納リスト,(tstring)検索タグ
//
//戻り値：なし
/////////////////////////////////////////////
void ACTORMANAGER::FindObject(std::vector<GAMEOBJECT*>& list, tstring tag)
{
    for (auto& data : GameObject)
    {
        if (data->GetTag() == tag)
        {
            list.emplace_back(data);
        }
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

    //---リストのクリア---//
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
    //---各種宣言---//
    bool bDestroy;

    std::list<GAMEOBJECT*>::iterator itrObject;

    //---初期化処理---//
    bDestroy = false;
    itrObject = GameObject.begin();

    //---現存オブジェクトの更新---//
    for (auto& data : GameObject)
    {
        data->Update();
    }

    //---廃棄の実行---//
    while (itrObject != GameObject.end())
    {
        for (auto& itrDestroy = DestroyObject.begin(); itrDestroy != DestroyObject.end(); ++itrDestroy)
        {
            //廃棄リストと照合
            if (*itrObject == *itrDestroy)
            {
                itrObject = GameObject.erase(itrObject);
                DestroyObject.remove(*itrDestroy);
                bDestroy = true;
                break;
            }
        }

        //廃棄しなかったときのみインクリメント
        if (bDestroy)
        {
            bDestroy = false;
        }
        else
        {
            ++itrObject;
        }
    }

    //---リストのクリア---//
    DestroyObject.clear();
}