////wb_t@CΗέέ//
#include "ActorManager.h"
#include "Effect.h"
#include "EffectFactory.h"

//Φθ`//
/////////////////////////////////////////////
//ΦΌFInstantiateBatteryGimmick
//
//@\FCδΜΆ¬
//
//ψF(D3DXVECTOR3)Κu,(D3DXVECTOR3)ε«³
//
//ίθlFΘ΅
/////////////////////////////////////////////
void EFFECTFACTORY::InstantiateSkillEffect(D3DXVECTOR3 position, D3DXVECTOR2 scale, bool inverted)
{
    //---Ά¬---//
    ACTORMANAGER::GameObject.emplace_back(new EFFECT(TEXT("SKILLEFFECT"), position, scale, inverted, {4, 4}));
}