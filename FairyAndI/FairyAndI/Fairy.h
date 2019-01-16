#ifndef _FAIRY_H_
#define _FAIRY_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"

//�������萔�E�}�N����`������//
#define	VALUE_MOVE_FAIRY 2.0F   // �ړ����x

//�������񋓌^��`������//
typedef enum
{
    STATE_CHASE,
    STATE_SYNTHIESIS,
    STATE_MAX
} STATE;

//�������O���錾������//
class SPHERE;

//�������N���X�錾������//
class FAIRY final : public GAMEOBJECT
{
	private:
        LPDIRECT3DTEXTURE9 Texture;	//�e�N�X�`���ւ̃|�C���^
        LPD3DXMESH Mesh;		    //���b�V�����ւ̃|�C���^
        LPD3DXBUFFER MaterialBuffer;//�}�e���A�����ւ̃|�C���^
        DWORD MaterialValue;	    //�}�e���A�����̐�
        D3DXVECTOR3	Move;	        //�ړ���
        D3DXVECTOR3	ElementPosition;//����G�������g�̈ʒu
		bool Collection;	        //������
        STATE State;
		float ToTargetAngle;

        std::vector<GAMEOBJECT*> Element;

        SPHERE* Collision;

        bool SearchElement(D3DXVECTOR3&);

	public:
        FAIRY(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);

		HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void OnCollision(COLLISION*);

		D3DXVECTOR3 GetPos(void);
};

#endif