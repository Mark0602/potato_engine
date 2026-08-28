# Render_Pool

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `render.h`  
**Documented overloads:** 7

This page documents the engine-owned callables declared for `Render_Pool`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Draw command;
command.transform = {{100.0f, 80.0f}, {32.0f, 32.0f}};
Engine::render_pool->submit(command);
~~~

## Functions

### ~Render_Pool

~~~cpp
Render_Pool::~Render_Pool() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

---

### clear

~~~cpp
void Render_Pool::clear()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Clears all draw commands from the pool. This does not delete the textures or objects; it simply clears the list of commands to be drawn.

**Parameters:** None.

---

### empty

~~~cpp
bool Render_Pool::empty() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if the render pool is empty (no draw commands).

**Parameters:** None.

---

### flush

~~~cpp
void Render_Pool::flush()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sorts the draw commands by z-index and submits them to the SDL renderer. This should be called once per frame to render all queued draw commands.

**Parameters:** None.

---

### Render_Pool

~~~cpp
Render_Pool::Render_Pool(SDL_Renderer *renderer)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Render_Pool.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### size

~~~cpp
size_t Render_Pool::size() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `size_t`

Returns the number of draw commands in the render pool.

**Parameters:** None.

---

### submit

~~~cpp
void Render_Pool::submit(const Draw &draw_command)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Submits a draw command to the render pool. If both the texture and font are null, or the command is not visible, it will be ignored.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `draw_command` | `const Draw &` | Value supplied for the draw_command parameter. | — |



