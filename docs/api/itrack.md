# ITrack

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `audio.h`  
**Documented overloads:** 7

This page documents the engine-owned callables declared for `ITrack`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Audio music;
music.load("assets/audio/theme.ogg");
music.set_loop_count(-1);
music.play();
~~~

## Functions

### ~ITrack

~~~cpp
ITrack::~ITrack()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

---

### ITrack

~~~cpp
ITrack::ITrack() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs an ITrack object with the specified track, audio, and lifetime.

**Parameters:** None.

---

### ITrack

~~~cpp
ITrack::ITrack(const ITrack &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### ITrack

~~~cpp
ITrack::ITrack(ITrack &&) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a ITrack value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### ITrack

~~~cpp
ITrack::ITrack(MIX_Track *t, Audio *a, uint32_t l)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs an ITrack object with the specified track, audio, and lifetime.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `MIX_Track *` | Pointer to the SDL_Mixer track. | — |
| `a` | `Audio *` | Pointer to the Audio instance associated with the track. | — |
| `l` | `uint32_t` | Lifetime of the track in frames, 0 for infinite. | — |


---

### operator=

~~~cpp
ITrack & ITrack::operator=(const ITrack &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `ITrack &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator=

~~~cpp
ITrack & ITrack::operator=(ITrack &&) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `ITrack &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.



