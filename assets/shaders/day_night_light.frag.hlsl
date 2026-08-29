#define MAX_LIGHTS 16

struct FragmentInput
{
    // SDL's custom GPU render-state pipeline exposes non-system vertex
    // outputs as sequential TEXCOORD semantics on Direct3D 12.
    float4 color : TEXCOORD0;
    float2 uv : TEXCOORD1;
    float4 position : SV_Position;
};

// SDL_GPU render-state fragment resources use space2 for sampled textures and
// space3 for uniform buffers on Direct3D 12.
Texture2D<float4> base_texture : register(t0, space2);
SamplerState base_sampler : register(s0, space2);

cbuffer LightingUniforms : register(b0, space3)
{
    float4 viewport;                         // output px, output px, count, shadow strength
    float4 ambient;                          // night tint RGB, night brightness
    float4 cycle;                            // night amount, logical width/height, pixel-art flag
    float4 light_position_radius[MAX_LIGHTS]; // logical x/y, radius, intensity
    float4 light_color_softness[MAX_LIGHTS];  // RGB, edge softness
};

float2 pixel_art_uv(float2 uv)
{
    uint texture_width;
    uint texture_height;
    base_texture.GetDimensions(texture_width, texture_height);
    float2 texture_size = float2(texture_width, texture_height);
    float2 texel_size = 1.0f / max(texture_size, 1.0f.xx);

    // Same box-filter UV correction used by SDL's GPU pixel-art shader.
    float2 box_size = clamp(fwidth(uv) * texture_size, 1e-5f.xx, 1.0f.xx);
    float2 texel = uv * texture_size - 0.5f * box_size;
    float2 offset = smoothstep(1.0f.xx - box_size, 1.0f.xx, frac(texel));
    return (floor(texel) + 0.5f.xx + offset) * texel_size;
}

float4 main(FragmentInput input) : SV_Target0
{
    float2 sample_uv = cycle.w > 0.5f ? pixel_art_uv(input.uv) : input.uv;
    float4 base = input.color * base_texture.Sample(base_sampler, sample_uv);
    float2 logical_position = input.position.xy * cycle.yz / max(viewport.xy, 1.0f.xx);

    float darkness = saturate(cycle.x) * saturate(viewport.w);
    float3 night_light = ambient.rgb * saturate(ambient.a);
    float3 illumination = lerp(1.0f.xxx, night_light, darkness);

    uint count = min((uint)(viewport.z + 0.5f), (uint)MAX_LIGHTS);
    for (uint i = 0; i < count; ++i)
    {
        float4 light_data = light_position_radius[i];
        float4 light_color = light_color_softness[i];
        float radius = max(light_data.z, 0.001f);
        float inner_radius = radius * (1.0f - saturate(light_color.w));
        float falloff = 1.0f - smoothstep(inner_radius, radius,
                                          distance(logical_position, light_data.xy));

        // Lights are subtle during the day and fully visible at night. Areas
        // outside every light remain at the ambient level, forming soft 2D shadows.
        float visibility = lerp(0.12f, 1.0f, saturate(cycle.x));
        illumination += light_color.rgb * light_data.w * falloff * visibility * darkness;
    }

    base.rgb *= saturate(illumination);
    return base;
}
