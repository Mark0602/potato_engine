# Gameplay and Scenes API

**Engine version:** Potato Engine 1.0.0  
**Language:** C++

This reference lists every engine-owned function overload declared in the covered headers. Signatures preserve parameter types, names, default values, qualifiers, and namespaces from the source. Access labels identify members that are not part of the public calling surface.

## Detailed workflow example

~~~cpp
class PlayerController final : public script {
public:
    void on_start() override {
        owner->add_tag("player");
    }

    void on_update(float delta_time) override {
        Vec movement{Input::axis("move_x"), Input::axis("move_y")};
        owner->position_update(normalize(movement) * 180.0f * delta_time);
    }
};

REGISTER_SCRIPT(PlayerController);
SceneManager::instance().register_scene(1, "gameplay");
SceneManager::instance().request_scene(1);
~~~

## animations.h

---

### add

~~~cpp
void AnimGroup::add(Anim a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds an Anim to the group.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `Anim` | The Anim to add to the group. | — |

---

### add

~~~cpp
void StaggeredSlideIn::add(Object *obj, Vec target_pos, Vec offset, float dur, float delay, std::function< float(float)> ease=Ease::out_back)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `obj` | `Object *` | Value supplied for the obj parameter. | — |
| `target_pos` | `Vec` | Value supplied for the target_pos parameter. | — |
| `offset` | `Vec` | Value supplied for the offset parameter. | — |
| `dur` | `float` | Value supplied for the dur parameter. | — |
| `delay` | `float` | Value supplied for the delay parameter. | — |
| `ease` | `std::function< float(float)>` | Value supplied for the ease parameter. | `Ease::out_back` |

---

### in_out_quad

~~~cpp
float Ease::in_out_quad(float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the in out quad operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `float` | Value supplied for the t parameter. | — |

---

### in_quad

~~~cpp
float Ease::in_quad(float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the in quad operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `float` | Value supplied for the t parameter. | — |

---

### is_running

~~~cpp
bool Anim::is_running() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### is_running

~~~cpp
bool AnimGroup::is_running() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### is_running

~~~cpp
bool StaggeredSlideIn::is_running() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### linear

~~~cpp
float Ease::linear(float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the linear operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `float` | Value supplied for the t parameter. | — |

---

### make_fade_in

~~~cpp
Anim make_fade_in(Object *obj, float dur, std::function< float(float)> ease=Ease::out_quad, std::function< void()> on_done=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Anim`

Creates an Anim that fades an object in. The object's opacity will be increased from 0 to 1 over the specified duration.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `obj` | `Object *` | Pointer to the Object to animate. | — |
| `dur` | `float` | Duration of the animation in seconds. | — |
| `ease` | `std::function< float(float)>` | Easing function to use for the animation. Defaults to Ease::out_quad. | `Ease::out_quad` |
| `on_done` | `std::function< void()>` | Optional callback to invoke when the animation is complete. | — |

---

### make_fade_out

~~~cpp
Anim make_fade_out(Object *obj, float dur, std::function< float(float)> ease=Ease::in_quad, std::function< void()> on_done=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Anim`

Creates an Anim that fades an object out and hides it. The object's opacity will be reduced from 1 to 0 over the specified duration. After the animation completes, the object will be hidden and its opacity will be reset to 1.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `obj` | `Object *` | Pointer to the Object to animate. | — |
| `dur` | `float` | Duration of the animation in seconds. | — |
| `ease` | `std::function< float(float)>` | Easing function to use for the animation. Defaults to Ease::in_quad. | `Ease::in_quad` |
| `on_done` | `std::function< void()>` | Optional callback to invoke when the animation is complete. | — |

---

### make_slide_in

~~~cpp
AnimGroup make_slide_in(Object *obj, Vec target_pos, Vec offset, float dur, std::function< float(float)> ease=Ease::out_back, std::function< void()> on_done=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `AnimGroup`

Creates an AnimGroup that slides an object into view and fades it in. The object will be moved from (target_pos + offset) to target_pos over the specified duration, and its opacity will be increased from 0 to 1. After the animation completes, the object will be fully visible and interactive.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `obj` | `Object *` | Pointer to the Object to animate. | — |
| `target_pos` | `Vec` | The final position of the object after the slide-in animation. | — |
| `offset` | `Vec` | The offset to apply to the target position for the starting position of the slide-in effect. | — |
| `dur` | `float` | Duration of the animation in seconds. | — |
| `ease` | `std::function< float(float)>` | Easing function to use for the animation. Defaults to Ease::out_back. | `Ease::out_back` |
| `on_done` | `std::function< void()>` | Optional callback to invoke when the animation is complete. | — |

---

### make_slide_out

~~~cpp
AnimGroup make_slide_out(Object *obj, Vec offset, float dur, std::function< float(float)> ease=Ease::in_quad, std::function< void()> on_done=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `AnimGroup`

Creates an AnimGroup that slides an object out of view and fades it out. The object will be moved to (current position + offset) over the specified duration, and its opacity will be reduced to 0. After the animation completes, the object will be hidden.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `obj` | `Object *` | Pointer to the Object to animate. | — |
| `offset` | `Vec` | The offset to apply to the object's current position for the slide-out effect. | — |
| `dur` | `float` | Duration of the animation in seconds. | — |
| `ease` | `std::function< float(float)>` | Easing function to use for the animation. Defaults to Ease::in_quad. | `Ease::in_quad` |
| `on_done` | `std::function< void()>` | Optional callback to invoke when the animation is complete. | — |

---

### out_back

~~~cpp
float Ease::out_back(float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Easing function that creates a "back" effect, where the animation overshoots and then returns to the target value. This function is useful for creating animations that have a sense of elasticity or bounce.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `float` | A normalized time value between 0 and 1, representing the progress of the animation. | — |

---

### out_cubic

~~~cpp
float Ease::out_cubic(float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Creates or emits a new engine value using the supplied configuration. Determine ownership from the return type and the owning pool or service.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `float` | Value supplied for the t parameter. | — |

---

### out_elastic

~~~cpp
float Ease::out_elastic(float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Easing function that creates an "elastic" effect, where the animation oscillates before settling. This function is useful for creating animations that have a spring-like or bouncy behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `float` | A normalized time value between 0 and 1, representing the progress of the animation. | — |

---

### out_quad

~~~cpp
float Ease::out_quad(float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the out elastic operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `float` | Value supplied for the t parameter. | — |

---

### progress

~~~cpp
float Anim::progress() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the progress operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### start

~~~cpp
void Anim::start(float dur, float f, float t, std::function< float(float)> ease, std::function< void(float)> apply_fn, std::function< void()> done_fn=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `dur` | `float` | Value supplied for the dur parameter. | — |
| `f` | `float` | Value supplied for the f parameter. | — |
| `t` | `float` | Value supplied for the t parameter. | — |
| `ease` | `std::function< float(float)>` | Value supplied for the ease parameter. | — |
| `apply_fn` | `std::function< void(float)>` | Value supplied for the apply_fn parameter. | — |
| `done_fn` | `std::function< void()>` | Value supplied for the done_fn parameter. | — |

---

### start

~~~cpp
void StaggeredSlideIn::start()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters:** None.

---

### tick

~~~cpp
void Anim::tick(float dt)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `dt` | `float` | Value supplied for the dt parameter. | — |

---

### tick

~~~cpp
void AnimGroup::tick(float dt)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Ticks all Anim objects in the group by the specified delta time. If all Anim objects have completed, the on_done callback will be invoked.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `dt` | `float` | The delta time to tick the animations by, in seconds. | — |

---

### tick

~~~cpp
void StaggeredSlideIn::tick(float dt)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `dt` | `float` | Value supplied for the dt parameter. | — |

---

### Header usage example

~~~cpp
Anim fade;
fade.start(
    0.25f,
    0.0f,
    1.0f,
    Ease::out_quad,
    [&label](float alpha) { label.set_texture_opacity(alpha); }
);
fade.tick(delta_seconds);
~~~

## object.h

---

### ~Object

~~~cpp
virtual Object::~Object()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

This overload performs the operation identified by its signature. Review its parameter and return metadata below, and call it only in the lifecycle phase required by the owning component.

**Parameters:** None.

---

### add

~~~cpp
void Object_Pool::add(Object *obj)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds an object to the pool.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `obj` | `Object *` | Pointer to the Object to add. | — |

---

### add_tag

~~~cpp
void Object::add_tag(const std::string &tag)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tag` | `const std::string &` | Value supplied for the tag parameter. | — |

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

### Button

~~~cpp
Button::Button() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters:** None.

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

### configure_as_ui

~~~cpp
void UI_Object::configure_as_ui()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Performs the center on screen operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

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

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `renderer` | `SDL_Renderer *` | The SDL renderer to draw with. | — |

---

### fill_transform

~~~cpp
Transform Progress_Bar::fill_transform() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### find_all_by_tag

~~~cpp
std::vector< Object * > Object_Pool::find_all_by_tag(const std::string &tag) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< Object * >`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tag` | `const std::string &` | Value supplied for the tag parameter. | — |

---

### find_by_name

~~~cpp
Object * Object_Pool::find_by_name(const std::string &name) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Object *`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `name` | `const std::string &` | Value supplied for the name parameter. | — |

---

### find_by_tag

~~~cpp
Object * Object_Pool::find_by_tag(const std::string &tag) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Object *`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tag` | `const std::string &` | Value supplied for the tag parameter. | — |

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

### get_all

~~~cpp
std::vector< Object * > Object_Pool::get_all() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< Object * >`

Returns a vector of all objects in the pool.

**Parameters:** None.

---

### get_font

~~~cpp
IFont * UI_Object::get_font() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `IFont *`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

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

Returns the current transform of the object.

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

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tag` | `const std::string &` | Value supplied for the tag parameter. | — |

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

### is_interactive

~~~cpp
bool UI_Object::is_interactive() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

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

### normalized_value

~~~cpp
float UI_Value::normalized_value() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Computes the named mathematical result from the supplied values without intentionally changing them. Units and coordinate conventions follow the parameter types and surrounding API.

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
| `x` | `float` | Left edge in logical pixels. | — |
| `y` | `float` | Top edge in logical pixels. | — |
| `w` | `float` | Width in logical pixels. | — |
| `h` | `float` | Height in logical pixels. | — |
| `rx` | `float` | Rotation angle in degrees (default 0). | — |
| `ry` | `float` | Facing direction (not implemented yet, default 0). | — |
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
| `x` | `float` | Left edge in logical pixels. | — |
| `y` | `float` | Top edge in logical pixels. | — |
| `w` | `float` | Width in logical pixels. | — |
| `h` | `float` | Height in logical pixels. | — |
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

### Object_Pool

~~~cpp
Object_Pool::Object_Pool() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### on_click

~~~cpp
bool Button::on_click(const Vec &mouse_pos) const override
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

### on_click

~~~cpp
bool UI_Object::on_click(const Vec &mouse_pos) const override
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
bool Button::on_hover(const Vec &mouse_pos) const override
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

### on_hover

~~~cpp
bool UI_Object::on_hover(const Vec &mouse_pos) const override
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

### operator=

~~~cpp
UI_Object & UI_Object::operator=(const UI_Object &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `UI_Object &`

Handles an engine lifecycle callback or input event. Override or call it only at the event-processing phase described by the owning type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

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

### Progress_Bar

~~~cpp
Progress_Bar::Progress_Bar()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Performs the position update operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### Progress_Bar

~~~cpp
Progress_Bar::Progress_Bar(float x, float y, float w, float h, float minimum=0.0f, float maximum=1.0f, float initial_value=0.0f, UI_Orientation direction=UI_Orientation::Horizontal, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Progress_Bar value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `x` | `float` | Value supplied for the x parameter. | — |
| `y` | `float` | Value supplied for the y parameter. | — |
| `w` | `float` | Value supplied for the w parameter. | — |
| `h` | `float` | Value supplied for the h parameter. | — |
| `minimum` | `float` | Value supplied for the minimum parameter. | — |
| `maximum` | `float` | Value supplied for the maximum parameter. | — |
| `initial_value` | `float` | Value supplied for the initial_value parameter. | — |
| `direction` | `UI_Orientation` | Value supplied for the direction parameter. | `UI_Orientation::Horizontal` |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |

---

### Progress_Bar

~~~cpp
Progress_Bar::Progress_Bar(Vec p, Vec s, float minimum=0.0f, float maximum=1.0f, float initial_value=0.0f, UI_Orientation direction=UI_Orientation::Horizontal, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Progress_Bar value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `p` | `Vec` | Value supplied for the p parameter. | — |
| `s` | `Vec` | Value supplied for the s parameter. | — |
| `minimum` | `float` | Value supplied for the minimum parameter. | — |
| `maximum` | `float` | Value supplied for the maximum parameter. | — |
| `initial_value` | `float` | Value supplied for the initial_value parameter. | — |
| `direction` | `UI_Orientation` | Value supplied for the direction parameter. | `UI_Orientation::Horizontal` |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |

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

### remove

~~~cpp
void Object_Pool::remove(Object *obj)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes an object from the pool.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `obj` | `Object *` | Pointer to the Object to remove. | — |

---

### remove_tag

~~~cpp
void Object::remove_tag(const std::string &tag)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tag` | `const std::string &` | Value supplied for the tag parameter. | — |

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

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `scale_factor` | `float` | The multiplier to apply to the current size. | — |
| `animated` | `bool` | If true, lerp smoothly towards the scaled size. | — |
| `anim_speed` | `float` | Lerp speed in units/sec. Default 10.0f. | — |

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
| `scale_factor` | `float` | The target scale multiplier (e.g. 1.1f = 10% larger). | — |
| `original_size` | `Vec` | The base size to scale from / reset to. | — |
| `condition` | `bool` | If true, scale up; if false, reset to original. | — |
| `animated` | `bool` | If true, lerp smoothly towards the target size each frame. | — |
| `anim_speed` | `float` | How fast the animation plays (lerp units/sec). Default 10.0f. | — |

---

### set_checked

~~~cpp
void Toggle::set_checked(bool value)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the rotation update operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `value` | `bool` | Value supplied for the value parameter. | — |

---

### set_enabled

~~~cpp
void UI_Object::set_enabled(bool value)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `value` | `bool` | Value supplied for the value parameter. | — |

---

### set_font

~~~cpp
void UI_Object::set_font(IFont *font)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `font` | `IFont *` | Value supplied for the font parameter. | — |

---

### set_input_transparent

~~~cpp
void Object::set_input_transparent(bool transparent)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets whether the object should ignore hover/click checks.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `transparent` | `bool` | If true, the object will not respond to hover/click events. | — |

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

### set_range

~~~cpp
void UI_Value::set_range(float minimum, float maximum)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `minimum` | `float` | Value supplied for the minimum parameter. | — |
| `maximum` | `float` | Value supplied for the maximum parameter. | — |

---

### set_step

~~~cpp
void UI_Value::set_step(float value_step)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `value_step` | `float` | Value supplied for the value_step parameter. | — |

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

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `alpha` | `float` | New opacity in the range [0.0, 1.0]. | — |

---

### set_transform

~~~cpp
void Object::set_transform(const Transform &new_transform)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the transform of the object.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_transform` | `const Transform &` | The new transform containing position, size, and rotation. | — |

---

### set_value

~~~cpp
bool UI_Value::set_value(float new_value)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_value` | `float` | Value supplied for the new_value parameter. | — |

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

### Slider

~~~cpp
Slider::Slider()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters:** None.

---

### Slider

~~~cpp
Slider::Slider(float x, float y, float w, float h, float minimum=0.0f, float maximum=1.0f, float initial_value=0.0f, UI_Orientation direction=UI_Orientation::Horizontal, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr, float value_step=0.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Slider value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `x` | `float` | Value supplied for the x parameter. | — |
| `y` | `float` | Value supplied for the y parameter. | — |
| `w` | `float` | Value supplied for the w parameter. | — |
| `h` | `float` | Value supplied for the h parameter. | — |
| `minimum` | `float` | Value supplied for the minimum parameter. | — |
| `maximum` | `float` | Value supplied for the maximum parameter. | — |
| `initial_value` | `float` | Value supplied for the initial_value parameter. | — |
| `direction` | `UI_Orientation` | Value supplied for the direction parameter. | `UI_Orientation::Horizontal` |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |
| `value_step` | `float` | Value supplied for the value_step parameter. | — |

---

### Slider

~~~cpp
Slider::Slider(Vec p, Vec s, float minimum=0.0f, float maximum=1.0f, float initial_value=0.0f, UI_Orientation direction=UI_Orientation::Horizontal, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr, float value_step=0.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Slider value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `p` | `Vec` | Value supplied for the p parameter. | — |
| `s` | `Vec` | Value supplied for the s parameter. | — |
| `minimum` | `float` | Value supplied for the minimum parameter. | — |
| `maximum` | `float` | Value supplied for the maximum parameter. | — |
| `initial_value` | `float` | Value supplied for the initial_value parameter. | — |
| `direction` | `UI_Orientation` | Value supplied for the direction parameter. | `UI_Orientation::Horizontal` |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |
| `value_step` | `float` | Value supplied for the value_step parameter. | — |

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

### thumb_center

~~~cpp
Vec Slider::thumb_center() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters:** None.

---

### thumb_transform

~~~cpp
Transform Slider::thumb_transform(Vec thumb_size) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Performs the thumb transform operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `thumb_size` | `Vec` | Value supplied for the thumb_size parameter. | — |

---

### Toggle

~~~cpp
Toggle::Toggle()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Toggle value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### Toggle

~~~cpp
Toggle::Toggle(float x, float y, float w, float h, bool initial_state=false, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Toggle value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `x` | `float` | Value supplied for the x parameter. | — |
| `y` | `float` | Value supplied for the y parameter. | — |
| `w` | `float` | Value supplied for the w parameter. | — |
| `h` | `float` | Value supplied for the h parameter. | — |
| `initial_state` | `bool` | Value supplied for the initial_state parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |

---

### Toggle

~~~cpp
Toggle::Toggle(Vec p, Vec s, bool initial_state=false, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Toggle value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `p` | `Vec` | Value supplied for the p parameter. | — |
| `s` | `Vec` | Value supplied for the s parameter. | — |
| `initial_state` | `bool` | Value supplied for the initial_state parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |

---

### toggle_at

~~~cpp
bool Toggle::toggle_at(const Vec &pointer_pos)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the toggle at operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pointer_pos` | `const Vec &` | Value supplied for the pointer_pos parameter. | — |

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

---

### UI_Object

~~~cpp
UI_Object::UI_Object()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Performs the toggle visibility operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### UI_Object

~~~cpp
UI_Object::UI_Object()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### UI_Object

~~~cpp
UI_Object::UI_Object(const UI_Object &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### UI_Object

~~~cpp
UI_Object::UI_Object(const UI_Object &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### UI_Object

~~~cpp
UI_Object::UI_Object(float x, float y, float w, float h, float rx, float ry=0.0f, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `x` | `float` | Value supplied for the x parameter. | — |
| `y` | `float` | Value supplied for the y parameter. | — |
| `w` | `float` | Value supplied for the w parameter. | — |
| `h` | `float` | Value supplied for the h parameter. | — |
| `rx` | `float` | Value supplied for the rx parameter. | — |
| `ry` | `float` | Value supplied for the ry parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |

---

### UI_Object

~~~cpp
UI_Object::UI_Object(float x, float y, float w, float h, float rx, float ry=0.0f, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `x` | `float` | Value supplied for the x parameter. | — |
| `y` | `float` | Value supplied for the y parameter. | — |
| `w` | `float` | Value supplied for the w parameter. | — |
| `h` | `float` | Value supplied for the h parameter. | — |
| `rx` | `float` | Value supplied for the rx parameter. | — |
| `ry` | `float` | Value supplied for the ry parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |

---

### UI_Object

~~~cpp
UI_Object::UI_Object(float x, float y, float w, float h, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `x` | `float` | Value supplied for the x parameter. | — |
| `y` | `float` | Value supplied for the y parameter. | — |
| `w` | `float` | Value supplied for the w parameter. | — |
| `h` | `float` | Value supplied for the h parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |

---

### UI_Object

~~~cpp
UI_Object::UI_Object(float x, float y, float w, float h, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `x` | `float` | Value supplied for the x parameter. | — |
| `y` | `float` | Value supplied for the y parameter. | — |
| `w` | `float` | Value supplied for the w parameter. | — |
| `h` | `float` | Value supplied for the h parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |

---

### UI_Object

~~~cpp
UI_Object::UI_Object(Transform transform, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `transform` | `Transform` | Value supplied for the transform parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |

---

### UI_Object

~~~cpp
UI_Object::UI_Object(Transform transform, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `transform` | `Transform` | Value supplied for the transform parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |

---

### UI_Object

~~~cpp
UI_Object::UI_Object(Vec p, Vec s, Vec r={0.0f, 0.0f}, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `p` | `Vec` | Value supplied for the p parameter. | — |
| `s` | `Vec` | Value supplied for the s parameter. | — |
| `r` | `Vec` | Value supplied for the r parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |

---

### UI_Object

~~~cpp
UI_Object::UI_Object(Vec p, Vec s, Vec r={0.0f, 0.0f}, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `p` | `Vec` | Value supplied for the p parameter. | — |
| `s` | `Vec` | Value supplied for the s parameter. | — |
| `r` | `Vec` | Value supplied for the r parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |

---

### UI_Value

~~~cpp
UI_Value::UI_Value() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Value value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### UI_Value

~~~cpp
UI_Value::UI_Value(float minimum, float maximum, float initial_value, float value_step=0.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Value value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `minimum` | `float` | Value supplied for the minimum parameter. | — |
| `maximum` | `float` | Value supplied for the maximum parameter. | — |
| `initial_value` | `float` | Value supplied for the initial_value parameter. | — |
| `value_step` | `float` | Value supplied for the value_step parameter. | — |

---

### update_from_pointer

~~~cpp
bool Slider::update_from_pointer(const Vec &pointer_pos)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pointer_pos` | `const Vec &` | Value supplied for the pointer_pos parameter. | — |

---

### value_at

~~~cpp
float Slider::value_at(const Vec &pointer_pos) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the value at operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pointer_pos` | `const Vec &` | Value supplied for the pointer_pos parameter. | — |

---

### Header usage example

~~~cpp
Object* player = new Object({0.0f, 0.0f}, {32.0f, 32.0f});
player->name = "player";
player->add_tag("controllable");
Engine::object_pool->add(player);
~~~

## entity.h

---

### ~Entity

~~~cpp
Entity::~Entity()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

This overload performs the operation identified by its signature. Review its parameter and return metadata below, and call it only in the lifecycle phase required by the owning component.

**Parameters:** None.

---

### activate

~~~cpp
void Entity::activate()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Activates the entity, allowing it to be updated and rendered.

**Parameters:** None.

---

### deactivate

~~~cpp
void Entity::deactivate()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Deactivates the entity, preventing it from being updated or rendered.

**Parameters:** None.

---

### Entity

~~~cpp
Entity::Entity() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters:** None.

---

### Entity

~~~cpp
Entity::Entity(Transform t, Texture *tex=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Entity value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `Transform` | Value supplied for the t parameter. | — |
| `tex` | `Texture *` | Value supplied for the tex parameter. | `nullptr` |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | `nullptr` |
| `l` | `Logger *` | Value supplied for the l parameter. | `nullptr` |

---

### Entity

~~~cpp
Entity::Entity(Vec p, Vec s, Vec r={0.0f, 0.0f}, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Entity value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `p` | `Vec` | Value supplied for the p parameter. | — |
| `s` | `Vec` | Value supplied for the s parameter. | — |
| `r` | `Vec` | Value supplied for the r parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | `nullptr` |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | `nullptr` |
| `l` | `Logger *` | Value supplied for the l parameter. | `nullptr` |

---

### free

~~~cpp
void Entity::free()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Frees the entity's resources and marks it as inactive. This method should be called when the entity is no longer needed to avoid memory leaks.

**Parameters:** None.

---

### get_pos

~~~cpp
Vec Entity::get_pos() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the position of the entity.

**Parameters:** None.

---

### get_texture

~~~cpp
Texture * Entity::get_texture() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Texture *`

Gets the size of the entity.

**Parameters:** None.

---

### is_alive

~~~cpp
bool Entity::is_alive() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if the entity is alive based on its health and lifetime.

**Parameters:** None.

---

### set_pos

~~~cpp
void Entity::set_pos(const Vec &new_pos)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the position of the entity.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_pos` | `constVec &` | The new position to set for the entity. | — |

---

### set_texture

~~~cpp
void Entity::set_texture(Texture *new_texture)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the texture of the entity.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_texture` | `Texture *` | Pointer to the new texture to set for the entity. | — |

---

### Header usage example

~~~cpp
Entity enemy;
enemy.set_pos({240.0f, 120.0f});
enemy.activate();
~~~

## particle.h

---

### ~Particle_Emitter

~~~cpp
Particle_Emitter::~Particle_Emitter()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### draw

~~~cpp
void Particle_Emitter::draw(SDL_Renderer *renderer)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws all active particles using the provided SDL renderer.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `renderer` | `SDL_Renderer *` | The SDL renderer to draw with. | — |

---

### draw

~~~cpp
void Particle::draw(SDL_Renderer *renderer)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws the particle using its texture at its current position and size.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `renderer` | `SDL_Renderer *` | The SDL renderer to draw with. | — |

---

### free

~~~cpp
void Particle_Emitter::free()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** None.

---

### is_alive

~~~cpp
bool Particle_Emitter::is_alive() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if the emitter is still active (either has remaining duration or active particles).

**Parameters:** None.

---

### is_alive

~~~cpp
bool Particle::is_alive() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if the particle is still alive (i.e., its lifetime is greater than zero).

**Parameters:** None.

---

### Particle

~~~cpp
Particle::Particle(Vec pos, Vec psize, Texture *tex, Vec vel, float lifetime, ParticlePattern pattern, Vec origin, float angle, float orbit_radius, float orbit_speed)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Particle with the specified properties.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `Vec` | Initial position of the particle. | — |
| `psize` | `Vec` | Size of the particle. | — |
| `tex` | `Texture *` | Pointer to the texture to render for this particle. | — |
| `vel` | `Vec` | Initial velocity of the particle. | — |
| `lifetime` | `float` | How long the particle should live (in seconds). | — |
| `pattern` | `ParticlePattern` | The movement pattern for the particle. | — |
| `origin` | `Vec` | The origin point for orbiting or attracting patterns. | — |
| `angle` | `float` | Initial angle for orbiting or spiral patterns. | — |
| `orbit_radius` | `float` | Radius for orbiting or spiral patterns. | — |
| `orbit_speed` | `float` | Angular speed for orbiting or spiral patterns. | — |

---

### Particle_Emitter

~~~cpp
Particle_Emitter::Particle_Emitter(Vec pos, Vec particle_size, float radius, float duration, int max_particles, float emit_rate, float particle_lifetime, ParticlePattern pattern, std::vector< Texture * > textures, Logger *logger=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Particle_Emitter with the specified properties.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `Vec` | Position of the emitter in logical coordinates. | — |
| `particle_size` | `Vec` | Size of each spawned particle. | — |
| `radius` | `float` | Radius around the emitter position to spawn particles. | — |
| `duration` | `float` | How long the emitter should emit particles (in seconds). | — |
| `max_particles` | `int` | Maximum number of active particles at once. | — |
| `emit_rate` | `float` | Number of particles to spawn per second. | — |
| `particle_lifetime` | `float` | Lifetime of each particle (in seconds). | — |
| `pattern` | `ParticlePattern` | Movement pattern for the spawned particles. | — |
| `textures` | `std::vector< Texture * >` | List of textures to randomly assign to spawned particles. | — |
| `logger` | `Logger *` | Value supplied for the logger parameter. | — |

---

### spawn_particle

~~~cpp
void Particle_Emitter::spawn_particle()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### update

~~~cpp
void Particle_Emitter::update(float dt)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the emitter and its particles.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `dt` | `float` | Time elapsed since the last update (in seconds). | — |

---

### update

~~~cpp
void Particle::update(float dt)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the particle's position and state based on its movement pattern and elapsed time.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `dt` | `float` | Time elapsed since the last update (in seconds). | — |

---

### Header usage example

~~~cpp
Particle_Emitter emitter;
emitter.spawn_particle();
emitter.update(delta_seconds);
~~~

## label.h

---

### ~TextBox

~~~cpp
TextBox::~TextBox() override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters:** None.

---

### blur

~~~cpp
void TextBox::blur()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the blur operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### clear

~~~cpp
void TextBox::clear()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### clear_shadow

~~~cpp
void Label::clear_shadow()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### draw

~~~cpp
void Label::draw(SDL_Renderer *renderer) override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws the label immediately with the assigned font.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `renderer` | `SDL_Renderer *` | SDL renderer used for drawing. | — |

---

### erase_next_character

~~~cpp
void TextBox::erase_next_character()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** None.

---

### erase_previous_character

~~~cpp
void TextBox::erase_previous_character()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### finish

~~~cpp
void TextBox::finish(SDL_Scancode release_scancode)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `release_scancode` | `SDL_Scancode` | Value supplied for the release_scancode parameter. | — |

---

### focus

~~~cpp
bool TextBox::focus(bool clear_existing_text=true)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the focus operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `clear_existing_text` | `bool` | Value supplied for the clear_existing_text parameter. | — |

---

### get_color

~~~cpp
Color Label::get_color() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color`

Gets the label color.

**Parameters:** None.

---

### get_cursor_position

~~~cpp
std::size_t TextBox::get_cursor_position() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::size_t`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_font

~~~cpp
IFont * Label::get_font() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `IFont *`

Gets the currently assigned font.

**Parameters:** None.

---

### get_max_length

~~~cpp
std::size_t TextBox::get_max_length() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::size_t`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_prefix

~~~cpp
const std::string & TextBox::get_prefix() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_scale

~~~cpp
float Label::get_scale() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Gets the draw scale used by the font.

**Parameters:** None.

---

### get_text

~~~cpp
const std::string & Label::get_text() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Gets the current text of the label.

**Parameters:** None.

---

### get_value

~~~cpp
const std::string & TextBox::get_value() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### handle_event

~~~cpp
TextBox_Result TextBox::handle_event(const SDL_Event &event)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `TextBox_Result`

Handles an engine lifecycle callback or input event. Override or call it only at the event-processing phase described by the owning type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `event` | `const SDL_Event &` | Value supplied for the event parameter. | — |

---

### insert_text

~~~cpp
void TextBox::insert_text(const std::string &text)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Performs the insert text operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `text` | `const std::string &` | Value supplied for the text parameter. | — |

---

### is_focused

~~~cpp
bool TextBox::is_focused() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### Label

~~~cpp
Label::Label() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Label value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### Label

~~~cpp
Label::Label(const Label &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Label value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### Label

~~~cpp
Label::Label(const Transform &transform, const std::string &text, IFont *font=nullptr, Logger *logger=nullptr, Object_Pool *object_pool=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Label object with no assigned font.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `transform` | `const Transform &` | Transform data inherited from Object. | — |
| `text` | `const std::string &` | The text to display on the label. | — |
| `font` | `IFont *` | Value supplied for the font parameter. | — |
| `logger` | `Logger *` | Optional logger for debug output. | — |
| `object_pool` | `Object_Pool *` | Optional pool used for automatic rendering. | — |

---

### Label

~~~cpp
Label::Label(const Vec &pos, const Vec &size, const Vec &rot, const std::string &text, const std::string &font_name, Logger *logger=nullptr, Object_Pool *object_pool=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Label object and resolves its font from Engine::asset_pool.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | The top-left position of the label in logical coordinates. | — |
| `size` | `const Vec &` | The width and height of the label in logical pixels. | — |
| `rot` | `const Vec &` | Rotation data inherited from Object. | — |
| `text` | `const std::string &` | The text to display on the label. | — |
| `font_name` | `const std::string &` | Name of the font stored in Asset_Pool. | — |
| `logger` | `Logger *` | Optional logger for debug output. | — |
| `object_pool` | `Object_Pool *` | Optional pool used for automatic rendering. | — |

---

### Label

~~~cpp
Label::Label(const Vec &pos, const Vec &size, const Vec &rot, const std::string &text, IFont *font, Logger *logger=nullptr, Object_Pool *object_pool=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Label object with a borrowed font pointer.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | The top-left position of the label in logical coordinates. | — |
| `size` | `const Vec &` | The width and height of the label in logical pixels. | — |
| `rot` | `const Vec &` | Rotation data inherited from Object. | — |
| `text` | `const std::string &` | The text to display on the label. | — |
| `font` | `IFont *` | Borrowed IFont pointer. Ownership stays with Asset_Pool or the caller. | — |
| `logger` | `Logger *` | Optional logger for debug output. | — |
| `object_pool` | `Object_Pool *` | Optional pool used for automatic rendering. | — |

---

### Label

~~~cpp
Label::Label(const Vec &pos, const Vec &size, const Vec &rot, const std::string &text, Logger *logger=nullptr, Object_Pool *object_pool=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Label object with no assigned font.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | The top-left position of the label in logical coordinates. | — |
| `size` | `const Vec &` | The width and height of the label in logical pixels. | — |
| `rot` | `const Vec &` | Rotation data inherited from Object. | — |
| `text` | `const std::string &` | The text to display on the label. | — |
| `logger` | `Logger *` | Optional logger for debug output. | — |
| `object_pool` | `Object_Pool *` | Optional pool used for automatic rendering. | — |

---

### make_draw_command

~~~cpp
Draw Label::make_draw_command() const override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Draw`

Creates a font draw command for Render_Pool.

**Parameters:** None.

---

### next_utf8_boundary

~~~cpp
static std::size_t TextBox::next_utf8_boundary(const std::string &text, std::size_t position)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Storage:** static · **Returns:** `std::size_t`

Constructs a Label value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `text` | `const std::string &` | Value supplied for the text parameter. | — |
| `position` | `std::size_t` | Value supplied for the position parameter. | — |

---

### operator=

~~~cpp
TextBox & TextBox::operator=(const TextBox &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `TextBox &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### previous_utf8_boundary

~~~cpp
static std::size_t TextBox::previous_utf8_boundary(const std::string &text, std::size_t position)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Storage:** static · **Returns:** `std::size_t`

Performs the previous utf8 boundary operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `text` | `const std::string &` | Value supplied for the text parameter. | — |
| `position` | `std::size_t` | Value supplied for the position parameter. | — |

---

### refresh_display_text

~~~cpp
void TextBox::refresh_display_text()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Performs the refresh display text operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### resize_to_text

~~~cpp
Vec Label::resize_to_text()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Updates the Object size from the current font and text.

**Parameters:** None.

---

### set_color

~~~cpp
void Label::set_color(const Color &new_color)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the label color.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_color` | `const Color &` | New text color and opacity. | — |

---

### set_font

~~~cpp
void Label::set_font(IFont *new_font)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the borrowed font pointer used for rendering.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_font` | `IFont *` | Borrowed IFont pointer. Ownership stays with the caller. | — |

---

### set_font_from_asset_pool

~~~cpp
bool Label::set_font_from_asset_pool(const std::string &font_name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Resolves and sets the font from Engine::asset_pool.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `font_name` | `const std::string &` | Name of the font stored in Asset_Pool. | — |

---

### set_max_length

~~~cpp
void TextBox::set_max_length(std::size_t maximum_bytes)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the resize to text operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `maximum_bytes` | `std::size_t` | Value supplied for the maximum_bytes parameter. | — |

---

### set_prefix

~~~cpp
void TextBox::set_prefix(const std::string &prefix)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `prefix` | `const std::string &` | Value supplied for the prefix parameter. | — |

---

### set_scale

~~~cpp
void Label::set_scale(float new_scale)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the draw scale used by the font.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_scale` | `float` | New scale multiplier. Values <= 0 are ignored. | — |

---

### set_shadow

~~~cpp
void Label::set_shadow(const Vec &offset, const Color &color)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Enables a simple drop shadow rendered immediately behind the text.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `offset` | `const Vec &` | Shadow offset in logical pixels. | — |
| `color` | `const Color &` | Shadow color; its alpha is multiplied by the label opacity. | — |

---

### set_text

~~~cpp
void Label::set_text(const std::string &new_text)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the text of the label.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_text` | `const std::string &` | The new text to display. | — |

---

### set_value

~~~cpp
void TextBox::set_value(const std::string &value)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `value` | `const std::string &` | Value supplied for the value parameter. | — |

---

### single_line_text

~~~cpp
static std::string TextBox::single_line_text(std::string text)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Storage:** static · **Returns:** `std::string`

Performs the single line text operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `text` | `std::string` | Value supplied for the text parameter. | — |

---

### submit_draw_commands

~~~cpp
void Label::submit_draw_commands(Render_Pool &render_pool) override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `render_pool` | `Render_Pool &` | Value supplied for the render_pool parameter. | — |

---

### TextBox

~~~cpp
TextBox::TextBox(const TextBox &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a TextBox value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### TextBox

~~~cpp
TextBox::TextBox(const Transform &transform={}, IFont *font=nullptr, Object_Pool *object_pool=nullptr, Logger *logger=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a TextBox value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `transform` | `const Transform &` | Value supplied for the transform parameter. | — |
| `font` | `IFont *` | Value supplied for the font parameter. | — |
| `object_pool` | `Object_Pool *` | Value supplied for the object_pool parameter. | — |
| `logger` | `Logger *` | Value supplied for the logger parameter. | — |

---

### Header usage example

~~~cpp
Label score;
score.set_text("Score: 100");
score.set_color(Color::white());
~~~

## scene.h

---

### cancel_scene_request

~~~cpp
void SceneManager::cancel_scene_request()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

This overload performs the operation identified by its signature. Review its parameter and return metadata below, and call it only in the lifecycle phase required by the owning component.

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

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `id` | `int` | Value supplied for the id parameter. | — |

---

### consume_scene_request

~~~cpp
bool SceneManager::consume_scene_request(int &out_id)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the consume scene request operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `out_id` | `int &` | Value supplied for the out_id parameter. | — |

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

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `scene_id` | `int` | Value supplied for the scene_id parameter. | — |
| `label` | `const std::string &` | Value supplied for the label parameter. | — |
| `step` | `std::function< bool()>` | Value supplied for the step parameter. | — |
| `weight` | `float` | Value supplied for the weight parameter. | — |

---

### enqueue_load_task

~~~cpp
void SceneManager::enqueue_load_task(int scene_id, const std::string &label, std::function< void()> action, float weight=1.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `scene_id` | `int` | Value supplied for the scene_id parameter. | — |
| `label` | `const std::string &` | Value supplied for the label parameter. | — |
| `action` | `std::function< void()>` | Value supplied for the action parameter. | — |
| `weight` | `float` | Value supplied for the weight parameter. | — |

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

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `id` | `int` | Numeric scene identifier (>= 0). | — |
| `name` | `const std::string &` | Unique name for the scene. | — |

---

### request_scene

~~~cpp
bool SceneManager::request_scene(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `name` | `const std::string &` | Value supplied for the name parameter. | — |

---

### request_scene

~~~cpp
bool SceneManager::request_scene(int id)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Requests a deferred scene transition.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `id` | `int` | Value supplied for the id parameter. | — |

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

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `id` | `int` | Value supplied for the id parameter. | — |

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

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `name` | `const std::string &` | The registered scene name. | — |

---

### set_scene

~~~cpp
void SceneManager::set_scene(int id)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Switches the active scene by numeric ID.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `id` | `int` | The scene to make active. | — |

---

### take_load_tasks

~~~cpp
std::vector< Load_Task > SceneManager::take_load_tasks(int scene_id)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< Load_Task >`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `scene_id` | `int` | Value supplied for the scene_id parameter. | — |

---

### Header usage example

~~~cpp
SceneManager::instance().register_scene(1, "menu");
SceneManager::instance().request_scene(1);
~~~

## script-base.h

---

### ~script

~~~cpp
virtual script::~script() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

This overload performs the operation identified by its signature. Review its parameter and return metadata below, and call it only in the lifecycle phase required by the owning component.

**Parameters:** None.

---

### execution_order

~~~cpp
virtual int script::execution_order() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `int`

Controls the order this script is updated and rendered. Lower value = called earlier. Default is 0. Override via the SCRIPT_ORDER(n) macro inside the class.

**Parameters:** None.

---

### on_destroy

~~~cpp
virtual void script::on_destroy()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Called once when the script is about to be destroyed. Release any resources allocated in on_start.

**Parameters:** None.

---

### on_event

~~~cpp
virtual void script::on_event(const SDL_Event &event)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Called for every SDL event before on_update.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `event` | `const SDL_Event &` | The SDL_Event that occurred (keyboard, mouse, window, etc.). | — |

---

### on_post_render

~~~cpp
virtual void script::on_post_render()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Called after the world render queue and lighting pass have finished.

**Parameters:** None.

---

### on_render

~~~cpp
virtual void script::on_render()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Called every frame during the render phase. Runs after on_update. Use for custom draw calls or debug overlays.

**Parameters:** None.

---

### on_start

~~~cpp
virtual void script::on_start()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Called once when the script is first created, before the first frame. Use this to load textures, initialise state, etc.

**Parameters:** None.

---

### on_update

~~~cpp
virtual void script::on_update(float delta_time)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Called every frame before rendering.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `delta_time` | `float` | Time in seconds since the last frame. | — |

---

### scene_id

~~~cpp
virtual int script::scene_id() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `int`

The scene this script belongs to. The script's on_update, on_render and on_event are only called when the active scene matches this value. Return -1 (default) to run in every scene regardless of the active scene. Override via the SCRIPT_SCENE(id) macro inside the class.

**Parameters:** None.

---

### Header usage example

~~~cpp
class PlayerScript : public script {
public:
    void on_update(float delta_time) override { /* gameplay */ }
};
~~~

## script-registry.h

---

### create_all_scripts

~~~cpp
std::vector< script * > script_registry::create_all_scripts()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< script * >`

Creates all registered scripts and sorts them by execution_order(). Lower execution_order() values appear first. The caller takes ownership of the returned pointers.

**Parameters:** None.

---

### instance

~~~cpp
static script_registry & script_registry::instance()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `script_registry &`

Performs the execution order operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### register_script

~~~cpp
void script_registry::register_script(script_factory factory)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Registers a factory function that creates one script instance. Called automatically by REGISTER_SCRIPT at startup.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `factory` | `script_factory` | A callable that returns a heap-allocated script*. | — |

---

### script_registry

~~~cpp
script_registry::script_registry() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters:** None.

---

### Header usage example

~~~cpp
REGISTER_SCRIPT(PlayerScript);
~~~












