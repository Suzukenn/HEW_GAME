#ifndef _FAIRY_H_
#define _FAIRY_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "Base3Dobject.h"
#include "Main.h"
#include "Item.h"
#include "Model.h"

#define	VALUE_MOVE_FAIRY	(2.0F)					// �ړ����x

class FAIRY final : private BASE3DOBJECT 
{
	private:
        LPDIRECT3DTEXTURE9 Texture;	//�e�N�X�`���ւ̃|�C���^
        LPD3DXMESH Mesh;		    //���b�V�����ւ̃|�C���^
        LPD3DXBUFFER MaterialBuffer;//�}�e���A�����ւ̃|�C���^
        DWORD MaterialValue;	    //�}�e���A�����̐�
        D3DXVECTOR3			Move;	// �ړ�
		bool				m_stat;	// ���
		int					m_shadow;
		float				m_tar;
		ITEM*				Item;
		int					m_num;		//�A�C�e���̓Y�����p
		LPD3DXVECTOR3		m_itemPos;
		LPD3DXVECTOR3		m_itemDistance;

	public:
		HRESULT Initialize(void);
		void Uninitialize(void);
		void Update(D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, ITEM*);
		void Draw(void);

		void TakeUpItem(LPD3DXVECTOR3);
		D3DXVECTOR3 GetPos(void);
		bool Check(void);
};
#endif