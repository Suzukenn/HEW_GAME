////＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Effect.h"
#include "EffectFactory.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：InstantiateBatteryGimmick
//
//機能：砲台の生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)大きさ
//
//戻り値：なし
/////////////////////////////////////////////
void EFFECTFACTORY::InstantiateSkillEffect(D3DXVECTOR3 position, D3DXVECTOR2 scale, bool inverted)
{
    //---生成---//
    ACTORMANAGER::GameObject.emplace_back(new EFFECT(TEXT("SKILLEFFECT"), position, scale, inverted, {4, 4}));
}