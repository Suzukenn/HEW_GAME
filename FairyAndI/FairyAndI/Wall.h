#ifndef _WALL_H_
#define _WALL_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Skill.h"

//＝＝＝前方宣言＝＝＝//
class OBB;

//＝＝＝クラス宣言＝＝＝//
class WALL final : public SKILL
{
    private:
        std::weak_ptr<MODEL> Model;
        OBB* Collision;

    public:
        WALL(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
        ~WALL(void);

        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
        void Update(void);

        void OnCollision(COLLISION*);
};

#endif