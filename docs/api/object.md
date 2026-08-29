# Object

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `object.h`  
**Documented overloads:** 48

This page documents the engine-owned callables declared for `Object`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Object* player = new Object({0.0f, 0.0f}, {32.0f, 32.0f});
player->name = "player";
player->add_tag("controllable");
Engine::object_pool->add(player);

Object weapon(Transform{{20.0f, 8.0f}, {16.0f, 8.0f}});
weapon.set_parent(player, false); // transform is now a local offset
Transform weapon_world = weapon.get_world_transform();
~~~

## Functions

### operator=

~~~cpp
Object & Object::operator=(const Object &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Copy assignment is disabled because object address identity participates in registries and hierarchy links, and an object may own an attached script.

---

### Object

~~~cpp
Object::Object(const Object &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Copy construction is disabled. Store dynamic objects behind stable owning pointers such as `std::unique_ptr<Object>`.

---

### add_child

~~~cpp
bool Object::add_child(Object *child, bool keep_world_transform=true)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Makes `child` a direct child of this object. The relationship is non-owning. Returns `false` for a null child or an invalid cyclic relationship.

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `child` | `Object *` | Borrowed child object. | — |
| `keep_world_transform` | `bool` | Preserve the child's current world appearance. | `true` |

---

### clear_children

~~~cpp
void Object::clear_children(bool keep_world_transform=true)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Detaches every direct child without deleting it.

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `keep_world_transform` | `bool` | Preserve each child's current world appearance. | `true` |

---

### get_children

~~~cpp
const std::vector<Object *> & Object::get_children() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::vector<Object *> &`

Returns the direct, non-owning child list. Do not retain the reference beyond this object's lifetime or modify the referenced vector.

**Parameters:** None.

---

### get_local_transform

~~~cpp
Transform Object::get_local_transform() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Returns the local transform. It is identical to world space when the object has no parent.

**Parameters:** None.

---

### get_parent

~~~cpp
Object * Object::get_parent() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Object *`

Returns the borrowed parent pointer, or `nullptr` for a root object.

**Parameters:** None.

---

### get_world_transform

~~~cpp
Transform Object::get_world_transform() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Composes the complete parent chain and returns the effective world transform.

**Parameters:** None.

---

### has_parent

~~~cpp
bool Object::has_parent() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Returns whether this object currently has a parent.

**Parameters:** None.

---

### is_ancestor_of

~~~cpp
bool Object::is_ancestor_of(const Object *object) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Returns whether this object occurs in `object`'s parent chain.

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `object` | `const Object *` | Borrowed object whose ancestors are inspected. | — |

---

### remove_child

~~~cpp
bool Object::remove_child(Object *child, bool keep_world_transform=true)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Detaches a direct child without deleting it. Returns `false` when the object is null or is not a direct child.

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `child` | `Object *` | Borrowed direct child. | — |
| `keep_world_transform` | `bool` | Preserve the child's current world appearance. | `true` |

---

### set_local_transform

~~~cpp
void Object::set_local_transform(const Transform &new_transform)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Replaces the local transform. For a root object this is also its world transform.

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_transform` | `const Transform &` | New parent-local transform. | — |

---

### set_parent

~~~cpp
bool Object::set_parent(Object *new_parent, bool keep_world_transform=true)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Changes the non-owning parent relationship. Passing `nullptr` creates a root. Self-parenting and cycles are rejected without modifying the hierarchy.

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_parent` | `Object *` | Borrowed new parent, or `nullptr`. | — |
| `keep_world_transform` | `bool` | Preserve the object's current world appearance. | `true` |

---

### set_world_transform

~~~cpp
void Object::set_world_transform(const Transform &new_transform)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets world space and converts the value into current parent-local space when necessary.

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_transform` | `const Transform &` | Desired world transform. | — |

---

### ~Object

~~~cpp
virtual Object::~Object()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

This function belongs to the documented engine type. Its exact behavior, inputs, and result are described by the signature and metadata in this entry.

**Parameters:** None.

---

### add_tag

~~~cpp
void Object::add_tag(const std::string &tag)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### attach_script

~~~cpp
void Object::attach_script(script *s)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Attaches a script to this object. The script's owner pointer will be set to this object. The script will be added to Engine::object_scripts and its on_start() method will be called immediately, when this function is called. Every instance of script is responsible for cleaning up its own resources in on_destroy(). Every instance of this object is responsible for calling on_destroy() on its attached script before the script is deleted. Every instance of script is responsible for removing itself from Engine::object_scripts when it is destroyed. If you want to use a script in multiple objects, create a new instance for each object.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `s` | `script *` | Value supplied for the s parameter. | — |


---

### center_on_screen

~~~cpp
void Object::center_on_screen()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Centers the object on the screen based on the current window size. Uses Engine::window to get the current window dimensions.

**Parameters:** None.

---

### detach_script

~~~cpp
void Object::detach_script()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Detaches and deletes the script from this object, if any.

**Parameters:** None.

---

### draw

~~~cpp
virtual void Object::draw(SDL_Renderer *renderer)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Renders the object using its texture at its current pos and size. Does nothing if the texture is not loaded. Logs a warning if a logger is set.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### free

~~~cpp
void Object::free()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Releases the texture and resets state.

**Parameters:** None.

---

### get_object_pool

~~~cpp
Object_Pool * Object::get_object_pool() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Object_Pool *`

Returns the object pool that manages this object.

**Parameters:** None.

---

### get_transform

~~~cpp
Transform Object::get_transform() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Returns the local transform of the object. For a root object it is also the world transform.

**Parameters:** None.

---

### has_tag

~~~cpp
bool Object::has_tag(const std::string &tag) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### hide

~~~cpp
void Object::hide()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Hides the object by setting its visibility to false and making it input transparent.

**Parameters:** None.

---

### make_draw_command

~~~cpp
virtual Draw Object::make_draw_command() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Draw`

Creates or emits a new engine value using the supplied configuration. Determine ownership from the return type and the owning pool or service.

**Parameters:** None.

---

### Object

~~~cpp
Object::Object(float x, float y, float w, float h, float rx=0.f, float ry=0.f, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs an Object from individual floats.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `Texture *` | Pointer to a loaded Texture, or nullptr. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Optional logger. | — |


---

### Object

~~~cpp
Object::Object(float x, float y, float w, float h, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs an Object from individual floats, with default rotation and logger.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `Texture *` | Pointer to a loaded Texture, or nullptr. | — |
| `objp` | `Object_Pool *` | Optional object pool. | — |
| `l` | `Logger *` | Optional logger. | — |


---

### Object

~~~cpp
Object::Object(Transform transform, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `transform` | `Transform` | Value supplied for the transform parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |


---

### Object

~~~cpp
Object::Object(Vec p, Vec s, Vec r={0.0f, 0.0f}, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs an Object from Vec structs.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `p` | `Vec` | Top-left position. | — |
| `s` | `Vec` | Size (width, height). | — |
| `r` | `Vec` | Rotation (angle, facing direction). | — |
| `t` | `Texture *` | Pointer to a loaded Texture, or nullptr. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Optional logger. | — |


---

### on_click

~~~cpp
virtual bool Object::on_click(const Vec &mouse_pos) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Returns true if mouse_pos is within the object's bounding box (alias for on_hover).

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `mouse_pos` | `const Vec &` | Cursor position in logical coordinates. | — |


---

### on_hover

~~~cpp
virtual bool Object::on_hover(const Vec &mouse_pos) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Returns true if mouse_pos is within the object's bounding box.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `mouse_pos` | `const Vec &` | Cursor position in logical coordinates. | — |


---

### position_update

~~~cpp
void Object::position_update(const Vec &pos2)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Moves the object to the given position.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos2` | `const Vec &` | The new top-left position. | — |


---

### register_with_pool

~~~cpp
void Object::register_with_pool()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters:** None.

---

### remove_tag

~~~cpp
void Object::remove_tag(const std::string &tag)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### rotation_update

~~~cpp
void Object::rotation_update(const Vec &rotation2)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Rotates the object to the given angle and facing direction.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `rotation2` | `const Vec &` | The new rotation angle and facing direction. | — |


---

### scale_centered

~~~cpp
void Object::scale_centered(float scale_factor, bool animated=false, float anim_speed=10.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Scales the object around its center by a given factor.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### scale_centered_condition

~~~cpp
void Object::scale_centered_condition(float scale_factor, Vec original_size, bool condition, bool animated=false, float anim_speed=10.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Scales the object around its center by a given factor when the condition is met, otherwise resets to original size. Useful for hover effects or conditional scaling.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `original_size` | `Vec` | The base size to scale from / reset to. | — |


---

### set_input_transparent

~~~cpp
void Object::set_input_transparent(bool transparent)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets whether the object should ignore hover/click checks.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_logger

~~~cpp
void Object::set_logger(Logger *l)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the logger for the object.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `l` | `Logger *` | Pointer to a Logger instance, or nullptr for no logging. | — |


---

### set_object_pool

~~~cpp
void Object::set_object_pool(Object_Pool *objp)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the object pool that manages this object. Automatically adds the object to the pool if not already present.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `objp` | `Object_Pool *` | Pointer to the Object_Pool. Pass nullptr to remove from the current pool. | — |


---

### set_texture

~~~cpp
void Object::set_texture(Texture *t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the texture for the object.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `Texture *` | Pointer to a loaded Texture, or nullptr for no texture. | — |


---

### set_texture_opacity

~~~cpp
void Object::set_texture_opacity(float alpha)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Changes the opacity of the texture.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_transform

~~~cpp
void Object::set_transform(const Transform &new_transform)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the local transform of the object. For a root object it also sets world space.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_transform` | `const Transform &` | The new transform containing position, size, and rotation. | — |


---

### show

~~~cpp
void Object::show()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Shows the object by setting its visibility to true and making it respond to input.

**Parameters:** None.

---

### size_update

~~~cpp
void Object::size_update(const Vec &size2)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Resizes the object to the given size.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `size2` | `const Vec &` | The new width and height. | — |


---

### submit_draw_commands

~~~cpp
virtual void Object::submit_draw_commands(Render_Pool &render_pool)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Submits every draw command needed by this object.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `render_pool` | `Render_Pool &` | Value supplied for the render_pool parameter. | — |


---

### toggle_visibility

~~~cpp
void Object::toggle_visibility()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Toggles the visibility and input transparency of the object. If the object is currently visible, it will be hidden and made input transparent. If the object is currently hidden, it will be shown and made responsive to input.

**Parameters:** None.
