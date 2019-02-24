#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//

//＝＝＝クラス宣言＝＝＝//
class TRANSFORM
{
    public:
        D3DXVECTOR3 Position;   //位置座標
        D3DXVECTOR3 Rotation;   //向き
        D3DXVECTOR3 Scale;      //大きさ

        void MakeWorldMatrix(D3DXMATRIX& world)
        {
            //---各種宣言---//
            D3DXMATRIX mtxRotation;
            D3DXMATRIX mtxScale;
            D3DXMATRIX mtxTranslate;

            //大きさを反映
            D3DXMatrixScaling(&mtxScale, Scale.x, Scale.y, Scale.z);
            D3DXMatrixMultiply(&world, &world, &mtxScale);

            //回転を反映
            D3DXMatrixRotationYawPitchRoll(&mtxRotation, D3DXToRadian(Rotation.y), D3DXToRadian(Rotation.x), D3DXToRadian(Rotation.z));
            D3DXMatrixMultiply(&world, &world, &mtxRotation);

            //移動を反映
            D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
            D3DXMatrixMultiply(&world, &world, &mtxTranslate);
        }
};

#endif