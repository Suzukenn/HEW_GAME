//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// ���C�g�̏���������
//=============================================================================
HRESULT LIGHT::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&m_aLight[0], sizeof(D3DLIGHT9));

	// ���C�g�̃^�C�v�̐ݒ�
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// �g�U��
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ����
	m_aLight[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.0f, -0.6f, -1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[0].Direction, &vecDir);

	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(0, &m_aLight[0]);

	// ���C�g�̐ݒ�
	pDevice->LightEnable(0, FALSE);


	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&m_aLight[1], sizeof(D3DLIGHT9));

	// ���C�g�̃^�C�v�̐ݒ�
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	// �g�U��
	m_aLight[1].Diffuse = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);

	// ����
	m_aLight[1].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    // ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.0f, -1.0f, 0.8f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[1].Direction, &vecDir);

	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(1, &m_aLight[1]);

	// ���C�g�̐ݒ�
	pDevice->LightEnable(1, TRUE);


	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&m_aLight[2], sizeof(D3DLIGHT9));

	// ���C�g�̃^�C�v�̐ݒ�
	m_aLight[2].Type = D3DLIGHT_POINT;

	// �g�U��
	m_aLight[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ����
	m_aLight[2].Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);

    // ���C�g�̈ʒu�̐ݒ�
    m_aLight[2].Position = D3DXVECTOR3(0.0f, 20.0f, 0.0f);

	// ���C�g�̌����̐ݒ�
	m_aLight[2].Attenuation0 = 0.0f;
	m_aLight[2].Attenuation1 = 0.0f;
	m_aLight[2].Attenuation2 = 0.01f;
	m_aLight[2].Falloff = 1.0f;

	// ���C�g�͈̔͂̐ݒ�
	m_aLight[2].Range = 50.0f;

	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(2, &m_aLight[2]);

	// ���C�g�̐ݒ�
	pDevice->LightEnable(2, FALSE);


	// ���C�e�B���O���[�h
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	return S_OK;
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void LIGHT::Uninit(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void LIGHT::Update(D3DXVECTOR3* Player)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

    // ���C�g�̈ʒu�̐ݒ�
	m_aLight[2].Position.x = Player->x;
	m_aLight[2].Position.z = Player->z;

	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(2, &m_aLight[2]);
}
