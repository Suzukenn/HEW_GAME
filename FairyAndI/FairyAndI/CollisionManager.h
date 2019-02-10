#ifndef _COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include <list>
#include <unordered_map>
#include <vector>
#include "Main.h"

//�������O���錾������//
class COLLISION;
class GAMEOBJECT;
class OBB;
class SPHERE;

//�������񋓌^��`������//
typedef enum
{
    COLLISIONTYPE_OBB,
    COLLISIONTYPE_SPHERE,
    COLLISIONTYPE_MAX
} COLLISIONTYPE;

//�������N���X�錾������//
class COLLISIONMANAGER
{
    private:
        static std::list<COLLISION*> Collision;
        static std::list<COLLISION*> DestroyCollision;
        static std::vector<COLLISION*> HitList;
        static std::vector<COLLISION*> HitOpponent;
        static std::unordered_map<tstring, std::unordered_map<tstring, bool>> CollsitionLayer;

    public:
        static void Destroy(COLLISION*);
        static HRESULT Initialize(void);
        static void Uninitialize(void);
        static void Update(void);

        static OBB* InstantiateToOBB(D3DXVECTOR3, D3DXVECTOR3, tstring, GAMEOBJECT*);
        static SPHERE* InstantiateToSphere(D3DXVECTOR3, float, tstring, GAMEOBJECT*);
};

#endif