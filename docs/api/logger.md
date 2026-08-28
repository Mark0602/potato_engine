# Logger

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `debug.h`  
**Documented overloads:** 17

This page documents the engine-owned callables declared for `Logger`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Logger logger;
logger.init("logs/latest.log");
logger.log(Log_Level::INFO, "Game", "Started");
~~~

## Functions

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

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


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


---

### frame_indexing

~~~cpp
void Logger::frame_indexing(bool state)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Enables or disables per-frame index prefixes in log lines.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


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

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


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

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


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


