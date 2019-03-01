//�������O���[�o���錾������//
float4x4 WorldViewProjection; //���W�ϊ��s��
texture  g_Texture;           //�e�N�X�`��

//�������T���v���[��`������//
//�e�N�X�`���̃T���v�����O���@
sampler MeshTextureSampler =
sampler_state
{
    Texture = < g_Texture >;//�Ώۂ̃e�N�X�`��(�O������󂯎��܂�)  
    MinFilter = LINEAR;     //�k�����̃T���v�����O(LINEAR�����`�⊮)

    MagFilter = LINEAR;     //�g�厞
    MipFilter = NONE;       //�~�b�v�}�b�v

    //�e�N�X�`���A�h���b�V���O���[�h
    AddressU = Clamp;	//�iClanp��0�`1�ȊO�̍��W�̎��ɒ[�����̃s�N�Z�����Ђ��̂΂��j
    AddressV = Clamp;
};

//�������\���̒�`������//
//���_�V�F�[�_�̏o�͏o�͒�`
struct VERTEX_INPUT
{
    float4 Position : POSITION0;
    float4 Diffuse : COLOR0;
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
    output.Position = mul(input.Position, WorldViewProjection);
    output.Diffuse = input.Diffuse;
    output.Texture = input.Texture;

    return output;
}

/////////////////////////////////////////////
//�֐����FDefaultPixelShader
//
//�@�\�F�ʏ�̃s�N�Z���V�F�[�_
//
//�����F(float3)�ʒu
//
//�߂�l�F(float4)�����̐���
/////////////////////////////////////////////
PIXEL_OUTPUT DefaultPixelShader(VERTEX_OUTPUT input)
{
    //---�e��錾---//
    PIXEL_OUTPUT output;

    //---�f�[�^�̑��---//
    output.Color = tex2D(MeshTextureSampler, input.Texture) * input.Diffuse;

    return output;
}

/////////////////////////////////////////////
//�֐����FPixelToMono
//
//�@�\�F���m�N����
//
//�����F(float3)�ʒu
//
//�߂�l�F(float4)�����̐���
/////////////////////////////////////////////
PIXEL_OUTPUT PixelToMono(VERTEX_OUTPUT input)
{
    PIXEL_OUTPUT output;

    //�e�N�X�`���̃s�N�Z���F�ɒ��_�F�����������F
    float4 color = tex2D(MeshTextureSampler, input.Texture) * input.Diffuse;
    //float4 color = float4(0.0F, 0.0F, 0.0F, 1.0F);

    //���m�N�����ɂ���Ƃ���RGB�̕��S�����B
    float4 tomono = float4(0.298912F, 0.586611F, 0.114478F, 0.0F);

    //�e�N�X�`���̃s�N�Z���F�ɒ��_�F����������
    output.Color = dot(color, tomono);

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