#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//

//�������N���X�錾������//
class TRANSFORM
{
    public:
        D3DXVECTOR3 Position;   //�ʒu���W
        D3DXVECTOR3 Rotation;   //����
        D3DXVECTOR3 Scale;      //�傫��

        void MakeWorldMatrix(D3DXMATRIX& world)
        {
            //---�e��錾---//
            D3DXMATRIX mtxRotation;
            D3DXMATRIX mtxScale;
            D3DXMATRIX mtxTranslate;

            //�傫���𔽉f
            D3DXMatrixScaling(&mtxScale, Scale.x, Scale.y, Scale.z);
            D3DXMatrixMultiply(&world, &world, &mtxScale);

            //��]�𔽉f
            D3DXMatrixRotationYawPitchRoll(&mtxRotation, D3DXToRadian(Rotation.y), D3DXToRadian(Rotation.x), D3DXToRadian(Rotation.z));
            D3DXMatrixMultiply(&world, &world, &mtxRotation);

            //�ړ��𔽉f
            D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
            D3DXMatrixMultiply(&world, &world, &mtxTranslate);
        }
};

#endif