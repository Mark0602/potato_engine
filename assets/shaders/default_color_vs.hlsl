struct VSInput {
    float2 position : POSITION;
    float4 color    : COLOR0;
};

struct VSOutput {
    float4 position : SV_Position;
    float4 color    : COLOR0;
};

VSOutput main(VSInput i) {
    VSOutput o;
    // Nincs mátrix, NDC-ben rajzolunk (-1..1 tartomány)
    o.position = float4(i.position, 0.0, 1.0);
    o.color    = i.color;
    return o;
}