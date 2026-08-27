# Assets, fonts, audio, and localization

## Asset pool

`Asset_Pool` is the engine-owned cache for textures, fonts, audio files, localization tables, localized texture definitions, and audio group tags. Assets are stored by unique string names in `std::unique_ptr`; every pointer returned by `get_texture`, `get_font`, `get_audio`, or `get_audio_group` is borrowed.

Duplicate loads keep the cached asset and log a warning. `has_*` checks do not log; `get_*` returns `nullptr` and logs when a name is missing. Unloading or clearing an asset invalidates every borrowed pointer to it.

```cpp
auto* assets = Engine::asset_pool;
assets->load_texture("logo", "logo.png"); // assets/textures/logo.png
assets->load_sdl_font("body", "assets/fonts/body.ttf", 18);
assets->load_audio("click", "assets/audio/click.wav", true);

Texture* logo = assets->get_texture("logo");
IFont* body = assets->get_font("body");
Audio* click = assets->get_audio("click");
```

Only normal texture loading supplies an automatic `assets/textures/` prefix. Font, audio, localization, tilemap, and mod paths are explicit.

## Fonts

`IFont` is the common interface for load/unload, text measurement, pixel-art selection, and drawing. Implementations are:

- `SDL_Font`: scalable TTF/OTF text through SDL_ttf;
- `Tileset_Font`: fixed-grid bitmap glyphs mapped by a character-map string.

`IFont_Props` bundles renderer, text, path, position, color, base size, and scale for retained draw calls. Direct argument overloads are also available.

SDL fonts render dynamic text through temporary textures. `set_pixel_art(true)` requests hard-edged sampling. Tileset fonts are always pixel-art and calculate glyph indices left-to-right/top-to-bottom from the provided map.

Use `Label` for text that should participate in the normal render queue, camera, z-index, shadow, and object lifecycle.

## Audio assets

`Audio` owns a loaded `MIX_Audio` resource and uses a borrowed mixer/track pool. Set `predecode=true` for small, low-latency effects; use `false` to stream larger music files.

`Audio_Props` controls:

- gain;
- 3D position used for panning/attenuation, or horizontal panning through `set_panning(-1..1)`;
- pitch, clamped to `0.1..100`;
- loop count (`0` once, positive repeats, `-1` infinite);
- requested playback state;
- fade-out duration in milliseconds.

Normal `play`, `pause`, `resume`, and `stop` update requested state and are applied during `Track_Pool::flush_tracks()` each frame. The `force_*` variants issue the operation immediately. `play_fnf()` is unmanaged fire-and-forget playback and should be reserved for cases that do not need later control.

## Track pool

`Track_Pool` preallocates the configured number of default mixer tracks and creates dynamic tracks if all are busy. It owns `ITrack` instances, while each track only borrows its current `Audio`.

Default tracks persist for the pool lifetime. Dynamic tracks have a configurable lifetime and are released for reuse. `flush_tracks(dt)` applies changed properties, advances timers, and maintains tracks. Use `get_free_track`, `create_new_default_track`, `create_new_dynamic_track`, `release_track`, and `update_track` for low-level management.

`set_master_gain()` changes mixer-wide gain. This is the effective master control; the standalone `Engine::master_gain` variable is only a public value unless the game synchronizes it with the pool.

## Audio groups

The asset pool can associate one audio name with multiple arbitrary tags such as `music`, `ui`, or `ambience`.

```cpp
assets->load_audio("menu_click", "assets/audio/click.wav", "ui");
assets->load_audio("menu_back", "assets/audio/back.wav", "ui");

assets->set_audio_group_gain("ui", 0.7f);
assets->play_audio_group_shuffled("ui");
```

Group operations can set complete properties, gain, pitch, or looping and can play, shuffle-play, pause, resume, or stop all members. Removing/unloading audio also removes its group references.

## Localization

`Localization` loads nested JSON objects and flattens them to dotted keys. The active tag is checked first, then the fallback tag. A missing key returns a visible debug string and may be logged.

```json
{
  "menu": {
    "play": "Play",
    "coins": "Coins: {count}"
  }
}
```

```cpp
assets->load_locale("en", "assets/locales/en.json");
assets->load_locale("de", "assets/locales/de.json");
assets->set_locale("de");

std::string play = assets->get_text("menu.play");
std::string coins = assets->format_text("menu.coins", {{"count", "12"}});
```

`load_locales_from_directory()` loads `.json` files in sorted order and uses each filename stem as its tag. Tags are generic variants and can represent languages, themes, or seasonal content.

## Localized textures

Register multiple paths under one logical texture name by adding a locale tag:

```cpp
assets->load_texture("title", "title_en.png", "en");
assets->load_texture("title", "title_de.png", "de");
assets->set_locale("de");
Texture* title = assets->get_texture("title");
```

Localized variants load lazily for the active locale and fall back to `Localization::get_fallback_tag()`. Changing the locale may unload and replace the texture object. Any previously returned pointer for that localized name becomes invalid; resolve it again after every successful locale change.

`Asset_Pool::set_locale()` succeeds if either text or a texture variant exists for the tag, updates available text localization, and refreshes every registered localized texture.

