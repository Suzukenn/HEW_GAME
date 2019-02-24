//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BackGround.h"
#include "TextureManager.h"
#include "SideViewCamera.h"

#define MAX_BILLBOARD 1

#define FLD_X_MIN			(-150.0f)
#define FLD_X_MAX			(150.0f)
#define FLD_Z_MIN			(-150.0f)
#define FLD_Z_MAX			(150.0f)

// �\���̒�`
typedef struct _TBillboard {
	int				stat;	// ���
	D3DXVECTOR3		pos;	// �ʒu
	D3DXVECTOR3		vel;	// ���x
} TBillboard;

// ---�v���g�^�C�v�錾---
HRESULT MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);

//---�O���[�o���ϐ�---
D3DXMATRIX          g_matrix;   //  ���[���h�s��     
LPD3DXSPRITE        pSprite;    //  �X�v���C�g�Ǘ��ϐ�      
LPDIRECT3DTEXTURE9  tex;        //  �e�N�X�`�����[�h�ϐ�  
static LPDIRECT3DTEXTURE9 g_pD3DTextureBillboard;		// �e�N�X�`���ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBillboard;	// ���_�o�b�t�@�ւ̃|�C���^

static D3DXMATRIX g_mtxWorldBillboard;			// ���[���h�}�g���b�N�X
static TBillboard g_billboard[MAX_BILLBOARD];	// �r���{�[�h���

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�w�i�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BACKGROUND::Draw(void)
{
    BILLBOARD::Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�w�i�̏�����
//
//�����F(LPCTSTR)�e�N�X�`����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT BACKGROUND::Initialize(LPCTSTR texturename, D3DXVECTOR3 position, D3DXVECTOR3 size)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    hResult = BILLBOARD::Initialize(texturename, position, size);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�w�i�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BACKGROUND::Uninitialize(void)
{
\

	if (g_pD3DTextureBillboard)
	{// �e�N�X�`���̊J��
		g_pD3DTextureBillboard->Release();
		g_pD3DTextureBillboard = NULL;
	}
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�w�i�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BACKGROUND::Update(void)
{

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice)
{
	int g_nNumBlockX, g_nNumBlockZ, g_nNumVertex, g_nNumPolygon;
	float g_fSizeBlockX, g_fSizeBlockZ;
	// �u���b�N��
	g_nNumBlockX = 1;
	g_nNumBlockZ = 1;

	// ���_��
	g_nNumVertex = 4;

	// �|���S����
	g_nNumPolygon = 2;

	// �u���b�N�T�C�Y
	g_fSizeBlockX = 200.0f;
	g_fSizeBlockZ = 200.0f;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nNumVertex,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffBillboard,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;
		const float fSizeTexX = 1.0f;
		const float fSizeTexZ = 1.0f;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntVtxY = 0; nCntVtxY < g_nNumBlockZ; nCntVtxY++)
		{
			for (int nCntVtxX = 0; nCntVtxX < (g_nNumBlockX + 1); nCntVtxX++, pVtx += 2)
			{
				// ���_���W�̐ݒ�
				pVtx[0].Vertex.x = -(g_nNumBlockX / 2.0f) * g_fSizeBlockX + nCntVtxX * g_fSizeBlockX;
				pVtx[0].Vertex.y = (g_nNumBlockZ / 2.0f) * g_fSizeBlockZ - (nCntVtxY + 1) * g_fSizeBlockZ;
				pVtx[0].Vertex.z = 0.0f;
				pVtx[1].Vertex.x = -(g_nNumBlockX / 2.0f) * g_fSizeBlockX + nCntVtxX * g_fSizeBlockX;
				pVtx[1].Vertex.y = (g_nNumBlockZ / 2.0f) * g_fSizeBlockZ - nCntVtxY * g_fSizeBlockZ;
				pVtx[1].Vertex.z = 0.0f;

				// �@���̐ݒ�
				pVtx[0].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				pVtx[1].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

				// ���ˌ��̐ݒ�
				pVtx[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].Texture.x = fSizeTexX * nCntVtxX;
				pVtx[0].Texture.y = fSizeTexZ * (nCntVtxY + 1);
				pVtx[1].Texture.x = fSizeTexX * nCntVtxX;
				pVtx[1].Texture.y = fSizeTexZ * nCntVtxY;
			}
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBillboard->Unlock();
	}

	return S_OK;
}

// �r���{�[�h����
int  BACKGROUND::CreateBillboard(LPD3DXVECTOR3 pos, LPD3DXVECTOR3 vel)
{
	int nBillboard = -1;

	for (int i = 0; i < MAX_BILLBOARD; ++i) {
		if (g_billboard[i].stat) continue;
		g_billboard[i].pos = *pos;
		g_billboard[i].vel = *vel;
		g_billboard[i].stat = 1;
		return i;
	}
	return nBillboard;
}

// �r���{�[�h�j��
void  BACKGROUND::ReleaseBillboard(int nBillboard)
{
	if (nBillboard < 0 || nBillboard >= MAX_BILLBOARD)
		return;
	g_billboard[nBillboard].stat = 0;
}

