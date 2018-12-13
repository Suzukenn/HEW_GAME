//�������w�b�_�t�@�C���ǂݍ��݁�����//
//#include "Collision.h"
#include "Fairy.h"
#include "InputManager.h"
#include "Item.h"
#include "ModelManager.h"
#include "Player.h"
#include "SideViewCamera.h"

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
	Position = D3DXVECTOR3(0.0F, 20.0F, 0.0F);
	Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
	Move = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Tag = tag;
	m_stat = false;
	m_tar = 0;
	m_num = 0;
	m_itemDistance = 0;
	m_itemPos = 0;

    //X�t�@�C���̓ǂݍ���
    hResult = D3DXLoadMeshFromX(TEXT("Data/Common/Model/Character/car001.x"), D3DXMESH_SYSTEMMEM, GetDevice(), nullptr, &MaterialBuffer, nullptr, &MaterialValue, &Mesh);
    if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("�t�F�A���[�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
		return hResult;
	}

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
	Rotation = PLAYER::GetPlayerRotation(); 
	int num = 0;

    static int cnt;

    if (++cnt > 120)
    {
        cnt = 0;
    }

	//�{�^������������A�C�e�������ɍs��
	if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P,XINPUT_GAMEPAD_X, TRIGGER))
	{
		m_stat = true;
	}

	//���g�p�Ȃ�
	if(!m_stat)
	{
		//�d���܂ł̋���
		D3DXVECTOR3 DisFairy;
		DisFairy.x = PLAYER::GetPlayerPosition().x - Position.x;
		DisFairy.y = PLAYER::GetPlayerPosition().y  + 20.0F - Position.y;

		//�e�̔��ˊp�x�擾���ړ��ʐݒ�
		if (DisFairy.x <= 0.1F && DisFairy.y <= 0.1F) DisFairy.x += 0.00001F; //atan2�G���[�h�~
		m_tar = atan2f(DisFairy.y, DisFairy.x);

		//�ړ��ʊi�[
		Move.x = cosf(m_tar) * VALUE_MOVE_FAIRY;
        Move.y = sinf(m_tar) * VALUE_MOVE_FAIRY + (sinf(-D3DX_PI * 0.5F + D3DX_PI / 60.0F * cnt) + 1.0F) * 0.5F;
        if (Rotation.y == SIDEVIEWCAMERA::GetRotation().y - D3DX_PI * 0.5F && Position.x > PLAYER::GetPlayerPosition().x - 20.0F && Position.x < PLAYER::GetPlayerPosition().x + 20.0F)
        {
            Move.x = 0.0F;
        }
        else if (Rotation.y == SIDEVIEWCAMERA::GetRotation().y + D3DX_PI * 0.5F && Position.x < PLAYER::GetPlayerPosition().x + 20.0F &&  Position.x > PLAYER::GetPlayerPosition().x - 20.0F)
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
        Position += Move;
	}
	//else //(�A�C�e�������ɍs���Ă���)
	//{
	//	for (int i = 0; i < MAX_ITEM; i++)
	//	{
	//		if (Item[i].GetStat() == 1)
	//		{
	//			num = -1;
	//			if (CollisionBall(&Position, Item[i].GetPos(), 100.0f, 10.0f))
	//			{
	//				Item[i].SetItemDistance(&(Position - *Item[i].GetPos()));
	//				m_itemDistance = Item[i].GetItemDistance();
	//				if (m_itemDistance->x < 0)
	//				{
	//					m_itemDistance->x *= -1;
	//				}
	//				if (m_itemDistance->x < Item[m_num].GetItemDistance()->x)
	//				{
	//					m_num = i;
	//				}
	//			}
	//			else
	//			{
	//				m_stat = false;
	//				return;
	//			}
	//			if (!Item[m_num].GetStat())
	//			{
	//				m_num = i;
	//			}
	//			m_itemPos = Item[m_num].GetPos();
	//			TakeUpItem(m_itemPos);
 //               Position += Move;
	//		}
	//		else if (Check())
	//		{
	//			m_stat = false;
	//		}
	//	}
	//}
}

void FAIRY::TakeUpItem(LPD3DXVECTOR3 pos)
{
	//�ڕW�܂ł̋���
	D3DXVECTOR3 Distance;
    Distance = *pos - Position;

	//�e�̔��ˊp�x�擾���ړ��ʐݒ�
	if (Distance.x == 0 && Distance.y == 0) Distance.x += 0.00001F; //atan2�G���[�h�~
	m_tar = atan2f(Distance.y, Distance.x);

	//�ړ��ʊi�[
	Move = D3DXVECTOR3(cosf(m_tar) * VALUE_MOVE_FAIRY, sinf(m_tar) * VALUE_MOVE_FAIRY, 0.0F);

	//�A�C�e���Ƃ̓����蔻��
	//if (CollisionBall(&Position, pos, 10.0F, 10.0F))
	//{
	//	Move.x = 0.0f;
	//	m_stat = false;
	//	//Item[m_num].SetStat(0);
	//}
}

D3DXVECTOR3 FAIRY::GetPos(void)
{
	return Position;
}

//�v���g�^�C�v��ɉ��ǂ���
bool FAIRY::Check(void)
{
    int nCounter;

    //for (nCounter = 0; nCounter < MAX_ITEM; ++nCounter)
    //{
    //    //if (Item[nCounter].GetStat())
    //    //{
    //    //    return false;
    //    //}
    //}

    return true;

	//if (!Item[0].GetStat() && !Item[1].GetStat() && !Item[2].GetStat() && !Item[3].GetStat() &&
	//	!Item[4].GetStat() && !Item[5].GetStat() && !Item[6].GetStat() && !Item[7].GetStat() &&
	//	!Item[8].GetStat() && !Item[9].GetStat() && !Item[10].GetStat() && !Item[11].GetStat() &&
	//	!Item[12].GetStat() && !Item[13].GetStat() && !Item[14].GetStat())
	//{
	//	return true;
	//}
	//return false;
}