//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Ground.h"
#include "Texture.h"
#include "TextureManager.h"

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
void GROUND::Draw(void)
{
    //---�e��錾---//
    D3DXMATRIX mtxRotation;
    D3DXMATRIX mtxTranslate;
    D3DXMATRIX mtxWorld;

    LPDIRECT3DDEVICE9 pDevice;
    std::shared_ptr<TEXTURE> pTexture;

    //---����������---//
    pDevice = GetDevice();
    D3DXMatrixIdentity(&mtxWorld);
    pTexture = Texture.lock();
    if (!pTexture)
    {
        MessageBox(nullptr, TEXT("�`��Ώۂ̃e�N�X�`�������݂��܂���"), TEXT("�`��G���["), MB_OK);
    }

    //���[���h�}�g���b�N�X�̐ݒ�---//
    //���[���h�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&mtxWorld);

    //�ݒ�
    Transform.MakeWorldMatrix(mtxWorld);
    GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);

    //---�`��---//
    //���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
    pDevice->SetStreamSource(0, *VertexBuffer, 0, sizeof(VERTEX_3D));

    //���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_3D);

    //�C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
    pDevice->SetIndices(*IndexBuffer);

    //�e�N�X�`���̐ݒ�
    pDevice->SetTexture(0, pTexture->Image);

    //�|���S���̕`��
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VertexValue, 0, PolygonValue);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�n�`�̏�����
//
//�����F(LPCTSTR)�e�N�X�`����,(const int&)X�|���S����,(const int&)Z�|���S����,(const float&)X�T�C�Y,(const float&)Z�T�C�Y
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT GROUND::Initialize(LPCTSTR texturename, const int& valueX, const int& valueZ, const float& sizeX, const float& sizeZ)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    Transform.Position = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Transform.Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);

    //---�e�N�X�`���̓ǂݍ���---//
    hResult = TEXTUREMANAGER::GetTexture(texturename, Texture);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�n�`�̃e�N�X�`���̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---���_���̍쐬---//
    hResult = MakeVertex(valueX, valueZ, sizeX, sizeZ);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�n�`�̒��_���̍쐬�Ɏ��s���܂���"), texturename, MB_OK);
        Uninitialize();
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FMakeVertex
//
//�@�\�F�n�`�̒��_�f�[�^�̍쐬
//
//�����F(int)X�|���S����,(int)Z�|���S����,(float)�T�C�YX,(float)�T�C�YZ
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT GROUND::MakeVertex(int valueX, int valueZ, float sizeX, float sizeZ)
{
    //---�e��錾---//
    int nCounterX;
    int nCounterZ;
    int nIndexNumber;
    int nIndexValue;
    int nVertexNumber;
    HRESULT hResult;

    LPDIRECT3DDEVICE9 pDevice;
    VERTEX_3D *pVertex;
    WORD *pIndex;

    //---����������---//
    pDevice = GetDevice();
    IndexBuffer.reset(new LPDIRECT3DINDEXBUFFER9);
    VertexBuffer.reset(new LPDIRECT3DVERTEXBUFFER9);

    //---�e��Z�o---//
    VertexValue = (valueX + 1) * (valueZ + 1);                          //���_��(�C���f�b�N�X�L�Ȃ�)
    nIndexValue = (valueX + 1) * (valueZ << 1) + ((valueZ - 1) << 1);   //�C���f�b�N�X��(�k�ރ|���S�����l��)
    PolygonValue = valueX * (valueZ << 1) + ((valueZ - 1) << 2);        //�|���S����(�k�ރ|���S�����l��)

    //---�o�b�t�@�̐���---//
    //���_�o�b�t�@
    hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VertexValue, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, VertexBuffer.get(), nullptr);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�n�`�̒��_�o�b�t�@�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    //�C���f�b�N�X�o�b�t�@
    hResult = pDevice->CreateIndexBuffer(sizeof(WORD) * nIndexValue, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, IndexBuffer.get(), nullptr);
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
    for (nCounterZ = 0; nCounterZ < (valueZ + 1); ++nCounterZ)
    {
        for (nCounterX = 0; nCounterX < (valueX + 1); ++nCounterX)
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
    for (nCounterZ = 0; nCounterZ < valueZ; ++nCounterZ)
    {
        //�k�ރ|���S���̏d����ݒ�
        if (nCounterZ > 0)
        {
            pIndex[nIndexNumber] = (nCounterZ + 1) * (valueX + 1);
            nIndexNumber++;
        }
        for (int nCounterX = 0; nCounterX < (valueX + 1); ++nCounterX)
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

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�n�`�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GROUND::Uninitialize(void)
{
    //---�J��---//
    SAFE_RELEASE((*VertexBuffer));
    SAFE_RELEASE((*IndexBuffer));
    Texture.reset();
}