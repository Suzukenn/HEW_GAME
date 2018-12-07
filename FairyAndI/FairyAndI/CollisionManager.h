#ifndef _COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include <list>
#include <vector>
#include "Main.h"

//�������O���錾������//
class COLLISION;
class GAMEOBJECT;

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
        static std::list<COLLISION*> HitList;

    public:
        static HRESULT Initialize(void);
        static void Uninitialize(void);
        static void Update(void);

        static COLLISION* InstantiateToOBB(D3DXVECTOR3, D3DXVECTOR3, tstring, tstring, GAMEOBJECT*);
        static COLLISION* InstantiateToSphere(D3DXVECTOR3, float, tstring, tstring, GAMEOBJECT*);
};

#endif