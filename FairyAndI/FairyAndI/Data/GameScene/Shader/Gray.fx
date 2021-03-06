//＝＝＝グローバル宣言＝＝＝//
float4x4 WorldViewProjection; //座標変換行列
texture  Texture;           //テクスチャ

//＝＝＝サンプラー定義＝＝＝//
//テクスチャのサンプリング方法
sampler MeshTextureSampler =
sampler_state
{
    Texture = <Texture>;    //対象のテクスチャ(外部から受け取ります)  

    MagFilter = LINEAR;     //拡大時
    MinFilter = LINEAR;     //縮小時
};

//＝＝＝構造体定義＝＝＝//
//頂点シェーダの出力出力定義
struct VERTEX_INPUT
{
    float3 Position : POSITION0;
    float2 Texture : TEXCOORD0;
};

//頂点シェーダの出力出力定義
struct VERTEX_OUTPUT
{
    float4 Position : POSITION0;
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
//引数：(VERTEX_INPUT)頂点情報
//
//戻り値：(VERTEX_OUTPUT)頂点情報
/////////////////////////////////////////////
VERTEX_OUTPUT DefaultVertexShader(VERTEX_INPUT input)
{
    //---各種宣言---//
    VERTEX_OUTPUT output;

    //---データの代入---//
    output.Position = mul(float4(input.Position, 1.0F), WorldViewProjection);
    output.Texture = input.Texture;

    return output;
}

/////////////////////////////////////////////
//関数名：DefaultPixelShader
//
//機能：通常のピクセルシェーダ
//
//引数：(VERTEX_OUTPUT)頂点情報
//
//戻り値：(PIXEL_OUTPUT)ピクセル情報
/////////////////////////////////////////////
PIXEL_OUTPUT DefaultPixelShader(VERTEX_OUTPUT input)
{
    //---各種宣言---//
    PIXEL_OUTPUT output;

    //---データの代入---//
    output.Color = tex2D(MeshTextureSampler, input.Texture);

    if (output.Color.a <= 0.0F)
    {
        discard;
    }

    return output;
}

/////////////////////////////////////////////
//関数名：PixelToMono
//
//機能：モノクロ化
//
//引数：(VERTEX_OUTPUT)頂点情報
//
//戻り値：(PIXEL_OUTPUT)ピクセル情報
/////////////////////////////////////////////
PIXEL_OUTPUT PixelToMono(VERTEX_OUTPUT input)
{
    PIXEL_OUTPUT output;
    float4 color;

    //テクスチャのピクセル色に頂点色を合成した色
    color = tex2D(MeshTextureSampler, input.Texture);

    //テクスチャのピクセル色に頂点色を合成する
    output.Color = dot(color, float4(0.298912F, 0.586611F, 0.114478F, 0.0F));

    //アルファ値だけは元のテクスチャに戻す
    output.Color.a = color.a;

    if (output.Color.a <= 0.0F)
    {
        discard;
    }

    return output;
}

//＝＝＝シェーダ呼び出し＝＝＝//
technique Gray
{
    pass Pass0
    {
        VertexShader = compile vs_2_0 DefaultVertexShader();
        PixelShader = compile ps_2_0 DefaultPixelShader();
    }

    pass Pass1
    {
        VertexShader = compile vs_2_0 DefaultVertexShader();
        PixelShader = compile ps_2_0 PixelToMono();
    }
}