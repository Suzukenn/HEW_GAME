//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <d3dx9mesh.h>
#include "Field.h"
#include "TextureManager.h"

//�������O���[�o���錾������//
LPD3DXMESH FIELD::Mesh;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FCheckField
//
//�@�\�F�n�`�̓����蔻��
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool FIELD::CheckField(LPD3DXVECTOR3 rayposition, LPD3DXVECTOR3 raydirection, float& afterposition)
{
    //---�e��錾---//
    int nCounter;
    BOOL bResult;
    float fHitU;
    float fHitV;
    HRESULT hResult;
    DWORD dwHitIndex;

    WORD dwHitVertexNo[3];

    LPWORD pIndex;
    VERTEX_3D* pVertex;

    //---����������---//
    dwHitIndex = -1;

    //���C�s�b�L���O
    hResult = D3DXIntersect(Mesh, rayposition, raydirection, &bResult, &dwHitIndex, &fHitU, &fHitV, nullptr, nullptr, nullptr);
    if (SUCCEEDED(hResult) && bResult)
    {
        hResult = Mesh->LockIndexBuffer(0, (void**)&pIndex);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("�n�`�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
            return false;
        }
        for (nCounter = 0; nCounter < 3; ++nCounter)
        {
            dwHitVertexNo[nCounter] = pIndex[dwHitIndex * 3 + nCounter];
        }

        hResult = Mesh->UnlockIndexBuffer();
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("�n�`�̃��f�����̊J���Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
            return false;
        }

        //���������|���S���擾
        hResult = Mesh->LockVertexBuffer(0, (void**)&pVertex);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("�n�`�̃��f���|���S���̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
            return false;
        }


        //�n�ʂ̍����ɍ��킹��
        afterposition = pVertex[dwHitVertexNo[0]].Vertex.y + fHitU * (pVertex[dwHitVertexNo[1]].Vertex.y - pVertex[dwHitVertexNo[0]].Vertex.y) + fHitV * (pVertex[dwHitVertexNo[2]].Vertex.y - pVertex[dwHitVertexNo[0]].Vertex.y);

        hResult = Mesh->UnlockVertexBuffer();
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("�n�`�̃��f���|���S���̊J���Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
            return false;
        }

        return bResult ? true : false;
    }
    else
    {
        return false;
    }
}

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
    DWORD nCounter;
    D3DXMATRIX mtxWorld;
    D3DMATERIAL9 matDef;

    LPDIRECT3DDEVICE9 pDevice;
    LPD3DXMATERIAL pMatrix;

    //---����������---//
    pDevice = GetDevice();

    D3DXMatrixIdentity(&mtxWorld);

    //���[���h�}�g���b�N�X�̐ݒ�---//
    Transform.MakeWorldMatrix(mtxWorld);

    //---�`��---//
    // ���݂̃}�e���A�����擾
    pDevice->GetMaterial(&matDef);

    //�|�C���^���擾
    pMatrix = (LPD3DXMATERIAL)MaterialBuffer->GetBufferPointer();

    for (nCounter = 0; nCounter < MaterialValue; ++nCounter)
    {
        //�}�e���A���̐ݒ�
        pDevice->SetMaterial(&pMatrix[nCounter].MatD3D);

        //�e�N�X�`���̐ݒ�
        pDevice->SetTexture(0, Texture);

        //�`��
        Mesh->DrawSubset(nCounter);
    }

    //�}�e���A�����f�t�H���g�ɖ߂�
    pDevice->SetMaterial(&matDef);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�n�`�̏�����
//
//�����F(LPCTSTR)���f����,(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT FIELD::Initialize(LPCTSTR modelfile, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 scale)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    //�����ݒ�
    Transform.Position = position;
    Transform.Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Transform.Scale = scale;

    //X�t�@�C���̓ǂݍ���
    hResult = D3DXLoadMeshFromX(modelfile, D3DXMESH_SYSTEMMEM, GetDevice(), nullptr, &MaterialBuffer, nullptr, &MaterialValue, &Mesh);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�n�`�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
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
    SAFE_RELEASE(MaterialBuffer);
    SAFE_RELEASE(Mesh);
    SAFE_RELEASE(Texture);
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