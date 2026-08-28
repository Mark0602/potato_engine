# SceneManager

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `scene.h`  
**Documented overloads:** 18

This page documents the engine-owned callables declared for `SceneManager`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
SceneManager::instance().register_scene(1, "menu");
SceneManager::instance().request_scene(1);
~~~

## Functions

### cancel_scene_request

~~~cpp
void SceneManager::cancel_scene_request()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

This function belongs to the documented engine type. Its exact behavior, inputs, and result are described by the signature and metadata in this entry.

**Parameters:** None.

---

### complete_transition

~~~cpp
void SceneManager::complete_transition(int id)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the complete transition operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### consume_scene_request

~~~cpp
bool SceneManager::consume_scene_request(int &out_id)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the consume scene request operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### current_scene

~~~cpp
int SceneManager::current_scene() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `int`

Performs the current scene operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### current_scene_name

~~~cpp
const std::string & SceneManager::current_scene_name() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Returns the name of the currently active scene. Returns an empty string if the current ID was not registered with a name.

**Parameters:** None.

---

### enqueue_load_step

~~~cpp
void SceneManager::enqueue_load_step(int scene_id, const std::string &label, std::function< bool()> step, float weight=1.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the current scene name operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### enqueue_load_task

~~~cpp
void SceneManager::enqueue_load_task(int scene_id, const std::string &label, std::function< void()> action, float weight=1.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### has_scene_request

~~~cpp
bool SceneManager::has_scene_request() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### instance

~~~cpp
static SceneManager & SceneManager::instance()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `SceneManager &`

Performs the instance operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### register_scene

~~~cpp
void SceneManager::register_scene(int id, const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Associates an integer ID with a human-readable name. Can be called multiple times to register all scenes up front.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### request_scene

~~~cpp
bool SceneManager::request_scene(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### request_scene

~~~cpp
bool SceneManager::request_scene(int id)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Requests a deferred scene transition.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### requested_scene

~~~cpp
int SceneManager::requested_scene() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `int`

Queues or records the requested engine transition. The operation may complete later during the appropriate frame phase.

**Parameters:** None.

---

### scene_name

~~~cpp
const std::string & SceneManager::scene_name(int id) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Performs the scene name operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### SceneManager

~~~cpp
SceneManager::SceneManager() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private

Constructs a SceneManager value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### set_scene

~~~cpp
void SceneManager::set_scene(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Switches the active scene by name. Does nothing if the name was never registered.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_scene

~~~cpp
void SceneManager::set_scene(int id)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Switches the active scene by numeric ID.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### take_load_tasks

~~~cpp
std::vector< Load_Task > SceneManager::take_load_tasks(int scene_id)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< Load_Task >`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.



