# Asset_Pool

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `asset_pool.h`  
**Documented overloads:** 45

This page documents the engine-owned callables declared for `Asset_Pool`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

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

## Usage example

~~~cpp
Engine::asset_pool->load_texture("player", "player.png");
Texture* player = Engine::asset_pool->get_texture("player");
~~~

## Functions

### ~Asset_Pool

~~~cpp
Asset_Pool::~Asset_Pool() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

This function belongs to the documented engine type. Its exact behavior, inputs, and result are described by the signature and metadata in this entry.

**Parameters:** None.

---

### activate_localized_texture

~~~cpp
bool Asset_Pool::activate_localized_texture(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `bool`

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### add_audio_to_group

~~~cpp
void Asset_Pool::add_audio_to_group(const std::string &audio_name, const std::string &tag)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds an already loaded audio file to a group tag.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Asset_Pool

~~~cpp
Asset_Pool::Asset_Pool() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters:** None.

---

### Asset_Pool

~~~cpp
Asset_Pool::Asset_Pool(SDL_Renderer *renderer, Logger *logger=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs an Asset_Pool with a given SDL_Renderer and optional Logger.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Optional pointer to a Logger for logging messages; defaults to nullptr. | — |


---

### clear

~~~cpp
void Asset_Pool::clear()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Clears all cached assets from the pool.

**Parameters:** None.

---

### format_text

~~~cpp
std::string Asset_Pool::format_text(const std::string &key, const std::unordered_map< std::string, std::string > &values) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::string`

Retrieves a localized string by key and formats it with provided values.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_audio

~~~cpp
Audio * Asset_Pool::get_audio(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Audio *`

Retrieves an audio file by name.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_audio_group

~~~cpp
std::vector< Audio * > Asset_Pool::get_audio_group(const std::string &tag)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< Audio * >`

Gets every loaded audio file attached to a group tag.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_font

~~~cpp
IFont * Asset_Pool::get_font(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `IFont *`

Retrieves a font by name.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_locale

~~~cpp
const std::string & Asset_Pool::get_locale() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Gets the current locale tag.

**Parameters:** None.

---

### get_text

~~~cpp
std::string Asset_Pool::get_text(const std::string &key) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::string`

Retrieves a localized string by key using the current locale.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_texture

~~~cpp
Texture * Asset_Pool::get_texture(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Texture *`

Retrieves a texture by name.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### has_audio

~~~cpp
bool Asset_Pool::has_audio(const std::string &name) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if an audio file with the given name exists in the pool.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### has_audio_group

~~~cpp
bool Asset_Pool::has_audio_group(const std::string &tag) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if an audio group tag exists.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### has_font

~~~cpp
bool Asset_Pool::has_font(const std::string &name) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if a font with the given name exists in the pool.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### has_texture

~~~cpp
bool Asset_Pool::has_texture(const std::string &name) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if a texture with the given name exists in the pool.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### load_audio

~~~cpp
void Asset_Pool::load_audio(const std::string &name, const std::string &path, bool predecode=true)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Loads an audio file from disk and adds it to the pool.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### load_audio

~~~cpp
void Asset_Pool::load_audio(const std::string &name, const std::string &path, const std::string &tag, bool predecode=true)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Loads an audio file from disk and adds it to an audio group tag.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### load_audio

~~~cpp
void Asset_Pool::load_audio(const std::string &name, const std::string &path, const std::vector< std::string > &tags, bool predecode=true)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Loads an audio file from disk and adds it to multiple audio group tags.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### load_locale

~~~cpp
bool Asset_Pool::load_locale(const std::string &locale_tag, const std::string &path)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Loads a texture from a file and adds it to the pool, with an option to specify a custom SDL_Renderer.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### load_locales_from_directory

~~~cpp
std::size_t Asset_Pool::load_locales_from_directory(const std::string &directory)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::size_t`

Loads all locale JSON files from a directory and adds them to the pool.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### load_sdl_font

~~~cpp
void Asset_Pool::load_sdl_font(const std::string &name, const std::string &path, int size=16, bool pixel_art=false)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Loads an SDL_ttf font from disk and adds it to the pool.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### load_texture

~~~cpp
void Asset_Pool::load_texture(const std::string &name, const std::string &path, bool use_default_path=true)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Loads a texture from a file and adds it to the pool.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### load_texture

~~~cpp
void Asset_Pool::load_texture(const std::string &name, const std::string &path, const std::string &locale_tag, bool use_default_path=true)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Registers a locale-specific texture variant under a shared logical name. Inactive variants stay unloaded. Locale changes invalidate previously returned pointers for localized textures, so callers should resolve them again by name.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### load_tileset_font

~~~cpp
void Asset_Pool::load_tileset_font(const std::string &name, const std::string &path, const Vec &tile_size, const std::string &char_map)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Loads a tileset font atlas from disk and adds it to the pool.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tile_size` | `const Vec &` | Size of one glyph tile in the atlas. | — |


---

### localization

~~~cpp
const Localization & Asset_Pool::localization() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const Localization &`

Retrieves the Localization object for managing localized text (const version).

**Parameters:** None.

---

### localization

~~~cpp
Localization & Asset_Pool::localization()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Localization &`

Retrieves the Localization object for managing localized text.

**Parameters:** None.

---

### pause_audio_group

~~~cpp
void Asset_Pool::pause_audio_group(const std::string &tag)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Pauses every audio file in a group.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### play_audio_group

~~~cpp
void Asset_Pool::play_audio_group(const std::string &tag)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Plays every audio file in a group.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### play_audio_group_shuffled

~~~cpp
void Asset_Pool::play_audio_group_shuffled(const std::string &tag)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Plays every audio file in a group in a shuffled order.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### remove_audio_from_all_groups

~~~cpp
void Asset_Pool::remove_audio_from_all_groups(const std::string &audio_name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Constructs a Asset_Pool value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### remove_audio_from_group

~~~cpp
void Asset_Pool::remove_audio_from_group(const std::string &audio_name, const std::string &tag)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes an audio file from a group tag.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### resume_audio_group

~~~cpp
void Asset_Pool::resume_audio_group(const std::string &tag)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Resumes every audio file in a group.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_audio_group_gain

~~~cpp
void Asset_Pool::set_audio_group_gain(const std::string &tag, float gain)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the gain for every audio file in a group.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_audio_group_loop_count

~~~cpp
void Asset_Pool::set_audio_group_loop_count(const std::string &tag, int loop_count)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the loop count for every audio file in a group.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_audio_group_pitch

~~~cpp
void Asset_Pool::set_audio_group_pitch(const std::string &tag, float pitch)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the pitch for every audio file in a group.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_audio_group_props

~~~cpp
void Asset_Pool::set_audio_group_props(const std::string &tag, const Audio_Props &props)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Applies a full Audio_Props value to every audio file in a group.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `props` | `const Audio_Props &` | The properties to apply. | — |


---

### set_locale

~~~cpp
bool Asset_Pool::set_locale(const std::string &locale_tag)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Sets the current locale for localized assets.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_logger

~~~cpp
void Asset_Pool::set_logger(Logger *logger)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the Logger to be used for logging messages.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Pointer to the Logger. | — |


---

### set_renderer

~~~cpp
void Asset_Pool::set_renderer(SDL_Renderer *renderer)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the SDL_Renderer to be used for texture loading.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### stop_audio_group

~~~cpp
void Asset_Pool::stop_audio_group(const std::string &tag)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Stops every audio file in a group.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### unload_audio

~~~cpp
void Asset_Pool::unload_audio(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Unloads an audio file from the pool by name.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### unload_font

~~~cpp
void Asset_Pool::unload_font(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Unloads a font from the pool by name.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### unload_texture

~~~cpp
void Asset_Pool::unload_texture(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Unloads a texture from the pool by name.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.



