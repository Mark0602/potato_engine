# Draw

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `render.h`  
**Documented overloads:** 5

This page documents the engine-owned callables declared for `Draw`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Draw command;
command.transform = {{100.0f, 80.0f}, {32.0f, 32.0f}};
Engine::render_pool->submit(command);
~~~

## Functions

### Draw

~~~cpp
Draw::Draw() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Draw value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### Draw

~~~cpp
Draw::Draw(IFont *font, const std::string &text, const Transform &transform, const Color &tint, uint8_t z_index=128, float scale=1.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a text draw command with the specified font, text, transform, tint, z-index and scale.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `font` | `IFont *` | Pointer to the IFont to draw with. The font is borrowed from Asset_Pool or another owner. | — |
| `transform` | `const Transform &` | Position and optional bounds for the text. | — |
| `tint` | `const Color &` | Text color. | — |


---

### Draw

~~~cpp
Draw::Draw(Texture *texture, const Transform &transform, const Color &tint, uint8_t z_index=128)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Draw_Command with the specified texture, transform, tint, and z-index.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `texture` | `Texture *` | Pointer to the Texture to draw. | — |
| `transform` | `const Transform &` | The Transform (position, size, rotation) for the draw command. | — |
| `tint` | `const Color &` | The Color tint to apply to the texture. | — |


---

### Draw

~~~cpp
Draw::Draw(Texture *texture, const Transform &transform, uint8_t z_index)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Draw_Command with the specified texture, transform, and z-index.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `texture` | `Texture *` | Pointer to the Texture to draw. | — |
| `transform` | `const Transform &` | The Transform (position, size, rotation) for the draw command. | — |


---

### Draw

~~~cpp
Draw::Draw(Texture *texture, const Transform &transform)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Draw_Command with the specified texture and transform.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `texture` | `Texture *` | Pointer to the Texture to draw. | — |
| `transform` | `const Transform &` | The Transform (position, size, rotation) for the draw command. | — |



