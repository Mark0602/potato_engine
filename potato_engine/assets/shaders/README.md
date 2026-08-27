# Day/night and point-light shader

`day_night_light.frag.hlsl` is the editable source for Direct3D 12 and Vulkan.
Run `compile.bat` after editing it to regenerate the DXIL and SPIR-V files. The
Metal source is kept in `day_night_light.frag.msl` because SDL can compile MSL
at runtime.

The light pass is available when the GPU renderer and shader support are enabled.
A script only has to own a `light_source`:

```cpp
#include "src/light.h"

light_source lamp{{520.0f, 280.0f}, 180.0f, {255, 190, 110, 255}, 1.2f, 0.35f};

void on_start() override {
    Engine::lighting->set_time_of_day(21.5f);
    Engine::lighting->set_auto_advance(true);
    Engine::lighting->set_day_length(600.0f);
}
```

`position` and `radius` are world-space by default and follow the active
camera. Set `screen_space = true` for a light expressed in logical screen
coordinates. Up to 16 enabled lights are sent to the shader each frame.

This is a deliberately cheap 2D lighting model: unlit regions become the
ambient night color and point lights restore local brightness with a soft
falloff. It does not calculate geometry-cast silhouettes; those require an
occluder or normal map pass.
