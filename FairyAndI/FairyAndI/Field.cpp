//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Field.h"
#include "InputManager.h"

//�������萔�E�}�N����`������//
#define	TEXTURE_FILENAME	"data/TEXTURE/field000.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
//#define	VALUE_MOVE_FIELD	(5.0f)							// �ړ����x
//#define	VALUE_ROTATE_FIELD	(D3DX_PI * 0.001f)				// ��]���x

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�n�`�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void FIELD::Draw(void)
{
    //---�e��錾---//
    LPDIRECT3DDEVICE9 pDevice;
    D3DXMATRIX mtxRotation;
    D3DXMATRIX mtxTranslate;
    D3DXMATRIX mtxWorld;

    //---����������---//
    pDevice = GetDevice();

    //���[���h�}�g���b�N�X�̐ݒ�---//
    //���[���h�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&mtxWorld);

    //��]�𔽉f
    D3DXMatrixRotationYawPitchRoll(&mtxRotation, Rotation.y, Rotation.x, Rotation.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRotation);

    //�ړ��𔽉f
    D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

    //���[���h�}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

    //���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
    pDevice->SetStreamSource(0, *VertexBuffer, 0, sizeof(VERTEX_3D));

    //���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_3D);

    //�C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
    pDevice->SetIndices(*IndexBuffer);

    //�e�N�X�`���̐ݒ�
    pDevice->SetTexture(0, *Texture);

    //�|���S���̕`��
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VertexValue, 0, PolygonValue);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�n�`�̏�����
//
//�����F(LPTSTR)�摜�̃t�@�C����, 
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT FIELD::Initialize(const LPCTSTR& filepath, const int& valueX, const int& valueZ, const float& sizeX, const float& sizeZ)
{
    //---�e��錾---//
    LPDIRECT3DDEVICE9 pDevice;
    HRESULT hResult;

    //---����������---//
    Position = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    pDevice = GetDevice();
    Texture.reset(new LPDIRECT3DTEXTURE9());

    //---�e�N�X�`���̓ǂݍ���---//
    hResult = D3DXCreateTextureFromFile(pDevice, filepath, Texture.get());
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�n�`�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���"), filepath, MB_OK);
        Uninitialize();
        return hResult;
    }

    //---���_���̍쐬---//
    hResult = MakeVertex(pDevice, valueX, valueZ, sizeX, sizeZ);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�n�`�̒��_���̍쐬�Ɏ��s���܂���"), filepath, MB_OK);
        Uninitialize();
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�n�`�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void FIELD::Uninitialize(void)
{
    //---�J��---//
    SAFE_RELEASE((*VertexBuffer));
    SAFE_RELEASE((*IndexBuffer));
    SAFE_RELEASE((*Texture));
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�n�`�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void FIELD::Update(void)
{

}


/////////////////////////////////////////////
//�֐����FMakeVertex
//
//�@�\�F�n�`�̒��_�f�[�^�̍쐬
//
//�����F(LPDIRECT3DDEVICE9 device, int valueX, int valueZ, float sizeX, float sizeZ
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
HRESULT FIELD::MakeVertex(LPDIRECT3DDEVICE9 device, int valueX, int valueZ, float sizeX, float sizeZ)
{
    //---�e��錾---//
    int nCounterX;
    int nCounterZ;
    int nIndexNumber;
    int nIndexValue;
    int nVertexNumber;
    HRESULT hResult;

    VERTEX_3D *pVertex;
    WORD *pIndex;

    //---����������---//
    IndexBuffer.reset(new LPDIRECT3DINDEXBUFFER9());
    VertexBuffer.reset(new LPDIRECT3DVERTEXBUFFER9());

    //---�e��Z�o---//
    VertexValue = (valueX + 1) * (valueZ + 1);                          //���_��(�C���f�b�N�X�L�Ȃ�)
    nIndexValue = (valueX + 1) * (valueZ << 1) + ((valueZ - 1) << 1);   //�C���f�b�N�X��(�k�ރ|���S�����l��)
    PolygonValue = valueX * (valueZ << 1) + ((valueZ - 1) << 2);        //�|���S����(�k�ރ|���S�����l��)

    //---�o�b�t�@�̐���---//
    //���_�o�b�t�@
    hResult = device->CreateVertexBuffer(sizeof(VERTEX_3D) * VertexValue, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, VertexBuffer.get(), nullptr);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�n�`�̒��_�o�b�t�@�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    //�C���f�b�N�X�o�b�t�@
    hResult = device->CreateIndexBuffer(sizeof(WORD) * nIndexValue, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, IndexBuffer.get(), nullptr);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�n�`�̃C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    //---���_�o�b�t�@�̒��g�𖄂߂�---//
    //�o�b�t�@�̃|�C���^���擾
    hResult = (*VertexBuffer)->Lock(0, 0, (void**)&pVertex, 0);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�n�`�̒��_�o�b�t�@�̃|�C���^�̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    //�l�̐ݒ�
    for (nCounterZ = 0; nCounterZ < (valueZ + 1); nCounterZ++)
    {
        for (nCounterX = 0; nCounterX < (valueX + 1); nCounterX++)
        {
            nVertexNumber = nCounterZ * (valueX + 1) + nCounterX;
            pVertex[nVertexNumber].Vertex.x = -(valueX >> 1) * sizeX + nCounterX * sizeX;
            pVertex[nVertexNumber].Vertex.y = 0.0F;
            pVertex[nVertexNumber].Vertex.z = (valueX >> 1) * sizeZ - nCounterZ * sizeZ;
            pVertex[nVertexNumber].Normal = D3DXVECTOR3(0.0F, 1.0F, 0.0F);
            pVertex[nVertexNumber].Diffuse = D3DXCOLOR(1.0F, 1.0F, 1.0F, 1.0F);
            pVertex[nVertexNumber].Texture.x = 1.0F * nCounterX;
            pVertex[nVertexNumber].Texture.y = 1.0F * nCounterZ;
        }
    }

    //�o�b�t�@�̃|�C���^�̊J��
    hResult = (*VertexBuffer)->Unlock();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�n�`�̒��_�o�b�t�@�̃|�C���^�̊J���Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    //---�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�---//
    //�o�b�t�@�̃|�C���^���擾
    hResult = (*IndexBuffer)->Lock(0, 0, (void**)&pIndex, 0);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�n�`�̃C���f�b�N�X�o�b�t�@�̃|�C���^�̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    nIndexNumber = 0;
    for (nCounterZ = 0; nCounterZ < valueZ; nCounterZ++)
    {
        //�k�ރ|���S���̏d����ݒ�
        if (nCounterZ > 0)
        {
            pIndex[nIndexNumber] = (nCounterZ + 1) * (valueX + 1);
            nIndexNumber++;
        }
        for (int nCounterX = 0; nCounterX < (valueX + 1); nCounterX++)
        {
            pIndex[nIndexNumber] = (nCounterZ + 1) * (valueX + 1) + nCounterX;
            nIndexNumber++;
            pIndex[nIndexNumber] = nCounterZ * (valueX + 1) + nCounterX;
            nIndexNumber++;
        }

        //�k�ރ|���S���̂��߂̏d����ݒ�
        if (nCounterZ < valueZ - 1)
        {
            pIndex[nIndexNumber] = nCounterZ * (valueX + 1) + valueX;
            nIndexNumber++;
        }
    }

    //�o�b�t�@�̃|�C���^�̊J��
    hResult = (*IndexBuffer)->Unlock();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�n�`�̃C���f�b�N�X�o�b�t�@�̃|�C���^�̊J���Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    return hResult;
}