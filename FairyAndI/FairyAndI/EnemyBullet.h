#ifndef _ENEMY_BULLET_H_
#define _ENEMY_BULLET_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//＝＝＝前方宣言＝＝＝//
class SPHERE;

//＝＝＝クラス宣言＝＝＝//
class ENEMYBULLET final : public GAMEOBJECT
{
    private:
        bool Gray;
        D3DXVECTOR3 Move;
        DWORD BornTime;

        std::weak_ptr<MODEL> Model;
        std::weak_ptr<SHADER> Shader;
        SPHERE* Collision;

    public:
        ENEMYBULLET(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
        ~ENEMYBULLET(void);

        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
        void Update(void);

        void OnCollision(COLLISION*);
};

#endif