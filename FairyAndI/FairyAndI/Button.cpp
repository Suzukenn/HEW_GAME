//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Button.h"
#include "InputManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�{�^���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BUTTON::Draw(void)
{
    //---�e��錾---//
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();

    //---�����ݒ�---//
    pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX_2D)); //���_�����ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);                                  //�t�H�[�}�b�g�ݒ�
    pDevice->SetTexture(0, Graphic);                              //�e�N�X�`���ݒ�

    //---���_�o�b�t�@�ɂ��w�i�`��---//
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�{�^���̏�����
//
//�����F(LPTSTR)�摜�̃t�@�C����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT BUTTON::Initialize(LPTSTR filepath, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
	//---�e��錾---//
	int nCounter;
	HRESULT hResult;
	LPDIRECT3DDEVICE9 pDevice;

    VERTEX_2D* pVertex;

	//---����������---//
	pDevice = GetDevice();
    Position = position;
    Size = size;

	//---�e�N�X�`���̓ǂݍ���---//
	hResult = D3DXCreateTextureFromFile(pDevice, filepath, &Graphic);
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("�{�^���̉摜�̎擾�Ɏ��s���܂���"), filepath, MB_OK);
		Graphic = nullptr;
		return hResult;
	}

	//---���_�o�b�t�@�̐���---//
	hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, 0, FVF_VERTEX_2D, D3DPOOL_MANAGED, &VertexBuffer, nullptr);
	if (FAILED(hResult))
	{
		return hResult;
	}

	//---���_�o�b�t�@�ւ̒l�̐ݒ�---//
	//�o�b�t�@�̃|�C���^���擾
	VertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	//�l�̐ݒ�
	for (nCounter = 0; nCounter < 4; nCounter++)
	{
		pVertex[nCounter].U = (float)(nCounter & 1);
		pVertex[nCounter].V = (float)((nCounter >> 1) & 1);
		pVertex[nCounter].Position.x = pVertex[nCounter].U * Size.x + Position.x;
		pVertex[nCounter].Position.y = pVertex[nCounter].V * Size.y + Position.y;
		pVertex[nCounter].Position.z = 0.0F;
		pVertex[nCounter].RHW = 1.0F;
		pVertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	//�o�b�t�@�̃|�C���^�̉��
	VertexBuffer->Unlock();

	return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�{�^���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BUTTON::Uninitialize(void)
{
    //---�J��---//
    SAFE_RELEASE(VertexBuffer);
    SAFE_RELEASE(Graphic)
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�{�^���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BUTTON::Update(void)
{
    //---�e��錾---//
    D3DXVECTOR2 vecCursorPoition;

    //---����������---//
    vecCursorPoition.x = (FLOAT)INPUTMANAGER::GetMousePosition().x;
    vecCursorPoition.y = (FLOAT)INPUTMANAGER::GetMousePosition().y;

    //---����---//
    if (Position.x < vecCursorPoition.x && vecCursorPoition.x < (Position.x + Size.x))
    {
        if (Position.y < vecCursorPoition.y && vecCursorPoition.y < (Position.y + Size.y))
        {
            Behavior();
        }
    }
}