# Camera_Pool

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `camera.h`  
**Documented overloads:** 15

This page documents the engine-owned callables declared for `Camera_Pool`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Camera* camera = Engine::camera_pool->create("gameplay");
camera->set_position({320.0f, 180.0f});
camera->set_zoom(2.0f);
~~~

## Functions

### ~Camera_Pool

~~~cpp
Camera_Pool::~Camera_Pool() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### active_camera

~~~cpp
Camera * Camera_Pool::active_camera()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Camera *`

Returns the camera currently used by the render pipeline.

**Parameters:** None.

---

### active_camera

~~~cpp
const Camera * Camera_Pool::active_camera() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const Camera *`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### Camera_Pool

~~~cpp
Camera_Pool::Camera_Pool()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Creates the pool and the default main_cam.

**Parameters:** None.

---

### Camera_Pool

~~~cpp
Camera_Pool::Camera_Pool(const Camera_Pool &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Camera value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### clear

~~~cpp
void Camera_Pool::clear()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Deletes every non-main camera and makes main_cam active again.

**Parameters:** None.

---

### create

~~~cpp
Camera * Camera_Pool::create(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Camera *`

Creates a camera with the given name.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get

~~~cpp
Camera * Camera_Pool::get(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Camera *`

Finds a camera by name.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get

~~~cpp
const Camera * Camera_Pool::get(const std::string &name) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const Camera *`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### main_camera

~~~cpp
Camera * Camera_Pool::main_camera()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Camera *`

Returns the always-present default camera.

**Parameters:** None.

---

### main_camera

~~~cpp
const Camera * Camera_Pool::main_camera() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const Camera *`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### operator=

~~~cpp
Camera_Pool & Camera_Pool::operator=(const Camera_Pool &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Camera_Pool &`

Performs the move operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### remove

~~~cpp
bool Camera_Pool::remove(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Removes a camera from the pool. main_cam is protected and will never be removed by this function.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_active

~~~cpp
bool Camera_Pool::set_active(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Makes an existing camera the active render camera.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### size

~~~cpp
size_t Camera_Pool::size() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `size_t`

Returns how many cameras are owned by the pool.

**Parameters:** None.


