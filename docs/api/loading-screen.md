# Loading_Screen

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `loading_screen.h`  
**Documented overloads:** 26

This page documents the engine-owned callables declared for `Loading_Screen`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Engine::loading_screen->enqueue_step("Load level", [] { load_level(); });
Engine::loading_screen->update(delta_seconds);
~~~

## Functions

### ~Loading_Screen

~~~cpp
Loading_Screen::~Loading_Screen()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### active

~~~cpp
bool Loading_Screen::active() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### begin

~~~cpp
void Loading_Screen::begin(const std::string &title="Loading", Action on_complete={})
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the begin operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `on_complete` | `Action` | Value supplied for the on_complete parameter. | — |


---

### cancel

~~~cpp
void Loading_Screen::cancel()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### current_task

~~~cpp
const std::string & Loading_Screen::current_task() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Performs the current task operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### draw_fallback_background

~~~cpp
void Loading_Screen::draw_fallback_background()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** None.

---

### draw_progress_bar

~~~cpp
void Loading_Screen::draw_progress_bar(float value)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### draw_spinner

~~~cpp
void Loading_Screen::draw_spinner(float elapsed_seconds)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### enqueue

~~~cpp
void Loading_Screen::enqueue(const std::string &label, Action action, float weight=1.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `action` | `Action` | Value supplied for the action parameter. | — |


---

### enqueue_step

~~~cpp
void Loading_Screen::enqueue_step(const std::string &label, Step step, float weight=1.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `step` | `Step` | Value supplied for the step parameter. | — |


---

### error

~~~cpp
const std::string & Loading_Screen::error() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Performs the error operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### fail

~~~cpp
void Loading_Screen::fail(const std::string &message)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Performs the fail operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### failed

~~~cpp
bool Loading_Screen::failed() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### finish

~~~cpp
void Loading_Screen::finish()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

---

### frame_budget_ms

~~~cpp
float Loading_Screen::frame_budget_ms() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the frame budget ms operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### load_artwork

~~~cpp
bool Loading_Screen::load_artwork(const std::string &background_path, const std::string &icon_path, Vec icon_frame_size={})
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `icon_frame_size` | `Vec` | Value supplied for the icon_frame_size parameter. | — |


---

### Loading_Screen

~~~cpp
Loading_Screen::Loading_Screen(const Loading_Screen &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Loading_Screen value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Loading_Screen

~~~cpp
Loading_Screen::Loading_Screen(SDL_Renderer *renderer, Logger *logger=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Loading_Screen value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Value supplied for the logger parameter. | — |


---

### operator=

~~~cpp
Loading_Screen & Loading_Screen::operator=(const Loading_Screen &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Loading_Screen &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### pending_task_count

~~~cpp
std::size_t Loading_Screen::pending_task_count() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::size_t`

Performs the pending task count operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### progress

~~~cpp
float Loading_Screen::progress() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the progress operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### render

~~~cpp
void Loading_Screen::render(float delta_seconds)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_artwork

~~~cpp
void Loading_Screen::set_artwork(Texture *background, Texture *icon)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `background` | `Texture *` | Value supplied for the background parameter. | — |
| `icon` | `Texture *` | Value supplied for the icon parameter. | — |


---

### set_frame_budget_ms

~~~cpp
void Loading_Screen::set_frame_budget_ms(float milliseconds)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### title

~~~cpp
const std::string & Loading_Screen::title() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Performs the title operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### update

~~~cpp
void Loading_Screen::update(float delta_seconds)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.



