struct VertexIn
{
    float3 pos : POSITION;
    float4 col : COLOR;
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
    output.col = input.col;
    return output;
}