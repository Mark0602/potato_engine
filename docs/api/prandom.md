# prandom

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `prandom.h`  
**Documented overloads:** 8

This page documents the engine-owned callables declared for `prandom`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
int damage = random_range(8, 12);
~~~

## Functions

### device

~~~cpp
rd & prandom::device()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `rd &`

This function belongs to the documented engine type. Its exact behavior, inputs, and result are described by the signature and metadata in this entry.

**Parameters:** None.

---

### engine

~~~cpp
mt & prandom::engine()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `mt &`

Performs the engine operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### random_choice

~~~cpp
T prandom::random_choice(const std::vector< T > &choices)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `T`

Produces a pseudo-random result constrained by the supplied range, collection, or weights. Ensure any referenced collection remains valid for the duration of the call.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### random_choice_weighted

~~~cpp
T prandom::random_choice_weighted(const std::vector< T > &choices, const std::vector< float > &weight)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `T`

Produces a pseudo-random result constrained by the supplied range, collection, or weights. Ensure any referenced collection remains valid for the duration of the call.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### random_choice_weighted

~~~cpp
T prandom::random_choice_weighted(std::initializer_list< T > choices, std::initializer_list< float > weights)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `T`

Produces a pseudo-random result constrained by the supplied range, collection, or weights. Ensure any referenced collection remains valid for the duration of the call.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### random_range

~~~cpp
T prandom::random_range(T min, T max)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `T`

Produces a pseudo-random result constrained by the supplied range, collection, or weights. Ensure any referenced collection remains valid for the duration of the call.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### random_range_weighted

~~~cpp
T prandom::random_range_weighted(T min, T max, const std::vector< float > &weight)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `T`

Produces a pseudo-random result constrained by the supplied range, collection, or weights. Ensure any referenced collection remains valid for the duration of the call.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### random_weighted_index

~~~cpp
std::size_t prandom::random_weighted_index(const std::vector< float > &weights, Logger *logger=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::size_t`

Produces a pseudo-random result constrained by the supplied range, collection, or weights. Ensure any referenced collection remains valid for the duration of the call.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Value supplied for the logger parameter. | — |



