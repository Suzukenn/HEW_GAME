//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "Fairy.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "Player.h"
#include "SideViewCamera.h"
#include "Sphere.h"

//�������萔�E�}�N����`������//
#define	VALUE_ROTATE_FAIRY	(D3DX_PI * 0.02F)		// ��]���x

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FFAIRY
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
FAIRY::FAIRY(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, tag, position, rotation);
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�t�F�A���[�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void FAIRY::Draw(void)
{
    //---�e��錾---//
    DWORD nCounter;
    LPDIRECT3DDEVICE9 pDevice;
    D3DXMATRIX mtxWorld;
    LPD3DXMATERIAL pMatrix;
    D3DMATERIAL9 matDef;

    //---����������---//
    pDevice = GetDevice();

    //---���[���h�}�g���N�X�̐ݒ�---//
    //������
    D3DXMatrixIdentity(&mtxWorld);

    //�ݒ�
    Transform.MakeWorldMatrix(mtxWorld);

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
//�@�\�F�t�F�A���[�̏�����
//
//�����F(LPCTSTR)���f����,(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT FAIRY::Initialize(LPCTSTR modelfile, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
	//�����ݒ�
	Transform.Position = D3DXVECTOR3(0.0F, 20.0F, 0.0F);
    Transform.Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
	Move = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Tag = tag;
    Collection = false;
    ToTargetAngle = 0.0F;
    ElementPosition = Transform.Position;
    State = STATE_CHASE;

    //X�t�@�C���̓ǂݍ���
    hResult = D3DXLoadMeshFromX(TEXT("Data/Common/Model/Character/car001.x"), D3DXMESH_SYSTEMMEM, GetDevice(), nullptr, &MaterialBuffer, nullptr, &MaterialValue, &Mesh);
    if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("�t�F�A���[�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
		return hResult;
	}

    //---�����蔻��̕t�^---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(D3DXVECTOR3(Transform.Position.x + 0.0F, Transform.Position.y + 10.0F, Transform.Position.z + 0.0F), 5.0F, TEXT("Character"), this);

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
void FAIRY::OnCollision(COLLISION* opponent)
{
    if (opponent->Owner->GetTag() == TEXT("Player"))
    {
        //�E����
        if (Transform.Rotation.y == SIDEVIEWCAMERA::GetRotation().y - D3DX_PI * 0.5F)
        {
            if (Transform.Position.x > PLAYER::GetPlayerPosition().x - 15.0F)
            {
                Move.x = -(VALUE_MOVE_FAIRY) / 3.0F;
            }
            else
            {
                Move.x = 0.0F;
                Move.z = 0.0F;
            }
        }
        //������
        else if (Transform.Rotation.y == SIDEVIEWCAMERA::GetRotation().y + D3DX_PI * 0.5F)
        {
            if (Transform.Position.x < PLAYER::GetPlayerPosition().x + 15.0F)
            {
                Move.x = VALUE_MOVE_FAIRY / 3.0F;
            }
            else
            {
                Move.x = 0.0F;
                Move.z = 0.0F;
            }
        }
    }
    else if (opponent->Owner->GetTag() == TEXT("Element"))
    {
        Collection = false;
    }
}

/////////////////////////////////////////////
//�֐����FSearchElement
//
//�@�\�F�ł��߂��G�������g�̌���
//
//�����F�Ȃ�
//
//�߂�l�F(D3DXVECTOR3)�ŒZ�ʒu
/////////////////////////////////////////////
bool FAIRY::SearchElement(D3DXVECTOR3& destination)
{
    //---�e��錾---//
    float fCurrentCalcDistance;         //���ݎZ�o��������
    float fShortestDistance;            //�b��ŒZ����
    D3DXVECTOR3 vecDistance;

    //---����������---//
    Element.clear();
    fShortestDistance = INFINITY;

    //�G�������g������
    ACTORMANAGER::FindObject(Element, TEXT("Element"));

    if (Element.empty())
    {
        destination = Transform.Position;
        return false;
    }
    else
    {
        for (auto& data : Element)
        {
            //���g�Ƃ̋����̎Z�o
            vecDistance = data->GetPosition() - Transform.Position;
            fCurrentCalcDistance = vecDistance.x * vecDistance.x + vecDistance.y * vecDistance.y;

            //�ŒZ�����Ȃ����A�C�e����ύX
            if (fShortestDistance > fCurrentCalcDistance)
            {
                fShortestDistance = fCurrentCalcDistance;
                destination = data->GetPosition();
            }
        }
        return true;
    }
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�t�F�A���[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void FAIRY::Uninitialize(void)
{
    SAFE_RELEASE(Texture);
    SAFE_RELEASE(Mesh);
    SAFE_RELEASE(MaterialBuffer);
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�t�F�A���[�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void FAIRY::Update(void)
{	
    //---�e��錾---//
    D3DXVECTOR3 vecFairyDistance;

    //---����������---//
    Transform.Rotation = PLAYER::GetPlayerRotation();
	int num = 0;

    static int cnt;

    if (++cnt > 120)
    {
        cnt = 0;
    }

    //�ړ�
    Transform.Position += Move;
    Collision->Position = Transform.Position;


    //�{�^������������v�l��Ԃֈڍs
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        if (State == STATE_SYNTHIESIS)
        {
            State = STATE_CHASE;
        }
        else
        {
            State = STATE_SYNTHIESIS;
        }
    }

	//�{�^������������A�C�e�������ɍs��
	if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P,XINPUT_GAMEPAD_X, TRIGGER))
	{
        Collection = SearchElement(ElementPosition);
	}

    if (Collection)
    {
        //�d���ƃG�������g�̋����̎Z�o
        vecFairyDistance.x = ElementPosition.x - Transform.Position.x;
        vecFairyDistance.y = ElementPosition.y - Transform.Position.y;
        Transform.Rotation.y = 90.0F * ((ElementPosition.x > Transform.Position.x) - (ElementPosition.x < Transform.Position.x));
    }
    else
    {
        //�d���ƃv���C���[�̋����̎Z�o
        vecFairyDistance.x = PLAYER::GetPlayerPosition().x - Transform.Position.x;
        vecFairyDistance.y = PLAYER::GetPlayerPosition().y + 20.0F - Transform.Position.y;
        Transform.Rotation.y = 90.0F * ((PLAYER::GetPlayerPosition().x > Transform.Position.x) - (PLAYER::GetPlayerPosition().x < Transform.Position.x));
    }

	//�e�̔��ˊp�x�擾���ړ��ʐݒ�
    if (vecFairyDistance.x <= 0.1F && vecFairyDistance.y <= 0.1F)
    {
        vecFairyDistance.x += 0.00001F; //atan2�G���[�h�~
    }
        
    ToTargetAngle = atan2f(vecFairyDistance.y, vecFairyDistance.x);

	//�ړ��ʊi�[
	Move.x = cosf(ToTargetAngle) * VALUE_MOVE_FAIRY;
    Move.y = sinf(ToTargetAngle) * VALUE_MOVE_FAIRY + (sinf(-D3DX_PI * 0.5F + D3DX_PI / 60.0F * cnt) + 1.0F) * 0.5F;
    if (Transform.Rotation.y == SIDEVIEWCAMERA::GetRotation().y - D3DX_PI * 0.5F && Transform.Position.x > PLAYER::GetPlayerPosition().x - 20.0F && Transform.Position.x < PLAYER::GetPlayerPosition().x + 20.0F)
    {
        Move.x = 0.0F;
    }
    else if (Transform.Rotation.y == SIDEVIEWCAMERA::GetRotation().y + D3DX_PI * 0.5F && Transform.Position.x < PLAYER::GetPlayerPosition().x + 20.0F && Transform.Position.x > PLAYER::GetPlayerPosition().x - 20.0F)
    {
        Move.x = 0.0F;
    }

    //�v���C���[�Ƃ̓����蔻��
		//if (CollisionBall(&Position, &playerPos, 15.0F, 15.0F))
		//{
  //          //�E����
		//	if (Rotation.y == rotCamera.y - D3DX_PI * 0.5F)
		//	{
  //              if (Position.x > playerPos.x - 15.0F)
  //              {
  //                  Move.x = -(VALUE_MOVE_FAIRY) / 3.0F;
  //              }
  //              else
  //              {
  //                  Move.x = 0.0F;
  //              }
		//	}
		//	else if (Rotation.y == rotCamera.y + D3DX_PI * 0.5F)
		//	{
  //              if (Position.x < playerPos.x + 15.0F)
  //              {
  //                  Move.x = VALUE_MOVE_FAIRY / 3.0F;
  //              }
  //              else
  //              {
  //                  Move.x = 0.0F;
  //              }
  //          }
		//	return;
		//}
}

D3DXVECTOR3 FAIRY::GetPos(void)
{
	return Transform.Position;
}