//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Debug.h"
#include "FlexibleCamera.h"
#include "InputManager.h"

//�������萔�E�}�N����`������//
#define MOVE_VALUE 2.0F
#define ROTATE_VALUE (D3DX_PI * 0.01F)

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�J�����̏�����
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)�����_
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT FLEXIBLECAMERA::Initialize(D3DXVECTOR3 position, D3DXVECTOR3 reverso)
{
    //---�e��錾---//
    float fVectorX;
    float fVectorZ;

    //---����������---//
    Position = position;
    Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    ReversoPoint = reverso;
    UpVector = D3DXVECTOR3(0.0F, 1.0F, 0.0F);

    fVectorX = Position.x - ReversoPoint.x;
    fVectorZ = Position.z - ReversoPoint.z;
    Interval = sqrtf(fVectorX * fVectorX + fVectorZ * fVectorZ);

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�J�����̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void FLEXIBLECAMERA::Uninitialize(void)
{

}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�J�����̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void FLEXIBLECAMERA::Update(void)
{
    //---����---//
    //���ړ�   
    if (INPUTMANAGER::GetKey(DIK_A, HOLD))
    {
        if (INPUTMANAGER::GetKey(DIK_W, HOLD))
        {
            Position.x -= cosf(Rotation.y + D3DX_PI * 0.25F) * MOVE_VALUE;
            Position.z += sinf(Rotation.y + D3DX_PI * 0.25F) * MOVE_VALUE;
        }
        else if (INPUTMANAGER::GetKey(DIK_S, HOLD))
        {
            Position.x -= cosf(Rotation.y - D3DX_PI * 0.25F) * MOVE_VALUE;
            Position.z += sinf(Rotation.y - D3DX_PI * 0.25F) * MOVE_VALUE;
        }
        else
        {
            Position.x -= cosf(Rotation.y) * MOVE_VALUE;
            Position.z += sinf(Rotation.y) * MOVE_VALUE;
        }

        ReversoPoint.x = Position.x + sinf(Rotation.y) * Interval;
        ReversoPoint.z = Position.z + cosf(Rotation.y) * Interval;
    }

    //�E�ړ�
    else if (INPUTMANAGER::GetKey(DIK_D, HOLD))
    {
        if (INPUTMANAGER::GetKey(DIK_W, HOLD))
        {
            Position.x += cosf(Rotation.y - D3DX_PI * 0.25F) * MOVE_VALUE;
            Position.z -= sinf(Rotation.y - D3DX_PI * 0.25F) * MOVE_VALUE;
        }
        else if (INPUTMANAGER::GetKey(DIK_S, HOLD))
        {
            Position.x += cosf(Rotation.y + D3DX_PI * 0.25F) * MOVE_VALUE;
            Position.z -= sinf(Rotation.y + D3DX_PI * 0.25F) * MOVE_VALUE;
        }
        else
        {
            Position.x += cosf(Rotation.y) * MOVE_VALUE;
            Position.z -= sinf(Rotation.y) * MOVE_VALUE;
        }

        ReversoPoint.x = Position.x + sinf(Rotation.y) * Interval;
        ReversoPoint.z = Position.z + cosf(Rotation.y) * Interval;
    }

    //�O�ړ�
    if (INPUTMANAGER::GetKey(DIK_W, HOLD))
    {
        Position.x += sinf(Rotation.y) * MOVE_VALUE;
        Position.z += cosf(Rotation.y) * MOVE_VALUE;

        ReversoPoint.x = Position.x + sinf(Rotation.y) * Interval;
        ReversoPoint.z = Position.z + cosf(Rotation.y) * Interval;
    }

    //��ړ�
    else if (INPUTMANAGER::GetKey(DIK_S, HOLD))
    {
        Position.x -= sinf(Rotation.y) * MOVE_VALUE;
        Position.z -= cosf(Rotation.y) * MOVE_VALUE;

        ReversoPoint.x = Position.x + sinf(Rotation.y) * Interval;
        ReversoPoint.z = Position.z + cosf(Rotation.y) * Interval;
    }

    //������
    if (INPUTMANAGER::GetKey(DIK_Z, HOLD))
    {
        Rotation.y += ROTATE_VALUE;
        if (Rotation.y > D3DX_PI)
        {
            Rotation.y -= D3DX_PI * 2.0F;
        }
        Position.x = ReversoPoint.x - sinf(Rotation.y) * Interval;
        Position.z = ReversoPoint.z - cosf(Rotation.y) * Interval;
    }

    //�E����
    else if (INPUTMANAGER::GetKey(DIK_C, HOLD))
    {
        Rotation.y -= ROTATE_VALUE;
        if (Rotation.y < -D3DX_PI)
        {
            Rotation.y += D3DX_PI * 2.0F;
        }
        Position.x = ReversoPoint.x - sinf(Rotation.y) * Interval;
        Position.z = ReversoPoint.z - cosf(Rotation.y) * Interval;
    }

    //���_�㏸
    if (INPUTMANAGER::GetKey(DIK_Y, HOLD))
    {
        Position.y += MOVE_VALUE;
    }

    //���_���~
    else if (INPUTMANAGER::GetKey(DIK_N, HOLD))
    {
        Position.y -= MOVE_VALUE;
    }

    //�����_������
    if (INPUTMANAGER::GetKey(DIK_Q, HOLD))
    {
        Rotation.y -= ROTATE_VALUE;
        if (Rotation.y < -D3DX_PI)
        {
            Rotation.y += D3DX_PI * 2.0F;
        }
        ReversoPoint.x = Position.x + sinf(Rotation.y) * Interval;
        ReversoPoint.z = Position.z + cosf(Rotation.y) * Interval;
    }

    //�����_�E����
    else if (INPUTMANAGER::GetKey(DIK_E, HOLD))
    {
        Rotation.y += ROTATE_VALUE;
        if (Rotation.y > D3DX_PI)
        {
            Rotation.y -= D3DX_PI * 2.0F;
        }
        ReversoPoint.x = Position.x + sinf(Rotation.y) * Interval;
        ReversoPoint.z = Position.z + cosf(Rotation.y) * Interval;
    }

    //�����_�㏸
    if (INPUTMANAGER::GetKey(DIK_T, HOLD))
    {
        ReversoPoint.y += MOVE_VALUE;
    }

    //�����_���~
    else if (INPUTMANAGER::GetKey(DIK_B, HOLD))
    {
        ReversoPoint.y -= MOVE_VALUE;
    }

    //���Z�b�g
    if (INPUTMANAGER::GetKey(DIK_L, TRIGGER))
    {
        Position = D3DXVECTOR3(0.0F, 100.0F, -200.0F);
        ReversoPoint = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
        Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    }

    SetCamera();

#ifdef _DEBUG
    //---�f�o�b�O�\��---//
    //DEBUG::PrintDebugData(TEXT("[�J�����̎��_�@�F(%f�F%f�F%f)]\n"), Position.x, Position.y, Position.z);
    //DEBUG::PrintDebugData(TEXT("[�J�����̒����_�F(%f�F%f�F%f)]\n"), ReversoPoint.x, ReversoPoint.y, ReversoPoint.z);
    //DEBUG::PrintDebugData(TEXT("[�J�����̌����@�F(%f)]\n"), Rotation.y);
    //DEBUG::PrintDebugData(TEXT("\n"));
    //DEBUG::PrintDebugData(TEXT("***���_����***\n"));
    //DEBUG::PrintDebugData(TEXT("�O�ړ��FW\n"));
    //DEBUG::PrintDebugData(TEXT("��ړ��FS\n"));
    //DEBUG::PrintDebugData(TEXT("���ړ��FA\n"));
    //DEBUG::PrintDebugData(TEXT("�E�ړ��FD\n"));
    //DEBUG::PrintDebugData(TEXT("***�ʒu����***\n"));
    //DEBUG::PrintDebugData(TEXT("��ړ��FY\n"));
    //DEBUG::PrintDebugData(TEXT("���ړ��FN\n"));
    //DEBUG::PrintDebugData(TEXT("������FZ\n"));
    //DEBUG::PrintDebugData(TEXT("�E����FC\n"));
    //DEBUG::PrintDebugData(TEXT("***�����_����***\n"));
    //DEBUG::PrintDebugData(TEXT("��ړ��FT\n"));
    //DEBUG::PrintDebugData(TEXT("���ړ��FB\n"));
    //DEBUG::PrintDebugData(TEXT("������FQ\n"));
    //DEBUG::PrintDebugData(TEXT("�E����FE\n"));
#endif
}

/////////////////////////////////////////////
//�֐����FSetCamera
//
//�@�\�F�J�����̐ݒ�
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT FLEXIBLECAMERA::SetCamera(void)
{
    //---�e��錾---//
    HRESULT hResult;
    D3DXMATRIX mtxView;					// �r���[�}�g���b�N�X
    D3DXMATRIX mtxProjection;			// �v���W�F�N�V�����}�g���b�N�X
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();

    //---�r���[�}�g���N�X�̐ݒ�---//
    //������
    D3DXMatrixIdentity(&mtxView);

    //�쐬
    D3DXMatrixLookAtLH(&mtxView, &Position, &ReversoPoint, &UpVector);

    //�ݒ�
    hResult = pDevice->SetTransform(D3DTS_VIEW, &mtxView);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�J�����̃r���[�}�g���N�X�̐ݒ�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    //---�v���W�F�N�V�����}�g���b�N�X�ݒ�---//
    //������
    D3DXMatrixIdentity(&mtxProjection);

    //�쐬
    D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(45.0F), SCREEN_WIDTH / SCREEN_HEIGHT, 10.0F, 1000.0F);

    //�ݒ�
    hResult = pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�J�����̃v���W�F�N�V�����}�g���N�X�̐ݒ�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    return hResult;
}