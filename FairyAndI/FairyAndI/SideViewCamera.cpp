//�������w�b�_�t�@�C���ǂݍ�������//
#include "Fairy.h"
#include "InputManager.h"
#include "Player.h"
#include "SideViewCamera.h"
#include "SquareGauge.h"

//�������萔�E�}�N����`������//
#define	CAM_POS_P_X			(0.0f)					// �J�����̎��_�����ʒu(X���W)
#define	CAM_POS_P_Y			(10.0f)				// �J�����̎��_�����ʒu(Y���W)
#define	CAM_POS_P_Z			(-100.0f)				// �J�����̎��_�����ʒu(Z���W)
#define	CAM_POS_R_X			(0.0f)					// �J�����̒����_�����ʒu(X���W)
#define	CAM_POS_R_Y			(50.0f)					// �J�����̒����_�����ʒu(Y���W)
#define	CAM_POS_R_Z			(0.0f)					// �J�����̒����_�����ʒu(Z���W)
#define CAM_MAX_WID			1400.0F
#define CAM_MIN_WID			-1400.F

//�������O���[�o���錾������//
D3DXVECTOR3 SIDEVIEWCAMERA::Position;
D3DXVECTOR3 SIDEVIEWCAMERA::Rotation;
D3DXVECTOR3	SIDEVIEWCAMERA::ReversoPoint;
D3DXVECTOR3 SIDEVIEWCAMERA::UpVector;
float SIDEVIEWCAMERA::Interval;
D3DXMATRIX SIDEVIEWCAMERA::ViewMatrix;
D3DXMATRIX SIDEVIEWCAMERA::ProjectionMatrix;
bool SIDEVIEWCAMERA::PositionPlace;

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�J�����̏�����
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)�����_
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT SIDEVIEWCAMERA::Initialize(D3DXVECTOR3 position, D3DXVECTOR3 reverso)
{
    //---�e��錾---//
    float fVectorX;
    float fVectorZ;

    Position = position;
    Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    ReversoPoint = reverso;
    UpVector = D3DXVECTOR3(0.0F, 1.0F, 0.0F);
    PositionPlace = false;

    fVectorX = Position.x - ReversoPoint.x;
    fVectorZ = Position.z - ReversoPoint.z;
    Interval = sqrtf(fVectorX * fVectorX + fVectorZ * fVectorZ);

	return S_OK;
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
HRESULT SIDEVIEWCAMERA::SetCamera(void)
{
    //---�e��錾---//
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();

    //---�r���[�}�g���N�X�̐ݒ�---//
    //������
    D3DXMatrixIdentity(&ViewMatrix);

    //�쐬
    D3DXMatrixLookAtLH(&ViewMatrix, &Position, &ReversoPoint, &UpVector);

    //�ݒ�
    hResult = pDevice->SetTransform(D3DTS_VIEW, &ViewMatrix);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�T�C�h�r���[�J�����̃r���[�}�g���N�X�̐ݒ�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    //---�v���W�F�N�V�����}�g���b�N�X�ݒ�---//
    //������
    D3DXMatrixIdentity(&ProjectionMatrix);

    //�쐬
    D3DXMatrixPerspectiveFovLH(&ProjectionMatrix, D3DXToRadian(45.0F), SCREEN_WIDTH / SCREEN_HEIGHT, 10.0F, 1000.0F);

    //�ݒ�
    hResult = pDevice->SetTransform(D3DTS_PROJECTION, &ProjectionMatrix);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�T�C�h�r���[�J�����̃v���W�F�N�V�����}�g���N�X�̐ݒ�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    return hResult;
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
void SIDEVIEWCAMERA::Uninitialize(void)
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
void SIDEVIEWCAMERA::Update(D3DXVECTOR3 player)
{
    //---�e��錾---//
    float fStickVector;
    static bool Mode;
    D3DXVECTOR3 FairyPosition;

    FairyPosition = FAIRY::GetFairyPosition();
    Mode = SQUAREGAUGE::GetFairyTime();

    //---�ړ�����---//
    //�J�����̌����擾
    fStickVector = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT).x;

    //�[�ɂ��邩�̔��蔻��
    if (player.x >= Position.x && Position.x >= CAM_MAX_WID || player.x <= Position.x && Position.x <= CAM_MIN_WID)
    {
        PositionPlace = true;
    }
    //���_���E�ɂ��ăv���C���[���J����pos�ȉ��ɂȂ�A�܂��͌��_��荶�ɂ��ăv���C���[���J����pos�ȏ�ɂȂ�����
    else if (player.x < Position.x && Position.x > 0.0F || player.x > Position.x && Position.x < 0.0F)
    {
        PositionPlace = false;
    }

    /*if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
    Mode = !Mode;
    }
    else if (SQUAREGAUGE::GetFairyTime() == false)
    {
    Mode = false;
    }*/

    if (!PositionPlace)
    {
        //�v���C���[��^�񒆂ɂ��Ēǂ������鏈��
        Position = D3DXVECTOR3(player.x, 60.0F, player.z - 100.0F);
        ReversoPoint = D3DXVECTOR3(player.x, 30.0F, player.z);
    }
    else
    {
        //�X�N���[������
        Position.x += VALUE_MOVE_PLAYER * fStickVector * 0.5F;
        ReversoPoint = D3DXVECTOR3(Position.x, 30.0F, player.z);
    }

    if (Mode)
    {
        Position = D3DXVECTOR3(FairyPosition.x, FairyPosition.y + 10.0F, FairyPosition.z - 50.0F);
        ReversoPoint = D3DXVECTOR3(FairyPosition.x, FairyPosition.y + 10.0F, FairyPosition.z);
    }

    //�J�����̈ړ�����
    if (Position.x > CAM_MAX_WID)
    {
        Position.x = CAM_MAX_WID;
        ReversoPoint.x = CAM_MAX_WID;
    }
    if (Position.x < CAM_MIN_WID)
    {
        Position.x = CAM_MIN_WID;
        ReversoPoint.x = CAM_MIN_WID;
    }

    SetCamera();
}

/////////////////////////////////////////////
//�֐����FGetRotation
//
//�@�\�F�J�����̉�]�̎擾
//
//�����F�Ȃ�
//
//�߂�l�F(D3DXVECTOR3)��]
/////////////////////////////////////////////
D3DXVECTOR3 SIDEVIEWCAMERA::GetRotation(void)
{
	return Rotation;
}

/////////////////////////////////////////////
//�֐����FGetProjectionMatrix
//
//�@�\�F�J�����̃v���W�F�N�V�����}�g���N�X�̎擾
//
//�����F(LPD3DXMATRIX)�i�[�}�g���N�X
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SIDEVIEWCAMERA::GetProjectionMatrix(LPD3DXMATRIX projectionmatrix)
{
    if (projectionmatrix)
    {
        *projectionmatrix = ProjectionMatrix;
    }
    else
    {
        projectionmatrix = nullptr;
    }
}

/////////////////////////////////////////////
//�֐����FGetViewMatrix
//
//�@�\�F�J�����̃r���[�}�g���N�X�̎擾
//
//�����F(LPD3DXMATRIX)�i�[�}�g���N�X
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SIDEVIEWCAMERA::GetViewMatrix(LPD3DXMATRIX viewmatrix)
{
    if (viewmatrix)
    {
        *viewmatrix = ViewMatrix;
    }
    else
    {
        viewmatrix = nullptr;
    }
}