# Core and Utilities API

**Engine version:** Potato Engine 1.0.0  
**Language:** C++

This reference lists every engine-owned function overload declared in the covered headers. Signatures preserve parameter types, names, default values, qualifiers, and namespaces from the source. Access labels identify members that are not part of the public calling surface.

## Detailed workflow example

~~~cpp
config::game_config config;
config.title = "Potato Adventure";
config.renderer_backend = RendererBackend::CPU;

Engine::Application application(config);
if (!application.initialize()) {
    return 1;
}

Logger session_log;
session_log.init("logs/session.log");
session_log.log(Log_Level::INFO, "Bootstrap", "Application initialized");

Vec spawn{64.0f, 96.0f};
Vec target{320.0f, 180.0f};
Vec direction = normalize(target - spawn);
Timer autosave;
autosave.start(30.0f);

return application.run();
~~~

## engine.h

---

### ~Application

~~~cpp
Engine::Application::~Application()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

---

### ~SDLstate

~~~cpp
SDLstate::~SDLstate()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

---

### Application

~~~cpp
Engine::Application::Application(config::game_config config={})
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Application value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `config` | `config::game_config` | Value supplied for the config parameter. | — |

---

### Application

~~~cpp
Engine::Application::Application(const Application &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Application value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### begin_frame

~~~cpp
bool SDLstate::begin_frame()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** None.

---

### clearup

~~~cpp
void SDLstate::clearup()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### get_renderer_backend

~~~cpp
RendererBackend SDLstate::get_renderer_backend() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `RendererBackend`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### getlogicalheight

~~~cpp
std::uint16_t SDLstate::getlogicalheight() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::uint16_t`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### getlogicalwidth

~~~cpp
std::uint16_t SDLstate::getlogicalwidth() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::uint16_t`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### getwindowheight

~~~cpp
std::uint16_t SDLstate::getwindowheight() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::uint16_t`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### getwindowwidth

~~~cpp
std::uint16_t SDLstate::getwindowwidth() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::uint16_t`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### initialize

~~~cpp
bool Engine::Application::initialize()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the initialize operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### initiate

~~~cpp
bool SDLstate::initiate(RendererBackend backend=RendererBackend::CPU)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the initiate operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `backend` | `RendererBackend` | Value supplied for the backend parameter. | `RendererBackend::CPU` |

---

### is_gpu_renderer

~~~cpp
bool SDLstate::is_gpu_renderer() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### is_initialized

~~~cpp
bool Engine::Application::is_initialized() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### load_config

~~~cpp
static bool config::load_config(const std::string &path, project_config &pconf, game_config &gconf, settings &settings)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `bool`

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `path` | `const std::string &` | Value supplied for the path parameter. | — |
| `pconf` | `project_config &` | Value supplied for the pconf parameter. | — |
| `gconf` | `game_config &` | Value supplied for the gconf parameter. | — |
| `settings` | `settings &` | Value supplied for the settings parameter. | — |

---

### operator=

~~~cpp
Application & Engine::Application::operator=(const Application &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Application &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### operator=

~~~cpp
SDLstate & SDLstate::operator=(const SDLstate &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `SDLstate &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### present

~~~cpp
void SDLstate::present()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** None.

---

### quit

~~~cpp
void Engine::quit()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the quit operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### run

~~~cpp
int Engine::Application::run()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `int`

Performs the run operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### SDLstate

~~~cpp
SDLstate::SDLstate(const SDLstate &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a SDLstate value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### SDLstate

~~~cpp
SDLstate::SDLstate(std::string title="Potato Engine", std::uint16_t window_width=1280, std::uint16_t window_height=720, std::uint16_t logical_width=1280, std::uint16_t logical_height=720)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a SDLstate value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `title` | `std::string` | Value supplied for the title parameter. | — |
| `window_width` | `std::uint16_t` | Value supplied for the window_width parameter. | — |
| `window_height` | `std::uint16_t` | Value supplied for the window_height parameter. | — |
| `logical_width` | `std::uint16_t` | Value supplied for the logical_width parameter. | — |
| `logical_height` | `std::uint16_t` | Value supplied for the logical_height parameter. | — |

---

### shutdown

~~~cpp
void Engine::Application::shutdown()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

---

### using_gpu_renderer

~~~cpp
bool Engine::using_gpu_renderer()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the using gpu renderer operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### Header usage example

~~~cpp
config::game_config cfg;
cfg.title = "Potato Demo";
Engine::Application app(cfg);
if (!app.initialize()) return 1;
return app.run();
~~~

## vec.h

---

### operator-

~~~cpp
Transform Transform::operator-(const Transform &other) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

This overload performs the operation identified by its signature. Review its parameter and return metadata below, and call it only in the lifecycle phase required by the owning component.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Transform &` | Value supplied for the other parameter. | — |

---

### operator-

~~~cpp
Vec Vec::operator-(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Implements the operator- operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### operator-=

~~~cpp
Transform & Transform::operator-=(const Transform &other)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform &`

Implements the operator-= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Transform &` | Value supplied for the other parameter. | — |

---

### operator-=

~~~cpp
Vec & Vec::operator-=(const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec &`

Implements the operator-= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |

---

### operator!=

~~~cpp
bool Vec::operator!=(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Implements the operator!= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### operator*

~~~cpp
Transform Transform::operator*(float scalar) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Implements the operator* operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `scalar` | `float` | Value supplied for the scalar parameter. | — |

---

### operator*

~~~cpp
Vec Vec::operator*(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Component-wise multiplication.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### operator*

~~~cpp
Vec Vec::operator*(float b) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Scalar multiplication.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `b` | `float` | Value supplied for the b parameter. | — |

---

### operator*=

~~~cpp
Transform & Transform::operator*=(float scalar)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform &`

Implements the operator* operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `scalar` | `float` | Value supplied for the scalar parameter. | — |

---

### operator*=

~~~cpp
Vec & Vec::operator*=(const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec &`

Component-wise multiply-assign.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |

---

### operator*=

~~~cpp
Vec & Vec::operator*=(float b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec &`

Implements the operator*= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `b` | `float` | Value supplied for the b parameter. | — |

---

### operator/

~~~cpp
Transform Transform::operator/(float scalar) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Implements the operator/ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `scalar` | `float` | Value supplied for the scalar parameter. | — |

---

### operator/

~~~cpp
Vec Vec::operator/(float b) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Scalar division. Behaviour is undefined if b is zero.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `b` | `float` | Value supplied for the b parameter. | — |

---

### operator/=

~~~cpp
Transform & Transform::operator/=(float scalar)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform &`

Implements the operator/ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `scalar` | `float` | Value supplied for the scalar parameter. | — |

---

### operator/=

~~~cpp
Vec & Vec::operator/=(float b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec &`

Implements the operator/= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `b` | `float` | Value supplied for the b parameter. | — |

---

### operator+

~~~cpp
Transform Transform::operator+(const Transform &other) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Implements the operator+ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Transform &` | Value supplied for the other parameter. | — |

---

### operator+

~~~cpp
Vec Vec::operator+(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Implements the operator+ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### operator+=

~~~cpp
Transform & Transform::operator+=(const Transform &other)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform &`

Implements the operator+= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Transform &` | Value supplied for the other parameter. | — |

---

### operator+=

~~~cpp
Vec & Vec::operator+=(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec &`

Implements the operator+= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### operator<

~~~cpp
bool Vec::operator<(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

True only if both x and y are strictly less.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### operator<=

~~~cpp
bool Vec::operator<=(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Implements the operator< operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### operator==

~~~cpp
bool Vec::operator==(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Implements the operator== operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### operator>

~~~cpp
bool Vec::operator>(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

True only if both x and y are strictly greater.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### operator>=

~~~cpp
bool Vec::operator>=(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Implements the operator> operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### Transform

~~~cpp
Transform::Transform() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Transform value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### Transform

~~~cpp
Transform::Transform(const Vec &pos, const Vec &size, const Vec &rotation)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Transform with given position, size, and rotation.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | Position in 2D space. | — |
| `size` | `const Vec &` | Size in 2D space. | — |
| `rotation` | `const Vec &` | Rotation in 2D space. x is the angle in degrees, y is the SDL_FlipMode. | — |

---

### Transform

~~~cpp
Transform::Transform(const Vec &pos, const Vec &size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Transform with given position and size.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | Position in 2D space. | — |
| `size` | `const Vec &` | Size in 2D space. | — |

---

### Transform

~~~cpp
Transform::Transform(const Vec &pos)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Transform with given position.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | Position in 2D space. | — |

---

### Vec

~~~cpp
Vec::Vec() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Transform value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### Vec

~~~cpp
Vec::Vec(float x, float y)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Vec with given x and y values.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `x` | `float` | Horizontal component. | — |
| `y` | `float` | Vertical component. | — |

---

### Header usage example

~~~cpp
Vec velocity{120.0f, 0.0f};
Transform player{{32.0f, 48.0f}, {16.0f, 16.0f}};
player.pos += velocity * delta_seconds;
~~~

## color.h

---

### black

~~~cpp
static const Color Color::black()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined black color (0, 0, 0, 255).

**Parameters:** None.

---

### blue

~~~cpp
static const Color Color::blue()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined blue color (0, 0, 255, 255).

**Parameters:** None.

---

### brown

~~~cpp
static const Color Color::brown()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined brown color (165, 42, 42, 255).

**Parameters:** None.

---

### Color

~~~cpp
Color::Color() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Color with specified red, green, blue, and alpha values.

**Parameters:** None.

---

### Color

~~~cpp
Color::Color(const SDL_Color &color)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Color from an SDL_Color.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `color` | `const SDL_Color &` | SDL_Color to convert to Color. Constructs a Color from an SDL_Color. | — |

---

### Color

~~~cpp
Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a=255)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Color with specified red, green, blue, and alpha values.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `r` | `uint8_t` | Red component (0-255). | — |
| `g` | `uint8_t` | Green component (0-255). | — |
| `b` | `uint8_t` | Blue component (0-255). | — |
| `a` | `uint8_t` | Alpha component (0-255). Constructs a Color with specified RGBA values. | — |

---

### cyan

~~~cpp
static const Color Color::cyan()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined cyan color (0, 255, 255, 255).

**Parameters:** None.

---

### dark_blue

~~~cpp
static const Color Color::dark_blue()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined dark blue color (0, 0, 139, 255).

**Parameters:** None.

---

### dark_cyan

~~~cpp
static const Color Color::dark_cyan()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined dark cyan color (0, 139, 139, 255).

**Parameters:** None.

---

### dark_gray

~~~cpp
static const Color Color::dark_gray()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined dark gray color (169, 169, 169, 255).

**Parameters:** None.

---

### dark_green

~~~cpp
static const Color Color::dark_green()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined dark green color (0, 100, 0, 255).

**Parameters:** None.

---

### dark_magenta

~~~cpp
static const Color Color::dark_magenta()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined dark magenta color (139, 0, 139, 255).

**Parameters:** None.

---

### dark_red

~~~cpp
static const Color Color::dark_red()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined dark red color (139, 0, 0, 255).

**Parameters:** None.

---

### dark_yellow

~~~cpp
static const Color Color::dark_yellow()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined dark yellow color (204, 204, 0, 255).

**Parameters:** None.

---

### from_hex

~~~cpp
static Color Color::from_hex(uint32_t hex)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `Color`

Creates a Color from a hexadecimal value.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `hex` | `uint32_t` | Hexadecimal value representing the color (0xRRGGBBAA). | — |

---

### from_hex_string

~~~cpp
static Color Color::from_hex_string(std::string hex_string)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `Color`

Creates a Color from a hexadecimal string.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `hex_string` | `std::string` | Hexadecimal string representing the color (e.g., "FF00FF00"). | — |

---

### from_sdl_color

~~~cpp
static Color Color::from_sdl_color(const SDL_Color &color)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `Color`

Creates a Color from an SDL_Color.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `color` | `const SDL_Color &` | SDL_Color to convert to Color. | — |

---

### gray

~~~cpp
static const Color Color::gray()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined gray color (128, 128, 128, 255).

**Parameters:** None.

---

### green

~~~cpp
static const Color Color::green()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined green color (0, 255, 0, 255).

**Parameters:** None.

---

### light_blue

~~~cpp
static const Color Color::light_blue()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined light blue color (173, 216, 230, 255).

**Parameters:** None.

---

### light_cyan

~~~cpp
static const Color Color::light_cyan()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined light cyan color (224, 255, 255, 255).

**Parameters:** None.

---

### light_gray

~~~cpp
static const Color Color::light_gray()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined light gray color (211, 211, 211, 255).

**Parameters:** None.

---

### light_green

~~~cpp
static const Color Color::light_green()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined light green color (144, 238, 144, 255).

**Parameters:** None.

---

### light_magenta

~~~cpp
static const Color Color::light_magenta()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined light magenta color (255, 182, 255, 255).

**Parameters:** None.

---

### light_red

~~~cpp
static const Color Color::light_red()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined light red color (255, 182, 193, 255).

**Parameters:** None.

---

### light_yellow

~~~cpp
static const Color Color::light_yellow()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined light yellow color (255, 255, 224, 255).

**Parameters:** None.

---

### magenta

~~~cpp
static const Color Color::magenta()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined magenta color (255, 0, 255, 255).

**Parameters:** None.

---

### operator-

~~~cpp
Color Color::operator-(const Color &other) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color`

Constructs a Vec value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Color &` | Value supplied for the other parameter. | — |

---

### operator-=

~~~cpp
Color & Color::operator-=(const Color &other)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color &`

Implements the operator-= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Color &` | Value supplied for the other parameter. | — |

---

### operator!=

~~~cpp
bool Color::operator!=(const Color &other) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Implements the operator!= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Color &` | Value supplied for the other parameter. | — |

---

### operator*

~~~cpp
Color Color::operator*(float scalar) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color`

Implements the operator* operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `scalar` | `float` | Value supplied for the scalar parameter. | — |

---

### operator*=

~~~cpp
Color & Color::operator*=(float scalar)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color &`

Implements the operator*= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `scalar` | `float` | Value supplied for the scalar parameter. | — |

---

### operator/

~~~cpp
Color Color::operator/(float scalar) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color`

Implements the operator/ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `scalar` | `float` | Value supplied for the scalar parameter. | — |

---

### operator/=

~~~cpp
Color & Color::operator/=(float scalar)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color &`

Implements the operator/= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `scalar` | `float` | Value supplied for the scalar parameter. | — |

---

### operator+

~~~cpp
Color Color::operator+(const Color &other) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color`

Implements the operator+ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Color &` | Value supplied for the other parameter. | — |

---

### operator+=

~~~cpp
Color & Color::operator+=(const Color &other)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color &`

Implements the operator+= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Color &` | Value supplied for the other parameter. | — |

---

### operator==

~~~cpp
bool Color::operator==(const Color &other) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Implements the operator== operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Color &` | Value supplied for the other parameter. | — |

---

### orange

~~~cpp
static const Color Color::orange()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined orange color (255, 165, 0, 255).

**Parameters:** None.

---

### pink

~~~cpp
static const Color Color::pink()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined pink color (255, 192, 203, 255).

**Parameters:** None.

---

### purple

~~~cpp
static const Color Color::purple()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined purple color (128, 0, 128, 255).

**Parameters:** None.

---

### red

~~~cpp
static const Color Color::red()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined red color (255, 0, 0, 255).

**Parameters:** None.

---

### to_sdl_color

~~~cpp
SDL_Color Color::to_sdl_color() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `SDL_Color`

Converts the Color to an SDL_Color.

**Parameters:** None.

---

### transparent

~~~cpp
static const Color Color::transparent()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined transparent color (0, 0, 0, 0).

**Parameters:** None.

---

### white

~~~cpp
static const Color Color::white()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined white color (255, 255, 255, 255).

**Parameters:** None.

---

### with_alpha

~~~cpp
Color Color::with_alpha(uint8_t alpha) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color`

Creates a Color with specified alpha value.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `alpha` | `uint8_t` | Alpha component (0.0f - 1.0f). | — |

---

### yellow

~~~cpp
static const Color Color::yellow()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined yellow color (255, 255, 0, 255).

**Parameters:** None.

---

### Header usage example

~~~cpp
Color tint = Color::from_hex_string("#FFAA33");
tint = tint.with_alpha(192);
~~~

## utils.h

---

### abs

~~~cpp
Vec abs(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns a vector with each component replaced by its absolute value.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### angle

~~~cpp
float angle(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Angle (radians) from point a to point b, measured from the positive X axis.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |

---

### angle_between

~~~cpp
float angle_between(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Unsigned angle between two direction vectors (radians).

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |

---

### angle_between_degrees

~~~cpp
float angle_between_degrees(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Unsigned angle between two vectors in degrees. See angle_between().

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |

---

### angle_between_radians

~~~cpp
float angle_between_radians(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Alias for angle_between() — returns the unsigned angle in radians.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |

---

### angle_between_signed

~~~cpp
float angle_between_signed(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Signed angle from a to b (radians). Positive = counter-clockwise.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |

---

### angle_between_signed_degrees

~~~cpp
float angle_between_signed_degrees(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Signed angle from a to b in degrees. See angle_between_signed().

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |

---

### angle_between_signed_radians

~~~cpp
float angle_between_signed_radians(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Alias for angle_between_signed() — returns the signed angle in radians.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |

---

### ceil

~~~cpp
Vec ceil(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns a vector with each component rounded up to the nearest integer.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### clamp

~~~cpp
float clamp(float value, float min, float max)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Clamps a float value between a minimum and maximum.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `value` | `float` | The value to clamp. | — |
| `min` | `float` | The minimum value. | — |
| `max` | `float` | The maximum value. | — |

---

### clamp

~~~cpp
int clamp(int value, int min, int max)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `int`

Clamps an integer value between a minimum and maximum.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `value` | `int` | The value to clamp. | — |
| `min` | `int` | The minimum value. | — |
| `max` | `int` | The maximum value. | — |

---

### clamp

~~~cpp
Vec clamp(const Vec &a, const Vec &min, const Vec &max)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Clamps each component of a between the corresponding components of min and max.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value to clamp. | — |
| `min` | `const Vec &` | Per-component minimum. | — |
| `max` | `const Vec &` | Per-component maximum. | — |

---

### convert_FRect_to_Vec

~~~cpp
Vec convert_FRect_to_Vec(const SDL_FRect &rect)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Extracts the top-left position {x, y} from an SDL_FRect as a Vec.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `rect` | `const SDL_FRect &` | Value supplied for the rect parameter. | — |

---

### convert_Vec_to_FRect

~~~cpp
SDL_FRect convert_Vec_to_FRect(const Vec &a, const Vec &size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `SDL_FRect`

Converts a position Vec and a size Vec into an SDL_FRect.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Top-left position. | — |
| `size` | `const Vec &` | Width and height. | — |

---

### cross

~~~cpp
float cross(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

2D cross product (scalar). Positive if b is counter-clockwise from a.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |

---

### distance

~~~cpp
float distance(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Calculates the distance between two Vec points.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | The first Vec point. | — |
| `b` | `const Vec &` | The second Vec point. | — |

---

### distance_squared

~~~cpp
float distance_squared(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Calculates the squared distance between two Vec points.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | The first Vec point. | — |
| `b` | `const Vec &` | The second Vec point. | — |

---

### dot

~~~cpp
float dot(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Dot product of two vectors. Positive = same direction, 0 = perpendicular, negative = opposite.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |

---

### floor

~~~cpp
Vec floor(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns a vector with each component rounded down to the nearest integer.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### fullscreen_window

~~~cpp
void fullscreen_window(SDL_Window *window)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the SDL window to fullscreen mode if it is valid.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `window` | `SDL_Window *` | Pointer to the SDL_Window to set to fullscreen. If nullptr, the function | — |

---

### get_mouse_position

~~~cpp
static Vec get_mouse_position()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `Vec`

Gets the current mouse position in logical coordinates. This function retrieves the current mouse position in window coordinates and converts it to logical coordinates based on the current SDL renderer.

**Parameters:** None.

---

### get_window_bottom_center

~~~cpp
Vec get_window_bottom_center()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the bottom-center point of the window in logical coordinates as a Vec. This function calculates the bottom-center point of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

---

### get_window_bottom_left

~~~cpp
Vec get_window_bottom_left()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the top-right corner of the window in logical coordinates as a Vec. This function calculates the top-right corner of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

---

### get_window_bottom_right

~~~cpp
Vec get_window_bottom_right()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the bottom-right corner of the window in logical coordinates as a Vec. This function calculates the bottom-right corner of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

---

### get_window_center

~~~cpp
Vec get_window_center()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the center of the window in logical coordinates as a Vec. This function calculates the center point of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

---

### get_window_left_center

~~~cpp
Vec get_window_left_center()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the left-center point of the window in logical coordinates as a Vec. This function calculates the left-center point of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

---

### get_window_right_center

~~~cpp
Vec get_window_right_center()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the right-center point of the window in logical coordinates as a Vec. This function calculates the right-center point of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

---

### get_window_size

~~~cpp
Vec get_window_size()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the window size in logical coordinates as a Vec. This function retrieves the current size of the SDL window and returns it as a Vec, where x is the width and y is the height.

**Parameters:** None.

---

### get_window_top_center

~~~cpp
Vec get_window_top_center()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the top-center point of the window in logical coordinates as a Vec. This function calculates the top-center point of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

---

### get_window_top_left

~~~cpp
Vec get_window_top_left()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the top-left corner of the window in logical coordinates as a Vec. This function returns the top-left corner of the SDL window, which is always at (0, 0) in logical coordinates.

**Parameters:** None.

---

### get_window_top_right

~~~cpp
Vec get_window_top_right()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the bottom-left corner of the window in logical coordinates as a Vec. This function calculates the bottom-left corner of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

---

### invert

~~~cpp
Vec invert(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns a vector pointing in the opposite direction (-x, -y).

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### is_point_in_circle

~~~cpp
bool is_point_in_circle(const Vec &point, const Vec &circle_center, float radius)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Tests whether a point lies inside or on the boundary of a circle.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `point` | `const Vec &` | Point to test. | — |
| `circle_center` | `const Vec &` | Centre of the circle. | — |
| `radius` | `float` | Radius of the circle. | — |

---

### is_point_in_rect

~~~cpp
bool is_point_in_rect(const Vec &point, const Vec &rect_Vec, const SDL_FRect &rect)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Tests whether a point is inside an SDL_FRect offset by rect_Vec.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `point` | `const Vec &` | Point to test in logical coordinates. | — |
| `rect_Vec` | `const Vec &` | Top-left offset added to rect.x/y. | — |
| `rect` | `const SDL_FRect &` | Rectangle (x, y ignored; w, h used for size). | — |

---

### length

~~~cpp
float length(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Calculates the length (magnitude) of a Vec.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | The Vec whose length is to be calculated. | — |

---

### length_squared

~~~cpp
float length_squared(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Calculates the squared length (magnitude) of a Vec.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | The Vec whose squared length is to be calculated. | — |

---

### lerp

~~~cpp
Vec lerp(const Vec &a, const Vec &b, float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Linearly interpolates between two vectors.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Start value (t = 0). | — |
| `b` | `const Vec &` | End value (t = 1). | — |
| `t` | `float` | Blend factor. Clamping to [0, 1] is the caller's responsibility. | — |

---

### lerp_color

~~~cpp
void lerp_color(Color &color, const Color &target, float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Linearly interpolates between two colors.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `color` | `Color &` | The starting color, which will be modified to the interpolated value. | — |
| `target` | `const Color &` | The target color to interpolate towards. | — |
| `t` | `float` | The interpolation factor, where 0.0 returns color and 1.0 returns target. Values outside the range [0.0, 1.0] will extrapolate beyond the two colors. | — |

---

### maximize_window

~~~cpp
void maximize_window(SDL_Window *window)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Maximizes the SDL window if it is valid.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `window` | `SDL_Window *` | Pointer to the SDL_Window to maximize. If nullptr, the function does nothing. | — |

---

### nearly_equal

~~~cpp
bool nearly_equal(const Vec &a, const Vec &b, float epsilon=0.01f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if two Vec points are nearly equal within a given epsilon.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | The first Vec point. | — |
| `b` | `const Vec &` | The second Vec point. | — |
| `epsilon` | `float` | The tolerance for equality. Default is 0.01f. | — |

---

### normalize

~~~cpp
Vec normalize(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns a unit vector in the same direction as a. Returns {0,0} if a is zero.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### os_cursor_visibility

~~~cpp
void os_cursor_visibility(bool visible, Logger *logger=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Changes the visibility of the OS cursor.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `visible` | `bool` | If true, the cursor will be shown; if false, it will be hidden. | — |
| `logger` | `Logger *` | Optional logger for debugging purposes. By default nullptr, which means no logging will occur. | — |

---

### perpendicular

~~~cpp
Vec perpendicular(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns a vector perpendicular to a, rotated 90° counter-clockwise.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### reflect

~~~cpp
Vec reflect(const Vec &a, const Vec &normal)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Reflects vector a off a surface with the given unit normal.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Incoming direction vector. | — |
| `normal` | `const Vec &` | Unit normal of the surface. | — |

---

### rotate

~~~cpp
Vec rotate(const Vec &a, float angle)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Rotates vector a by angle degrees counter-clockwise.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Vector to rotate. | — |
| `angle` | `float` | Rotation angle in degrees. | — |

---

### round

~~~cpp
Vec round(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns a vector with each component rounded to the nearest integer.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |

---

### windowed_window

~~~cpp
void windowed_window(SDL_Window *window)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the SDL window to windowed mode if it is valid.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `window` | `SDL_Window *` | Pointer to the SDL_Window to set to windowed mode. If nullptr, the function does nothing. | — |

---

### Header usage example

~~~cpp
Vec direction = normalize(target - origin);
float separation = distance(origin, target);
~~~

## debug.h

---

### close

~~~cpp
void Logger::close()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Flushes and closes the log file.

**Parameters:** None.

---

### finalize_log

~~~cpp
void Logger::finalize_log()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Flushes and renames the log file to a timestamped filename. Call this on clean shutdown so the log is not overwritten next run.

**Parameters:** None.

---

### flood_logging

~~~cpp
void Logger::flood_logging(bool state)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Enables or disables flood logging (DEBUG messages every frame). Disable this in release builds to avoid log spam.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `state` | `bool` | true to enable. | — |

---

### format_line

~~~cpp
std::string Logger::format_line(Log_Level level, const std::string &category, const std::string &message)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `std::string`

Performs the orange operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `level` | `Log_Level` | Value supplied for the level parameter. | — |
| `category` | `const std::string &` | Value supplied for the category parameter. | — |
| `message` | `const std::string &` | Value supplied for the message parameter. | — |

---

### frame_indexing

~~~cpp
void Logger::frame_indexing(bool state)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Enables or disables per-frame index prefixes in log lines.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `state` | `bool` | true to enable frame indexing. | — |

---

### get_elapsed_time_string

~~~cpp
std::string Logger::get_elapsed_time_string()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `std::string`

Performs the frame indexing operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### get_logged_message

~~~cpp
std::string Logger::get_logged_message()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::string`

Retrieves the entire contents of the log file as a string.

**Parameters:** None.

---

### get_min_level

~~~cpp
Log_Level Logger::get_min_level() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Log_Level`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### increment_frame_index

~~~cpp
void Logger::increment_frame_index()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Increments the internal frame counter by 1.

**Parameters:** None.

---

### init

~~~cpp
void Logger::init(const std::string &filepath="logs/latest.log")
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Opens the log file and starts the timer.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `filepath` | `const std::string &` | Path to the log file. Default: "logs/latest.log". | — |

---

### is_flood_logging

~~~cpp
bool Logger::is_flood_logging() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the increment frame index operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### is_initialized

~~~cpp
bool Logger::is_initialized() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### level_to_string

~~~cpp
static const char * Logger::level_to_string(Log_Level level)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Storage:** static · **Returns:** `const char *`

Performs the level to string operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `level` | `Log_Level` | Value supplied for the level parameter. | — |

---

### log

~~~cpp
void Logger::log(Log_Level level, const std::string &category, const std::string &message)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Writes a message to the log (file + stdout).

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `level` | `Log_Level` | Severity level of the message. | — |
| `category` | `const std::string &` | Short label identifying the system (e.g. "Render", "Input"). | — |
| `message` | `const std::string &` | The log message text. | — |

---

### Logger

~~~cpp
Logger::Logger()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Performs the log operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### set_frame_index

~~~cpp
void Logger::set_frame_index(long index)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Manually sets the frame counter.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `index` | `long` | The frame index value to set. | — |

---

### set_min_level

~~~cpp
void Logger::set_min_level(Log_Level level)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the minimum level to log. Messages below this are ignored.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `level` | `Log_Level` | The new minimum Log_Level. | — |

---

### Header usage example

~~~cpp
Logger logger;
logger.init("logs/latest.log");
logger.log(Log_Level::INFO, "Game", "Started");
~~~

## timer.h

---

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

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `duration` | `float` | How long the timer should run in seconds. | — |
| `callback` | `std::function< void()>` | Optional function called once when the timer expires. | — |

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

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `delta_time` | `float` | Time elapsed since the last frame, in seconds. | — |

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

---

### Header usage example

~~~cpp
Timer cooldown;
cooldown.start(1.0f);
cooldown.tick(delta_seconds);
~~~

## prandom.h

---

### device

~~~cpp
rd & prandom::device()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `rd &`

This overload performs the operation identified by its signature. Review its parameter and return metadata below, and call it only in the lifecycle phase required by the owning component.

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

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `choices` | `const std::vector< T > &` | Value supplied for the choices parameter. | — |

---

### random_choice_weighted

~~~cpp
T prandom::random_choice_weighted(const std::vector< T > &choices, const std::vector< float > &weight)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `T`

Produces a pseudo-random result constrained by the supplied range, collection, or weights. Ensure any referenced collection remains valid for the duration of the call.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `choices` | `const std::vector< T > &` | Value supplied for the choices parameter. | — |
| `weight` | `const std::vector< float > &` | Value supplied for the weight parameter. | — |

---

### random_choice_weighted

~~~cpp
T prandom::random_choice_weighted(std::initializer_list< T > choices, std::initializer_list< float > weights)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `T`

Produces a pseudo-random result constrained by the supplied range, collection, or weights. Ensure any referenced collection remains valid for the duration of the call.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `choices` | `std::initializer_list< T >` | Value supplied for the choices parameter. | — |
| `weights` | `std::initializer_list< float >` | Value supplied for the weights parameter. | — |

---

### random_range

~~~cpp
T prandom::random_range(T min, T max)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `T`

Produces a pseudo-random result constrained by the supplied range, collection, or weights. Ensure any referenced collection remains valid for the duration of the call.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `min` | `T` | Value supplied for the min parameter. | — |
| `max` | `T` | Value supplied for the max parameter. | — |

---

### random_range_weighted

~~~cpp
T prandom::random_range_weighted(T min, T max, const std::vector< float > &weight)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `T`

Produces a pseudo-random result constrained by the supplied range, collection, or weights. Ensure any referenced collection remains valid for the duration of the call.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `min` | `T` | Value supplied for the min parameter. | — |
| `max` | `T` | Value supplied for the max parameter. | — |
| `weight` | `const std::vector< float > &` | Value supplied for the weight parameter. | — |

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
| `weights` | `const std::vector< float > &` | Value supplied for the weights parameter. | — |
| `logger` | `Logger *` | Value supplied for the logger parameter. | — |

---

### Header usage example

~~~cpp
int damage = random_range(8, 12);
~~~

## functionality_trigger.h

---

### clear

~~~cpp
void functionality_trigger::clear()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

This overload performs the operation identified by its signature. Review its parameter and return metadata below, and call it only in the lifecycle phase required by the owning component.

**Parameters:** None.

---

### evaluate

~~~cpp
bool functionality_trigger::evaluate(const std::string &trigger_id, const trigger_context &context={})
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the evaluate operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `trigger_id` | `const std::string &` | Value supplied for the trigger_id parameter. | — |
| `context` | `const trigger_context &` | Value supplied for the context parameter. | — |

---

### register_source

~~~cpp
bool functionality_trigger::register_source(const std::string &trigger_id, const void *owner, trigger_source source)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `trigger_id` | `const std::string &` | Value supplied for the trigger_id parameter. | — |
| `owner` | `const void *` | Value supplied for the owner parameter. | — |
| `source` | `trigger_source` | Value supplied for the source parameter. | — |

---

### unregister_sources

~~~cpp
void functionality_trigger::unregister_sources(const void *owner)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `owner` | `const void *` | Value supplied for the owner parameter. | — |

---

### Header usage example

~~~cpp
Functionality_Trigger::register_source(owner, source);
Functionality_Trigger::unregister_sources(owner);
~~~

## game_console.h

---

### handle_event

~~~cpp
bool game_console::handle_event(const SDL_Event &event)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

This overload performs the operation identified by its signature. Review its parameter and return metadata below, and call it only in the lifecycle phase required by the owning component.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `event` | `const SDL_Event &` | Value supplied for the event parameter. | — |

---

### hide_console

~~~cpp
void game_console::hide_console()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

---

### is_console_visible

~~~cpp
bool game_console::is_console_visible()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### is_supported

~~~cpp
bool game_console::is_supported()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### show_console

~~~cpp
bool game_console::show_console()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters:** None.

---

### toggle_console

~~~cpp
void game_console::toggle_console()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the toggle console operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### Header usage example

~~~cpp
if (Game_Console::is_supported()) Game_Console::toggle_console();
~~~

## save_game.h

---

### add

~~~cpp
void Save_Pool::add(Object *object)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

This overload performs the operation identified by its signature. Review its parameter and return metadata below, and call it only in the lifecycle phase required by the owning component.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `object` | `Object *` | Value supplied for the object parameter. | — |

---

### apply_snapshot

~~~cpp
bool Save_Game::apply_snapshot(const Snapshot &snapshot)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Applies the requested state change to the target object or service. Validate target pointers and preconditions before invoking the operation.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `snapshot` | `const Snapshot &` | Value supplied for the snapshot parameter. | — |

---

### capture_current

~~~cpp
Snapshot Save_Game::capture_current()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Snapshot`

Serializes or captures the requested engine state. The destination and success reporting behavior follow the parameters and return type shown below.

**Parameters:** None.

---

### capture_object

~~~cpp
Object_State Save_Game::capture_object(const Object &object)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Object_State`

Serializes or captures the requested engine state. The destination and success reporting behavior follow the parameters and return type shown below.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `object` | `const Object &` | Value supplied for the object parameter. | — |

---

### capture_snapshot

~~~cpp
Save_Game::Snapshot Save_Pool::capture_snapshot() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Save_Game::Snapshot`

Serializes or captures the requested engine state. The destination and success reporting behavior follow the parameters and return type shown below.

**Parameters:** None.

---

### clear

~~~cpp
void Save_Pool::clear()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### contains

~~~cpp
bool Save_Pool::contains(const Object *object) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the contains operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `object` | `const Object *` | Value supplied for the object parameter. | — |

---

### empty

~~~cpp
bool Save_Pool::empty() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### get_all

~~~cpp
std::vector< Object * > Save_Pool::get_all() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< Object * >`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### load_and_apply

~~~cpp
bool Save_Game::load_and_apply(const std::string &path)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `path` | `const std::string &` | Value supplied for the path parameter. | — |

---

### load_snapshot

~~~cpp
bool Save_Game::load_snapshot(const std::string &path, Snapshot &out_snapshot)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `path` | `const std::string &` | Value supplied for the path parameter. | — |
| `out_snapshot` | `Snapshot &` | Value supplied for the out_snapshot parameter. | — |

---

### remove

~~~cpp
void Save_Pool::remove(Object *object)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `object` | `Object *` | Value supplied for the object parameter. | — |

---

### save_current

~~~cpp
bool Save_Game::save_current(const std::string &path)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Serializes or captures the requested engine state. The destination and success reporting behavior follow the parameters and return type shown below.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `path` | `const std::string &` | Value supplied for the path parameter. | — |

---

### save_snapshot

~~~cpp
bool Save_Game::save_snapshot(const Snapshot &snapshot, const std::string &path)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Serializes or captures the requested engine state. The destination and success reporting behavior follow the parameters and return type shown below.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `snapshot` | `const Snapshot &` | Value supplied for the snapshot parameter. | — |
| `path` | `const std::string &` | Value supplied for the path parameter. | — |

---

### Header usage example

~~~cpp
Save_Game::save_current("saves/slot1.bin");
Save_Game::load_and_apply("saves/slot1.bin");
~~~













