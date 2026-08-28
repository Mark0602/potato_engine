# script

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `script-base.h`  
**Documented overloads:** 9

This page documents the engine-owned callables declared for `script`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

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

## Usage example

~~~cpp
class PlayerScript : public script {
public:
    void on_update(float delta_time) override { /* gameplay */ }
};
~~~

## Functions

### ~script

~~~cpp
virtual script::~script() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

This function belongs to the documented engine type. Its exact behavior, inputs, and result are described by the signature and metadata in this entry.

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

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


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

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


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


