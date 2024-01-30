
cbuffer ConstantBuffer : register(b0)
{
    float time;
}

struct PS_INPUT
{
    float4 Diffuse : COLOR0; // �f�B�t���[�Y�J���[
    float4 Specular : COLOR1; // �X�y�L�����J���[
    float4 TexCoords0_1 : TEXCOORD0; // xy:�e�N�X�`�����W zw:�T�u�e�N�X�`�����W
    float3 VPosition : TEXCOORD1; // ���W( �r���[��� )
    float3 VNormal : TEXCOORD2; // �@��( �r���[��� )
#ifdef BUMPMAP
	float3 VTan            : TEXCOORD3 ;    // �ڐ�( �r���[��� )
	float3 VBin            : TEXCOORD4 ;    // �]�@��( �r���[��� )
#endif // BUMPMAP
    float1 Fog : TEXCOORD5; // �t�H�O�p�����[�^( x )

#if SHADOWMAP
	float3 ShadowMap0Pos   : TEXCOORD6 ;	// �V���h�E�}�b�v�O�̃��C�g���W( x, y, z )
	float3 ShadowMap1Pos   : TEXCOORD7 ;	// �V���h�E�}�b�v�P�̃��C�g���W( x, y, z )
	float3 ShadowMap2Pos   : TEXCOORD8 ;	// �V���h�E�}�b�v�Q�̃��C�g���W( x, y, z )
#endif // SHADOWMAP

    float4 Position : SV_POSITION; // ���W( �v���W�F�N�V������� )
};

SamplerState smp : register(s0); // �f�B�t���[�Y�}�b�v�e�N�X�`��
Texture2D tex : register(t0); // �f�B�t���[�Y�}�b�v�e�N�X�`��


struct PS_OUTPUT
{
    float4 col : SV_TARGET0;
    float4 depth : SV_TARGET1;
    float4 norm : SV_TARGET2;
};

PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT ret;
    ret.depth = input.Position.zwyx;
    ret.col = input.Diffuse * tex.Sample(smp, input.TexCoords0_1.xy);

    //���C�g�̌�����ݒ�
    float3 lightDir = { 0.5f, 2.0f, 0.5f };
    lightDir = normalize(lightDir);

    //�@�����𐳋K��
    input.VNormal = normalize(input.VNormal);

    //���̋��������C�g�����Ɩ@�������̓��ςŋ��߂�
    float bright = dot(lightDir, input.VNormal);

    //���̋����̉�����ݒ�
    if (bright <= 0.35f)
    {
        bright = 0.35f;
    }
    
    //���̋�����i�K�ɕ�����
    if (bright > 0.8f)
    {
        bright = 1.0f;
    }
    else if (bright > 0.6f)
    {
        bright = 0.8f;
    }
    else if (bright > 0.4f)
    {
        bright = 0.6f;
    }
    else
    {
        bright = 0.4f;
    }

    //���Ƃ̐F�Ɍ��̋�����������
    ret.col.r *= bright;
    ret.col.g *= bright;
    ret.col.b *= bright;
    
    ret.col.r = ret.col.r + time;
   
    return ret;
}