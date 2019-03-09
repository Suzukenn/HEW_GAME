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
#include "SquareGauge.h"

//�������萔�E�}�N����`������//
#define	VALUE_ROTATE_FAIRY	(D3DX_PI * 0.02F)		// ��]���x

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FFAIRY
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
FAIRY::FAIRY(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, position, rotation);
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
    D3DXMATRIX mtxWorld;

    //---���[���h�}�g���N�X�̐ݒ�---//
    //������
    D3DXMatrixIdentity(&mtxWorld);

    //�ݒ�
    Transform.MakeWorldMatrix(mtxWorld);

    //---�`��---//
    Model.Draw(mtxWorld, false);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�t�F�A���[�̏�����
//
//�����F(LPCTSTR)���f����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT FAIRY::Initialize(LPCTSTR modelfile, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
	//�����ݒ�
	Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(100.0F, 100.0F, 100.0F);
	Move = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Tag = TEXT("Fairy");
    Collection = false;
    ToTargetAngle = 0.0F;
    ElementPosition = Transform.Position;
    State = STATE_WAIT;

    //---���f���̓ǂݍ���---//
    hResult = Model.Initialize(modelfile, 1.0F);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�t�F�A���[�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }
    else
    {
        Model.ChangeAnimation(STATE_WAIT);
    }

    //---�����蔻��̕t�^---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 5.0F, TEXT("Character"), this);

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
    //�v���C���[�̌��ɂ�
    if (opponent->Owner->GetTag() == TEXT("Player"))
    {
       /* Move.x = 0.0F;
        Move.y = 0.0F;*/
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
    Model.Uninitialize();
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
    static int nFrameCount = 0;
    static bool bThink = false;

    //�t���[�����̃J�E���g
    if (++nFrameCount > 120)
    {
        nFrameCount = 0;
    }

    //�ړ�
    Transform.Position += Move;
    Collision->Position = Transform.Position;

    //�{�^������������v�l��Ԃֈڍs
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        bThink = !bThink;
        Model.ChangeAnimation(bThink ? STATE_THINK : (DWORD)State);
    }
	else if (SQUAREGAUGE::GetFairyTime() == false)
	{
		bThink = false;
		Model.ChangeAnimation(bThink ? STATE_THINK : (DWORD)State);
	}

    //�{�^������������A�C�e�������ɍs��
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_X, TRIGGER))
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

    //�ړ��ʐݒ�
    if (vecFairyDistance.x == 0.1F && vecFairyDistance.y == 0.1F)
    {
        vecFairyDistance.x += 0.0001F; //atan2�G���[�h�~
    }

    ToTargetAngle = atan2f(vecFairyDistance.y, vecFairyDistance.x);

    //�ړ��ʊi�[
    Move.x = cosf(ToTargetAngle) * VALUE_MOVE_FAIRY;
    Move.y = sinf(ToTargetAngle) * VALUE_MOVE_FAIRY + (sinf(D3DXToRadian(-180.0F) + D3DX_PI / 60.0F * nFrameCount) + 1.0F) * 0.5F;

    if (!Collection)
    {
        if (Transform.Position.x >= PLAYER::GetPlayerPosition().x - 5.0F && Transform.Position.x <= PLAYER::GetPlayerPosition().x + 5.0F)
        {
			Transform.Rotation.y = PLAYER::GetPlayerRotation().y;
			Move.x = 0.0F;
            if (Transform.Position.y >= PLAYER::GetPlayerPosition().y - 5.0F && Transform.Position.y <= PLAYER::GetPlayerPosition().y + 5.0F)
            {
				Move.y = (sinf(D3DXToRadian(-180.0F) + D3DX_PI / 60.0F * nFrameCount) + 1.0F) * 0.5F;
            }
        }
    }
    //�A�j���[�V�����̕ύX
	if (!bThink)
	{
		State = Move.x == 0.0F ? STATE_WAIT : STATE_MOVE;
		Model.ChangeAnimation((DWORD)State);
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