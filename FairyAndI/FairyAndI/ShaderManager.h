#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include <unordered_map>
#include "FileParameter.h"
#include "Main.h"
#include "Shader.h"

//＝＝＝クラス宣言＝＝＝//
class SHADERMANAGER
{
private:
    static std::unordered_map<tstring, std::shared_ptr<SHADER>> Shader;

    static HRESULT Create(const FILEPARAMETER&);
    static HRESULT Load(std::vector<FILEPARAMETER>&, LPCTSTR);

public:
    static HRESULT Initialize(LPCTSTR);
    static void Uninitialize(void);

    static HRESULT GetShader(LPCTSTR, std::weak_ptr<SHADER>&);

    friend SHADER;
};

#endif