//wb_t@CΗέέ//
#include "ActorManager.h"
#include "CharacterFactory.h"
#include "Fairy.h"
#include "Player.h"

//OϋιΎ//

//Φθ`//
/////////////////////////////////////////////
//ΦΌFInstantiateFairy
//
//@\FvC[ΜΆ¬
//
//ψF(D3DXVECTOR3)Κu,(D3DXVECTOR3)ρ]
//
//ίθlFΘ΅
/////////////////////////////////////////////
void CHARACTERFACTORY::InstantiateFairy(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    ACTORMANAGER::GameObject.emplace_back(new FAIRY(TEXT("Data/Common/Model/Character/car001.x"), TEXT("Fairy"), position, rotation));
}

/////////////////////////////////////////////
//ΦΌFInstantiatePlayer
//
//@\FvC[ΜΆ¬
//
//ψF(D3DXVECTOR3)Κu,(D3DXVECTOR3)ρ]
//
//ίθlFΘ΅
/////////////////////////////////////////////
void CHARACTERFACTORY::InstantiatePlayer(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    ACTORMANAGER::GameObject.emplace_back(new PLAYER(TEXT("Data/Common/Model/Character/tiny_4anim.x"), TEXT("Player"), position, rotation));
}