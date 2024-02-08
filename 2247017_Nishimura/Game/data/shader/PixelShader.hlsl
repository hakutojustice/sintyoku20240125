
cbuffer ConstantBuffer : register(b0)
{
    float time;
}

struct PS_INPUT
{
    float4 Diffuse : COLOR0; // ディフューズカラー
    float4 Specular : COLOR1; // スペキュラカラー
    float4 TexCoords0_1 : TEXCOORD0; // xy:テクスチャ座標 zw:サブテクスチャ座標
    float3 VPosition : TEXCOORD1; // 座標( ビュー空間 )
    float3 VNormal : TEXCOORD2; // 法線( ビュー空間 )
#ifdef BUMPMAP
	float3 VTan            : TEXCOORD3 ;    // 接線( ビュー空間 )
	float3 VBin            : TEXCOORD4 ;    // 従法線( ビュー空間 )
#endif // BUMPMAP
    float1 Fog : TEXCOORD5; // フォグパラメータ( x )

#if SHADOWMAP
	float3 ShadowMap0Pos   : TEXCOORD6 ;	// シャドウマップ０のライト座標( x, y, z )
	float3 ShadowMap1Pos   : TEXCOORD7 ;	// シャドウマップ１のライト座標( x, y, z )
	float3 ShadowMap2Pos   : TEXCOORD8 ;	// シャドウマップ２のライト座標( x, y, z )
#endif // SHADOWMAP

    float4 Position : SV_POSITION; // 座標( プロジェクション空間 )
};

SamplerState smp : register(s0); // ディフューズマップテクスチャ
Texture2D tex : register(t0); // ディフューズマップテクスチャ


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

    //ライトの向きを設定
    float3 lightDir = { 0.5f, 2.0f, 0.5f };
    lightDir = normalize(lightDir);

    //法線情報を正規化
    input.VNormal = normalize(input.VNormal);

    //光の強さをライト方向と法線方向の内積で求める
    float bright = dot(lightDir, input.VNormal);

    //光の強さの下限を設定
    if (bright <= 0.35f)
    {
        bright = 0.35f;
    }
    
    //光の強さを段階に分ける
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

    //もとの色に光の強さをかける
    ret.col.r *= bright;
    ret.col.g *= bright;
    ret.col.b *= bright;
    
    ret.col.r = ret.col.r + time;
   
    return ret;
}