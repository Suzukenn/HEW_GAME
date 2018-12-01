//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Item.h"
#include "SideViewCamera.h"
#include "Collision.h"
#include "ModelManager.h"

//�������萔�E�}�N����`������//

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�A�C�e���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ITEM::Draw(void)
{
    //---�e��錾---//
    int nCounter;
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
    pMatrix = (LPD3DXMATERIAL)Model->MaterialBuffer->GetBufferPointer();

    for (nCounter = 0; nCounter < (int)Model->MaterialValue; ++nCounter)
    {
        //�}�e���A���̐ݒ�
        pDevice->SetMaterial(&pMatrix[nCounter].MatD3D);

        //�e�N�X�`���̐ݒ�
        pDevice->SetTexture(0, *Model->Texture);

        //�`��
        Model->Mesh->DrawSubset(nCounter);
    }

    //�}�e���A�����f�t�H���g�ɖ߂�
    pDevice->SetMaterial(&matDef);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F���f���̏�����
//
//�����F(LPCTSTR)���f���t�@�C����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ITEM::Initialize(LPCTSTR modelname)
{
    //---�e��錾---//
    HRESULT hResult;
    D3DXVECTOR3 rotCamera;

    //---����������---//
    Model.reset(new MODEL);

    // �ʒu�E�����̏����ݒ�
    Position = D3DXVECTOR3(0.0F, 10.0F, 0.0F);
    Rotation = D3DXVECTOR3(0.0F, SIDEVIEWCAMERA::GetRotation().y - D3DX_PI * 0.5F, 0.0F);

    // X�t�@�C���̓ǂݍ���
    hResult = MODELMANAGER::GetModel(modelname, *Model);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�A�C�e���̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

	// ������
    Name = modelname;
    return hResult;
}

/////////////////////////////////////////////
//�֐����FOnCollision
//
//�@�\�F�����蔻�莞�̋���
//
//�����F(LPCTSTR)���f���t�@�C����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
void ITEM::OnCollision(COLLISION* opponent)
{

}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F���f���̏I��
//
//�����F(LPCTSTR)���f���t�@�C����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
void ITEM::Uninitialize(void)
{
    //SAFE_RELEASE((*Model->Texture));
    //SAFE_RELEASE(Model->Mesh);
    //SAFE_RELEASE(Model->MaterialBuffer);
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F���f���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ITEM::Update(void)
{

}