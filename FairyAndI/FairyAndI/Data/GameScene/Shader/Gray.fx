//�������O���[�o���錾������//
float4x4 WorldViewProjection; //���W�ϊ��s��
texture  Texture;           //�e�N�X�`��

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
    float2 Texture : TEXCOORD0;
};

//���_�V�F�[�_�̏o�͏o�͒�`
struct VERTEX_OUTPUT
{
    float4 Position : POSITION0;
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
//�����F(VERTEX_INPUT)���_���
//
//�߂�l�F(VERTEX_OUTPUT)���_���
/////////////////////////////////////////////
VERTEX_OUTPUT DefaultVertexShader(VERTEX_INPUT input)
{
    //---�e��錾---//
    VERTEX_OUTPUT output = (VERTEX_OUTPUT)0;

    //---�f�[�^�̑��---//
    output.Position = mul(float4(input.Position, 1.0F), WorldViewProjection);
    output.Texture = input.Texture;

    return output;
}

/////////////////////////////////////////////
//�֐����FDefaultPixelShader
//
//�@�\�F�ʏ�̃s�N�Z���V�F�[�_
//
//�����F(VERTEX_OUTPUT)���_���
//
//�߂�l�F(PIXEL_OUTPUT)�s�N�Z�����
/////////////////////////////////////////////
PIXEL_OUTPUT DefaultPixelShader(VERTEX_OUTPUT input)
{
    //---�e��錾---//
    PIXEL_OUTPUT output = (PIXEL_OUTPUT)0;

    //---�f�[�^�̑��---//
    output.Color = tex2D(MeshTextureSampler, input.Texture);

    return output;
}

/////////////////////////////////////////////
//�֐����FPixelToMono
//
//�@�\�F���m�N����
//
//�����F(VERTEX_OUTPUT)���_���
//
//�߂�l�F(PIXEL_OUTPUT)�s�N�Z�����
/////////////////////////////////////////////
PIXEL_OUTPUT PixelToMono(VERTEX_OUTPUT input)
{
    PIXEL_OUTPUT output = (PIXEL_OUTPUT)0;
    float4 color;

    //�e�N�X�`���̃s�N�Z���F�ɒ��_�F�����������F
    color = tex2D(MeshTextureSampler, input.Texture);

    //�e�N�X�`���̃s�N�Z���F�ɒ��_�F����������
    output.Color = dot(color, float4(0.298912F, 0.586611F, 0.114478F, 0.0F));

    //�A���t�@�l�����͌��̃e�N�X�`���ɖ߂�
    output.Color.w = color.w;

    return output;
}

//�������V�F�[�_�Ăяo��������//
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