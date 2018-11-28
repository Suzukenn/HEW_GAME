//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "Player.h"
#include "SideViewCamera.h"
#include "WordMenu.h"

//�������萔�E�}�N����`������//
#define GRAVITY 0.18F
#define JUMP 5.0F

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�v���C���[�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void PLAYER::Draw(void)
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
//�@�\�F�v���C���[�̏�����
//
//�����F(LPCTSTR)���f���t�@�C����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT PLAYER::Initialize(LPCTSTR modelfile)
{
    //---�e��錾---//
    HRESULT hResult;

	//---����������---//
	//�ʒu�E�����̏����ݒ�
	Position = D3DXVECTOR3(0.0F, 10.0F, 0.0F);
	Rotation = D3DXVECTOR3(0.0F, SIDEVIEWCAMERA::GetRotation().y - D3DX_PI * 0.5F, 0.0F);
    Size = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
	Move = D3DXVECTOR3(0.0F, 0.0F, 0.0F);

    //X�t�@�C���̓ǂݍ���
    hResult = D3DXLoadMeshFromX(TEXT("Data/Common/Model/Character/car000.x"), D3DXMESH_SYSTEMMEM, GetDevice(), nullptr, &MaterialBuffer, nullptr, &MaterialValue, &Mesh);
    if(FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�v���C���[�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
		return hResult;
	}
	return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�v���C���[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void PLAYER::Uninitialize(void)
{
    SAFE_RELEASE(Texture);
    SAFE_RELEASE(Mesh);
    SAFE_RELEASE(MaterialBuffer);
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�v���C���[�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void PLAYER::Update(void)
{
    //---�e��錾---//
    D3DXVECTOR2 vecStickVector;
    D3DXVECTOR3 vecCameraRotation;
    POINTS StickPoints;

    //---�ړ�����---//
	//�J�����̌����擾
    vecCameraRotation = SIDEVIEWCAMERA::GetRotation();
    StickPoints = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT);
    vecStickVector = D3DXVECTOR2((float)((StickPoints.x > 0) - (StickPoints.x < 0)), (float)((StickPoints.y > 0) - (StickPoints.y < 0)));

	//�d�͉��Z
	Move.y -= GRAVITY;

	//�ړ�
	Position.x += sinf(vecCameraRotation.y + D3DX_PI * 0.5F) * VALUE_MOVE_PLAYER * vecStickVector.x;
    Position.z += cosf(vecCameraRotation.y + D3DX_PI * 0.5F) * VALUE_MOVE_PLAYER * vecStickVector.y;

    Rotation.y = vecCameraRotation.y - D3DX_PI * 0.5F * vecStickVector.x;

	//�W�����v
	if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
	{
        Move.y += JUMP;
	}

	//---�ʒu���X�V---//
    Position.y += Move.y;

	//�ړ�����
	if (Position.y < 0.0F)
	{
        Position.y = 0.0F;
		Move.y = 0.0F;
	}
	if (Position.x > 1500.0F)
	{
        Position.x = 1500.0F;
	}
	else if (Position.x < -1500.0F)
	{
        Position.x = -1500.0F;
	}

    //---�A�C�e������---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
    {
        ACTORMANAGER::Instantiate(WORDMENU::NotificationItem());
    }
}

// ���f���ʒu�̎擾
const D3DXVECTOR3 PLAYER::GetPlayerPosition(void)
{
	return Position;
}

// ���f�������̎擾
const LPD3DXVECTOR3 PLAYER::GetPlayerRotation(void)
{
	return &Rotation;
}