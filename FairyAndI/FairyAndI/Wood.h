#ifndef _WOOD_H_
#define _WOOD_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Enemy.h"

//�������񋓌^��`������//
typedef enum
{
    WOODSTATE_WAIT,
    WOODSTATE_ATTACK,
    MAX_WOODSTATE
} WOODSTATE;

//�������N���X�錾������//
class WOOD final : public ENEMY
{
    private:
        WOODSTATE State;

    public:
        WOOD(D3DXVECTOR3, D3DXVECTOR3);
        ~WOOD(void);

        HRESULT Initialize(D3DXVECTOR3, D3DXVECTOR3);
        void Uninitialize(void);
        void Update(void);
        void Draw(void);

        void OnCollision(COLLISION*);
};

#endif