//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Collision.h"

/////////////////////////////////////////////
//�֐����FCOLLISION
//
//�@�\�F�R���W�����̏�����
//
//�����F(tstring)����^�O,(tstring)�������C���[,(GAMEOBJECT*)������
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
COLLISION::COLLISION(tstring layer, GAMEOBJECT* owner)
{
    Layer = layer;
    Owner = owner;
}