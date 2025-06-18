struct PixelInput
{
    float4 pos : SV_Position;
    float4 col : COLOR;
};


float4 main(PixelInput input) : SV_TARGET
{
    return input.col;
}