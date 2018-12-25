//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Collision.h"
#include "Fairy.h"
#include "InputManager.h"
#include "Item.h"
#include "ModelManager.h"
#include "Player.h"
#include "SideViewCamera.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define	VALUE_ROTATE_FAIRY	(D3DX_PI * 0.02F)		// 回転速度

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：FAIRY
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(tstirng)タグ,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
FAIRY::FAIRY(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, tag, position, rotation);
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
    DWORD nCounter;
    LPDIRECT3DDEVICE9 pDevice;
    D3DXMATRIX mtxRotation;
    D3DXMATRIX mtxTranslate;
    D3DXMATRIX mtxWorld;
    LPD3DXMATERIAL pMatrix;
    D3DMATERIAL9 matDef;

    //---初期化処理---//
    pDevice = GetDevice();

    //---ワールドマトリクスの設定---//
    //初期化
    D3DXMatrixIdentity(&mtxWorld);

    //回転を反映
    D3DXMatrixRotationYawPitchRoll(&mtxRotation, Rotation.y, Rotation.x, Rotation.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRotation);

    //移動を反映
    D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

    //設定
    pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

    // 現在のマテリアルを取得
    pDevice->GetMaterial(&matDef);

    //---描画---//
    //ポインタを取得
    pMatrix = (LPD3DXMATERIAL)MaterialBuffer->GetBufferPointer();

    for (nCounter = 0; nCounter < MaterialValue; ++nCounter)
    {
        //マテリアルの設定
        pDevice->SetMaterial(&pMatrix[nCounter].MatD3D);

        //テクスチャの設定
        pDevice->SetTexture(0, Texture);

        //描画
        Mesh->DrawSubset(nCounter);
    }

    //マテリアルをデフォルトに戻す
    pDevice->SetMaterial(&matDef);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：フェアリーの初期化
//
//引数：(LPCTSTR)モデル名,(tstirng)タグ,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT FAIRY::Initialize(LPCTSTR modelfile, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
	//初期設定
	Position = D3DXVECTOR3(0.0F, 20.0F, 0.0F);
	Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
	Move = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Tag = tag;
    Collection = false;
    ToTargetAngle = 0.0F;
    ElementPosition = Position;
    State = STATE_CHASE;

    //Xファイルの読み込み
    hResult = D3DXLoadMeshFromX(TEXT("Data/Common/Model/Character/car001.x"), D3DXMESH_SYSTEMMEM, GetDevice(), nullptr, &MaterialBuffer, nullptr, &MaterialValue, &Mesh);
    if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("フェアリーのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
		return hResult;
	}

    //---当たり判定の付与---//
    //Collision = COLLISIONMANAGER::InstantiateToOBB(D3DXVECTOR3(Position.x + 5.0F, Position.y + 5.0F, Position.z + 5.0F), D3DXVECTOR3(5.0F, 5.0F, 5.0F), TEXT("Character"), this);

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
    if (opponent->Owner->GetTag().find(TEXT("Player")) != tstring::npos)
    {

    }
    else if (opponent->Owner->GetTag().find(TEXT("Element")) != tstring::npos)
    {
        Collection = true;
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
        destination = Position;
        return false;
    }
    else
    {
        for (auto& data : Element)
        {
            //自身との距離の算出
            vecDistance = data->GetPosition() - Position;
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
    SAFE_RELEASE(Texture);
    SAFE_RELEASE(Mesh);
    SAFE_RELEASE(MaterialBuffer);
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

    //---初期化処理---//
	Rotation = PLAYER::GetPlayerRotation(); 
	int num = 0;

    static int cnt;

    if (++cnt > 120)
    {
        cnt = 0;
    }

    //ボタンを押したら思考状態へ移行
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        State = STATE_SYNTHIESIS;
    }

    if (State == STATE_SYNTHIESIS)
    {
        return;
    }

	//ボタンを押したらアイテムを取りに行く
	if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P,XINPUT_GAMEPAD_X, TRIGGER))
	{
        Collection = SearchElement(ElementPosition);
	}

    if (Collection)
    {
        //妖精とエレメントの距離の算出
        vecFairyDistance.x = ElementPosition.x - Position.x;
        vecFairyDistance.y = ElementPosition.y - Position.y;
        Rotation.y = 90.0F * ((ElementPosition.x > Position.x) - (ElementPosition.x < Position.x));
    }
    else
    {
        //妖精とプレイヤーの距離の算出
        vecFairyDistance.x = PLAYER::GetPlayerPosition().x - Position.x;
        vecFairyDistance.y = PLAYER::GetPlayerPosition().y + 20.0F - Position.y;
        Rotation.y = 90.0F * ((PLAYER::GetPlayerPosition().x > Position.x) - (PLAYER::GetPlayerPosition().x < Position.x));
    }

	//弾の発射角度取得し移動量設定
    if (vecFairyDistance.x <= 0.1F && vecFairyDistance.y <= 0.1F)
    {
        vecFairyDistance.x += 0.00001F; //atan2エラー防止
    }
        
    ToTargetAngle = atan2f(vecFairyDistance.y, vecFairyDistance.x);

	//移動量格納
	Move.x = cosf(ToTargetAngle) * VALUE_MOVE_FAIRY;
    Move.y = sinf(ToTargetAngle) * VALUE_MOVE_FAIRY + (sinf(-D3DX_PI * 0.5F + D3DX_PI / 60.0F * cnt) + 1.0F) * 0.5F;
    if (Rotation.y == SIDEVIEWCAMERA::GetRotation().y - D3DX_PI * 0.5F && Position.x > PLAYER::GetPlayerPosition().x - 20.0F && Position.x < PLAYER::GetPlayerPosition().x + 20.0F)
    {
        Move.x = 0.0F;
    }
    else if (Rotation.y == SIDEVIEWCAMERA::GetRotation().y + D3DX_PI * 0.5F && Position.x < PLAYER::GetPlayerPosition().x + 20.0F &&  Position.x > PLAYER::GetPlayerPosition().x - 20.0F)
    {
        Move.x = 0.0F;
    }

    //移動
    Position += Move;

    //プレイヤーとの当たり判定
		//if (CollisionBall(&Position, &playerPos, 15.0F, 15.0F))
		//{
  //          //右向き
		//	if (Rotation.y == rotCamera.y - D3DX_PI * 0.5F)
		//	{
  //              if (Position.x > playerPos.x - 15.0F)
  //              {
  //                  Move.x = -(VALUE_MOVE_FAIRY) / 3.0F;
  //              }
  //              else
  //              {
  //                  Move.x = 0.0F;
  //              }
		//	}
		//	else if (Rotation.y == rotCamera.y + D3DX_PI * 0.5F)
		//	{
  //              if (Position.x < playerPos.x + 15.0F)
  //              {
  //                  Move.x = VALUE_MOVE_FAIRY / 3.0F;
  //              }
  //              else
  //              {
  //                  Move.x = 0.0F;
  //              }
  //          }
		//	return;
		//}
	//else //(アイテムを取りに行っている)
	//{
	//	for (int i = 0; i < MAX_ITEM; i++)
	//	{
	//		if (Item[i].GetStat() == 1)
	//		{
	//			num = -1;
	//			if (CollisionBall(&Position, Item[i].GetPos(), 100.0f, 10.0f))
	//			{
	//				Item[i].SetItemDistance(&(Position - *Item[i].GetPos()));
	//				m_itemDistance = Item[i].GetItemDistance();
	//				if (m_itemDistance->x < 0)
	//				{
	//					m_itemDistance->x *= -1;
	//				}
	//				if (m_itemDistance->x < Item[m_num].GetItemDistance()->x)
	//				{
	//					m_num = i;
	//				}
	//			}
	//			else
	//			{
	//				m_stat = false;
	//				return;
	//			}
	//			if (!Item[m_num].GetStat())
	//			{
	//				m_num = i;
	//			}
	//			m_itemPos = Item[m_num].GetPos();
	//			TakeUpItem(m_itemPos);
 //               Position += Move;
	//		}
	//		else if (Check())
	//		{
	//			m_stat = false;
	//		}
	//	}
	//}
}

void FAIRY::TakeUpItem(LPD3DXVECTOR3 pos)
{
	//目標までの距離
	D3DXVECTOR3 Distance;
    Distance = *pos - Position;

	//弾の発射角度取得し移動量設定
	if (Distance.x == 0 && Distance.y == 0) Distance.x += 0.00001F; //atan2エラー防止
    ToTargetAngle = atan2f(Distance.y, Distance.x);

	//移動量格納
	Move = D3DXVECTOR3(cosf(ToTargetAngle) * VALUE_MOVE_FAIRY, sinf(ToTargetAngle) * VALUE_MOVE_FAIRY, 0.0F);

	//アイテムとの当たり判定
	//if (CollisionBall(&Position, pos, 10.0F, 10.0F))
	//{
	//	Move.x = 0.0f;
	//	m_stat = false;
	//	//Item[m_num].SetStat(0);
	//}
}

D3DXVECTOR3 FAIRY::GetPos(void)
{
	return Position;
}