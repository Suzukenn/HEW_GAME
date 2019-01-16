//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <list>
#include <vector>
#include "Collision.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Main.h"
#include "OBB.h"
#include "Sphere.h"

//�������O���[�o���ϐ�������//
std::list<COLLISION*> COLLISIONMANAGER::Collision;
std::list<COLLISION*> COLLISIONMANAGER::DestroyCollision;
std::vector<COLLISION*> COLLISIONMANAGER::HitList;
std::vector<COLLISION*> COLLISIONMANAGER::HitOpponent;
std::unordered_map<tstring, std::unordered_map<tstring, bool>> COLLISIONMANAGER::CollsitionLayer;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDestroy
//
//�@�\�F�R���W�����̍폜
//
//�����F(COLLISION*)�폜�R���W����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void COLLISIONMANAGER::Destroy(COLLISION* collision)
{
    //---�p�����X�g�֓o�^---//
    DestroyCollision.emplace_back(collision);
}

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

    std::unordered_map<tstring, bool>conWork;

    //---����������---//
    Collision.clear();
    DestroyCollision.clear();
    HitList.clear();
    HitOpponent.clear();
    hResult = S_OK;

    //---�Փ˃��C���[�̐ݒ�---//
    conWork.emplace(TEXT("Character"), true);
    conWork.emplace(TEXT("Skill"), true);
    conWork.emplace(TEXT("Field"), true);
    conWork.emplace(TEXT("Object"), true);
    CollsitionLayer.emplace(TEXT("Character"), conWork);

    conWork.clear();

    conWork.emplace(TEXT("Skill"), true);
    conWork.emplace(TEXT("Field"), true);
    conWork.emplace(TEXT("Object"), true);
    CollsitionLayer.emplace(TEXT("Skill"), conWork);

    conWork.clear();

    conWork.emplace(TEXT("Field"), true);
    conWork.emplace(TEXT("Object"), true);
    CollsitionLayer.emplace(TEXT("Field"), conWork);

    conWork.clear();

    conWork.emplace(TEXT("Object"), true);
    CollsitionLayer.emplace(TEXT("Object"), conWork);

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
OBB* COLLISIONMANAGER::InstantiateToOBB(D3DXVECTOR3 position, D3DXVECTOR3 axislength, tstring layer, GAMEOBJECT* owner)
{
    Collision.emplace_back(new OBB(position, axislength, layer, owner));
    return dynamic_cast<OBB*>(Collision.back());
}

/////////////////////////////////////////////
//�֐����FInstantiateToSphere
//
//�@�\�F���R���W�����̓o�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
SPHERE* COLLISIONMANAGER::InstantiateToSphere(D3DXVECTOR3 position, float radius, tstring layer, GAMEOBJECT* owner)
{
    Collision.emplace_back(new SPHERE(position, radius, layer, owner));
    return dynamic_cast<SPHERE*>(Collision.back());
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
    DestroyCollision.clear();
    HitList.clear();
    HitOpponent.clear();
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
    //---�e��錾---//
    int nCounter;
    bool bCheck;
    bool bDestroy;
    bool bHit;

    OBB* pObb;
    SPHERE* pSphere;

    std::list<COLLISION*>::iterator itrCollision;

    //---����������---//
    bDestroy = false;
    itrCollision = Collision.begin();

    //---�Փ˔���---//
    for (auto& itrBase = Collision.begin(); itrBase != Collision.end(); ++itrBase)
    {
        for (auto& itrOpponent = std::next(itrBase) ; itrOpponent != Collision.end(); ++itrOpponent)
        {
            //�Փ˃��C���[����
            try
            {
                bCheck = CollsitionLayer.at((*itrBase)->Layer).at((*itrOpponent)->Layer);
            }
            catch(std::out_of_range&)
            {
                bCheck = CollsitionLayer.at((*itrOpponent)->Layer).at((*itrBase)->Layer);
            }
            if (!bCheck)
            {
                continue;
            }

            //OBB�Ŋm�F
            pObb = dynamic_cast<OBB*>(*itrOpponent);
            if (pObb)
            {
                bHit = (*itrBase)->CheckCollisionToOBB(pObb);
            }
            else
            {
                //���Ŋm�F
                pSphere = dynamic_cast<SPHERE*>(*itrOpponent);
                if (pSphere)
                {
                    bHit = (*itrBase)->CheckCollisionToSphere(pSphere);
                }
            }
            
            //�Փ˃��X�g�ɓo�^
            if (bHit)
            {
                HitList.emplace_back(*itrBase);
                HitOpponent.emplace_back(*itrOpponent);
                HitList.emplace_back(*itrOpponent);
                HitOpponent.emplace_back(*itrBase);
            }
        }
    }

    //---�����������̏����̎��s---//
    for (nCounter = 0; nCounter < HitList.size(); ++nCounter)
    {
        HitList.at(nCounter)->Owner->OnCollision(HitOpponent.at(nCounter));
    }

    //---�p���̎��s---//
    while (itrCollision != Collision.end())
    {
        for (auto& itrDestroy = DestroyCollision.begin(); itrDestroy != DestroyCollision.end(); ++itrDestroy)
        {
            //�p�����X�g�Əƍ�
            if (*itrCollision == *itrDestroy)
            {
                (*itrCollision)->Owner = nullptr;
                itrCollision = Collision.erase(itrCollision);
                DestroyCollision.remove(*itrDestroy);
                bDestroy = true;
                break;
            }
        }

        //�p�����Ȃ������Ƃ��̂݃C���N�������g
        if (bDestroy)
        {
            bDestroy = false;
        }
        else
        {
            ++itrCollision;
        }
    }

    //---���X�g�̃N���A---//
    DestroyCollision.clear();
    HitList.clear();
    HitOpponent.clear();
}