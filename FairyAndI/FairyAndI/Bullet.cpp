//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Bullet.h"
#include "ModelManager.h"
#include "Sphere.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FBULLET
//
//�@�\�F�R���X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
BULLET::BULLET(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 size)
{
    Initialize(modelname, tag, position, rotation, size);
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�e�ۂ̕`��
//
//�����F(LPCTSTR)���f����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��],(D3DXVECTOR3)�傫��
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BULLET::Draw(void)
{
    //---�e��錾---//
    DWORD nCounter;
    LPDIRECT3DDEVICE9 pDevice;
    D3DXMATRIX mtxRotation;
    D3DXMATRIX mtxTranslate;
    D3DXMATRIX mtxWorld;
    LPD3DXMATERIAL pMatrix;
    D3DMATERIAL9 matDef;

    //---����������---//
    pDevice = GetDevice();

    //---���[���h�}�g���N�X�̐ݒ�---//
    //������
    D3DXMatrixIdentity(&mtxWorld);

    //��]�𔽉f
    D3DXMatrixRotationYawPitchRoll(&mtxRotation, Rotation.y, Rotation.x, Rotation.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRotation);

    //�ړ��𔽉f
    D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

    //�ݒ�
    pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

    // ���݂̃}�e���A�����擾
    pDevice->GetMaterial(&matDef);

    //---�`��---//
    //�|�C���^���擾
    pMatrix = (LPD3DXMATERIAL)(*Model).MaterialBuffer->GetBufferPointer();

    for (nCounter = 0; nCounter < (*Model).MaterialValue; ++nCounter)
    {
        //�}�e���A���̐ݒ�
        pDevice->SetMaterial(&pMatrix[nCounter].MatD3D);

        //�e�N�X�`���̐ݒ�
        pDevice->SetTexture(0, *(*Model).Texture);

        //�`��
        (*Model).Mesh->DrawSubset(nCounter);
    }

    //�}�e���A�����f�t�H���g�ɖ߂�
    pDevice->SetMaterial(&matDef);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�e�ۂ̏�����
//
//�����F(LPCTSTR)���f����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��],(D3DXVECTOR3)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT BULLET::Initialize(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 size)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    Position = position;
    Rotation = rotation;
    Size = size;

    //---���f���̓ǂݍ���---//
    hResult = MODELMANAGER::GetModel(modelname, Model.get());
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�e�ۂ̃��f���̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    Collision = new SPHERE(Position + size * 0.5F, Position.x * 0.5F, tag, this);

    return hResult;
}

/////////////////////////////////////////////
//�֐����FOnCollision
//
//�@�\�F�����蔻�蔽�����̋���
//
//�����F(COLLISITON)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BULLET::OnCollision(COLLISION* opponent)
{

}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�e�ۂ̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BULLET::Uninitialize(void)
{
    //---�J��---//
    Model->Release();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�e�ۂ̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BULLET::Update(void)
{
    Position.x += 1.0F;
}