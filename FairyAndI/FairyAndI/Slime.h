#ifndef _SLIME_H_
#define _SLIME_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Enemy.h"

//�������񋓌^��`������//
typedef enum
{
    SLIMESTATE_MOVE,
    SLIMESTATE_ATTACK,
    SLIMESTATE_RETURN,
    MAX_SLIMESTATE
} SLIMESTATE;

//�������N���X�錾������//
class SLIME final : public ENEMY
{
    private:
        D3DXVECTOR3 InitialPosition;
        D3DXVECTOR3 Move;
        SLIMESTATE State;

    public:
        SLIME(D3DXVECTOR3, D3DXVECTOR3);
        ~SLIME(void);

        HRESULT Initialize(D3DXVECTOR3, D3DXVECTOR3);
        void Uninitialize(void);
        void Update(void);
        void Draw(void);

        void OnCollision(COLLISION*);
};

#endif