//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <list>
#include "Collision.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Main.h"
#include "OBB.h"
#include "Sphere.h"

//�������O���[�o���ϐ�������//
std::list<COLLISION*> COLLISIONMANAGER::Collision;
std::list<COLLISION*> COLLISIONMANAGER::HitList;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�}�l�[�W���[�̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT COLLISIONMANAGER::Initialize(void)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    Collision.clear();
    HitList.clear();
    hResult = S_OK;

    return hResult;
}

/////////////////////////////////////////////
//�֐����FInstantiateToOBB
//
//�@�\�FOBB�R���W�����̓o�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
COLLISION* COLLISIONMANAGER::InstantiateToOBB(D3DXVECTOR3 position, D3DXVECTOR3 rotation, tstring tag, tstring layer, GAMEOBJECT* owner)
{
    Collision.emplace_back(new OBB(position, rotation, tag, layer, owner));
    return Collision.back();
}

/////////////////////////////////////////////
//�֐����FInstantiate
//
//�@�\�F�}�l�[�W���[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
COLLISION* COLLISIONMANAGER::InstantiateToSphere(D3DXVECTOR3 position, float radius, tstring tag, tstring layer, GAMEOBJECT* owner)
{
    Collision.emplace_back(new SPHERE(position, radius, tag, layer, owner));
    return Collision.back();
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�}�l�[�W���[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void COLLISIONMANAGER::Uninitialize(void)
{
    //---���---//
    Collision.clear();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�}�l�[�W���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void COLLISIONMANAGER::Update(void)
{
    //---�����蔻��̏���---//
    for (auto& itrBase = Collision.begin(); itrBase != Collision.end(); ++itrBase)
    {
        for (auto& itrOpponent = std::next(itrBase) ; itrOpponent != Collision.end(); ++itrOpponent)
        {
            //if ((*itrBase)->CheckCollision(nullptr))
            //{
            //    HitList.emplace_back(itrBase);
            //    HitList.emplace_back(itrOpponent);
            //}
        }
    }

    //---�����������̏����̎��s---//
    for (auto& data : HitList)
    {
        data->Owner->OnCollision(nullptr);
    }
}