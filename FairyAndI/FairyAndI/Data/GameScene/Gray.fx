//＝＝＝グローバル宣言＝＝＝//
float4x4 WorldViewProjection; //座標変換行列
texture  g_Texture;           //テクスチャ

//＝＝＝サンプラー定義＝＝＝//
//テクスチャのサンプリング方法
sampler MeshTextureSampler =
sampler_state
{
    Texture = < g_Texture >;//対象のテクスチャ(外部から受け取ります)  
    MinFilter = LINEAR;     //縮小時のサンプリング(LINEAR→線形補完)

    MagFilter = LINEAR;     //拡大時
    MipFilter = NONE;       //ミップマップ

    //テクスチャアドレッシングモード
    AddressU = Clamp;	//（Clanp→0～1以外の座標の時に端っこのピクセルをひきのばす）
    AddressV = Clamp;
};

//＝＝＝構造体定義＝＝＝//
//頂点シェーダの出力出力定義
struct VERTEX_INPUT
{
    float4 Position : POSITION0;
    float4 Diffuse : COLOR0;
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
    output.Position = mul(input.Position, WorldViewProjection);
    output.Diffuse = input.Diffuse;
    output.Texture = input.Texture;

    return output;
}

/////////////////////////////////////////////
//関数名：DefaultPixelShader
//
//機能：通常のピクセルシェーダ
//
//引数：(float3)位置
//
//戻り値：(float4)処理の成否
/////////////////////////////////////////////
PIXEL_OUTPUT DefaultPixelShader(VERTEX_OUTPUT input)
{
    //---各種宣言---//
    PIXEL_OUTPUT output;

    //---データの代入---//
    output.Color = tex2D(MeshTextureSampler, input.Texture) * input.Diffuse;

    return output;
}

/////////////////////////////////////////////
//関数名：PixelToMono
//
//機能：モノクロ化
//
//引数：(float3)位置
//
//戻り値：(float4)処理の成否
/////////////////////////////////////////////
PIXEL_OUTPUT PixelToMono(VERTEX_OUTPUT input)
{
    PIXEL_OUTPUT output;

    //テクスチャのピクセル色に頂点色を合成した色
    float4 color = tex2D(MeshTextureSampler, input.Texture) * input.Diffuse;
    //float4 color = float4(0.0F, 0.0F, 0.0F, 1.0F);

    //モノクロ化にするときのRGBの分担割合。
    float4 tomono = float4(0.298912F, 0.586611F, 0.114478F, 0.0F);

    //テクスチャのピクセル色に頂点色を合成する
    output.Color = dot(color, tomono);

    //アルファ値だけは元のテクスチャに戻す
    output.Color.w = color.w;

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