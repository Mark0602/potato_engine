# Timer

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `timer.h`  
**Documented overloads:** 9

This page documents the engine-owned callables declared for `Timer`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Timer cooldown;
cooldown.start(1.0f);
cooldown.tick(delta_seconds);
~~~

## Functions

### elapsed

~~~cpp
float Timer::elapsed() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** None.

---

### is_just_done

~~~cpp
bool Timer::is_just_done() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### is_running

~~~cpp
bool Timer::is_running() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### progress

~~~cpp
float Timer::progress() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the progress operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### remaining

~~~cpp
float Timer::remaining() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the remaining operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### start

~~~cpp
void Timer::start(float duration, std::function< void()> callback=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Starts (or restarts) the timer.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### stop

~~~cpp
void Timer::stop()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Stops and resets the timer without invoking the callback.

**Parameters:** None.

---

### tick

~~~cpp
void Timer::tick(float delta_time)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Advances the timer. Call every frame from on_update(delta_time).

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Timer

~~~cpp
Timer::Timer() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters:** None.


