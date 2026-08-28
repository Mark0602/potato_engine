# GPU_Renderer

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `render.h`  
**Documented overloads:** 11

This page documents the engine-owned callables declared for `GPU_Renderer`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Draw command;
command.transform = {{100.0f, 80.0f}, {32.0f, 32.0f}};
Engine::render_pool->submit(command);
~~~

## Functions

### ~GPU_Renderer

~~~cpp
GPU_Renderer::~GPU_Renderer()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

---

### begin_frame

~~~cpp
bool GPU_Renderer::begin_frame()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** None.

---

### device

~~~cpp
SDL_GPUDevice * GPU_Renderer::device() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `SDL_GPUDevice *`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### driver_name

~~~cpp
const char * GPU_Renderer::driver_name() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const char *`

Constructs a Draw value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### end_frame

~~~cpp
void GPU_Renderer::end_frame()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### GPU_Renderer

~~~cpp
GPU_Renderer::GPU_Renderer() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters:** None.

---

### GPU_Renderer

~~~cpp
GPU_Renderer::GPU_Renderer(const GPU_Renderer &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a GPU_Renderer value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### init

~~~cpp
bool GPU_Renderer::init(SDL_Window *window)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the init operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator=

~~~cpp
GPU_Renderer & GPU_Renderer::operator=(const GPU_Renderer &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `GPU_Renderer &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### renderer

~~~cpp
SDL_Renderer * GPU_Renderer::renderer() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `SDL_Renderer *`

Constructs a Render_Pool value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### shutdown

~~~cpp
void GPU_Renderer::shutdown()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.


