//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <list>
#include "Main.h"
#include "CollisionManager.h"

//�������O���[�o���ϐ�������//
std::list<COLLISION*> COLLISIONMANAGER::Collision;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�}�l�[�W���[�̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT COLLISIONMANAGER::Initialize(void)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    Collision.clear();
    hResult = S_OK;

    return hResult;
}

/////////////////////////////////////////////
//�֐����FInstantiate
//
//�@�\�F�}�l�[�W���[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void COLLISIONMANAGER::Instantiate(tstring objectname)
{
    //Collision.emplace_back(objectname);
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�}�l�[�W���[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void COLLISIONMANAGER::Uninitialize(void)
{
    //---���---//
    Collision.clear();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�e�N�X�`���̎擾
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void COLLISIONMANAGER::Update(void)
{

}