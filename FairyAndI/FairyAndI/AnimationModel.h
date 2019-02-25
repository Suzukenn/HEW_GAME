#ifndef _ANIMATION_MODEL_H_
#define _ANIMATION_MODEL_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <vector>
#include "AnimationModelHierarchy.h"
#include "Main.h"

//＝＝＝前方宣言＝＝＝//
class ANIMATIONMODELFREAM;
class ANIMATIONMODELCONTAINER;

//＝＝＝クラス宣言＝＝＝//
class ANIMATIONMODEL
{
    private:
        double PlaySpeed;                        //アニメーションスピード
        DWORD CurrentTrack;                     //現在のアニメーショントラック
        D3DXTRACK_DESC CurrentTrackDescription; //現在のアニメーションデータトラック
        UINT AnimationSetValue;                 //アニメーションセット
        D3DXMATRIX World;                       //ワールドマトリクス
        ANIMATIONMODELHIERARCHY Hierarchy;      //ヒエラルキークラス変数

        std::vector<LPD3DXANIMATIONSET> AnimationData;

        LPD3DXFRAME FrameRoot;                          //ボーン情報
        LPD3DXANIMATIONCONTROLLER AnimationController;  //アニメーションコントローラ

        HRESULT AllocateAllBoneMatrices(LPD3DXFRAME);
        HRESULT AllocateBoneMatrix(LPD3DXMESHCONTAINER);
        void DrawFrame(LPD3DXFRAME, bool);
        void SetTime(double);
        void RenderMeshContainer(LPD3DXMESHCONTAINER, LPD3DXFRAME, bool);
        void UpdateFrameMatrices(LPD3DXFRAME, LPD3DXMATRIX);

    public:
        void ChangeAnimation(DWORD);
        void Draw(D3DXMATRIX, bool);
        HRESULT Initialize(LPCTSTR, float);
        void SetSpeed(double speed) { PlaySpeed = speed; }
        void Uninitialize(void);
};

#endif