#pragma pack_matrix( row_major )

Texture2D mainTexture : register(t0);

SamplerState aSampler : register(s0);



//Make sure its an orthogonal proection
cbuffer CamData : register(b0)
{
    float4x4 View;
    float4x4 Projection;
}

cbuffer InstanceData : register(b1)
{
    float4x4 World;
    float4 cutRect;
    float texWidth;
    float texHeight;
};

//--------------------------------------------------------------------------------------

struct VS_INPUT
{
    float4 Pos : POSITION; //2D position x and z
    float2 Tex : TEXCOORD; // u v maps
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.Pos = mul(float4((float3)input.Pos, 1.0f), World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
    output.Tex = input.Tex;
    
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
    //Brain broke...

    // get the postion in UV space
    float uOffset = cutRect.x / texWidth;
    float vOffset = cutRect.y / texHeight;
    
    // get the height and width in UV space
    float tWidth = cutRect.z / texWidth;
    float tHeight = cutRect.w / texHeight;
    
    // finally  adjust to the positon of the cutout and then scale by the rects width and height
    float2 finalTex;
    finalTex.x = uOffset + (input.Tex.x * tWidth);
    finalTex.y = vOffset + (input.Tex.y * tHeight);

    return mainTexture.Sample(aSampler, finalTex);
    
}