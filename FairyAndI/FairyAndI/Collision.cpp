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
COLLISION::COLLISION(tstring tag, tstring layer, GAMEOBJECT* owner)
{
    Tag = tag;
    Layer = layer;
    Owner = owner;
}