//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "Element.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "SquareGauge.h"
#include "WordManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FELEMENT
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(tstirng)�^�C�v,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)�傫��
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
ELEMENT::ELEMENT(LPCTSTR modelname, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, type, position, rotation);
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
//�@�\�F�G�������g�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ELEMENT::Draw(void)
{
    //---�e��錾---//
    D3DXMATRIX mtxWorld;

    std::shared_ptr<MODEL> pModel;

    //---���[���h�}�g���N�X�̐ݒ�---//
    //������
    D3DXMatrixIdentity(&mtxWorld);

    //�ݒ�
    Transform.MakeWorldMatrix(mtxWorld);
    GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);

    //---�`��---//
    //�`��Ώۃ`�F�b�N
    pModel = Model.lock();
    if (!pModel)
    {
        MessageBox(nullptr, TEXT("�e�ۂ̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return;
    }

    //�`��
    pModel->Draw(Gray);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�G�������g�̏�����
//
//�����F(LPCTSTR)���f����,(tstirng)�^�C�v,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ELEMENT::Initialize(LPCTSTR modelname, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;
    D3DXVECTOR3 rotCamera;

    //---����������---//

    // �ʒu�E�����̏����ݒ�
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
    Gray = false;
    Type = type;
    Tag = TEXT("Element");

    //---���f���̓ǂݍ���---//
    hResult = MODELMANAGER::GetModel(modelname, Model);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�G�������g�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---�����蔻��̕t�^---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 5.0F, TEXT("Object"), this);

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
    if (opponent->Owner->GetTag() == TEXT("Fairy"))
    {
        ACTORMANAGER::Destroy(this);
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        WORDMANAGER::UnLockWord(Type.data());
    }
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�G�������g�̏I��
//
//�����F(LPCTSTR)���f���t�@�C����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
void ELEMENT::Uninitialize(void)
{
    if (Collision)
    {
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        Collision = nullptr;
    }
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�G�������g�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ELEMENT::Update(void)
{
   /* if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Gray = !Gray;
    }*/
	Gray = SQUAREGAUGE::GetFairyTime();

}