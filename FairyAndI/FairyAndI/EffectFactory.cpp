////�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "Effect.h"
#include "EffectFactory.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FInstantiateBatteryGimmick
//
//�@�\�F�C��̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)�傫��
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void EFFECTFACTORY::InstantiateSkillEffect(D3DXVECTOR3 position, D3DXVECTOR2 scale, bool inverted)
{
    //---����---//
    ACTORMANAGER::GameObject.emplace_back(new EFFECT(TEXT("SKILLEFFECT"), position, scale, inverted, {4, 4}));
}