# Graphics and Assets API

**Engine version:** Potato Engine 1.0.0  
**Language:** C++

This reference lists every engine-owned function overload declared in the covered headers. Signatures preserve parameter types, names, default values, qualifiers, and namespaces from the source. Access labels identify members that are not part of the public calling surface.

## Detailed workflow example

~~~cpp
Engine::asset_pool->load_texture("hero", "characters/hero.png");
Texture* hero_texture = Engine::asset_pool->get_texture("hero");
if (!hero_texture || !hero_texture->is_loaded()) {
    Engine::logger->log(Log_Level::ERROR, "Assets", "Hero texture is unavailable");
    return;
}

Camera* camera = Engine::camera_pool->create("gameplay");
camera->set_viewport({1280.0f, 720.0f});
camera->set_position({640.0f, 360.0f});
camera->set_zoom(1.5f);
Engine::camera_pool->set_active("gameplay");

Draw hero_draw;
hero_draw.texture = hero_texture;
hero_draw.transform = camera->world_to_screen({{400.0f, 260.0f}, hero_texture->get_size()});
Engine::render_pool->submit(hero_draw);
~~~

## render.h

### ~GPU_Renderer

~~~cpp
GPU_Renderer::~GPU_Renderer()
~~~

**Access:** public

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

### ~Render_Pool

~~~cpp
Render_Pool::~Render_Pool()=default
~~~

**Access:** public

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

### begin_frame

~~~cpp
bool GPU_Renderer::begin_frame()
~~~

**Access:** public  **Returns:** ``bool``

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** None.

### clear

~~~cpp
void Render_Pool::clear()
~~~

**Access:** public  **Returns:** ``void``

Clears all draw commands from the pool. This does not delete the textures or objects; it simply clears the list of commands to be drawn.

**Parameters:** None.

### device

~~~cpp
SDL_GPUDevice * GPU_Renderer::device() const
~~~

**Access:** public  **Returns:** ``SDL_GPUDevice *``

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

### Draw

~~~cpp
Draw::Draw()=default
~~~

**Access:** public

Constructs a Draw value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### Draw

~~~cpp
Draw::Draw(IFont *font, const std::string &text, const Transform &transform, const Color &tint, uint8_t z_index=128, float scale=1.0f)
~~~

**Access:** public

Constructs a text draw command with the specified font, text, transform, tint, z-index and scale.

**Parameters**

- `font` (`IFont *`): Pointer to the IFont to draw with. The font is borrowed from Asset_Pool or another owner.
- `text` (`const std::string &`): Text to draw.
- `transform` (`const Transform &`): Position and optional bounds for the text.
- `tint` (`const Color &`): Text color.
- `z_index` (`uint8_t`): The z-index for draw order.
- `scale` (`float`): Text scale multiplier.

### Draw

~~~cpp
Draw::Draw(Texture *texture, const Transform &transform, const Color &tint, uint8_t z_index=128)
~~~

**Access:** public

Constructs a Draw_Command with the specified texture, transform, tint, and z-index.

**Parameters**

- `texture` (`Texture *`): Pointer to the Texture to draw.
- `transform` (`const Transform &`): The Transform (position, size, rotation) for the draw command.
- `tint` (`const Color &`): The Color tint to apply to the texture.
- `z_index` (`uint8_t`): The z-index for draw order. Lower values are drawn later (on top).

### Draw

~~~cpp
Draw::Draw(Texture *texture, const Transform &transform, uint8_t z_index)
~~~

**Access:** public

Constructs a Draw_Command with the specified texture, transform, and z-index.

**Parameters**

- `texture` (`Texture *`): Pointer to the Texture to draw.
- `transform` (`const Transform &`): The Transform (position, size, rotation) for the draw command.
- `z_index` (`uint8_t`): The z-index for draw order. Lower values are drawn later (on top).

### Draw

~~~cpp
Draw::Draw(Texture *texture, const Transform &transform)
~~~

**Access:** public

Constructs a Draw_Command with the specified texture and transform.

**Parameters**

- `texture` (`Texture *`): Pointer to the Texture to draw.
- `transform` (`const Transform &`): The Transform (position, size, rotation) for the draw command.

### driver_name

~~~cpp
const char * GPU_Renderer::driver_name() const
~~~

**Access:** public  **Returns:** ``const char *``

Constructs a Draw value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### empty

~~~cpp
bool Render_Pool::empty() const
~~~

**Access:** public  **Returns:** ``bool``

Checks if the render pool is empty (no draw commands).

**Parameters:** None.

### end_frame

~~~cpp
void GPU_Renderer::end_frame()
~~~

**Access:** public  **Returns:** ``void``

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### flush

~~~cpp
void Render_Pool::flush()
~~~

**Access:** public  **Returns:** ``void``

Sorts the draw commands by z-index and submits them to the SDL renderer. This should be called once per frame to render all queued draw commands.

**Parameters:** None.

### GPU_Renderer

~~~cpp
GPU_Renderer::GPU_Renderer()=default
~~~

**Access:** public

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters:** None.

### GPU_Renderer

~~~cpp
GPU_Renderer::GPU_Renderer(const GPU_Renderer &)=delete
~~~

**Access:** public

Constructs a GPU_Renderer value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`const GPU_Renderer &`): Value supplied for the  parameter.

### init

~~~cpp
bool GPU_Renderer::init(SDL_Window *window)
~~~

**Access:** public  **Returns:** ``bool``

Performs the init operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `window` (`SDL_Window *`): Value supplied for the window parameter.

### operator=

~~~cpp
GPU_Renderer & GPU_Renderer::operator=(const GPU_Renderer &)=delete
~~~

**Access:** public  **Returns:** `GPU_Renderer &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`const GPU_Renderer &`): Value supplied for the  parameter.

### Render_Pool

~~~cpp
Render_Pool::Render_Pool(SDL_Renderer *renderer)
~~~

**Access:** public

Constructs a Render_Pool.

**Parameters**

- `renderer` (`SDL_Renderer *`): The SDL renderer used for all draw calls.

### renderer

~~~cpp
SDL_Renderer * GPU_Renderer::renderer() const
~~~

**Access:** public  **Returns:** ``SDL_Renderer *``

Constructs a Render_Pool value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### shutdown

~~~cpp
void GPU_Renderer::shutdown()
~~~

**Access:** public  **Returns:** ``void``

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

### size

~~~cpp
size_t Render_Pool::size() const
~~~

**Access:** public  **Returns:** ``size_t``

Returns the number of draw commands in the render pool.

**Parameters:** None.

### submit

~~~cpp
void Render_Pool::submit(const Draw &draw_command)
~~~

**Access:** public  **Returns:** ``void``

Submits a draw command to the render pool. If both the texture and font are null, or the command is not visible, it will be ignored.

**Parameters**

- `draw_command` (`const Draw &`): Value supplied for the draw_command parameter.

### Header usage example

~~~cpp
Draw command;
command.transform = {{100.0f, 80.0f}, {32.0f, 32.0f}};
Engine::render_pool->submit(command);
~~~

## texture.h

### ~Texture

~~~cpp
virtual Texture::~Texture()
~~~

**Access:** public

Frees the underlying SDL_Texture.

**Parameters:** None.

### draw

~~~cpp
void Texture::draw(SDL_Renderer *renderer, const SDL_FRect *src, const SDL_FRect *dst) const
~~~

**Access:** public  **Returns:** ``void``

Draws a sub-region of the texture into a destination rectangle.

**Parameters**

- `renderer` (`SDL_Renderer *`): Target SDL renderer.
- `src` (`const SDL_FRect *`): Source rectangle in texture coordinates (or nullptr for the full texture).
- `dst` (`const SDL_FRect *`): Destination rectangle in logical coordinates.

### draw

~~~cpp
void Texture::draw(SDL_Renderer *renderer, const Vec &pos, const Vec &size, const Vec &rotation) const
~~~

**Access:** public  **Returns:** ``void``

Draws the texture at pos scaled to size and rotated by rotation.

**Parameters**

- `renderer` (`SDL_Renderer *`): Target SDL renderer.
- `pos` (`const Vec &`): Top-left position in logical coordinates.
- `size` (`const Vec &`): Desired draw size (width, height).
- `rotation` (`const Vec &`): Rotation angle in degrees (clockwise).

### draw

~~~cpp
void Texture::draw(SDL_Renderer *renderer, const Vec &pos, const Vec &size) const
~~~

**Access:** public  **Returns:** ``void``

Draws the texture at pos scaled to size.

**Parameters**

- `renderer` (`SDL_Renderer *`): Target SDL renderer.
- `pos` (`const Vec &`): Top-left position in logical coordinates.
- `size` (`const Vec &`): Desired draw size (width, height).

### draw

~~~cpp
void Texture::draw(SDL_Renderer *renderer, const Vec &pos) const
~~~

**Access:** public  **Returns:** ``void``

Draws the texture at pos using its native size.

**Parameters**

- `renderer` (`SDL_Renderer *`): Target SDL renderer.
- `pos` (`const Vec &`): Top-left position in logical coordinates.

### draw_ex

~~~cpp
void Texture::draw_ex(SDL_Renderer *renderer, const SDL_FRect *source, const Transform &transform, const Color &tint) const
~~~

**Access:** public  **Returns:** ``void``

Performs the size operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `renderer` (`SDL_Renderer *`): Value supplied for the renderer parameter.
- `source` (`const SDL_FRect *`): Value supplied for the source parameter.
- `transform` (`const Transform &`): Value supplied for the transform parameter.
- `tint` (`const Color &`): Value supplied for the tint parameter.

### draw_ex

~~~cpp
void Texture::draw_ex(SDL_Renderer *renderer, const Transform &transform, const Color &tint) const
~~~

**Access:** public  **Returns:** ``void``

Draws the texture with a Transform and Color tint.

**Parameters**

- `renderer` (`SDL_Renderer *`): Target SDL renderer.
- `transform` (`const Transform &`): Transform containing position, size, and rotation.
- `tint` (`const Color &`): Color tint to apply.

### draw_ex

~~~cpp
void Texture::draw_ex(SDL_Renderer *renderer, const Vec &pos, const Vec &size, double angle, const Vec *center, SDL_FlipMode flip) const
~~~

**Access:** public  **Returns:** ``void``

Draws the texture with rotation and/or flip.

**Parameters**

- `renderer` (`SDL_Renderer *`): Target SDL renderer.
- `pos` (`const Vec &`): Top-left position in logical coordinates.
- `size` (`const Vec &`): Desired draw size.
- `angle` (`double`): Rotation angle in degrees (clockwise).
- `center` (`const Vec *`): Rotation center relative to pos, or nullptr for the texture centre.
- `flip` (`SDL_FlipMode`): One of SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL.

### free

~~~cpp
void Texture::free()
~~~

**Access:** public  **Returns:** ``void``

Destroys the SDL_Texture and resets internal state.

**Parameters:** None.

### get_gpu_texture

~~~cpp
SDL_GPUTexture * Texture::get_gpu_texture() const
~~~

**Access:** public  **Returns:** ``SDL_GPUTexture *``

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** None.

### get_height

~~~cpp
float Texture::get_height() const
~~~

**Access:** public  **Returns:** ``float``

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### get_path

~~~cpp
std::string Texture::get_path() const
~~~

**Access:** public  **Returns:** ``std::string``

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### get_scale_mode

~~~cpp
SDL_ScaleMode Texture::get_scale_mode() const
~~~

**Access:** public  **Returns:** ``SDL_ScaleMode``

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### get_sdl_texture

~~~cpp
SDL_Texture * Texture::get_sdl_texture() const
~~~

**Access:** public  **Returns:** ``SDL_Texture *``

Returns the underlying SDL_Texture pointer.

**Parameters:** None.

### get_SDL_Texture

~~~cpp
SDL_Texture * Texture::get_SDL_Texture() const
~~~

**Access:** public  **Returns:** ``SDL_Texture *``

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### get_size

~~~cpp
Vec Texture::get_size() const
~~~

**Access:** public  **Returns:** `Vec`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### get_texture_path

~~~cpp
std::string Texture::get_texture_path() const
~~~

**Access:** public  **Returns:** ``std::string``

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### get_width

~~~cpp
float Texture::get_width() const
~~~

**Access:** public  **Returns:** ``float``

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### has_alpha_mask

~~~cpp
bool Texture::has_alpha_mask() const
~~~

**Access:** public  **Returns:** ``bool``

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### is_fully_transparent

~~~cpp
bool Texture::is_fully_transparent() const
~~~

**Access:** public  **Returns:** ``bool``

Checks if the texture is fully transparent (all pixels have alpha = 0).

**Parameters:** None.

### is_gpu_backed

~~~cpp
bool Texture::is_gpu_backed() const
~~~

**Access:** public  **Returns:** ``bool``

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### is_loaded

~~~cpp
bool Texture::is_loaded() const
~~~

**Access:** public  **Returns:** ``bool``

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### is_pixel_opaque

~~~cpp
bool Texture::is_pixel_opaque(int x, int y, uint8_t alpha_threshold=1) const
~~~

**Access:** public  **Returns:** ``bool``

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters**

- `x` (`int`): Value supplied for the x parameter.
- `y` (`int`): Value supplied for the y parameter.
- `alpha_threshold` (`uint8_t`): Value supplied for the alpha_threshold parameter.

### is_region_transparent

~~~cpp
bool Texture::is_region_transparent(const SDL_FRect &region, uint8_t alpha_threshold=1) const
~~~

**Access:** public  **Returns:** ``bool``

Checks if a rectangular region of the texture is fully transparent.

**Parameters**

- `region` (`const SDL_FRect &`): The region to check, in texture coordinates.
- `alpha_threshold` (`uint8_t`): The alpha threshold to consider a pixel opaque (default: 1).

### load

~~~cpp
bool Texture::load(SDL_Renderer *renderer, const std::string &path)
~~~

**Access:** public  **Returns:** ``bool``

(Re)loads the texture from a file path.

**Parameters**

- `renderer` (`SDL_Renderer *`): The SDL renderer.
- `path` (`const std::string &`): Path to the image file.

### load_from_surface

~~~cpp
bool Texture::load_from_surface(SDL_Renderer *renderer, SDL_Surface *surface)
~~~

**Access:** public  **Returns:** ``bool``

(Re)loads the texture from an SDL_Surface.

**Parameters**

- `renderer` (`SDL_Renderer *`): The SDL renderer.
- `surface` (`SDL_Surface *`): Source surface.

### operator=

~~~cpp
Texture & Texture::operator=(const Texture &)=delete
~~~

**Access:** public  **Returns:** `Texture &`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters**

- `` (`const Texture &`): Value supplied for the  parameter.

### operator=

~~~cpp
Texture & Texture::operator=(Texture &&other) noexcept
~~~

**Access:** public  **Returns:** `Texture &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `other` (`Texture &&`): Value supplied for the other parameter.

### set_scale_mode

~~~cpp
void Texture::set_scale_mode(SDL_ScaleMode scale_mode)
~~~

**Access:** public  **Returns:** ``void``

Changes the scale mode (texture filtering).

**Parameters**

- `scale_mode` (`SDL_ScaleMode`): New mode, e.g. SDL_SCALEMODE_PIXELART or SDL_SCALEMODE_LINEAR.

### set_texture_opacity

~~~cpp
void Texture::set_texture_opacity(float alpha)
~~~

**Access:** public  **Returns:** ``void``

Changes the opacity of the texture.

**Parameters**

- `alpha` (`float`): New opacity in the range [0.0, 1.0].

### Texture

~~~cpp
Texture::Texture()=default
~~~

**Access:** public

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** None.

### Texture

~~~cpp
Texture::Texture(const Texture &)=delete
~~~

**Access:** public

Constructs a Texture value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`const Texture &`): Value supplied for the  parameter.

### Texture

~~~cpp
Texture::Texture(SDL_Renderer *renderer, const std::string &path, Logger *logger=nullptr, SDL_ScaleMode scale_mode=SDL_SCALEMODE_PIXELART)
~~~

**Access:** public

Loads a texture from a file.

**Parameters**

- `renderer` (`SDL_Renderer *`): The SDL renderer to create the texture with.
- `path` (`const std::string &`): Path to the image file (PNG, JPG, etc.).
- `logger` (`Logger *`): Optional logger; pass nullptr to suppress log output.
- `scale_mode` (`SDL_ScaleMode`): Scaling filter. Default: SDL_SCALEMODE_PIXELART (nearest-neighbour).

### Texture

~~~cpp
Texture::Texture(SDL_Renderer *renderer, SDL_Surface *surface, Logger *logger=nullptr, SDL_ScaleMode scale_mode=SDL_SCALEMODE_PIXELART)
~~~

**Access:** public

Creates a texture from an existing SDL_Surface.

**Parameters**

- `renderer` (`SDL_Renderer *`): The SDL renderer to create the texture with.
- `surface` (`SDL_Surface *`): The source surface (not freed by this constructor).
- `logger` (`Logger *`): Optional logger.
- `scale_mode` (`SDL_ScaleMode`): Scaling filter.

### Texture

~~~cpp
Texture::Texture(Texture &&other) noexcept
~~~

**Access:** public

Constructs a Texture value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `other` (`Texture &&`): Value supplied for the other parameter.

### Header usage example

~~~cpp
Texture texture;
texture.load("assets/player.png");
texture.draw({{100, 100}, texture.get_size()});
~~~

## fonts.h

### ~IFont

~~~cpp
virtual IFont::~IFont()=default
~~~

**Access:** public

Frees implementation-specific font resources.

**Parameters:** None.

### ~SDL_Font

~~~cpp
SDL_Font::~SDL_Font() override
~~~

**Access:** public

Constructs a Header usage example value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### ~Tileset_Font

~~~cpp
Tileset_Font::~Tileset_Font() override
~~~

**Access:** public

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

### draw

~~~cpp
virtual void IFont::draw(const IFont_Props &props) const =0
~~~

**Access:** public  **Returns:** ``void``

Draws text using a full properties object.

**Parameters**

- `props` (`const IFont_Props &`): Draw properties to use for this call.

### draw

~~~cpp
virtual void IFont::draw(SDL_Renderer *renderer, const std::string &text, const Vec &pos, const Color &color, float scale=1.0f) const =0
~~~

**Access:** public  **Returns:** ``void``

Draws text using direct arguments.

**Parameters**

- `renderer` (`SDL_Renderer *`): SDL renderer used for drawing.
- `text` (`const std::string &`): Text to draw.
- `pos` (`const Vec &`): Top-left draw position.
- `color` (`const Color &`): Text color and opacity.
- `scale` (`float`): Draw scale multiplier.

### draw

~~~cpp
void SDL_Font::draw(const IFont_Props &props) const override
~~~

**Access:** public  **Returns:** ``void``

Draws text using a full properties object.

**Parameters**

- `props` (`const IFont_Props &`): Draw properties to use for this call.

### draw

~~~cpp
void SDL_Font::draw(SDL_Renderer *renderer, const std::string &text, const Vec &pos, const Color &color, float scale=1.0f) const override
~~~

**Access:** public  **Returns:** ``void``

Draws text using direct arguments.

**Parameters**

- `renderer` (`SDL_Renderer *`): SDL renderer used for drawing.
- `text` (`const std::string &`): Text to draw.
- `pos` (`const Vec &`): Top-left draw position.
- `color` (`const Color &`): Text color and opacity.
- `scale` (`float`): Draw scale multiplier.

### draw

~~~cpp
void Tileset_Font::draw(const IFont_Props &props) const override
~~~

**Access:** public  **Returns:** ``void``

Draws text using a full properties object.

**Parameters**

- `props` (`const IFont_Props &`): Draw properties to use for this call.

### draw

~~~cpp
void Tileset_Font::draw(SDL_Renderer *renderer, const std::string &text, const Vec &pos, const Color &color, float scale=1.0f) const override
~~~

**Access:** public  **Returns:** ``void``

Draws text using direct arguments.

**Parameters**

- `renderer` (`SDL_Renderer *`): SDL renderer used for drawing.
- `text` (`const std::string &`): Text to draw.
- `pos` (`const Vec &`): Top-left draw position.
- `color` (`const Color &`): Text color and opacity.
- `scale` (`float`): Draw scale multiplier.

### get_char_map

~~~cpp
const std::string & Tileset_Font::get_char_map() const
~~~

**Access:** public  **Returns:** ``const std::string &``

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** None.

### get_props

~~~cpp
virtual IFont_Props * IFont::get_props() const
~~~

**Access:** public  **Returns:** `IFont_Props *`

Gets the retained draw properties pointer.

**Parameters:** None.

### get_size

~~~cpp
Vec SDL_Font::get_size(const std::string &text) const override
~~~

**Access:** public  **Returns:** `Vec`

Measures text using this font.

**Parameters**

- `text` (`const std::string &`): Text to measure.

### get_size

~~~cpp
Vec Tileset_Font::get_size(const std::string &text) const override
~~~

**Access:** public  **Returns:** `Vec`

Measures text using this font.

**Parameters**

- `text` (`const std::string &`): Text to measure.

### get_size

~~~cpp
virtual Vec IFont::get_size(const std::string &text) const =0
~~~

**Access:** public  **Returns:** `Vec`

Measures text using this font.

**Parameters**

- `text` (`const std::string &`): Text to measure.

### get_tile_size

~~~cpp
const Vec & Tileset_Font::get_tile_size() const
~~~

**Access:** public  **Returns:** `const Vec &`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### is_loaded

~~~cpp
bool SDL_Font::is_loaded() const override
~~~

**Access:** public  **Returns:** ``bool``

Checks if the font has a loaded backing resource.

**Parameters:** None.

### is_loaded

~~~cpp
bool Tileset_Font::is_loaded() const override
~~~

**Access:** public  **Returns:** ``bool``

Checks if the font has a loaded backing resource.

**Parameters:** None.

### is_loaded

~~~cpp
virtual bool IFont::is_loaded() const =0
~~~

**Access:** public  **Returns:** ``bool``

Checks if the font has a loaded backing resource.

**Parameters:** None.

### load

~~~cpp
bool SDL_Font::load(const std::string &path, int size=16) override
~~~

**Access:** public  **Returns:** ``bool``

Loads a font from disk.

**Parameters**

- `path` (`const std::string &`): Path to a TTF file or bitmap font atlas, depending on the implementation.
- `size` (`int`): Point size for SDL_Font, or tile size for Tileset_Font.

### load

~~~cpp
bool Tileset_Font::load(const std::string &path, int size=16) override
~~~

**Access:** public  **Returns:** ``bool``

Loads a font from disk.

**Parameters**

- `path` (`const std::string &`): Path to a TTF file or bitmap font atlas, depending on the implementation.
- `size` (`int`): Point size for SDL_Font, or tile size for Tileset_Font.

### load

~~~cpp
virtual bool IFont::load(const std::string &path, int size=16)=0
~~~

**Access:** public  **Returns:** ``bool``

Loads a font from disk.

**Parameters**

- `path` (`const std::string &`): Path to a TTF file or bitmap font atlas, depending on the implementation.
- `size` (`int`): Point size for SDL_Font, or tile size for Tileset_Font.

### load_tileset_font

~~~cpp
bool Tileset_Font::load_tileset_font(const std::string &path, const Vec &tile_size, const std::string &char_map)
~~~

**Access:** public  **Returns:** ``bool``

Loads a bitmap font atlas using Engine::renderer.

**Parameters**

- `path` (`const std::string &`): Path to the bitmap font atlas image.
- `tile_size` (`const Vec &`): Size of one glyph tile.
- `char_map` (`const std::string &`): Characters mapped left-to-right, top-to-bottom in the atlas.

### load_tileset_font

~~~cpp
bool Tileset_Font::load_tileset_font(SDL_Renderer *renderer, const std::string &path, const Vec &tile_size, const std::string &char_map)
~~~

**Access:** public  **Returns:** ``bool``

Loads a bitmap font atlas using an explicit renderer.

**Parameters**

- `renderer` (`SDL_Renderer *`): SDL renderer used to create the atlas texture.
- `path` (`const std::string &`): Path to the bitmap font atlas image.
- `tile_size` (`const Vec &`): Size of one glyph tile.
- `char_map` (`const std::string &`): Characters mapped left-to-right, top-to-bottom in the atlas.

### operator=

~~~cpp
SDL_Font & SDL_Font::operator=(const SDL_Font &)=delete
~~~

**Access:** public  **Returns:** `SDL_Font &`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters**

- `` (`const SDL_Font &`): Value supplied for the  parameter.

### operator=

~~~cpp
SDL_Font & SDL_Font::operator=(SDL_Font &&)=delete
~~~

**Access:** public  **Returns:** `SDL_Font &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`SDL_Font &&`): Value supplied for the  parameter.

### operator=

~~~cpp
Tileset_Font & Tileset_Font::operator=(const Tileset_Font &)=delete
~~~

**Access:** public  **Returns:** `Tileset_Font &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`const Tileset_Font &`): Value supplied for the  parameter.

### operator=

~~~cpp
Tileset_Font & Tileset_Font::operator=(Tileset_Font &&)=delete
~~~

**Access:** public  **Returns:** `Tileset_Font &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`Tileset_Font &&`): Value supplied for the  parameter.

### pixel_art

~~~cpp
bool SDL_Font::pixel_art() const override
~~~

**Access:** public  **Returns:** ``bool``

Performs the pixel art operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### pixel_art

~~~cpp
bool Tileset_Font::pixel_art() const override
~~~

**Access:** public  **Returns:** ``bool``

Performs the pixel art operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### pixel_art

~~~cpp
virtual bool IFont::pixel_art() const
~~~

**Access:** public  **Returns:** ``bool``

Performs the pixel art operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### SDL_Font

~~~cpp
SDL_Font::SDL_Font()=default
~~~

**Access:** public

Constructs a SDL_Font value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### SDL_Font

~~~cpp
SDL_Font::SDL_Font(const SDL_Font &)=delete
~~~

**Access:** public

Constructs a SDL_Font value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`const SDL_Font &`): Value supplied for the  parameter.

### SDL_Font

~~~cpp
SDL_Font::SDL_Font(SDL_Font &&)=delete
~~~

**Access:** public

Constructs a SDL_Font value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`SDL_Font &&`): Value supplied for the  parameter.

### set_char_map

~~~cpp
void Tileset_Font::set_char_map(const std::string &new_map)
~~~

**Access:** public  **Returns:** ``void``

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `new_map` (`const std::string &`): Value supplied for the new_map parameter.

### set_pixel_art

~~~cpp
virtual void IFont::set_pixel_art(bool enabled)
~~~

**Access:** public  **Returns:** ``void``

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `enabled` (`bool`): Value supplied for the enabled parameter.

### set_pixel_art

~~~cpp
void SDL_Font::set_pixel_art(bool enabled) override
~~~

**Access:** public  **Returns:** ``void``

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `enabled` (`bool`): Value supplied for the enabled parameter.

### set_props

~~~cpp
virtual void IFont::set_props(IFont_Props *new_props)
~~~

**Access:** public  **Returns:** ``void``

Sets the retained draw properties pointer.

**Parameters**

- `new_props` (`IFont_Props *`): Borrowed pointer; ownership stays with the caller.

### set_tile_size

~~~cpp
void Tileset_Font::set_tile_size(const Vec &tile_size)
~~~

**Access:** public  **Returns:** ``void``

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `tile_size` (`const Vec &`): Value supplied for the tile_size parameter.

### Tileset_Font

~~~cpp
Tileset_Font::Tileset_Font()=default
~~~

**Access:** public

Constructs a Tileset_Font value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### Tileset_Font

~~~cpp
Tileset_Font::Tileset_Font(const Tileset_Font &)=delete
~~~

**Access:** public

Constructs a Tileset_Font value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`const Tileset_Font &`): Value supplied for the  parameter.

### Tileset_Font

~~~cpp
Tileset_Font::Tileset_Font(Tileset_Font &&)=delete
~~~

**Access:** public

Constructs a Tileset_Font value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`Tileset_Font &&`): Value supplied for the  parameter.

### unload

~~~cpp
virtual void IFont::unload()=0
~~~

**Access:** public  **Returns:** ``void``

Unloads all resources held by the font.

**Parameters:** None.

### unload

~~~cpp
void SDL_Font::unload() override
~~~

**Access:** public  **Returns:** ``void``

Unloads all resources held by the font.

**Parameters:** None.

### unload

~~~cpp
void Tileset_Font::unload() override
~~~

**Access:** public  **Returns:** ``void``

Unloads all resources held by the font.

**Parameters:** None.

### Header usage example

~~~cpp
SDL_Font font;
font.load("assets/fonts/ui.ttf", 24);
font.draw(IFont_Props{});
~~~

## camera.h

### ~Camera_Pool

~~~cpp
Camera_Pool::~Camera_Pool()=default
~~~

**Access:** public

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

### active_camera

~~~cpp
Camera * Camera_Pool::active_camera()
~~~

**Access:** public  **Returns:** `Camera *`

Returns the camera currently used by the render pipeline.

**Parameters:** None.

### active_camera

~~~cpp
const Camera * Camera_Pool::active_camera() const
~~~

**Access:** public  **Returns:** `const Camera *`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### apply_bounds

~~~cpp
void Camera::apply_bounds()
~~~

**Access:** private  **Returns:** ``void``

Applies the requested state change to the target object or service. Validate target pointers and preconditions before invoking the operation.

**Parameters:** None.

### Camera

~~~cpp
Camera::Camera()=default
~~~

**Access:** public

Default constructor for the Camera class.

**Parameters:** None.

### Camera_Pool

~~~cpp
Camera_Pool::Camera_Pool()
~~~

**Access:** public

Creates the pool and the default main_cam.

**Parameters:** None.

### Camera_Pool

~~~cpp
Camera_Pool::Camera_Pool(const Camera_Pool &)=delete
~~~

**Access:** public

Constructs a Camera value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`const Camera_Pool &`): Value supplied for the  parameter.

### can_see

~~~cpp
bool Camera::can_see(const Transform &world_transform) const
~~~

**Access:** public  **Returns:** ``bool``

Returns true when a world-space transform overlaps the camera view. This is used by the render pipeline to skip objects outside the visible area.

**Parameters**

- `world_transform` (`const Transform &`): Value supplied for the world_transform parameter.

### clear

~~~cpp
void Camera_Pool::clear()
~~~

**Access:** public  **Returns:** ``void``

Deletes every non-main camera and makes main_cam active again.

**Parameters:** None.

### clear_bounds

~~~cpp
void Camera::clear_bounds()
~~~

**Access:** public  **Returns:** ``void``

Clears any bounds set for the camera, allowing it to move freely.

**Parameters:** None.

### create

~~~cpp
Camera * Camera_Pool::create(const std::string &name)
~~~

**Access:** public  **Returns:** `Camera *`

Creates a camera with the given name.

**Parameters**

- `name` (`const std::string &`): Value supplied for the name parameter.

### follow

~~~cpp
void Camera::follow(Object *target, float smoothing, float dt)
~~~

**Access:** public  **Returns:** ``void``

Makes the camera follow a target object with optional smoothing.

**Parameters**

- `target` (`Object *`): Pointer to the Object to follow.
- `smoothing` (`float`): The smoothing factor for following the target.
- `dt` (`float`): The delta time since the last frame.

### get

~~~cpp
Camera * Camera_Pool::get(const std::string &name)
~~~

**Access:** public  **Returns:** `Camera *`

Finds a camera by name.

**Parameters**

- `name` (`const std::string &`): Value supplied for the name parameter.

### get

~~~cpp
const Camera * Camera_Pool::get(const std::string &name) const
~~~

**Access:** public  **Returns:** `const Camera *`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters**

- `name` (`const std::string &`): Value supplied for the name parameter.

### get_position

~~~cpp
Vec Camera::get_position() const
~~~

**Access:** public  **Returns:** `Vec`

Gets the current position of the camera in world coordinates.

**Parameters:** None.

### get_rotation

~~~cpp
float Camera::get_rotation() const
~~~

**Access:** public  **Returns:** ``float``

Gets the current rotation of the camera in radians.

**Parameters:** None.

### get_viewport

~~~cpp
Vec Camera::get_viewport() const
~~~

**Access:** public  **Returns:** `Vec`

Gets the viewport size in logical screen pixels.

**Parameters:** None.

### get_zoom

~~~cpp
float Camera::get_zoom() const
~~~

**Access:** public  **Returns:** ``float``

Gets the current zoom level of the camera.

**Parameters:** None.

### main_camera

~~~cpp
Camera * Camera_Pool::main_camera()
~~~

**Access:** public  **Returns:** `Camera *`

Returns the always-present default camera.

**Parameters:** None.

### main_camera

~~~cpp
const Camera * Camera_Pool::main_camera() const
~~~

**Access:** public  **Returns:** `const Camera *`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### move

~~~cpp
void Camera::move(Vec delta)
~~~

**Access:** public  **Returns:** ``void``

Moves the camera by a specified delta in world coordinates.

**Parameters**

- `delta` (`Vec`): A Vec representing the change in position for the camera.

### operator=

~~~cpp
Camera_Pool & Camera_Pool::operator=(const Camera_Pool &)=delete
~~~

**Access:** public  **Returns:** `Camera_Pool &`

Performs the move operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `` (`const Camera_Pool &`): Value supplied for the  parameter.

### remove

~~~cpp
bool Camera_Pool::remove(const std::string &name)
~~~

**Access:** public  **Returns:** ``bool``

Removes a camera from the pool. main_cam is protected and will never be removed by this function.

**Parameters**

- `name` (`const std::string &`): Value supplied for the name parameter.

### reset

~~~cpp
void Camera::reset()
~~~

**Access:** public  **Returns:** ``void``

Resets the camera to its default state: position at (0,0), zoom level of 1, and no rotation. This function is useful for resetting the camera after a scene change or when you want to return to a default view.

**Parameters:** None.

### screen_size_to_world

~~~cpp
Vec Camera::screen_size_to_world(Vec screen_size) const
~~~

**Access:** public  **Returns:** `Vec`

Converts a size from screen coordinates to world coordinates.

**Parameters**

- `screen_size` (`Vec`): A Vec representing the size in screen coordinates.

### screen_to_world

~~~cpp
Transform Camera::screen_to_world(const Transform &screen_transform) const
~~~

**Access:** public  **Returns:** `Transform`

Converts a full screen transform back into world-space. Useful when placing objects from mouse or UI coordinates.

**Parameters**

- `screen_transform` (`const Transform &`): Value supplied for the screen_transform parameter.

### screen_to_world

~~~cpp
Vec Camera::screen_to_world(Vec screen_pos) const
~~~

**Access:** public  **Returns:** `Vec`

Converts a position from screen coordinates to world coordinates.

**Parameters**

- `screen_pos` (`Vec`): A Vec representing the position in screen coordinates.

### set_active

~~~cpp
bool Camera_Pool::set_active(const std::string &name)
~~~

**Access:** public  **Returns:** ``bool``

Makes an existing camera the active render camera.

**Parameters**

- `name` (`const std::string &`): Value supplied for the name parameter.

### set_bounds

~~~cpp
void Camera::set_bounds(Vec min, Vec max)
~~~

**Access:** public  **Returns:** ``void``

Sets the bounds for the camera's position.

**Parameters**

- `min` (`Vec`): A Vec representing the minimum bounds (top-left corner).
- `max` (`Vec`): A Vec representing the maximum bounds (bottom-right corner).

### set_position

~~~cpp
void Camera::set_position(Vec position)
~~~

**Access:** public  **Returns:** ``void``

Sets the position of the camera in world coordinates.

**Parameters**

- `position` (`Vec`): A Vec representing the new position of the camera.

### set_rotation

~~~cpp
void Camera::set_rotation(float rotation)
~~~

**Access:** public  **Returns:** ``void``

Sets the rotation of the camera in radians.

**Parameters**

- `rotation` (`float`): The new rotation angle in radians.

### set_viewport

~~~cpp
void Camera::set_viewport(float width, float height)
~~~

**Access:** public  **Returns:** ``void``

Sets the viewport dimensions for the camera.

**Parameters**

- `width` (`float`): The width of the viewport in pixels.
- `height` (`float`): The height of the viewport in pixels.

### set_viewport

~~~cpp
void Camera::set_viewport(Vec size)
~~~

**Access:** public  **Returns:** ``void``

Sets the viewport dimensions for the camera using a Vec.

**Parameters**

- `size` (`Vec`): A Vec where x is the width and y is the height of the viewport in pixels.

### set_zoom

~~~cpp
void Camera::set_zoom(float zoom)
~~~

**Access:** public  **Returns:** ``void``

Sets the zoom level of the camera.

**Parameters**

- `zoom` (`float`): The new zoom level. Must be greater than 0.

### shake

~~~cpp
void Camera::shake(float intensity, float duration)
~~~

**Access:** public  **Returns:** ``void``

Shakes the camera for a specified duration and intensity.

**Parameters**

- `intensity` (`float`): The intensity of the shake effect.
- `duration` (`float`): The duration of the shake effect in seconds.

### size

~~~cpp
size_t Camera_Pool::size() const
~~~

**Access:** public  **Returns:** ``size_t``

Returns how many cameras are owned by the pool.

**Parameters:** None.

### world_size_to_screen

~~~cpp
Vec Camera::world_size_to_screen(Vec world_size) const
~~~

**Access:** public  **Returns:** `Vec`

Converts a size from world coordinates to screen coordinates.

**Parameters**

- `world_size` (`Vec`): A Vec representing the size in world coordinates.

### world_to_screen

~~~cpp
Transform Camera::world_to_screen(const Transform &world_transform) const
~~~

**Access:** public  **Returns:** `Transform`

Converts a full world transform into screen-space. The position is offset by the camera and the size is scaled by zoom.

**Parameters**

- `world_transform` (`const Transform &`): Value supplied for the world_transform parameter.

### world_to_screen

~~~cpp
Vec Camera::world_to_screen(Vec world_pos) const
~~~

**Access:** public  **Returns:** `Vec`

Converts a position from world coordinates to screen coordinates.

**Parameters**

- `world_pos` (`Vec`): A Vec representing the position in world coordinates.

### Header usage example

~~~cpp
Camera* camera = Engine::camera_pool->create("gameplay");
camera->set_position({320.0f, 180.0f});
camera->set_zoom(2.0f);
~~~

## light.h

### ~light_source

~~~cpp
light_source::~light_source()
~~~

**Access:** public

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

### ~Light_System

~~~cpp
Light_System::~Light_System()
~~~

**Access:** public

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

### begin_world_pass

~~~cpp
bool Light_System::begin_world_pass(const Camera *camera)
~~~

**Access:** public  **Returns:** ``bool``

Performs the begin world pass operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `camera` (`const Camera *`): Value supplied for the camera parameter.

### end_world_pass

~~~cpp
void Light_System::end_world_pass()
~~~

**Access:** public  **Returns:** ``void``

Performs the end world pass operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### Float4

~~~cpp
Light_System::Float4::Float4()=default
~~~

**Access:** public

Constructs a Float4 value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### Float4

~~~cpp
Light_System::Float4::Float4(const Color &color, float w=1.0f)
~~~

**Access:** public

Constructs a Float4 value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `color` (`const Color &`): Value supplied for the color parameter.
- `w` (`float`): Value supplied for the w parameter.

### Float4

~~~cpp
Light_System::Float4::Float4(const Vec &vec, float z=0.0f, float w=0.0f)
~~~

**Access:** public

Constructs a Float4 value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `vec` (`const Vec &`): Value supplied for the vec parameter.
- `z` (`float`): Value supplied for the z parameter.
- `w` (`float`): Value supplied for the w parameter.

### Float4

~~~cpp
Light_System::Float4::Float4(const Vec4 &vec)
~~~

**Access:** public

Constructs a Float4 value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `vec` (`const Vec4 &`): Value supplied for the vec parameter.

### Float4

~~~cpp
Light_System::Float4::Float4(float x, float y, float z, float w)
~~~

**Access:** public

Constructs a Float4 value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `x` (`float`): Value supplied for the x parameter.
- `y` (`float`): Value supplied for the y parameter.
- `z` (`float`): Value supplied for the z parameter.
- `w` (`float`): Value supplied for the w parameter.

### get_night_amount

~~~cpp
float Light_System::get_night_amount() const
~~~

**Access:** public  **Returns:** ``float``

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### get_time_of_day

~~~cpp
float Light_System::get_time_of_day() const
~~~

**Access:** public  **Returns:** ``float``

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### init

~~~cpp
bool Light_System::init(SDL_Renderer *renderer, SDL_GPUDevice *device, Logger *logger=nullptr)
~~~

**Access:** public  **Returns:** ``bool``

Performs the init operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `renderer` (`SDL_Renderer *`): Value supplied for the renderer parameter.
- `device` (`SDL_GPUDevice *`): Value supplied for the device parameter.
- `logger` (`Logger *`): Value supplied for the logger parameter.

### is_auto_advance_enabled

~~~cpp
bool Light_System::is_auto_advance_enabled() const
~~~

**Access:** public  **Returns:** ``bool``

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### is_ready

~~~cpp
bool Light_System::is_ready() const
~~~

**Access:** public  **Returns:** ``bool``

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### light_count

~~~cpp
std::size_t Light_System::light_count() const
~~~

**Access:** public  **Returns:** ``std::size_t``

Performs the light count operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### light_source

~~~cpp
light_source::light_source(const light_source &)=delete
~~~

**Access:** public

Performs the light source operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `` (`const light_source &`): Value supplied for the  parameter.

### light_source

~~~cpp
light_source::light_source(Vec position={}, float radius=160.0f, Color color=Color::white(), float intensity=1.0f, float softness=0.35f)
~~~

**Access:** public

Performs the light source operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `position` (`Vec`): Value supplied for the position parameter.
- `radius` (`float`): Value supplied for the radius parameter.
- `color` (`Color`): Value supplied for the color parameter. Default: `Color::white()`.
- `intensity` (`float`): Value supplied for the intensity parameter.
- `softness` (`float`): Value supplied for the softness parameter.

### Light_System

~~~cpp
Light_System::Light_System()=default
~~~

**Access:** public

Constructs a Light_System value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### Light_System

~~~cpp
Light_System::Light_System(const Light_System &)=delete
~~~

**Access:** public

Constructs a Light_System value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`const Light_System &`): Value supplied for the  parameter.

### operator=

~~~cpp
light_source & light_source::operator=(const light_source &)=delete
~~~

**Access:** public  **Returns:** `light_source &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`const light_source &`): Value supplied for the  parameter.

### operator=

~~~cpp
Light_System & Light_System::operator=(const Light_System &)=delete
~~~

**Access:** public  **Returns:** `Light_System &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`const Light_System &`): Value supplied for the  parameter.

### register_light

~~~cpp
void Light_System::register_light(light_source *light)
~~~

**Access:** public  **Returns:** ``void``

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters**

- `light` (`light_source *`): Value supplied for the light parameter.

### set_active

~~~cpp
void Light_System::set_active(bool active, SDL_ScaleMode scale_mode=SDL_SCALEMODE_LINEAR)
~~~

**Access:** public  **Returns:** ``void``

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `active` (`bool`): Value supplied for the active parameter.
- `scale_mode` (`SDL_ScaleMode`): Value supplied for the scale_mode parameter.

### set_auto_advance

~~~cpp
void Light_System::set_auto_advance(bool enabled)
~~~

**Access:** public  **Returns:** ``void``

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `enabled` (`bool`): Value supplied for the enabled parameter.

### set_day_length

~~~cpp
void Light_System::set_day_length(float seconds)
~~~

**Access:** public  **Returns:** ``void``

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `seconds` (`float`): Value supplied for the seconds parameter.

### set_night_ambient

~~~cpp
void Light_System::set_night_ambient(Color color, float strength)
~~~

**Access:** public  **Returns:** ``void``

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `color` (`Color`): Value supplied for the color parameter.
- `strength` (`float`): Value supplied for the strength parameter.

### set_shadow_strength

~~~cpp
void Light_System::set_shadow_strength(float strength)
~~~

**Access:** public  **Returns:** ``void``

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `strength` (`float`): Value supplied for the strength parameter.

### set_time_of_day

~~~cpp
void Light_System::set_time_of_day(float hour)
~~~

**Access:** public  **Returns:** ``void``

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `hour` (`float`): Value supplied for the hour parameter.

### shutdown

~~~cpp
void Light_System::shutdown()
~~~

**Access:** public  **Returns:** ``void``

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

### unregister_light

~~~cpp
void Light_System::unregister_light(light_source *light)
~~~

**Access:** public  **Returns:** ``void``

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters**

- `light` (`light_source *`): Value supplied for the light parameter.

### update

~~~cpp
void Light_System::update(float delta_time)
~~~

**Access:** public  **Returns:** ``void``

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters**

- `delta_time` (`float`): Value supplied for the delta_time parameter.

### Header usage example

~~~cpp
Engine::lighting->set_time_of_day(20.0f);
Engine::lighting->set_shadow_strength(0.75f);
~~~

## asset_pool.h

### ~Asset_Pool

~~~cpp
Asset_Pool::~Asset_Pool()=default
~~~

**Access:** public

Constructs a Header usage example value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### activate_localized_texture

~~~cpp
bool Asset_Pool::activate_localized_texture(const std::string &name)
~~~

**Access:** private  **Returns:** ``bool``

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters**

- `name` (`const std::string &`): Value supplied for the name parameter.

### add_audio_to_group

~~~cpp
void Asset_Pool::add_audio_to_group(const std::string &audio_name, const std::string &tag)
~~~

**Access:** public  **Returns:** ``void``

Adds an already loaded audio file to a group tag.

**Parameters**

- `audio_name` (`const std::string &`): The name of the loaded audio file.
- `tag` (`const std::string &`): The group tag to attach.

### Asset_Pool

~~~cpp
Asset_Pool::Asset_Pool()=default
~~~

**Access:** public

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters:** None.

### Asset_Pool

~~~cpp
Asset_Pool::Asset_Pool(SDL_Renderer *renderer, Logger *logger=nullptr)
~~~

**Access:** public

Constructs an Asset_Pool with a given SDL_Renderer and optional Logger.

**Parameters**

- `renderer` (`SDL_Renderer *`): Pointer to the SDL_Renderer used for texture loading.
- `logger` (`Logger *`): Optional pointer to a Logger for logging messages; defaults to nullptr.

### clear

~~~cpp
void Asset_Pool::clear()
~~~

**Access:** public  **Returns:** ``void``

Clears all cached assets from the pool.

**Parameters:** None.

### format_text

~~~cpp
std::string Asset_Pool::format_text(const std::string &key, const std::unordered_map< std::string, std::string > &values) const
~~~

**Access:** public  **Returns:** ``std::string``

Retrieves a localized string by key and formats it with provided values.

**Parameters**

- `key` (`const std::string &`): The localization key.
- `values` (`std::string > &`): A map of placeholder names to their replacement values.

### get_audio

~~~cpp
Audio * Asset_Pool::get_audio(const std::string &name)
~~~

**Access:** public  **Returns:** `Audio *`

Retrieves an audio file by name.

**Parameters**

- `name` (`const std::string &`): The name of the audio file.

### get_audio_group

~~~cpp
std::vector< Audio * > Asset_Pool::get_audio_group(const std::string &tag)
~~~

**Access:** public  **Returns:** `std::vector< Audio * >`

Gets every loaded audio file attached to a group tag.

**Parameters**

- `tag` (`const std::string &`): The group tag to query.

### get_font

~~~cpp
IFont * Asset_Pool::get_font(const std::string &name)
~~~

**Access:** public  **Returns:** `IFont *`

Retrieves a font by name.

**Parameters**

- `name` (`const std::string &`): The name of the font.

### get_locale

~~~cpp
const std::string & Asset_Pool::get_locale() const
~~~

**Access:** public  **Returns:** ``const std::string &``

Gets the current locale tag.

**Parameters:** None.

### get_text

~~~cpp
std::string Asset_Pool::get_text(const std::string &key) const
~~~

**Access:** public  **Returns:** ``std::string``

Retrieves a localized string by key using the current locale.

**Parameters**

- `key` (`const std::string &`): The localization key.

### get_texture

~~~cpp
Texture * Asset_Pool::get_texture(const std::string &name)
~~~

**Access:** public  **Returns:** `Texture *`

Retrieves a texture by name.

**Parameters**

- `name` (`const std::string &`): The name of the texture.

### has_audio

~~~cpp
bool Asset_Pool::has_audio(const std::string &name) const
~~~

**Access:** public  **Returns:** ``bool``

Checks if an audio file with the given name exists in the pool.

**Parameters**

- `name` (`const std::string &`): The name of the audio file.

### has_audio_group

~~~cpp
bool Asset_Pool::has_audio_group(const std::string &tag) const
~~~

**Access:** public  **Returns:** ``bool``

Checks if an audio group tag exists.

**Parameters**

- `tag` (`const std::string &`): The group tag to check.

### has_font

~~~cpp
bool Asset_Pool::has_font(const std::string &name) const
~~~

**Access:** public  **Returns:** ``bool``

Checks if a font with the given name exists in the pool.

**Parameters**

- `name` (`const std::string &`): The name of the font.

### has_texture

~~~cpp
bool Asset_Pool::has_texture(const std::string &name) const
~~~

**Access:** public  **Returns:** ``bool``

Checks if a texture with the given name exists in the pool.

**Parameters**

- `name` (`const std::string &`): The name of the texture.

### load_audio

~~~cpp
void Asset_Pool::load_audio(const std::string &name, const std::string &path, bool predecode=true)
~~~

**Access:** public  **Returns:** ``void``

Loads an audio file from disk and adds it to the pool.

**Parameters**

- `name` (`const std::string &`): The name to associate with the audio file.
- `path` (`const std::string &`): The file path to the audio file.
- `predecode` (`bool`): If true, the audio will be decoded into memory. If false, it will stream from disk.

### load_audio

~~~cpp
void Asset_Pool::load_audio(const std::string &name, const std::string &path, const std::string &tag, bool predecode=true)
~~~

**Access:** public  **Returns:** ``void``

Loads an audio file from disk and adds it to an audio group tag.

**Parameters**

- `name` (`const std::string &`): The name to associate with the audio file.
- `path` (`const std::string &`): The file path to the audio file.
- `tag` (`const std::string &`): The group tag to attach to this audio file, for example "ui" or "music".
- `predecode` (`bool`): If true, the audio will be decoded into memory. If false, it will stream from disk.

### load_audio

~~~cpp
void Asset_Pool::load_audio(const std::string &name, const std::string &path, const std::vector< std::string > &tags, bool predecode=true)
~~~

**Access:** public  **Returns:** ``void``

Loads an audio file from disk and adds it to multiple audio group tags.

**Parameters**

- `name` (`const std::string &`): The name to associate with the audio file.
- `path` (`const std::string &`): The file path to the audio file.
- `tags` (`const std::vector< std::string > &`): The group tags to attach to this audio file.
- `predecode` (`bool`): If true, the audio will be decoded into memory. If false, it will stream from disk.

### load_locale

~~~cpp
bool Asset_Pool::load_locale(const std::string &locale_tag, const std::string &path)
~~~

**Access:** public  **Returns:** ``bool``

Loads a texture from a file and adds it to the pool, with an option to specify a custom SDL_Renderer.

**Parameters**

- `locale_tag` (`const std::string &`): Value supplied for the locale_tag parameter.
- `path` (`const std::string &`): The file path to the texture image.

### load_locales_from_directory

~~~cpp
std::size_t Asset_Pool::load_locales_from_directory(const std::string &directory)
~~~

**Access:** public  **Returns:** ``std::size_t``

Loads all locale JSON files from a directory and adds them to the pool.

**Parameters**

- `directory` (`const std::string &`): The directory path containing locale JSON files.

### load_sdl_font

~~~cpp
void Asset_Pool::load_sdl_font(const std::string &name, const std::string &path, int size=16, bool pixel_art=false)
~~~

**Access:** public  **Returns:** ``void``

Loads an SDL_ttf font from disk and adds it to the pool.

**Parameters**

- `name` (`const std::string &`): The name to associate with the font.
- `path` (`const std::string &`): The file path to the TTF/OTF font file.
- `size` (`int`): Font point size.
- `pixel_art` (`bool`): Value supplied for the pixel_art parameter.

### load_texture

~~~cpp
void Asset_Pool::load_texture(const std::string &name, const std::string &path, bool use_default_path=true)
~~~

**Access:** public  **Returns:** ``void``

Loads a texture from a file and adds it to the pool.

**Parameters**

- `name` (`const std::string &`): The name to associate with the texture.
- `path` (`const std::string &`): The file path to the texture image.
- `use_default_path` (`bool`): Value supplied for the use_default_path parameter.

### load_texture

~~~cpp
void Asset_Pool::load_texture(const std::string &name, const std::string &path, const std::string &locale_tag, bool use_default_path=true)
~~~

**Access:** public  **Returns:** ``void``

Registers a locale-specific texture variant under a shared logical name. Inactive variants stay unloaded. Locale changes invalidate previously returned pointers for localized textures, so callers should resolve them again by name.

**Parameters**

- `name` (`const std::string &`): Value supplied for the name parameter.
- `path` (`const std::string &`): Value supplied for the path parameter.
- `locale_tag` (`const std::string &`): Value supplied for the locale_tag parameter.
- `use_default_path` (`bool`): Value supplied for the use_default_path parameter.

### load_tileset_font

~~~cpp
void Asset_Pool::load_tileset_font(const std::string &name, const std::string &path, const Vec &tile_size, const std::string &char_map)
~~~

**Access:** public  **Returns:** ``void``

Loads a tileset font atlas from disk and adds it to the pool.

**Parameters**

- `name` (`const std::string &`): The name to associate with the font.
- `path` (`const std::string &`): The file path to the bitmap font atlas image.
- `tile_size` (`const Vec &`): Size of one glyph tile in the atlas.
- `char_map` (`const std::string &`): Characters mapped left-to-right, top-to-bottom in the atlas.

### localization

~~~cpp
const Localization & Asset_Pool::localization() const
~~~

**Access:** public  **Returns:** `const Localization &`

Retrieves the Localization object for managing localized text (const version).

**Parameters:** None.

### localization

~~~cpp
Localization & Asset_Pool::localization()
~~~

**Access:** public  **Returns:** `Localization &`

Retrieves the Localization object for managing localized text.

**Parameters:** None.

### pause_audio_group

~~~cpp
void Asset_Pool::pause_audio_group(const std::string &tag)
~~~

**Access:** public  **Returns:** ``void``

Pauses every audio file in a group.

**Parameters**

- `tag` (`const std::string &`): The group tag to pause.

### play_audio_group

~~~cpp
void Asset_Pool::play_audio_group(const std::string &tag)
~~~

**Access:** public  **Returns:** ``void``

Plays every audio file in a group.

**Parameters**

- `tag` (`const std::string &`): The group tag to play.

### play_audio_group_shuffled

~~~cpp
void Asset_Pool::play_audio_group_shuffled(const std::string &tag)
~~~

**Access:** public  **Returns:** ``void``

Plays every audio file in a group in a shuffled order.

**Parameters**

- `tag` (`const std::string &`): The group tag to play.

### remove_audio_from_all_groups

~~~cpp
void Asset_Pool::remove_audio_from_all_groups(const std::string &audio_name)
~~~

**Access:** private  **Returns:** ``void``

Constructs a Asset_Pool value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `audio_name` (`const std::string &`): Value supplied for the audio_name parameter.

### remove_audio_from_group

~~~cpp
void Asset_Pool::remove_audio_from_group(const std::string &audio_name, const std::string &tag)
~~~

**Access:** public  **Returns:** ``void``

Removes an audio file from a group tag.

**Parameters**

- `audio_name` (`const std::string &`): The name of the loaded audio file.
- `tag` (`const std::string &`): The group tag to detach.

### resume_audio_group

~~~cpp
void Asset_Pool::resume_audio_group(const std::string &tag)
~~~

**Access:** public  **Returns:** ``void``

Resumes every audio file in a group.

**Parameters**

- `tag` (`const std::string &`): The group tag to resume.

### set_audio_group_gain

~~~cpp
void Asset_Pool::set_audio_group_gain(const std::string &tag, float gain)
~~~

**Access:** public  **Returns:** ``void``

Sets the gain for every audio file in a group.

**Parameters**

- `tag` (`const std::string &`): The group tag to modify.
- `gain` (`float`): The gain value to apply.

### set_audio_group_loop_count

~~~cpp
void Asset_Pool::set_audio_group_loop_count(const std::string &tag, int loop_count)
~~~

**Access:** public  **Returns:** ``void``

Sets the loop count for every audio file in a group.

**Parameters**

- `tag` (`const std::string &`): The group tag to modify.
- `loop_count` (`int`): The loop count to apply.

### set_audio_group_pitch

~~~cpp
void Asset_Pool::set_audio_group_pitch(const std::string &tag, float pitch)
~~~

**Access:** public  **Returns:** ``void``

Sets the pitch for every audio file in a group.

**Parameters**

- `tag` (`const std::string &`): The group tag to modify.
- `pitch` (`float`): The pitch value to apply.

### set_audio_group_props

~~~cpp
void Asset_Pool::set_audio_group_props(const std::string &tag, const Audio_Props &props)
~~~

**Access:** public  **Returns:** ``void``

Applies a full Audio_Props value to every audio file in a group.

**Parameters**

- `tag` (`const std::string &`): The group tag to modify.
- `props` (`const Audio_Props &`): The properties to apply.

### set_locale

~~~cpp
bool Asset_Pool::set_locale(const std::string &locale_tag)
~~~

**Access:** public  **Returns:** ``bool``

Sets the current locale for localized assets.

**Parameters**

- `locale_tag` (`const std::string &`): The locale tag to set (e.g., "en", "fr").

### set_logger

~~~cpp
void Asset_Pool::set_logger(Logger *logger)
~~~

**Access:** public  **Returns:** ``void``

Sets the Logger to be used for logging messages.

**Parameters**

- `logger` (`Logger *`): Pointer to the Logger.

### set_renderer

~~~cpp
void Asset_Pool::set_renderer(SDL_Renderer *renderer)
~~~

**Access:** public  **Returns:** ``void``

Sets the SDL_Renderer to be used for texture loading.

**Parameters**

- `renderer` (`SDL_Renderer *`): Pointer to the SDL_Renderer.

### stop_audio_group

~~~cpp
void Asset_Pool::stop_audio_group(const std::string &tag)
~~~

**Access:** public  **Returns:** ``void``

Stops every audio file in a group.

**Parameters**

- `tag` (`const std::string &`): The group tag to stop.

### unload_audio

~~~cpp
void Asset_Pool::unload_audio(const std::string &name)
~~~

**Access:** public  **Returns:** ``void``

Unloads an audio file from the pool by name.

**Parameters**

- `name` (`const std::string &`): The name of the audio file to unload.

### unload_font

~~~cpp
void Asset_Pool::unload_font(const std::string &name)
~~~

**Access:** public  **Returns:** ``void``

Unloads a font from the pool by name.

**Parameters**

- `name` (`const std::string &`): The name of the font to unload.

### unload_texture

~~~cpp
void Asset_Pool::unload_texture(const std::string &name)
~~~

**Access:** public  **Returns:** ``void``

Unloads a texture from the pool by name.

**Parameters**

- `name` (`const std::string &`): The name of the texture to unload.

### Header usage example

~~~cpp
Engine::asset_pool->load_texture("player", "player.png");
Texture* player = Engine::asset_pool->get_texture("player");
~~~

## loading_screen.h

### ~Loading_Screen

~~~cpp
Loading_Screen::~Loading_Screen()
~~~

**Access:** public

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

### ~Simple_Tileset

~~~cpp
Simple_Tileset::~Simple_Tileset()
~~~

**Access:** public

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

### active

~~~cpp
bool Loading_Screen::active() const
~~~

**Access:** public  **Returns:** ``bool``

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### advance_frame

~~~cpp
void Simple_Tileset::advance_frame()
~~~

**Access:** public  **Returns:** ``void``

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters:** None.

### advance_frame_index

~~~cpp
void Simple_Tileset::advance_frame_index(std::size_t &frame_index) const
~~~

**Access:** public  **Returns:** ``void``

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters**

- `frame_index` (`std::size_t &`): Value supplied for the frame_index parameter.

### begin

~~~cpp
void Loading_Screen::begin(const std::string &title="Loading", Action on_complete={})
~~~

**Access:** public  **Returns:** ``void``

Performs the begin operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `title` (`const std::string &`): Value supplied for the title parameter.
- `on_complete` (`Action`): Value supplied for the on_complete parameter.

### cancel

~~~cpp
void Loading_Screen::cancel()
~~~

**Access:** public  **Returns:** ``void``

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### columns

~~~cpp
std::size_t Simple_Tileset::columns() const
~~~

**Access:** public  **Returns:** ``std::size_t``

Performs the columns operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### current_task

~~~cpp
const std::string & Loading_Screen::current_task() const
~~~

**Access:** public  **Returns:** ``const std::string &``

Performs the current task operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### draw_current_frame

~~~cpp
void Simple_Tileset::draw_current_frame(SDL_Renderer *renderer, const Vec &pos, const Vec &size) const
~~~

**Access:** public  **Returns:** ``void``

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters**

- `renderer` (`SDL_Renderer *`): Value supplied for the renderer parameter.
- `pos` (`const Vec &`): Value supplied for the pos parameter.
- `size` (`const Vec &`): Value supplied for the size parameter.

### draw_current_frame

~~~cpp
void Simple_Tileset::draw_current_frame(SDL_Renderer *renderer, const Vec &pos) const
~~~

**Access:** public  **Returns:** ``void``

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters**

- `renderer` (`SDL_Renderer *`): Value supplied for the renderer parameter.
- `pos` (`const Vec &`): Value supplied for the pos parameter.

### draw_fallback_background

~~~cpp
void Loading_Screen::draw_fallback_background()
~~~

**Access:** private  **Returns:** ``void``

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** None.

### draw_frame

~~~cpp
void Simple_Tileset::draw_frame(SDL_Renderer *renderer, const Vec &pos, std::size_t frame_index, const Vec &size) const
~~~

**Access:** public  **Returns:** ``void``

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters**

- `renderer` (`SDL_Renderer *`): Value supplied for the renderer parameter.
- `pos` (`const Vec &`): Value supplied for the pos parameter.
- `frame_index` (`std::size_t`): Value supplied for the frame_index parameter.
- `size` (`const Vec &`): Value supplied for the size parameter.

### draw_frame

~~~cpp
void Simple_Tileset::draw_frame(SDL_Renderer *renderer, const Vec &pos, std::size_t frame_index) const
~~~

**Access:** public  **Returns:** ``void``

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters**

- `renderer` (`SDL_Renderer *`): Value supplied for the renderer parameter.
- `pos` (`const Vec &`): Value supplied for the pos parameter.
- `frame_index` (`std::size_t`): Value supplied for the frame_index parameter.

### draw_progress_bar

~~~cpp
void Loading_Screen::draw_progress_bar(float value)
~~~

**Access:** private  **Returns:** ``void``

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters**

- `value` (`float`): Value supplied for the value parameter.

### draw_spinner

~~~cpp
void Loading_Screen::draw_spinner(float elapsed_seconds)
~~~

**Access:** private  **Returns:** ``void``

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters**

- `elapsed_seconds` (`float`): Value supplied for the elapsed_seconds parameter.

### enqueue

~~~cpp
void Loading_Screen::enqueue(const std::string &label, Action action, float weight=1.0f)
~~~

**Access:** public  **Returns:** ``void``

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters**

- `label` (`const std::string &`): Value supplied for the label parameter.
- `action` (`Action`): Value supplied for the action parameter.
- `weight` (`float`): Value supplied for the weight parameter.

### enqueue_step

~~~cpp
void Loading_Screen::enqueue_step(const std::string &label, Step step, float weight=1.0f)
~~~

**Access:** public  **Returns:** ``void``

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters**

- `label` (`const std::string &`): Value supplied for the label parameter.
- `step` (`Step`): Value supplied for the step parameter.
- `weight` (`float`): Value supplied for the weight parameter.

### error

~~~cpp
const std::string & Loading_Screen::error() const
~~~

**Access:** public  **Returns:** ``const std::string &``

Performs the error operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### fail

~~~cpp
void Loading_Screen::fail(const std::string &message)
~~~

**Access:** private  **Returns:** ``void``

Performs the fail operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `message` (`const std::string &`): Value supplied for the message parameter.

### failed

~~~cpp
bool Loading_Screen::failed() const
~~~

**Access:** public  **Returns:** ``bool``

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### finish

~~~cpp
void Loading_Screen::finish()
~~~

**Access:** private  **Returns:** ``void``

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

### frame_budget_ms

~~~cpp
float Loading_Screen::frame_budget_ms() const
~~~

**Access:** public  **Returns:** ``float``

Performs the frame budget ms operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### frame_count

~~~cpp
std::size_t Simple_Tileset::frame_count() const
~~~

**Access:** public  **Returns:** ``std::size_t``

Performs the frame count operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### free

~~~cpp
void Simple_Tileset::free()
~~~

**Access:** public  **Returns:** ``void``

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

### is_loaded

~~~cpp
bool Simple_Tileset::is_loaded() const
~~~

**Access:** public  **Returns:** ``bool``

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### load_artwork

~~~cpp
bool Loading_Screen::load_artwork(const std::string &background_path, const std::string &icon_path, Vec icon_frame_size={})
~~~

**Access:** public  **Returns:** ``bool``

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters**

- `background_path` (`const std::string &`): Value supplied for the background_path parameter.
- `icon_path` (`const std::string &`): Value supplied for the icon_path parameter.
- `icon_frame_size` (`Vec`): Value supplied for the icon_frame_size parameter.

### Loading_Screen

~~~cpp
Loading_Screen::Loading_Screen(const Loading_Screen &)=delete
~~~

**Access:** public

Constructs a Loading_Screen value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`const Loading_Screen &`): Value supplied for the  parameter.

### Loading_Screen

~~~cpp
Loading_Screen::Loading_Screen(SDL_Renderer *renderer, Logger *logger=nullptr)
~~~

**Access:** public

Constructs a Loading_Screen value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `renderer` (`SDL_Renderer *`): Value supplied for the renderer parameter.
- `logger` (`Logger *`): Value supplied for the logger parameter.

### make_tileset

~~~cpp
bool Simple_Tileset::make_tileset(const std::string &path, SDL_Renderer *renderer, Logger *logger=nullptr, Vec frame_size={0, 0})
~~~

**Access:** public  **Returns:** ``bool``

Creates or emits a new engine value using the supplied configuration. Determine ownership from the return type and the owning pool or service.

**Parameters**

- `path` (`const std::string &`): Value supplied for the path parameter.
- `renderer` (`SDL_Renderer *`): Value supplied for the renderer parameter.
- `logger` (`Logger *`): Value supplied for the logger parameter.
- `frame_size` (`Vec`): Value supplied for the frame_size parameter.

### operator=

~~~cpp
Loading_Screen & Loading_Screen::operator=(const Loading_Screen &)=delete
~~~

**Access:** public  **Returns:** `Loading_Screen &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`const Loading_Screen &`): Value supplied for the  parameter.

### operator=

~~~cpp
Simple_Tileset & Simple_Tileset::operator=(const Simple_Tileset &)=delete
~~~

**Access:** public  **Returns:** `Simple_Tileset &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`const Simple_Tileset &`): Value supplied for the  parameter.

### operator=

~~~cpp
Simple_Tileset & Simple_Tileset::operator=(Simple_Tileset &&other) noexcept
~~~

**Access:** public  **Returns:** `Simple_Tileset &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `other` (`Simple_Tileset &&`): Value supplied for the other parameter.

### pending_task_count

~~~cpp
std::size_t Loading_Screen::pending_task_count() const
~~~

**Access:** public  **Returns:** ``std::size_t``

Performs the pending task count operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### progress

~~~cpp
float Loading_Screen::progress() const
~~~

**Access:** public  **Returns:** ``float``

Performs the progress operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### render

~~~cpp
void Loading_Screen::render(float delta_seconds)
~~~

**Access:** public  **Returns:** ``void``

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters**

- `delta_seconds` (`float`): Value supplied for the delta_seconds parameter.

### reset_frame

~~~cpp
void Simple_Tileset::reset_frame()
~~~

**Access:** public  **Returns:** ``void``

Restores the component to its initial reusable state. Previously accumulated transient state is discarded.

**Parameters:** None.

### rows

~~~cpp
std::size_t Simple_Tileset::rows() const
~~~

**Access:** public  **Returns:** ``std::size_t``

Performs the rows operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### set_artwork

~~~cpp
void Loading_Screen::set_artwork(Texture *background, Texture *icon)
~~~

**Access:** public  **Returns:** ``void``

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `background` (`Texture *`): Value supplied for the background parameter.
- `icon` (`Texture *`): Value supplied for the icon parameter.

### set_frame_budget_ms

~~~cpp
void Loading_Screen::set_frame_budget_ms(float milliseconds)
~~~

**Access:** public  **Returns:** ``void``

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `milliseconds` (`float`): Value supplied for the milliseconds parameter.

### set_frame_size

~~~cpp
void Simple_Tileset::set_frame_size(const Vec &new_frame_size)
~~~

**Access:** public  **Returns:** ``void``

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `new_frame_size` (`const Vec &`): Value supplied for the new_frame_size parameter.

### set_whole_size

~~~cpp
void Simple_Tileset::set_whole_size(const Vec &new_whole_size)
~~~

**Access:** public  **Returns:** ``void``

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `new_whole_size` (`const Vec &`): Value supplied for the new_whole_size parameter.

### Simple_Tileset

~~~cpp
Simple_Tileset::Simple_Tileset()=default
~~~

**Access:** public

Constructs a Simple_Tileset value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### Simple_Tileset

~~~cpp
Simple_Tileset::Simple_Tileset(const Simple_Tileset &)=delete
~~~

**Access:** public

Constructs a Simple_Tileset value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`const Simple_Tileset &`): Value supplied for the  parameter.

### Simple_Tileset

~~~cpp
Simple_Tileset::Simple_Tileset(const std::string &path, SDL_Renderer *renderer, Logger *logger=nullptr, Vec frame_size={0, 0})
~~~

**Access:** public

Constructs a Simple_Tileset value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `path` (`const std::string &`): Value supplied for the path parameter.
- `renderer` (`SDL_Renderer *`): Value supplied for the renderer parameter.
- `logger` (`Logger *`): Value supplied for the logger parameter.
- `frame_size` (`Vec`): Value supplied for the frame_size parameter.

### Simple_Tileset

~~~cpp
Simple_Tileset::Simple_Tileset(Simple_Tileset &&other) noexcept
~~~

**Access:** public

Constructs a Simple_Tileset value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `other` (`Simple_Tileset &&`): Value supplied for the other parameter.

### title

~~~cpp
const std::string & Loading_Screen::title() const
~~~

**Access:** public  **Returns:** ``const std::string &``

Performs the title operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### update

~~~cpp
void Loading_Screen::update(float delta_seconds)
~~~

**Access:** public  **Returns:** ``void``

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters**

- `delta_seconds` (`float`): Value supplied for the delta_seconds parameter.

### Header usage example

~~~cpp
Engine::loading_screen->enqueue_step("Load level", [] { load_level(); });
Engine::loading_screen->update();
~~~








