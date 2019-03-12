//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "AnimationModelManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "Player.h"
#include "Skill.h"
#include "Sphere.h"
#include "SquareGauge.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：敵の描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ENEMY::Draw(void)
{
    //---各種宣言---//
    D3DXMATRIX mtxWorld;

    //---ワールドマトリクスの設定---//
    //初期化
    D3DXMatrixIdentity(&mtxWorld);

    //設定
    Transform.MakeWorldMatrix(mtxWorld);

    //---描画---//
    Model->Draw(mtxWorld, Gray);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：敵の初期化
//
//引数：(LPCTSTR)モデル名,(tstirng)タグ,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き,(D3DXVECTOR3)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ENEMY::Initialize(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
	//初期設定
	Transform.Position = position;
	Transform.Rotation = rotation;
    Transform.Scale = scale;
    AttackCool = 0;
    Gray = false;
	Tag = tag;
	//StateType = ENEMYSTATE_NORMAL;

    //Xファイルの読み込み
    hResult = ANIMATIONMODELMANAGER::GetModel(modelname, Model);
    if (SUCCEEDED(hResult))
    {
        Model->ChangeAnimation(0);
    }
    else
	{
        MessageBox(nullptr, TEXT("敵のモデル情報の取得に失敗しました"), modelname, MB_OK);
        Uninitialize();
		return hResult;
	}

	return hResult;
}

/////////////////////////////////////////////
//関数名：SearchTarget
//
//機能：索敵
//
//引数：(D3DXVECTOR3)目標位置,(float)視程
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool ENEMY::SearchTarget(D3DXVECTOR3 target, float visibility)
{
    if (target.x < Transform.Position.x + visibility && target > Transform.Position)
    {
        if (Transform.Rotation.y == 90.0F)
        {
            return true;
        }
    }
    else if (target.x > Transform.Position.x - visibility && target < Transform.Position)
    {
        if (Transform.Rotation.y == 270.0F)
        {
            return true;
        }
    }

    return false;
}

/////////////////////////////////////////////
//関数名：OnCollision
//
//機能：当たり判定反応時の挙動
//
//引数：(COLLISITON)相手
//
//戻り値：なし
/////////////////////////////////////////////
void ENEMY::OnCollision(COLLISION* opponent)
{

}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：敵の終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ENEMY::Uninitialize(void)
{
	//---開放---//
    Model->Uninitialize();
    Model.reset();
    if (Collision)
    {
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        Collision = nullptr;
    }
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：敵の更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ENEMY::Update(void)
{	
	//static int Count;	//端で少し止まる用

	//Transform.Position += Move;

	//switch (StateType)
	//{
	//    //===敵の通常時の行動===//
	//    case ENEMYSTATE_NORMAL:
	//	    //===敵の通常移動===//
	//	    if (Transform.Position.x > InitialPosition.x + 50.0F ||
	//		    Transform.Position.x < InitialPosition.x - 50.0F)
	//	    {
	//		    if (Transform.Position.x > InitialPosition.x + 50.0F)
	//		    {
	//			    Transform.Position.x = InitialPosition.x + 50.0F;
	//		    }
	//		    else if (Transform.Position.x < InitialPosition.x - 50.0F)
	//		    {
	//			    Transform.Position.x = InitialPosition.x - 50.0F;
	//		    }

	//		    //2秒止まる
	//		    if (++Count > 120)
	//		    {
	//			    Transform.Rotation.y *= -1;
	//			    Move.x *= -1;
	//			    Count = 0;
	//		    }
	//	    }
	//	    //===敵の索敵===//
	//	    //範囲内＆視界に入ったら（？）戦闘態勢へ
	//	    if (PLAYER::GetPlayerPosition().x > Transform.Position.x - 50.0F &&
	//		    PLAYER::GetPlayerPosition().x < Transform.Position.x + 50.0F)
	//	    {
	//		    if (PLAYER::GetPlayerPosition().x > Transform.Position.x && Transform.Rotation.y > 0.0F ||
	//			    PLAYER::GetPlayerPosition().x < Transform.Position.x &&Transform.Rotation.y < 0.0F)
	//		    {
	//			    StateType = ENEMYSTATE_BATTLE;
	//		    }
	//	    }
	//	    break;
	//
	//	    //===敵の戦闘態勢時の行動===//
	//    case ENEMYSTATE_BATTLE:
	//	    //===敵の戦闘時の移動===//
	//	    if (PLAYER::GetPlayerPosition().x - 10.0F <Transform.Position.x &&
	//		    PLAYER::GetPlayerPosition().x + 10.0F > Transform.Position.x)
	//	    {
	//		    Move.x = 0.0F;
	//		    //近距離攻撃ならここで宣言する
	//	    }
	//	    else if (PLAYER::GetPlayerPosition().x < Transform.Position.x)
	//	    {
	//		    Move.x = -1.0F;
	//		    Transform.Rotation.y = -180.0F;
	//	    }
	//	    else if (PLAYER::GetPlayerPosition().x > Transform.Position.x)
	//	    {
	//		    Move.x = 1.0F;
	//		    Transform.Rotation.y = 180.0F;
	//	    }

	//	    //===索敵範囲外なら==//
	//	    if (PLAYER::GetPlayerPosition().x < Transform.Position.x - 50.0F ||
	//		    PLAYER::GetPlayerPosition().x > Transform.Position.x + 50.0F)
	//	    {
	//		    if (InitialPosition.x + 50.0F < Transform.Position.x ||
	//			    InitialPosition.x - 50.0F > Transform.Position.x)
	//		    {
	//			    StateType = ENEMYSTATE_RETURN;
	//		    }
	//		    else
	//		    {
	//			    StateType = ENEMYSTATE_NORMAL;
	//		    }
	//	    }
	//	    break;

	//    //===元の位置に戻るまで===//
	//    case ENEMYSTATE_RETURN:

	//	    if (InitialPosition.x < Transform.Position.x)
	//	    {
	//		    Move.x = -1.0F;
	//		    Transform.Rotation.y = -180.0F;
	//	    }
	//	    else if (InitialPosition.x > Transform.Position.x)
	//	    {
	//		    Move.x = 1.0F;
	//		    Transform.Rotation.y = 180.0F;
	//	    }

	//	    //戻ってる最中にプレイヤーを見つけたら
	//	    if (PLAYER::GetPlayerPosition().x > Transform.Position.x && Transform.Rotation.y > 0.0F ||
	//		    PLAYER::GetPlayerPosition().x < Transform.Position.x && Transform.Rotation.y < 0.0F)
	//	    {
	//		    StateType = ENEMYSTATE_BATTLE;
	//	    }
	//	    //プレイヤーを見つけず初期位置まで来たら
	//	    else if (InitialPosition.x + 50.0F > Transform.Position.x &&
	//		    InitialPosition.x - 50.0F < Transform.Position.x)
	//	    {
	//		    StateType = ENEMYSTATE_NORMAL;
	//	    }
	//	    break;

	//    default:
	//	    break;
	//}

    Gray = SQUAREGAUGE::GetFairyTime();
    if (Gray)
    {
        return;
    }
}