#ifndef _PLAYER_H_
#define _PLAYER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "Base3Dobject.h"
#include "Main.h"
#include "Model.h"

//---�萔�E�}�N����`---//
#define	VALUE_MOVE_PLAYER 5.0F

//�������N���X��`������//
class PLAYER final : private BASE3DOBJECT
{
	private:
        LPDIRECT3DTEXTURE9 Texture;	//�e�N�X�`���ւ̃|�C���^
        LPD3DXMESH Mesh;		    //���b�V�����ւ̃|�C���^
        LPD3DXBUFFER MaterialBuffer;//�}�e���A�����ւ̃|�C���^
        DWORD MaterialValue;	    //�}�e���A�����̐�

        D3DXVECTOR3 Move;

	public:
        void Draw(void);
		HRESULT Initialize(LPCTSTR);
		void Uninitialize(void);
		void Update(void);
		const D3DXVECTOR3 GetPlayerPosition(void);
		const LPD3DXVECTOR3 GetPlayerRotation(void);
};
#endif
