float4 main(float2 inp : POSITION) : SV_POSITION
{
    return float4(inp, 0.0f, 1.0f);
}