//＝＝＝グローバル宣言＝＝＝//
float4x4 WorldViewProjection; //座標変換行列
texture  Texture;             //テクスチャ
float4   Diffuse;             //ディフューズ色

//＝＝＝サンプラー定義＝＝＝//
//テクスチャのサンプリング方法
sampler MeshTextureSampler =
sampler_state
{
    Texture = <Texture>;    //対象のテクスチャ(外部から受け取ります)  
    MinFilter = LINEAR;     //縮小時のサンプリング(LINEAR→線形補完)

    MagFilter = LINEAR;     //拡大時
    MinFilter = LINEAR;     //縮小時
    MipFilter = LINEAR;     //ミップマップ
};

//＝＝＝構造体定義＝＝＝//
//頂点シェーダの出力出力定義
struct VERTEX_INPUT
{
    float3 Position : POSITION0;
    float3 Normal : NORMAL0;
    float2 Texture : TEXCOORD0;
};

//頂点シェーダの出力出力定義
struct VERTEX_OUTPUT
{
    float4 Position : POSITION0;
    float4 Diffuse : COLOR0;
    float2 Texture : TEXCOORD0;
};

//ピクセルシェーダ出力定義
struct PIXEL_OUTPUT
{
    float4 Color : COLOR0;
};

//＝＝＝シェーダ定義＝＝＝//
/////////////////////////////////////////////
//関数名：DefaultVertexShader
//
//機能：通常の頂点シェーダ
//
//引数：(float3)位置
//
//戻り値：(float4)処理の成否
/////////////////////////////////////////////
VERTEX_OUTPUT DefaultVertexShader(VERTEX_INPUT input)
{
    //---各種宣言---//
    VERTEX_OUTPUT output;

    //---データの代入---//
    output.Position = mul(float4(input.Position, 1.0F), WorldViewProjection);
    output.Diffuse = Diffuse;
    output.Texture = input.Texture;

    return output;
}

/////////////////////////////////////////////
//関数名：DefaultNonTexturePixelShader
//
//機能：通常のテクスチャなしピクセルシェーダ
//
//引数：(float3)位置
//
//戻り値：(float4)処理の成否
/////////////////////////////////////////////
PIXEL_OUTPUT DefaultNonTexturePixelShader(VERTEX_OUTPUT input)
{
    //---各種宣言---//
    PIXEL_OUTPUT output;

    //---データの代入---//
    output.Color = input.Diffuse;

    return output;
}

/////////////////////////////////////////////
//関数名：NonTexturePixelShaderToMono
//
//機能：モノクロのテクスチャなしピクセルシェーダ
//
//引数：(float3)位置
//
//戻り値：(float4)処理の成否
/////////////////////////////////////////////
PIXEL_OUTPUT NonTexturePixelShaderToMono(VERTEX_OUTPUT input)
{
    //---各種宣言---//
    PIXEL_OUTPUT output;

    //---データの代入---//
    output.Color = dot(input.Diffuse, float4(0.298912F, 0.586611F, 0.114478F, 0.0F));

    return output;
}

/////////////////////////////////////////////
//関数名：DefaultTexturePixelShader
//
//機能：通常のテクスチャ付きピクセルシェーダ
//
//引数：(float3)位置
//
//戻り値：(float4)処理の成否
/////////////////////////////////////////////
PIXEL_OUTPUT DefaultTexturePixelShader(VERTEX_OUTPUT input)
{
    //---各種宣言---//
    PIXEL_OUTPUT output;

    //---データの代入---//
    output.Color = tex2D(MeshTextureSampler, input.Texture);

    return output;
}

/////////////////////////////////////////////
//関数名：TexturePixelShaderToMono
//
//機能：モノクロ化
//
//引数：(float3)位置
//
//戻り値：(float4)処理の成否
/////////////////////////////////////////////
PIXEL_OUTPUT TexturePixelShaderToMono(VERTEX_OUTPUT input)
{
    PIXEL_OUTPUT output;

    //テクスチャのピクセル色に頂点色を合成した色
    float4 color = tex2D(MeshTextureSampler, input.Texture);

    //テクスチャのピクセル色に頂点色を合成する
    output.Color = dot(color, float4(0.298912F, 0.586611F, 0.114478F, 0.0F));

    //アルファ値だけは元のテクスチャに戻す
    output.Color.w = color.w;

    return output;
}

//＝＝＝シェーダ呼び出し＝＝＝//
technique NonTextureModel
{
    pass Pass0
    {
        VertexShader = compile vs_2_0 DefaultVertexShader();
        PixelShader = compile ps_2_0 DefaultNonTexturePixelShader();
    }

    pass Pass1
    {
        VertexShader = compile vs_2_0 DefaultVertexShader();
        PixelShader = compile ps_2_0 NonTexturePixelShaderToMono();
    }
}

technique TextureModel
{
    pass Pass0
    {
        VertexShader = compile vs_2_0 DefaultVertexShader();
        PixelShader = compile ps_2_0 DefaultTexturePixelShader();
    }

    pass Pass1
    {
        VertexShader = compile vs_2_0 DefaultVertexShader();
        PixelShader = compile ps_2_0 TexturePixelShaderToMono();
    }
}