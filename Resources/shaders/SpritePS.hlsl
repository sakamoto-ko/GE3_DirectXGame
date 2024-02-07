#include "Sprite.hlsli"

struct Material
{
    float4 color;
    float4x4 uvTransform;
};

ConstantBuffer<Material> gMaterial : register(b0);

Texture2D<float> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    float4 transfomrUV = mul(float4(input.texcoord, 0.0f, 1.0f), gMaterial.uvTransform);
    
    float4 textureColor = gTexture.Sample(gSampler, transfomrUV.xy);
    
    output.color = gMaterial.color * textureColor;
    return output;
}