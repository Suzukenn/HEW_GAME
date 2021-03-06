#ifndef _FAIRY_H_
#define _FAIRY_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "AnimationModel.h"
#include "GameObject.h"
#include "Main.h"

//�������萔�E�}�N����`������//
#define	VALUE_MOVE_FAIRY 1.1F   // �ړ����x

//�������񋓌^��`������//
typedef enum
{
    STATE_WAIT,
    STATE_MOVE,
    STATE_THINK,
    STATE_MAX
} STATE;

//�������O���錾������//
class SPHERE;

//�������N���X�錾������//
class FAIRY final : public GAMEOBJECT
{
	private:
        D3DXVECTOR3	Move;	        //�ړ���
        D3DXVECTOR3	ElementPosition;//����G�������g�̈ʒu
		bool Collection;	        //������
        STATE State;
		float ToTargetAngle;
        std::shared_ptr<ANIMATIONMODEL> Model;

        std::vector<GAMEOBJECT*> Element;
        SPHERE* Collision;

        bool SearchElement(D3DXVECTOR3&);

	public:
        FAIRY(D3DXVECTOR3, D3DXVECTOR3);

		HRESULT Initialize(D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void OnCollision(COLLISION*);

		static D3DXVECTOR3 GetFairyPosition(void);
};

#endif