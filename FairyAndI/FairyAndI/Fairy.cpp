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
    D3DXMATRIX mtxWorld;
    LPD3DXMATERIAL pMatrix;
    D3DMATERIAL9 matDef;

    //---初期化処理---//
    pDevice = GetDevice();

    //---ワールドマトリクスの設定---//
    //初期化
    D3DXMatrixIdentity(&mtxWorld);

    //設定
    Transform.MakeWorldMatrix(mtxWorld);

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
	Transform.Position = D3DXVECTOR3(0.0F, 20.0F, 0.0F);
    Transform.Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
	Move = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Tag = tag;
    Collection = false;
    ToTargetAngle = 0.0F;
    ElementPosition = Transform.Position;
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
    Collision = COLLISIONMANAGER::InstantiateToSphere(D3DXVECTOR3(Transform.Position.x + 0.0F, Transform.Position.y + 10.0F, Transform.Position.z + 0.0F), 5.0F, TEXT("Character"), this);

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
    if (opponent->Owner->GetTag() == TEXT("Player"))
    {
        //右向き
        if (Transform.Rotation.y == SIDEVIEWCAMERA::GetRotation().y - D3DX_PI * 0.5F)
        {
            if (Transform.Position.x > PLAYER::GetPlayerPosition().x - 15.0F)
            {
                Move.x = -(VALUE_MOVE_FAIRY) / 3.0F;
            }
            else
            {
                Move.x = 0.0F;
                Move.z = 0.0F;
            }
        }
        //左向き
        else if (Transform.Rotation.y == SIDEVIEWCAMERA::GetRotation().y + D3DX_PI * 0.5F)
        {
            if (Transform.Position.x < PLAYER::GetPlayerPosition().x + 15.0F)
            {
                Move.x = VALUE_MOVE_FAIRY / 3.0F;
            }
            else
            {
                Move.x = 0.0F;
                Move.z = 0.0F;
            }
        }
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
    Transform.Rotation = PLAYER::GetPlayerRotation();
	int num = 0;

    static int cnt;

    if (++cnt > 120)
    {
        cnt = 0;
    }

    //移動
    Transform.Position += Move;
    Collision->Position = Transform.Position;


    //ボタンを押したら思考状態へ移行
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        if (State == STATE_SYNTHIESIS)
        {
            State = STATE_CHASE;
        }
        else
        {
            State = STATE_SYNTHIESIS;
        }
    }

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

	//弾の発射角度取得し移動量設定
    if (vecFairyDistance.x <= 0.1F && vecFairyDistance.y <= 0.1F)
    {
        vecFairyDistance.x += 0.00001F; //atan2エラー防止
    }
        
    ToTargetAngle = atan2f(vecFairyDistance.y, vecFairyDistance.x);

	//移動量格納
	Move.x = cosf(ToTargetAngle) * VALUE_MOVE_FAIRY;
    Move.y = sinf(ToTargetAngle) * VALUE_MOVE_FAIRY + (sinf(-D3DX_PI * 0.5F + D3DX_PI / 60.0F * cnt) + 1.0F) * 0.5F;
    if (Transform.Rotation.y == SIDEVIEWCAMERA::GetRotation().y - D3DX_PI * 0.5F && Transform.Position.x > PLAYER::GetPlayerPosition().x - 20.0F && Transform.Position.x < PLAYER::GetPlayerPosition().x + 20.0F)
    {
        Move.x = 0.0F;
    }
    else if (Transform.Rotation.y == SIDEVIEWCAMERA::GetRotation().y + D3DX_PI * 0.5F && Transform.Position.x < PLAYER::GetPlayerPosition().x + 20.0F && Transform.Position.x > PLAYER::GetPlayerPosition().x - 20.0F)
    {
        Move.x = 0.0F;
    }

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
}

D3DXVECTOR3 FAIRY::GetPos(void)
{
	return Transform.Position;
}