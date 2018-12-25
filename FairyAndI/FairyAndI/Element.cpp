//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "Element.h"
#include "ModelManager.h"
#include "SideViewCamera.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FELEMENT
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(tstirng)�^�C�v,(D3DXVECTOR3)�ʒu
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
ELEMENT::ELEMENT(LPCTSTR modelname, tstring type, D3DXVECTOR3 position)
{
    Initialize(modelname, type, position);
}

/////////////////////////////////////////////
//�֐����F~ELEMENT
//
//�@�\�F�f�X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
ELEMENT::~ELEMENT(void)
{
    Uninitialize();
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�A�C�e���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ELEMENT::Draw(void)
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
//�����F(LPCTSTR)���f����,(tstirng)�^�C�v,(D3DXVECTOR3)�ʒu
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ELEMENT::Initialize(LPCTSTR modelname, tstring type, D3DXVECTOR3 position)
{
    //---�e��錾---//
    HRESULT hResult;
    D3DXVECTOR3 rotCamera;

    //---����������---//
    Model.reset(new MODEL);

    // �ʒu�E�����̏����ݒ�
    Position = D3DXVECTOR3(0.0F, 10.0F, 0.0F);
    Rotation = D3DXVECTOR3(0.0F, SIDEVIEWCAMERA::GetRotation().y - D3DX_PI * 0.5F, 0.0F);
    Tag = TEXT("Element");

    // X�t�@�C���̓ǂݍ���
    hResult = MODELMANAGER::GetModel(modelname, *Model);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�G�������g�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---�����蔻��̕t�^---//
    Collision = COLLISIONMANAGER::InstantiateToOBB(D3DXVECTOR3(Position.x + 5.0F, Position.y + 5.0F, Position.z + 5.0F), D3DXVECTOR3(5.0F, 5.0F, 5.0F), TEXT("Element"), this);

	//������
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
void ELEMENT::OnCollision(COLLISION* opponent)
{
    if (opponent->Owner->GetTag().find(TEXT("Fairy")) != tstring::npos)
    {
        ACTORMANAGER::Destroy(this);
    }
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
void ELEMENT::Uninitialize(void)
{
    //SAFE_RELEASE((*Model->Texture));
    //SAFE_RELEASE(Model->Mesh);
    //SAFE_RELEASE(Model->MaterialBuffer);
    if (Collision)
    {
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        Collision = nullptr;
    }
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
void ELEMENT::Update(void)
{

}