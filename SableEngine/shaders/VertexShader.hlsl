struct VertexIn
{
    float3 pos : POSITION;
    float3 col : COLOR;
};

struct VertexOut
{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
};


VertexOut main(VertexIn input)
{
    VertexOut output;
    output.pos = float4(input.pos, 1.0f);
    output.col = float4(input.col, 1.0f);
    return output;
}