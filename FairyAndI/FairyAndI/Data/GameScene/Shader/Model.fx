//�������O���[�o���錾������//
float4x4 WorldViewProjection; //���W�ϊ��s��
texture  Texture;             //�e�N�X�`��
float4   Diffuse;             //�f�B�t���[�Y�F

//�������T���v���[��`������//
//�e�N�X�`���̃T���v�����O���@
sampler MeshTextureSampler =
sampler_state
{
    Texture = <Texture>;    //�Ώۂ̃e�N�X�`��(�O������󂯎��܂�)  
    MinFilter = LINEAR;     //�k�����̃T���v�����O(LINEAR�����`�⊮)

    MagFilter = LINEAR;     //�g�厞
    MinFilter = LINEAR;     //�k����
    MipFilter = LINEAR;     //�~�b�v�}�b�v
};

//�������\���̒�`������//
//���_�V�F�[�_�̏o�͏o�͒�`
struct VERTEX_INPUT
{
    float3 Position : POSITION0;
    float3 Normal : NORMAL0;
    float2 Texture : TEXCOORD0;
};

//���_�V�F�[�_�̏o�͏o�͒�`
struct VERTEX_OUTPUT
{
    float4 Position : POSITION0;
    float4 Diffuse : COLOR0;
    float2 Texture : TEXCOORD0;
};

//�s�N�Z���V�F�[�_�o�͒�`
struct PIXEL_OUTPUT
{
    float4 Color : COLOR0;
};

//�������V�F�[�_��`������//
/////////////////////////////////////////////
//�֐����FDefaultVertexShader
//
//�@�\�F�ʏ�̒��_�V�F�[�_
//
//�����F(float3)�ʒu
//
//�߂�l�F(float4)�����̐���
/////////////////////////////////////////////
VERTEX_OUTPUT DefaultVertexShader(VERTEX_INPUT input)
{
    //---�e��錾---//
    VERTEX_OUTPUT output;

    //---�f�[�^�̑��---//
    output.Position = mul(float4(input.Position, 1.0F), WorldViewProjection);
    output.Diffuse = Diffuse;
    output.Texture = input.Texture;

    return output;
}

/////////////////////////////////////////////
//�֐����FDefaultNonTexturePixelShader
//
//�@�\�F�ʏ�̃e�N�X�`���Ȃ��s�N�Z���V�F�[�_
//
//�����F(float3)�ʒu
//
//�߂�l�F(float4)�����̐���
/////////////////////////////////////////////
PIXEL_OUTPUT DefaultNonTexturePixelShader(VERTEX_OUTPUT input)
{
    //---�e��錾---//
    PIXEL_OUTPUT output;

    //---�f�[�^�̑��---//
    output.Color = input.Diffuse;

    return output;
}

/////////////////////////////////////////////
//�֐����FNonTexturePixelShaderToMono
//
//�@�\�F���m�N���̃e�N�X�`���Ȃ��s�N�Z���V�F�[�_
//
//�����F(float3)�ʒu
//
//�߂�l�F(float4)�����̐���
/////////////////////////////////////////////
PIXEL_OUTPUT NonTexturePixelShaderToMono(VERTEX_OUTPUT input)
{
    //---�e��錾---//
    PIXEL_OUTPUT output;

    //---�f�[�^�̑��---//
    output.Color = dot(input.Diffuse, float4(0.298912F, 0.586611F, 0.114478F, 0.0F));

    return output;
}

/////////////////////////////////////////////
//�֐����FDefaultTexturePixelShader
//
//�@�\�F�ʏ�̃e�N�X�`���t���s�N�Z���V�F�[�_
//
//�����F(float3)�ʒu
//
//�߂�l�F(float4)�����̐���
/////////////////////////////////////////////
PIXEL_OUTPUT DefaultTexturePixelShader(VERTEX_OUTPUT input)
{
    //---�e��錾---//
    PIXEL_OUTPUT output;

    //---�f�[�^�̑��---//
    output.Color = tex2D(MeshTextureSampler, input.Texture);

    return output;
}

/////////////////////////////////////////////
//�֐����FTexturePixelShaderToMono
//
//�@�\�F���m�N����
//
//�����F(float3)�ʒu
//
//�߂�l�F(float4)�����̐���
/////////////////////////////////////////////
PIXEL_OUTPUT TexturePixelShaderToMono(VERTEX_OUTPUT input)
{
    PIXEL_OUTPUT output;

    //�e�N�X�`���̃s�N�Z���F�ɒ��_�F�����������F
    float4 color = tex2D(MeshTextureSampler, input.Texture);

    //�e�N�X�`���̃s�N�Z���F�ɒ��_�F����������
    output.Color = dot(color, float4(0.298912F, 0.586611F, 0.114478F, 0.0F));

    //�A���t�@�l�����͌��̃e�N�X�`���ɖ߂�
    output.Color.w = color.w;

    return output;
}

//�������V�F�[�_�Ăяo��������//
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