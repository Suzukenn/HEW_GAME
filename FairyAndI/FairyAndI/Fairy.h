#ifndef _FAIRY_H_
#define _FAIRY_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Item.h"
#include "Model.h"

#define	VALUE_MOVE_FAIRY	(2.0F)					// �ړ����x

class FAIRY final : public GAMEOBJECT
{
	private:
        LPDIRECT3DTEXTURE9 Texture;	//�e�N�X�`���ւ̃|�C���^
        LPD3DXMESH Mesh;		    //���b�V�����ւ̃|�C���^
        LPD3DXBUFFER MaterialBuffer;//�}�e���A�����ւ̃|�C���^
        DWORD MaterialValue;	    //�}�e���A�����̐�

        D3DXVECTOR3			Move;	// �ړ�
		bool				Collection;	//������
		float				ToTargetAngle;
		int					m_num;		//�A�C�e���̓Y�����p

		D3DXVECTOR3	ElementPosition;

        std::vector<GAMEOBJECT*> Element;

        OBB* Collision;

        D3DXVECTOR3 SearchElement(void);

	public:
        FAIRY(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);

		HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void OnCollision(COLLISION*);

		void TakeUpItem(LPD3DXVECTOR3);
		D3DXVECTOR3 GetPos(void);
};

#endif