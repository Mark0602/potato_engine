# Core and Utilities API

**Engine version:** Potato Engine 1.0.0  
**Language:** C++

This file documents Potato Engine-owned callable names. Overloads share one entry. Constructors, destructors, operators, and declared helpers are included. Third-party APIs are excluded.

## engine.h

- **~Application(...)** — Releases resources owned by the instance.
- **~SDLstate(...)** — Releases resources owned by the instance.
- **Application(...)** — Constructs a Application instance.
- **begin_frame(...)** — Performs the begin frame operation defined by this header.
- **clearup(...)** — Clears the owned state or collection.
- **get_renderer_backend(...)** — Returns renderer backend.
- **getlogicalheight(...)** — Performs the getlogicalheight operation defined by this header.
- **getlogicalwidth(...)** — Performs the getlogicalwidth operation defined by this header.
- **getwindowheight(...)** — Performs the getwindowheight operation defined by this header.
- **getwindowwidth(...)** — Performs the getwindowwidth operation defined by this header.
- **initialize(...)** — Initializes the service or resource.
- **initiate(...)** — Initializes the service or resource.
- **is_gpu_renderer(...)** — Reports whether gpu renderer.
- **is_initialized(...)** — Reports whether initialized.
- **load_config(...)** — Loads config.
- **operator=(...)** — Replaces this object with another value; the declaration may disable copying.
- **present(...)** — Performs the present operation defined by this header.
- **quit(...)** — Performs the quit operation defined by this header.
- **run(...)** — Performs the run operation defined by this header.
- **SDLstate(...)** — Constructs a SDLstate instance.
- **shutdown(...)** — Releases initialized engine resources.
- **using_gpu_renderer(...)** — Performs the using gpu renderer operation defined by this header.

### Example

~~~cpp
config::game_config cfg;
cfg.title = "Potato Demo";
Engine::Application app(cfg);
if (!app.initialize()) return 1;
return app.run();
~~~

## vec.h

- **operator-(...)** — Returns the difference or negated result.
- **operator-=(...)** — Subtracts the right operand from this value.
- **operator!=(...)** — Tests for inequality.
- **operator*(...)** — Returns a product or scaled value.
- **operator*=(...)** — Multiplies this value by the right operand.
- **operator/(...)** — Returns a divided or scaled-down value.
- **operator/=(...)** — Divides this value by the right operand.
- **operator+(...)** — Returns the sum of the operands.
- **operator+=(...)** — Adds the right operand to this value.
- **operator<(...)** — Tests the component-wise less-than relation.
- **operator<=(...)** — Tests the component-wise less-than-or-equal relation.
- **operator==(...)** — Tests for equality.
- **operator>(...)** — Tests the component-wise greater-than relation.
- **operator>=(...)** — Tests the component-wise greater-than-or-equal relation.
- **Transform(...)** — Constructs a Transform instance.

### Example

~~~cpp
Vec velocity{120.0f, 0.0f};
Transform player{{32.0f, 48.0f}, {16.0f, 16.0f}};
player.pos += velocity * delta_seconds;
~~~

## color.h

- **Color(...)** — Constructs a Color instance.
- **from_hex(...)** — Performs the from hex operation defined by this header.
- **from_hex_string(...)** — Performs the from hex string operation defined by this header.
- **from_sdl_color(...)** — Performs the from sdl color operation defined by this header.
- **operator-(...)** — Returns the difference or negated result.
- **operator-=(...)** — Subtracts the right operand from this value.
- **operator!=(...)** — Tests for inequality.
- **operator*(...)** — Returns a product or scaled value.
- **operator*=(...)** — Multiplies this value by the right operand.
- **operator/(...)** — Returns a divided or scaled-down value.
- **operator/=(...)** — Divides this value by the right operand.
- **operator+(...)** — Returns the sum of the operands.
- **operator+=(...)** — Adds the right operand to this value.
- **operator==(...)** — Tests for equality.
- **to_sdl_color(...)** — Performs the to sdl color operation defined by this header.
- **with_alpha(...)** — Performs the with alpha operation defined by this header.

### Example

~~~cpp
Color tint = Color::from_hex_string("#FFAA33");
tint = tint.with_alpha(192);
~~~

## utils.h

- **abs(...)** — Performs the abs operation defined by this header.
- **angle(...)** — Performs the angle operation defined by this header.
- **angle_between(...)** — Performs the angle between operation defined by this header.
- **angle_between_degrees(...)** — Performs the angle between degrees operation defined by this header.
- **angle_between_radians(...)** — Performs the angle between radians operation defined by this header.
- **angle_between_signed(...)** — Performs the angle between signed operation defined by this header.
- **angle_between_signed_degrees(...)** — Performs the angle between signed degrees operation defined by this header.
- **angle_between_signed_radians(...)** — Performs the angle between signed radians operation defined by this header.
- **ceil(...)** — Performs the ceil operation defined by this header.
- **clamp(...)** — Performs the clamp operation defined by this header.
- **convert_FRect_to_Vec(...)** — Converts FRect to Vec.
- **convert_Vec_to_FRect(...)** — Converts Vec to FRect.
- **cross(...)** — Performs the cross operation defined by this header.
- **distance(...)** — Performs the distance operation defined by this header.
- **distance_squared(...)** — Performs the distance squared operation defined by this header.
- **dot(...)** — Performs the dot operation defined by this header.
- **floor(...)** — Performs the floor operation defined by this header.
- **fullscreen_window(...)** — Performs the fullscreen window operation defined by this header.
- **get_mouse_position(...)** — Returns mouse position.
- **get_window_bottom_center(...)** — Returns window bottom center.
- **get_window_bottom_left(...)** — Returns window bottom left.
- **get_window_bottom_right(...)** — Returns window bottom right.
- **get_window_center(...)** — Returns window center.
- **get_window_left_center(...)** — Returns window left center.
- **get_window_right_center(...)** — Returns window right center.
- **get_window_size(...)** — Returns window size.
- **get_window_top_center(...)** — Returns window top center.
- **get_window_top_left(...)** — Returns window top left.
- **get_window_top_right(...)** — Returns window top right.
- **invert(...)** — Performs the invert operation defined by this header.
- **is_point_in_circle(...)** — Reports whether point in circle.
- **is_point_in_rect(...)** — Reports whether point in rect.
- **length(...)** — Performs the length operation defined by this header.
- **length_squared(...)** — Performs the length squared operation defined by this header.
- **lerp(...)** — Performs the lerp operation defined by this header.
- **lerp_color(...)** — Performs the lerp color operation defined by this header.
- **maximize_window(...)** — Performs the maximize window operation defined by this header.
- **nearly_equal(...)** — Performs the nearly equal operation defined by this header.
- **normalize(...)** — Performs the normalize operation defined by this header.
- **os_cursor_visibility(...)** — Performs the os cursor visibility operation defined by this header.
- **perpendicular(...)** — Performs the perpendicular operation defined by this header.
- **reflect(...)** — Performs the reflect operation defined by this header.
- **rotate(...)** — Performs the rotate operation defined by this header.
- **round(...)** — Performs the round operation defined by this header.
- **Vec(...)** — Constructs a Vec instance.
- **windowed_window(...)** — Performs the windowed window operation defined by this header.

### Example

~~~cpp
Vec direction = normalize(target - origin);
float separation = distance(origin, target);
~~~

## debug.h

- **close(...)** — Performs the close operation defined by this header.
- **finalize_log(...)** — Performs the finalize log operation defined by this header.
- **flood_logging(...)** — Performs the flood logging operation defined by this header.
- **format_line(...)** — Formats a value for presentation.
- **frame_indexing(...)** — Performs the frame indexing operation defined by this header.
- **get_elapsed_time_string(...)** — Returns elapsed time string.
- **get_logged_message(...)** — Returns logged message.
- **get_min_level(...)** — Returns min level.
- **increment_frame_index(...)** — Performs the increment frame index operation defined by this header.
- **init(...)** — Initializes the service or resource.
- **is_flood_logging(...)** — Reports whether flood logging.
- **is_initialized(...)** — Reports whether initialized.
- **log(...)** — Performs the log operation defined by this header.
- **Logger(...)** — Constructs a Logger instance.
- **set_frame_index(...)** — Sets frame index.
- **set_min_level(...)** — Sets min level.

### Example

~~~cpp
Logger logger;
logger.init("logs/latest.log");
logger.log(Log_Level::INFO, "Game", "Started");
~~~

## timer.h

- **elapsed(...)** — Performs the elapsed operation defined by this header.
- **is_just_done(...)** — Reports whether just done.
- **is_running(...)** — Reports whether running.
- **progress(...)** — Performs the progress operation defined by this header.
- **remaining(...)** — Performs the remaining operation defined by this header.
- **start(...)** — Starts the operation or state.
- **stop(...)** — Stops the operation or state.
- **tick(...)** — Advances time-dependent state.
- **Timer(...)** — Constructs a Timer instance.

### Example

~~~cpp
Timer cooldown;
cooldown.start(1.0f);
cooldown.tick(delta_seconds);
~~~

## prandom.h

- **random_choice(...)** — Returns a random choice.
- **random_choice_weighted(...)** — Returns a random choice weighted.
- **random_range(...)** — Returns a random range.
- **random_range_weighted(...)** — Returns a random range weighted.
- **random_weighted_index(...)** — Returns a random weighted index.

### Example

~~~cpp
int damage = random_range(8, 12);
~~~

## functionality_trigger.h

- **clear(...)** — Clears the owned state or collection.
- **register_source(...)** — Registers source.
- **unregister_sources(...)** — Unregisters sources.

### Example

~~~cpp
Functionality_Trigger::register_source(owner, source);
Functionality_Trigger::unregister_sources(owner);
~~~

## game_console.h

- **handle_event(...)** — Handles event.
- **hide_console(...)** — Performs the hide console operation defined by this header.
- **is_console_visible(...)** — Reports whether console visible.
- **is_supported(...)** — Reports whether supported.
- **show_console(...)** — Performs the show console operation defined by this header.
- **toggle_console(...)** — Performs the toggle console operation defined by this header.

### Example

~~~cpp
if (Game_Console::is_supported()) Game_Console::toggle_console();
~~~

## save_game.h

- **add(...)** — Performs the add operation defined by this header.
- **apply_snapshot(...)** — Applies snapshot.
- **capture_current(...)** — Captures current.
- **capture_object(...)** — Captures object.
- **capture_snapshot(...)** — Captures snapshot.
- **clear(...)** — Clears the owned state or collection.
- **contains(...)** — Performs the contains operation defined by this header.
- **empty(...)** — Performs the empty operation defined by this header.
- **load_and_apply(...)** — Loads and apply.
- **load_snapshot(...)** — Loads snapshot.
- **remove(...)** — Performs the remove operation defined by this header.
- **save_current(...)** — Saves current.
- **save_snapshot(...)** — Saves snapshot.

### Example

~~~cpp
Save_Game::save_current("saves/slot1.bin");
Save_Game::load_and_apply("saves/slot1.bin");
~~~

