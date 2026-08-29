# Vec free functions

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `vec.h`  
**Documented overloads:** 3

## Functions

### compose_transform

~~~cpp
Transform compose_transform(const Transform &parent, const Transform &local)
~~~

Composes a parent world transform and child local transform. Position is rotated around the parent's top-left origin, positions and angles are combined, SDL flip flags are XOR-combined, and local size is preserved.

---

### relative_transform

~~~cpp
Transform relative_transform(const Transform &parent, const Transform &world)
~~~

Performs the inverse hierarchy conversion, producing a local transform whose composition with `parent` recreates `world`.

---

### rotate_vector

~~~cpp
Vec rotate_vector(const Vec &value, float degrees)
~~~

Rotates a vector by a degree angle. Positive values rotate clockwise in the engine's screen-coordinate convention.
