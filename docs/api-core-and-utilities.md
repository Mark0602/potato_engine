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

### ~Application

~~~cpp
Engine::Application::~Application()
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

### ~SDLstate

~~~cpp
SDLstate::~SDLstate()
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

### Application

~~~cpp
Engine::Application::Application(config::game_config config={})
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Application value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `config` (`config::game_config`): Value supplied for the config parameter.

### Application

~~~cpp
Engine::Application::Application(const Application &)=delete
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Application value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`const Application &`): Value supplied for the  parameter.

### begin_frame

~~~cpp
bool SDLstate::begin_frame()
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** None.

### clearup

~~~cpp
void SDLstate::clearup()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

### get_renderer_backend

~~~cpp
RendererBackend SDLstate::get_renderer_backend() const
~~~

**Access:** public  **Returns:** `RendererBackend`  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### getlogicalheight

~~~cpp
std::uint16_t SDLstate::getlogicalheight() const
~~~

**Access:** public  **Returns:** ``std::uint16_t``  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### getlogicalwidth

~~~cpp
std::uint16_t SDLstate::getlogicalwidth() const
~~~

**Access:** public  **Returns:** ``std::uint16_t``  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### getwindowheight

~~~cpp
std::uint16_t SDLstate::getwindowheight() const
~~~

**Access:** public  **Returns:** ``std::uint16_t``  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### getwindowwidth

~~~cpp
std::uint16_t SDLstate::getwindowwidth() const
~~~

**Access:** public  **Returns:** ``std::uint16_t``  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### initialize

~~~cpp
bool Engine::Application::initialize()
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Performs the initialize operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### initiate

~~~cpp
bool SDLstate::initiate(RendererBackend backend=RendererBackend::CPU)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Performs the initiate operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `backend` (`RendererBackend`): Value supplied for the backend parameter. Default: `RendererBackend::CPU`.

### is_gpu_renderer

~~~cpp
bool SDLstate::is_gpu_renderer() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### is_initialized

~~~cpp
bool Engine::Application::is_initialized() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### load_config

~~~cpp
static bool config::load_config(const std::string &path, project_config &pconf, game_config &gconf, settings &settings)
~~~

**Access:** public  **Storage:** static  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters**

- `path` (`const std::string &`): Value supplied for the path parameter.
- `pconf` (`project_config &`): Value supplied for the pconf parameter.
- `gconf` (`game_config &`): Value supplied for the gconf parameter.
- `settings` (`settings &`): Value supplied for the settings parameter.

### operator=

~~~cpp
Application & Engine::Application::operator=(const Application &)=delete
~~~

**Access:** public  **Returns:** `Application &`  **Engine version:** Potato Engine 1.0.0

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`const Application &`): Value supplied for the  parameter.

### operator=

~~~cpp
SDLstate & SDLstate::operator=(const SDLstate &)=delete
~~~

**Access:** public  **Returns:** `SDLstate &`  **Engine version:** Potato Engine 1.0.0

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`const SDLstate &`): Value supplied for the  parameter.

### present

~~~cpp
void SDLstate::present()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** None.

### quit

~~~cpp
void Engine::quit()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Performs the quit operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### run

~~~cpp
int Engine::Application::run()
~~~

**Access:** public  **Returns:** ``int``  **Engine version:** Potato Engine 1.0.0

Performs the run operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### SDLstate

~~~cpp
SDLstate::SDLstate(const SDLstate &)=delete
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a SDLstate value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`const SDLstate &`): Value supplied for the  parameter.

### SDLstate

~~~cpp
SDLstate::SDLstate(std::string title="Potato Engine", std::uint16_t window_width=1280, std::uint16_t window_height=720, std::uint16_t logical_width=1280, std::uint16_t logical_height=720)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a SDLstate value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `title` (`std::string`): Value supplied for the title parameter.
- `window_width` (`std::uint16_t`): Value supplied for the window_width parameter.
- `window_height` (`std::uint16_t`): Value supplied for the window_height parameter.
- `logical_width` (`std::uint16_t`): Value supplied for the logical_width parameter.
- `logical_height` (`std::uint16_t`): Value supplied for the logical_height parameter.

### shutdown

~~~cpp
void Engine::Application::shutdown()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

### using_gpu_renderer

~~~cpp
bool Engine::using_gpu_renderer()
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Performs the using gpu renderer operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### Header usage example

~~~cpp
config::game_config cfg;
cfg.title = "Potato Demo";
Engine::Application app(cfg);
if (!app.initialize()) return 1;
return app.run();
~~~

## vec.h

### operator-

~~~cpp
Transform Transform::operator-(const Transform &other) const
~~~

**Access:** public  **Returns:** `Transform`  **Engine version:** Potato Engine 1.0.0

Constructs a Header usage example value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `other` (`const Transform &`): Value supplied for the other parameter.

### operator-

~~~cpp
Vec Vec::operator-(const Vec &a) const
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Implements the operator- operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### operator-=

~~~cpp
Transform & Transform::operator-=(const Transform &other)
~~~

**Access:** public  **Returns:** `Transform &`  **Engine version:** Potato Engine 1.0.0

Implements the operator-= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `other` (`const Transform &`): Value supplied for the other parameter.

### operator-=

~~~cpp
Vec & Vec::operator-=(const Vec &b)
~~~

**Access:** public  **Returns:** `Vec &`  **Engine version:** Potato Engine 1.0.0

Implements the operator-= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `b` (`const Vec &`): Value supplied for the b parameter.

### operator!=

~~~cpp
bool Vec::operator!=(const Vec &a) const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Implements the operator!= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### operator*

~~~cpp
Transform Transform::operator*(float scalar) const
~~~

**Access:** public  **Returns:** `Transform`  **Engine version:** Potato Engine 1.0.0

Implements the operator* operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `scalar` (`float`): Value supplied for the scalar parameter.

### operator*

~~~cpp
Vec Vec::operator*(const Vec &a) const
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Component-wise multiplication.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### operator*

~~~cpp
Vec Vec::operator*(float b) const
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Scalar multiplication.

**Parameters**

- `b` (`float`): Value supplied for the b parameter.

### operator*=

~~~cpp
Transform & Transform::operator*=(float scalar)
~~~

**Access:** public  **Returns:** `Transform &`  **Engine version:** Potato Engine 1.0.0

Implements the operator* operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `scalar` (`float`): Value supplied for the scalar parameter.

### operator*=

~~~cpp
Vec & Vec::operator*=(const Vec &b)
~~~

**Access:** public  **Returns:** `Vec &`  **Engine version:** Potato Engine 1.0.0

Component-wise multiply-assign.

**Parameters**

- `b` (`const Vec &`): Value supplied for the b parameter.

### operator*=

~~~cpp
Vec & Vec::operator*=(float b)
~~~

**Access:** public  **Returns:** `Vec &`  **Engine version:** Potato Engine 1.0.0

Implements the operator*= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `b` (`float`): Value supplied for the b parameter.

### operator/

~~~cpp
Transform Transform::operator/(float scalar) const
~~~

**Access:** public  **Returns:** `Transform`  **Engine version:** Potato Engine 1.0.0

Implements the operator/ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `scalar` (`float`): Value supplied for the scalar parameter.

### operator/

~~~cpp
Vec Vec::operator/(float b) const
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Scalar division. Behaviour is undefined if b is zero.

**Parameters**

- `b` (`float`): Value supplied for the b parameter.

### operator/=

~~~cpp
Transform & Transform::operator/=(float scalar)
~~~

**Access:** public  **Returns:** `Transform &`  **Engine version:** Potato Engine 1.0.0

Implements the operator/ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `scalar` (`float`): Value supplied for the scalar parameter.

### operator/=

~~~cpp
Vec & Vec::operator/=(float b)
~~~

**Access:** public  **Returns:** `Vec &`  **Engine version:** Potato Engine 1.0.0

Implements the operator/= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `b` (`float`): Value supplied for the b parameter.

### operator+

~~~cpp
Transform Transform::operator+(const Transform &other) const
~~~

**Access:** public  **Returns:** `Transform`  **Engine version:** Potato Engine 1.0.0

Implements the operator+ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `other` (`const Transform &`): Value supplied for the other parameter.

### operator+

~~~cpp
Vec Vec::operator+(const Vec &a) const
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Implements the operator+ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### operator+=

~~~cpp
Transform & Transform::operator+=(const Transform &other)
~~~

**Access:** public  **Returns:** `Transform &`  **Engine version:** Potato Engine 1.0.0

Implements the operator+= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `other` (`const Transform &`): Value supplied for the other parameter.

### operator+=

~~~cpp
Vec & Vec::operator+=(const Vec &a)
~~~

**Access:** public  **Returns:** `Vec &`  **Engine version:** Potato Engine 1.0.0

Implements the operator+= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### operator<

~~~cpp
bool Vec::operator<(const Vec &a) const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

True only if both x and y are strictly less.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### operator<=

~~~cpp
bool Vec::operator<=(const Vec &a) const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Implements the operator< operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### operator==

~~~cpp
bool Vec::operator==(const Vec &a) const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Implements the operator== operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### operator>

~~~cpp
bool Vec::operator>(const Vec &a) const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

True only if both x and y are strictly greater.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### operator>=

~~~cpp
bool Vec::operator>=(const Vec &a) const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Implements the operator> operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### Transform

~~~cpp
Transform::Transform()=default
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Transform value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### Transform

~~~cpp
Transform::Transform(const Vec &pos, const Vec &size, const Vec &rotation)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Transform with given position, size, and rotation.

**Parameters**

- `pos` (`const Vec &`): Position in 2D space.
- `size` (`const Vec &`): Size in 2D space.
- `rotation` (`const Vec &`): Rotation in 2D space. x is the angle in degrees, y is the SDL_FlipMode.

### Transform

~~~cpp
Transform::Transform(const Vec &pos, const Vec &size)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Transform with given position and size.

**Parameters**

- `pos` (`const Vec &`): Position in 2D space.
- `size` (`const Vec &`): Size in 2D space.

### Transform

~~~cpp
Transform::Transform(const Vec &pos)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Transform with given position.

**Parameters**

- `pos` (`const Vec &`): Position in 2D space.

### Vec

~~~cpp
Vec::Vec()=default
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Transform value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### Vec

~~~cpp
Vec::Vec(float x, float y)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Vec with given x and y values.

**Parameters**

- `x` (`float`): Horizontal component.
- `y` (`float`): Vertical component.

### Header usage example

~~~cpp
Vec velocity{120.0f, 0.0f};
Transform player{{32.0f, 48.0f}, {16.0f, 16.0f}};
player.pos += velocity * delta_seconds;
~~~

## color.h

### black

~~~cpp
static const Color Color::black()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined black color (0, 0, 0, 255).

**Parameters:** None.

### blue

~~~cpp
static const Color Color::blue()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined blue color (0, 0, 255, 255).

**Parameters:** None.

### brown

~~~cpp
static const Color Color::brown()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined brown color (165, 42, 42, 255).

**Parameters:** None.

### Color

~~~cpp
Color::Color()=default
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Color with specified red, green, blue, and alpha values.

**Parameters:** None.

### Color

~~~cpp
Color::Color(const SDL_Color &color)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Color from an SDL_Color.

**Parameters**

- `color` (`const SDL_Color &`): SDL_Color to convert to Color. Constructs a Color from an SDL_Color.

### Color

~~~cpp
Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a=255)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Color with specified red, green, blue, and alpha values.

**Parameters**

- `r` (`uint8_t`): Red component (0-255).
- `g` (`uint8_t`): Green component (0-255).
- `b` (`uint8_t`): Blue component (0-255).
- `a` (`uint8_t`): Alpha component (0-255). Constructs a Color with specified RGBA values.

### cyan

~~~cpp
static const Color Color::cyan()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined cyan color (0, 255, 255, 255).

**Parameters:** None.

### dark_blue

~~~cpp
static const Color Color::dark_blue()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined dark blue color (0, 0, 139, 255).

**Parameters:** None.

### dark_cyan

~~~cpp
static const Color Color::dark_cyan()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined dark cyan color (0, 139, 139, 255).

**Parameters:** None.

### dark_gray

~~~cpp
static const Color Color::dark_gray()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined dark gray color (169, 169, 169, 255).

**Parameters:** None.

### dark_green

~~~cpp
static const Color Color::dark_green()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined dark green color (0, 100, 0, 255).

**Parameters:** None.

### dark_magenta

~~~cpp
static const Color Color::dark_magenta()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined dark magenta color (139, 0, 139, 255).

**Parameters:** None.

### dark_red

~~~cpp
static const Color Color::dark_red()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined dark red color (139, 0, 0, 255).

**Parameters:** None.

### dark_yellow

~~~cpp
static const Color Color::dark_yellow()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined dark yellow color (204, 204, 0, 255).

**Parameters:** None.

### from_hex

~~~cpp
static Color Color::from_hex(uint32_t hex)
~~~

**Access:** public  **Storage:** static  **Returns:** `Color`  **Engine version:** Potato Engine 1.0.0

Creates a Color from a hexadecimal value.

**Parameters**

- `hex` (`uint32_t`): Hexadecimal value representing the color (0xRRGGBBAA).

### from_hex_string

~~~cpp
static Color Color::from_hex_string(std::string hex_string)
~~~

**Access:** public  **Storage:** static  **Returns:** `Color`  **Engine version:** Potato Engine 1.0.0

Creates a Color from a hexadecimal string.

**Parameters**

- `hex_string` (`std::string`): Hexadecimal string representing the color (e.g., "FF00FF00").

### from_sdl_color

~~~cpp
static Color Color::from_sdl_color(const SDL_Color &color)
~~~

**Access:** public  **Storage:** static  **Returns:** `Color`  **Engine version:** Potato Engine 1.0.0

Creates a Color from an SDL_Color.

**Parameters**

- `color` (`const SDL_Color &`): SDL_Color to convert to Color.

### gray

~~~cpp
static const Color Color::gray()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined gray color (128, 128, 128, 255).

**Parameters:** None.

### green

~~~cpp
static const Color Color::green()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined green color (0, 255, 0, 255).

**Parameters:** None.

### light_blue

~~~cpp
static const Color Color::light_blue()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined light blue color (173, 216, 230, 255).

**Parameters:** None.

### light_cyan

~~~cpp
static const Color Color::light_cyan()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined light cyan color (224, 255, 255, 255).

**Parameters:** None.

### light_gray

~~~cpp
static const Color Color::light_gray()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined light gray color (211, 211, 211, 255).

**Parameters:** None.

### light_green

~~~cpp
static const Color Color::light_green()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined light green color (144, 238, 144, 255).

**Parameters:** None.

### light_magenta

~~~cpp
static const Color Color::light_magenta()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined light magenta color (255, 182, 255, 255).

**Parameters:** None.

### light_red

~~~cpp
static const Color Color::light_red()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined light red color (255, 182, 193, 255).

**Parameters:** None.

### light_yellow

~~~cpp
static const Color Color::light_yellow()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined light yellow color (255, 255, 224, 255).

**Parameters:** None.

### magenta

~~~cpp
static const Color Color::magenta()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined magenta color (255, 0, 255, 255).

**Parameters:** None.

### operator-

~~~cpp
Color Color::operator-(const Color &other) const
~~~

**Access:** public  **Returns:** `Color`  **Engine version:** Potato Engine 1.0.0

Constructs a Vec value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `other` (`const Color &`): Value supplied for the other parameter.

### operator-=

~~~cpp
Color & Color::operator-=(const Color &other)
~~~

**Access:** public  **Returns:** `Color &`  **Engine version:** Potato Engine 1.0.0

Implements the operator-= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `other` (`const Color &`): Value supplied for the other parameter.

### operator!=

~~~cpp
bool Color::operator!=(const Color &other) const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Implements the operator!= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `other` (`const Color &`): Value supplied for the other parameter.

### operator*

~~~cpp
Color Color::operator*(float scalar) const
~~~

**Access:** public  **Returns:** `Color`  **Engine version:** Potato Engine 1.0.0

Implements the operator* operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `scalar` (`float`): Value supplied for the scalar parameter.

### operator*=

~~~cpp
Color & Color::operator*=(float scalar)
~~~

**Access:** public  **Returns:** `Color &`  **Engine version:** Potato Engine 1.0.0

Implements the operator*= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `scalar` (`float`): Value supplied for the scalar parameter.

### operator/

~~~cpp
Color Color::operator/(float scalar) const
~~~

**Access:** public  **Returns:** `Color`  **Engine version:** Potato Engine 1.0.0

Implements the operator/ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `scalar` (`float`): Value supplied for the scalar parameter.

### operator/=

~~~cpp
Color & Color::operator/=(float scalar)
~~~

**Access:** public  **Returns:** `Color &`  **Engine version:** Potato Engine 1.0.0

Implements the operator/= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `scalar` (`float`): Value supplied for the scalar parameter.

### operator+

~~~cpp
Color Color::operator+(const Color &other) const
~~~

**Access:** public  **Returns:** `Color`  **Engine version:** Potato Engine 1.0.0

Implements the operator+ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `other` (`const Color &`): Value supplied for the other parameter.

### operator+=

~~~cpp
Color & Color::operator+=(const Color &other)
~~~

**Access:** public  **Returns:** `Color &`  **Engine version:** Potato Engine 1.0.0

Implements the operator+= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `other` (`const Color &`): Value supplied for the other parameter.

### operator==

~~~cpp
bool Color::operator==(const Color &other) const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Implements the operator== operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `other` (`const Color &`): Value supplied for the other parameter.

### orange

~~~cpp
static const Color Color::orange()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined orange color (255, 165, 0, 255).

**Parameters:** None.

### pink

~~~cpp
static const Color Color::pink()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined pink color (255, 192, 203, 255).

**Parameters:** None.

### purple

~~~cpp
static const Color Color::purple()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined purple color (128, 0, 128, 255).

**Parameters:** None.

### red

~~~cpp
static const Color Color::red()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined red color (255, 0, 0, 255).

**Parameters:** None.

### to_sdl_color

~~~cpp
SDL_Color Color::to_sdl_color() const
~~~

**Access:** public  **Returns:** ``SDL_Color``  **Engine version:** Potato Engine 1.0.0

Converts the Color to an SDL_Color.

**Parameters:** None.

### transparent

~~~cpp
static const Color Color::transparent()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined transparent color (0, 0, 0, 0).

**Parameters:** None.

### white

~~~cpp
static const Color Color::white()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined white color (255, 255, 255, 255).

**Parameters:** None.

### with_alpha

~~~cpp
Color Color::with_alpha(uint8_t alpha) const
~~~

**Access:** public  **Returns:** `Color`  **Engine version:** Potato Engine 1.0.0

Creates a Color with specified alpha value.

**Parameters**

- `alpha` (`uint8_t`): Alpha component (0.0f - 1.0f).

### yellow

~~~cpp
static const Color Color::yellow()
~~~

**Access:** public  **Storage:** static  **Returns:** `const Color`  **Engine version:** Potato Engine 1.0.0

Predefined yellow color (255, 255, 0, 255).

**Parameters:** None.

### Header usage example

~~~cpp
Color tint = Color::from_hex_string("#FFAA33");
tint = tint.with_alpha(192);
~~~

## utils.h

### abs

~~~cpp
Vec abs(const Vec &a)
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Returns a vector with each component replaced by its absolute value.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### angle

~~~cpp
float angle(const Vec &a, const Vec &b)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Angle (radians) from point a to point b, measured from the positive X axis.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.
- `b` (`const Vec &`): Value supplied for the b parameter.

### angle_between

~~~cpp
float angle_between(const Vec &a, const Vec &b)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Unsigned angle between two direction vectors (radians).

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.
- `b` (`const Vec &`): Value supplied for the b parameter.

### angle_between_degrees

~~~cpp
float angle_between_degrees(const Vec &a, const Vec &b)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Unsigned angle between two vectors in degrees. See angle_between().

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.
- `b` (`const Vec &`): Value supplied for the b parameter.

### angle_between_radians

~~~cpp
float angle_between_radians(const Vec &a, const Vec &b)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Alias for angle_between() — returns the unsigned angle in radians.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.
- `b` (`const Vec &`): Value supplied for the b parameter.

### angle_between_signed

~~~cpp
float angle_between_signed(const Vec &a, const Vec &b)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Signed angle from a to b (radians). Positive = counter-clockwise.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.
- `b` (`const Vec &`): Value supplied for the b parameter.

### angle_between_signed_degrees

~~~cpp
float angle_between_signed_degrees(const Vec &a, const Vec &b)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Signed angle from a to b in degrees. See angle_between_signed().

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.
- `b` (`const Vec &`): Value supplied for the b parameter.

### angle_between_signed_radians

~~~cpp
float angle_between_signed_radians(const Vec &a, const Vec &b)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Alias for angle_between_signed() — returns the signed angle in radians.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.
- `b` (`const Vec &`): Value supplied for the b parameter.

### ceil

~~~cpp
Vec ceil(const Vec &a)
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Returns a vector with each component rounded up to the nearest integer.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### clamp

~~~cpp
float clamp(float value, float min, float max)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Clamps a float value between a minimum and maximum.

**Parameters**

- `value` (`float`): The value to clamp.
- `min` (`float`): The minimum value.
- `max` (`float`): The maximum value.

### clamp

~~~cpp
int clamp(int value, int min, int max)
~~~

**Access:** public  **Returns:** ``int``  **Engine version:** Potato Engine 1.0.0

Clamps an integer value between a minimum and maximum.

**Parameters**

- `value` (`int`): The value to clamp.
- `min` (`int`): The minimum value.
- `max` (`int`): The maximum value.

### clamp

~~~cpp
Vec clamp(const Vec &a, const Vec &min, const Vec &max)
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Clamps each component of a between the corresponding components of min and max.

**Parameters**

- `a` (`const Vec &`): Value to clamp.
- `min` (`const Vec &`): Per-component minimum.
- `max` (`const Vec &`): Per-component maximum.

### convert_FRect_to_Vec

~~~cpp
Vec convert_FRect_to_Vec(const SDL_FRect &rect)
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Extracts the top-left position {x, y} from an SDL_FRect as a Vec.

**Parameters**

- `rect` (`const SDL_FRect &`): Value supplied for the rect parameter.

### convert_Vec_to_FRect

~~~cpp
SDL_FRect convert_Vec_to_FRect(const Vec &a, const Vec &size)
~~~

**Access:** public  **Returns:** ``SDL_FRect``  **Engine version:** Potato Engine 1.0.0

Converts a position Vec and a size Vec into an SDL_FRect.

**Parameters**

- `a` (`const Vec &`): Top-left position.
- `size` (`const Vec &`): Width and height.

### cross

~~~cpp
float cross(const Vec &a, const Vec &b)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

2D cross product (scalar). Positive if b is counter-clockwise from a.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.
- `b` (`const Vec &`): Value supplied for the b parameter.

### distance

~~~cpp
float distance(const Vec &a, const Vec &b)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Calculates the distance between two Vec points.

**Parameters**

- `a` (`const Vec &`): The first Vec point.
- `b` (`const Vec &`): The second Vec point.

### distance_squared

~~~cpp
float distance_squared(const Vec &a, const Vec &b)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Calculates the squared distance between two Vec points.

**Parameters**

- `a` (`const Vec &`): The first Vec point.
- `b` (`const Vec &`): The second Vec point.

### dot

~~~cpp
float dot(const Vec &a, const Vec &b)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Dot product of two vectors. Positive = same direction, 0 = perpendicular, negative = opposite.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.
- `b` (`const Vec &`): Value supplied for the b parameter.

### floor

~~~cpp
Vec floor(const Vec &a)
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Returns a vector with each component rounded down to the nearest integer.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### fullscreen_window

~~~cpp
void fullscreen_window(SDL_Window *window)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the SDL window to fullscreen mode if it is valid.

**Parameters**

- `window` (`SDL_Window *`): Pointer to the SDL_Window to set to fullscreen. If nullptr, the function

### get_mouse_position

~~~cpp
static Vec get_mouse_position()
~~~

**Access:** public  **Storage:** static  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets the current mouse position in logical coordinates. This function retrieves the current mouse position in window coordinates and converts it to logical coordinates based on the current SDL renderer.

**Parameters:** None.

### get_window_bottom_center

~~~cpp
Vec get_window_bottom_center()
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets the bottom-center point of the window in logical coordinates as a Vec. This function calculates the bottom-center point of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

### get_window_bottom_left

~~~cpp
Vec get_window_bottom_left()
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets the top-right corner of the window in logical coordinates as a Vec. This function calculates the top-right corner of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

### get_window_bottom_right

~~~cpp
Vec get_window_bottom_right()
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets the bottom-right corner of the window in logical coordinates as a Vec. This function calculates the bottom-right corner of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

### get_window_center

~~~cpp
Vec get_window_center()
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets the center of the window in logical coordinates as a Vec. This function calculates the center point of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

### get_window_left_center

~~~cpp
Vec get_window_left_center()
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets the left-center point of the window in logical coordinates as a Vec. This function calculates the left-center point of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

### get_window_right_center

~~~cpp
Vec get_window_right_center()
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets the right-center point of the window in logical coordinates as a Vec. This function calculates the right-center point of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

### get_window_size

~~~cpp
Vec get_window_size()
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets the window size in logical coordinates as a Vec. This function retrieves the current size of the SDL window and returns it as a Vec, where x is the width and y is the height.

**Parameters:** None.

### get_window_top_center

~~~cpp
Vec get_window_top_center()
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets the top-center point of the window in logical coordinates as a Vec. This function calculates the top-center point of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

### get_window_top_left

~~~cpp
Vec get_window_top_left()
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets the top-left corner of the window in logical coordinates as a Vec. This function returns the top-left corner of the SDL window, which is always at (0, 0) in logical coordinates.

**Parameters:** None.

### get_window_top_right

~~~cpp
Vec get_window_top_right()
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets the bottom-left corner of the window in logical coordinates as a Vec. This function calculates the bottom-left corner of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

### invert

~~~cpp
Vec invert(const Vec &a)
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Returns a vector pointing in the opposite direction (-x, -y).

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### is_point_in_circle

~~~cpp
bool is_point_in_circle(const Vec &point, const Vec &circle_center, float radius)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Tests whether a point lies inside or on the boundary of a circle.

**Parameters**

- `point` (`const Vec &`): Point to test.
- `circle_center` (`const Vec &`): Centre of the circle.
- `radius` (`float`): Radius of the circle.

### is_point_in_rect

~~~cpp
bool is_point_in_rect(const Vec &point, const Vec &rect_Vec, const SDL_FRect &rect)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Tests whether a point is inside an SDL_FRect offset by rect_Vec.

**Parameters**

- `point` (`const Vec &`): Point to test in logical coordinates.
- `rect_Vec` (`const Vec &`): Top-left offset added to rect.x/y.
- `rect` (`const SDL_FRect &`): Rectangle (x, y ignored; w, h used for size).

### length

~~~cpp
float length(const Vec &a)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Calculates the length (magnitude) of a Vec.

**Parameters**

- `a` (`const Vec &`): The Vec whose length is to be calculated.

### length_squared

~~~cpp
float length_squared(const Vec &a)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Calculates the squared length (magnitude) of a Vec.

**Parameters**

- `a` (`const Vec &`): The Vec whose squared length is to be calculated.

### lerp

~~~cpp
Vec lerp(const Vec &a, const Vec &b, float t)
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Linearly interpolates between two vectors.

**Parameters**

- `a` (`const Vec &`): Start value (t = 0).
- `b` (`const Vec &`): End value (t = 1).
- `t` (`float`): Blend factor. Clamping to [0, 1] is the caller's responsibility.

### lerp_color

~~~cpp
void lerp_color(Color &color, const Color &target, float t)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Linearly interpolates between two colors.

**Parameters**

- `color` (`Color &`): The starting color, which will be modified to the interpolated value.
- `target` (`const Color &`): The target color to interpolate towards.
- `t` (`float`): The interpolation factor, where 0.0 returns color and 1.0 returns target. Values outside the range [0.0, 1.0] will extrapolate beyond the two colors.

### maximize_window

~~~cpp
void maximize_window(SDL_Window *window)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Maximizes the SDL window if it is valid.

**Parameters**

- `window` (`SDL_Window *`): Pointer to the SDL_Window to maximize. If nullptr, the function does nothing.

### nearly_equal

~~~cpp
bool nearly_equal(const Vec &a, const Vec &b, float epsilon=0.01f)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks if two Vec points are nearly equal within a given epsilon.

**Parameters**

- `a` (`const Vec &`): The first Vec point.
- `b` (`const Vec &`): The second Vec point.
- `epsilon` (`float`): The tolerance for equality. Default is 0.01f.

### normalize

~~~cpp
Vec normalize(const Vec &a)
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Returns a unit vector in the same direction as a. Returns {0,0} if a is zero.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### os_cursor_visibility

~~~cpp
void os_cursor_visibility(bool visible, Logger *logger=nullptr)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Changes the visibility of the OS cursor.

**Parameters**

- `visible` (`bool`): If true, the cursor will be shown; if false, it will be hidden.
- `logger` (`Logger *`): Optional logger for debugging purposes. By default nullptr, which means no logging will occur.

### perpendicular

~~~cpp
Vec perpendicular(const Vec &a)
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Returns a vector perpendicular to a, rotated 90° counter-clockwise.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### reflect

~~~cpp
Vec reflect(const Vec &a, const Vec &normal)
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Reflects vector a off a surface with the given unit normal.

**Parameters**

- `a` (`const Vec &`): Incoming direction vector.
- `normal` (`const Vec &`): Unit normal of the surface.

### rotate

~~~cpp
Vec rotate(const Vec &a, float angle)
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Rotates vector a by angle degrees counter-clockwise.

**Parameters**

- `a` (`const Vec &`): Vector to rotate.
- `angle` (`float`): Rotation angle in degrees.

### round

~~~cpp
Vec round(const Vec &a)
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Returns a vector with each component rounded to the nearest integer.

**Parameters**

- `a` (`const Vec &`): Value supplied for the a parameter.

### windowed_window

~~~cpp
void windowed_window(SDL_Window *window)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the SDL window to windowed mode if it is valid.

**Parameters**

- `window` (`SDL_Window *`): Pointer to the SDL_Window to set to windowed mode. If nullptr, the function does nothing.

### Header usage example

~~~cpp
Vec direction = normalize(target - origin);
float separation = distance(origin, target);
~~~

## debug.h

### close

~~~cpp
void Logger::close()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Flushes and closes the log file.

**Parameters:** None.

### finalize_log

~~~cpp
void Logger::finalize_log()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Flushes and renames the log file to a timestamped filename. Call this on clean shutdown so the log is not overwritten next run.

**Parameters:** None.

### flood_logging

~~~cpp
void Logger::flood_logging(bool state)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Enables or disables flood logging (DEBUG messages every frame). Disable this in release builds to avoid log spam.

**Parameters**

- `state` (`bool`): true to enable.

### format_line

~~~cpp
std::string Logger::format_line(Log_Level level, const std::string &category, const std::string &message)
~~~

**Access:** private  **Returns:** ``std::string``  **Engine version:** Potato Engine 1.0.0

Performs the orange operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `level` (`Log_Level`): Value supplied for the level parameter.
- `category` (`const std::string &`): Value supplied for the category parameter.
- `message` (`const std::string &`): Value supplied for the message parameter.

### frame_indexing

~~~cpp
void Logger::frame_indexing(bool state)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Enables or disables per-frame index prefixes in log lines.

**Parameters**

- `state` (`bool`): true to enable frame indexing.

### get_elapsed_time_string

~~~cpp
std::string Logger::get_elapsed_time_string()
~~~

**Access:** private  **Returns:** ``std::string``  **Engine version:** Potato Engine 1.0.0

Performs the frame indexing operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### get_logged_message

~~~cpp
std::string Logger::get_logged_message()
~~~

**Access:** public  **Returns:** ``std::string``  **Engine version:** Potato Engine 1.0.0

Retrieves the entire contents of the log file as a string.

**Parameters:** None.

### get_min_level

~~~cpp
Log_Level Logger::get_min_level() const
~~~

**Access:** public  **Returns:** `Log_Level`  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### increment_frame_index

~~~cpp
void Logger::increment_frame_index()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Increments the internal frame counter by 1.

**Parameters:** None.

### init

~~~cpp
void Logger::init(const std::string &filepath="logs/latest.log")
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Opens the log file and starts the timer.

**Parameters**

- `filepath` (`const std::string &`): Path to the log file. Default: "logs/latest.log".

### is_flood_logging

~~~cpp
bool Logger::is_flood_logging() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Performs the increment frame index operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### is_initialized

~~~cpp
bool Logger::is_initialized() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### level_to_string

~~~cpp
static const char * Logger::level_to_string(Log_Level level)
~~~

**Access:** private  **Storage:** static  **Returns:** ``const char *``  **Engine version:** Potato Engine 1.0.0

Performs the level to string operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `level` (`Log_Level`): Value supplied for the level parameter.

### log

~~~cpp
void Logger::log(Log_Level level, const std::string &category, const std::string &message)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Writes a message to the log (file + stdout).

**Parameters**

- `level` (`Log_Level`): Severity level of the message.
- `category` (`const std::string &`): Short label identifying the system (e.g. "Render", "Input").
- `message` (`const std::string &`): The log message text.

### Logger

~~~cpp
Logger::Logger()
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Performs the log operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### set_frame_index

~~~cpp
void Logger::set_frame_index(long index)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Manually sets the frame counter.

**Parameters**

- `index` (`long`): The frame index value to set.

### set_min_level

~~~cpp
void Logger::set_min_level(Log_Level level)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the minimum level to log. Messages below this are ignored.

**Parameters**

- `level` (`Log_Level`): The new minimum Log_Level.

### Header usage example

~~~cpp
Logger logger;
logger.init("logs/latest.log");
logger.log(Log_Level::INFO, "Game", "Started");
~~~

## timer.h

### elapsed

~~~cpp
float Timer::elapsed() const
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** None.

### is_just_done

~~~cpp
bool Timer::is_just_done() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### is_running

~~~cpp
bool Timer::is_running() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### progress

~~~cpp
float Timer::progress() const
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Performs the progress operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### remaining

~~~cpp
float Timer::remaining() const
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Performs the remaining operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### start

~~~cpp
void Timer::start(float duration, std::function< void()> callback=nullptr)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Starts (or restarts) the timer.

**Parameters**

- `duration` (`float`): How long the timer should run in seconds.
- `callback` (`std::function< void()>`): Optional function called once when the timer expires.

### stop

~~~cpp
void Timer::stop()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Stops and resets the timer without invoking the callback.

**Parameters:** None.

### tick

~~~cpp
void Timer::tick(float delta_time)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Advances the timer. Call every frame from on_update(delta_time).

**Parameters**

- `delta_time` (`float`): Time elapsed since the last frame, in seconds.

### Timer

~~~cpp
Timer::Timer()=default
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters:** None.

### Header usage example

~~~cpp
Timer cooldown;
cooldown.start(1.0f);
cooldown.tick(delta_seconds);
~~~

## prandom.h

### device

~~~cpp
rd & prandom::device()
~~~

**Access:** public  **Returns:** `rd &`  **Engine version:** Potato Engine 1.0.0

Constructs a Header usage example value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### engine

~~~cpp
mt & prandom::engine()
~~~

**Access:** public  **Returns:** `mt &`  **Engine version:** Potato Engine 1.0.0

Performs the engine operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### random_choice

~~~cpp
T prandom::random_choice(const std::vector< T > &choices)
~~~

**Access:** public  **Returns:** ``T``  **Engine version:** Potato Engine 1.0.0

Produces a pseudo-random result constrained by the supplied range, collection, or weights. Ensure any referenced collection remains valid for the duration of the call.

**Parameters**

- `choices` (`const std::vector< T > &`): Value supplied for the choices parameter.

### random_choice_weighted

~~~cpp
T prandom::random_choice_weighted(const std::vector< T > &choices, const std::vector< float > &weight)
~~~

**Access:** public  **Returns:** ``T``  **Engine version:** Potato Engine 1.0.0

Produces a pseudo-random result constrained by the supplied range, collection, or weights. Ensure any referenced collection remains valid for the duration of the call.

**Parameters**

- `choices` (`const std::vector< T > &`): Value supplied for the choices parameter.
- `weight` (`const std::vector< float > &`): Value supplied for the weight parameter.

### random_choice_weighted

~~~cpp
T prandom::random_choice_weighted(std::initializer_list< T > choices, std::initializer_list< float > weights)
~~~

**Access:** public  **Returns:** ``T``  **Engine version:** Potato Engine 1.0.0

Produces a pseudo-random result constrained by the supplied range, collection, or weights. Ensure any referenced collection remains valid for the duration of the call.

**Parameters**

- `choices` (`std::initializer_list< T >`): Value supplied for the choices parameter.
- `weights` (`std::initializer_list< float >`): Value supplied for the weights parameter.

### random_range

~~~cpp
T prandom::random_range(T min, T max)
~~~

**Access:** public  **Returns:** ``T``  **Engine version:** Potato Engine 1.0.0

Produces a pseudo-random result constrained by the supplied range, collection, or weights. Ensure any referenced collection remains valid for the duration of the call.

**Parameters**

- `min` (`T`): Value supplied for the min parameter.
- `max` (`T`): Value supplied for the max parameter.

### random_range_weighted

~~~cpp
T prandom::random_range_weighted(T min, T max, const std::vector< float > &weight)
~~~

**Access:** public  **Returns:** ``T``  **Engine version:** Potato Engine 1.0.0

Produces a pseudo-random result constrained by the supplied range, collection, or weights. Ensure any referenced collection remains valid for the duration of the call.

**Parameters**

- `min` (`T`): Value supplied for the min parameter.
- `max` (`T`): Value supplied for the max parameter.
- `weight` (`const std::vector< float > &`): Value supplied for the weight parameter.

### random_weighted_index

~~~cpp
std::size_t prandom::random_weighted_index(const std::vector< float > &weights, Logger *logger=nullptr)
~~~

**Access:** public  **Returns:** ``std::size_t``  **Engine version:** Potato Engine 1.0.0

Produces a pseudo-random result constrained by the supplied range, collection, or weights. Ensure any referenced collection remains valid for the duration of the call.

**Parameters**

- `weights` (`const std::vector< float > &`): Value supplied for the weights parameter.
- `logger` (`Logger *`): Value supplied for the logger parameter.

### Header usage example

~~~cpp
int damage = random_range(8, 12);
~~~

## functionality_trigger.h

### clear

~~~cpp
void functionality_trigger::clear()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Constructs a Header usage example value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### evaluate

~~~cpp
bool functionality_trigger::evaluate(const std::string &trigger_id, const trigger_context &context={})
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Performs the evaluate operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `trigger_id` (`const std::string &`): Value supplied for the trigger_id parameter.
- `context` (`const trigger_context &`): Value supplied for the context parameter.

### register_source

~~~cpp
bool functionality_trigger::register_source(const std::string &trigger_id, const void *owner, trigger_source source)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters**

- `trigger_id` (`const std::string &`): Value supplied for the trigger_id parameter.
- `owner` (`const void *`): Value supplied for the owner parameter.
- `source` (`trigger_source`): Value supplied for the source parameter.

### unregister_sources

~~~cpp
void functionality_trigger::unregister_sources(const void *owner)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters**

- `owner` (`const void *`): Value supplied for the owner parameter.

### Header usage example

~~~cpp
Functionality_Trigger::register_source(owner, source);
Functionality_Trigger::unregister_sources(owner);
~~~

## game_console.h

### handle_event

~~~cpp
bool game_console::handle_event(const SDL_Event &event)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Constructs a Header usage example value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `event` (`const SDL_Event &`): Value supplied for the event parameter.

### hide_console

~~~cpp
void game_console::hide_console()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

### is_console_visible

~~~cpp
bool game_console::is_console_visible()
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### is_supported

~~~cpp
bool game_console::is_supported()
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### show_console

~~~cpp
bool game_console::show_console()
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters:** None.

### toggle_console

~~~cpp
void game_console::toggle_console()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Performs the toggle console operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### Header usage example

~~~cpp
if (Game_Console::is_supported()) Game_Console::toggle_console();
~~~

## save_game.h

### add

~~~cpp
void Save_Pool::add(Object *object)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Constructs a Header usage example value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `object` (`Object *`): Value supplied for the object parameter.

### apply_snapshot

~~~cpp
bool Save_Game::apply_snapshot(const Snapshot &snapshot)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Applies the requested state change to the target object or service. Validate target pointers and preconditions before invoking the operation.

**Parameters**

- `snapshot` (`const Snapshot &`): Value supplied for the snapshot parameter.

### capture_current

~~~cpp
Snapshot Save_Game::capture_current()
~~~

**Access:** public  **Returns:** `Snapshot`  **Engine version:** Potato Engine 1.0.0

Serializes or captures the requested engine state. The destination and success reporting behavior follow the parameters and return type shown below.

**Parameters:** None.

### capture_object

~~~cpp
Object_State Save_Game::capture_object(const Object &object)
~~~

**Access:** public  **Returns:** `Object_State`  **Engine version:** Potato Engine 1.0.0

Serializes or captures the requested engine state. The destination and success reporting behavior follow the parameters and return type shown below.

**Parameters**

- `object` (`const Object &`): Value supplied for the object parameter.

### capture_snapshot

~~~cpp
Save_Game::Snapshot Save_Pool::capture_snapshot() const
~~~

**Access:** public  **Returns:** `Save_Game::Snapshot`  **Engine version:** Potato Engine 1.0.0

Serializes or captures the requested engine state. The destination and success reporting behavior follow the parameters and return type shown below.

**Parameters:** None.

### clear

~~~cpp
void Save_Pool::clear()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

### contains

~~~cpp
bool Save_Pool::contains(const Object *object) const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Performs the contains operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `object` (`const Object *`): Value supplied for the object parameter.

### empty

~~~cpp
bool Save_Pool::empty() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### get_all

~~~cpp
std::vector< Object * > Save_Pool::get_all() const
~~~

**Access:** public  **Returns:** `std::vector< Object * >`  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### load_and_apply

~~~cpp
bool Save_Game::load_and_apply(const std::string &path)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters**

- `path` (`const std::string &`): Value supplied for the path parameter.

### load_snapshot

~~~cpp
bool Save_Game::load_snapshot(const std::string &path, Snapshot &out_snapshot)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters**

- `path` (`const std::string &`): Value supplied for the path parameter.
- `out_snapshot` (`Snapshot &`): Value supplied for the out_snapshot parameter.

### remove

~~~cpp
void Save_Pool::remove(Object *object)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters**

- `object` (`Object *`): Value supplied for the object parameter.

### save_current

~~~cpp
bool Save_Game::save_current(const std::string &path)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Serializes or captures the requested engine state. The destination and success reporting behavior follow the parameters and return type shown below.

**Parameters**

- `path` (`const std::string &`): Value supplied for the path parameter.

### save_snapshot

~~~cpp
bool Save_Game::save_snapshot(const Snapshot &snapshot, const std::string &path)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Serializes or captures the requested engine state. The destination and success reporting behavior follow the parameters and return type shown below.

**Parameters**

- `snapshot` (`const Snapshot &`): Value supplied for the snapshot parameter.
- `path` (`const std::string &`): Value supplied for the path parameter.

### Header usage example

~~~cpp
Save_Game::save_current("saves/slot1.bin");
Save_Game::load_and_apply("saves/slot1.bin");
~~~









