#ifndef _SQUARE_GAUGE_H_
#define _SQUARE_GAUGE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include "Main.h"
#include "Sprite.h"

//�������N���X�錾������//
class SQUAREGAUGE
{
    private:
        float Percent;
        D3DXVECTOR2 Size;
        std::array<VERTEX_2D, 4> MemoryVertex;                //���_�o�b�t�@
        std::unique_ptr<LPDIRECT3DTEXTURE9> MemoryTexture;    //�e�N�X�`���ւ̃|�C���^
        SPRITE Back;

    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, LPCTSTR, D3DXVECTOR2, D3DXVECTOR2);
        void Uninitialize(void);
        void Update(void);

        float GetPercent(void) { return Percent; }
        void SetPercent(float percent) { Percent = percent; }
};

#endif