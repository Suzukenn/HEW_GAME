//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "Fairy.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "Player.h"
#include "SideViewCamera.h"
#include "Sphere.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define	VALUE_ROTATE_FAIRY	(D3DX_PI * 0.02F)		// 回転速度

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：FAIRY
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
FAIRY::FAIRY(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, position, rotation);
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：フェアリーの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void FAIRY::Draw(void)
{
    //---各種宣言---//
    D3DXMATRIX mtxWorld;

    //---ワールドマトリクスの設定---//
    //初期化
    D3DXMatrixIdentity(&mtxWorld);

    //設定
    Transform.MakeWorldMatrix(mtxWorld);

    //---描画---//
    Model.Draw(mtxWorld, false);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：フェアリーの初期化
//
//引数：(LPCTSTR)モデル名,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT FAIRY::Initialize(LPCTSTR modelfile, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
	//初期設定
	Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(100.0F, 100.0F, 100.0F);
	Move = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Tag = TEXT("Fairy");
    Collection = false;
    ToTargetAngle = 0.0F;
    ElementPosition = Transform.Position;
    State = STATE_CHASE;

    //---モデルの読み込み---//
    hResult = Model.Initialize(modelfile, 1.0F);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("フェアリーのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }
    else
    {
        Model.ChangeAnimation(0);
    }

    //---当たり判定の付与---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 5.0F, TEXT("Character"), this);

	return hResult;
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
void FAIRY::OnCollision(COLLISION* opponent)
{
    //プレイヤーの後ろにつく
    if (opponent->Owner->GetTag() == TEXT("Player"))
    {
        /*Move.x = 0.0F;
        Move.z = 0.0F;*/
    }
    else if (opponent->Owner->GetTag() == TEXT("Element"))
    {
        Collection = false;
    }
}

/////////////////////////////////////////////
//関数名：SearchElement
//
//機能：最も近いエレメントの検索
//
//引数：なし
//
//戻り値：(D3DXVECTOR3)最短位置
/////////////////////////////////////////////
bool FAIRY::SearchElement(D3DXVECTOR3& destination)
{
    //---各種宣言---//
    float fCurrentCalcDistance;         //現在算出した距離
    float fShortestDistance;            //暫定最短距離
    D3DXVECTOR3 vecDistance;

    //---初期化処理---//
    Element.clear();
    fShortestDistance = INFINITY;

    //エレメントを検索
    ACTORMANAGER::FindObject(Element, TEXT("Element"));

    if (Element.empty())
    {
        destination = Transform.Position;
        return false;
    }
    else
    {
        for (auto& data : Element)
        {
            //自身との距離の算出
            vecDistance = data->GetPosition() - Transform.Position;
            fCurrentCalcDistance = vecDistance.x * vecDistance.x + vecDistance.y * vecDistance.y;

            //最短距離なら回収アイテムを変更
            if (fShortestDistance > fCurrentCalcDistance)
            {
                fShortestDistance = fCurrentCalcDistance;
                destination = data->GetPosition();
            }
        }
        return true;
    }
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：フェアリーの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void FAIRY::Uninitialize(void)
{
    Model.Uninitialize();
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：フェアリーの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void FAIRY::Update(void)
{
    //---各種宣言---//
    D3DXVECTOR3 vecFairyDistance;
    static int nFrameCount = 0;

    //フレーム数のカウント
    if (++nFrameCount > 120)
    {
        nFrameCount = 0;
    }

	//移動
	Transform.Position += Move;
	Collision->Position = Transform.Position;

    //ボタンを押したら思考状態へ移行
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        //if (State == STATE_CHASE)
        //{
        //    State = STATE_SYNTHIESIS;

        //}
        //else if (State == STATE_SYNTHIESIS)
        //{
        //    State = STATE_CHASE;
        //}
        State = (STATE)((DWORD)!State);

        Model.ChangeAnimation((DWORD)State);
    }
    //return;

	//ボタンを押したらアイテムを取りに行く
	if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P,XINPUT_GAMEPAD_X, TRIGGER))
	{
        Collection = SearchElement(ElementPosition);
	}

    if (Collection)
    {
        //妖精とエレメントの距離の算出
        vecFairyDistance.x = ElementPosition.x - Transform.Position.x;
        vecFairyDistance.y = ElementPosition.y - Transform.Position.y;
        Transform.Rotation.y = 90.0F * ((ElementPosition.x > Transform.Position.x) - (ElementPosition.x < Transform.Position.x));
    }
    else
    {
        //妖精とプレイヤーの距離の算出
        vecFairyDistance.x = PLAYER::GetPlayerPosition().x - Transform.Position.x;
        vecFairyDistance.y = PLAYER::GetPlayerPosition().y + 20.0F - Transform.Position.y;
        Transform.Rotation.y = 90.0F * ((PLAYER::GetPlayerPosition().x > Transform.Position.x) - (PLAYER::GetPlayerPosition().x < Transform.Position.x));
    }

	//移動量設定
    if (vecFairyDistance.x == 0.0F && vecFairyDistance.y == 0.0F)
    {
        vecFairyDistance.x += 0.00001F; //atan2エラー防止
    }
        
    ToTargetAngle = atan2f(vecFairyDistance.y, vecFairyDistance.x);

	//移動量格納
	Move.x = cosf(ToTargetAngle) * VALUE_MOVE_FAIRY;
    Move.y = sinf(ToTargetAngle) * VALUE_MOVE_FAIRY + (sinf(D3DXToRadian(-180.0F) + D3DX_PI / 60.0F * nFrameCount)) * 0.5F;

	if (!Collection)
	{
		//移動範囲指定
		if (Transform.Rotation.y == PLAYER::GetPlayerRotation().y && Transform.Position.x > PLAYER::GetPlayerPosition().x - 5.0F && Transform.Position.x < PLAYER::GetPlayerPosition().x + 5.0F)
		{
			Move.x = 0.0F;
		}
	}
}