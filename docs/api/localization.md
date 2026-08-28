# Localization

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `localization.h`  
**Documented overloads:** 16

This page documents the engine-owned callables declared for `Localization`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Detailed workflow example

~~~cpp
Localization text;
text.load("en-US", "assets/locales/en-US.json");
text.set_current_tag("en-US");

hud_label.set_text(text.format(
    "hud.score",
    {{"score", std::to_string(score)}}
));
~~~

## Usage example

~~~cpp
Localization strings;
strings.load("en-US", "assets/locales/en-US.json");
std::string title = strings.get("menu.title");
~~~

## Functions

### ~Localization

~~~cpp
Localization::~Localization() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### clear

~~~cpp
void Localization::clear()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Clears all loaded localization tables.

**Parameters:** None.

---

### format

~~~cpp
std::string Localization::format(const std::string &key, const std::unordered_map< std::string, std::string > &values) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::string`

Retrieves a localized string and replaces placeholders.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get

~~~cpp
std::string Localization::get(const std::string &key) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::string`

Retrieves a localized string by key.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_current_tag

~~~cpp
const std::string & Localization::get_current_tag() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Gets the currently active localization tag.

**Parameters:** None.

---

### get_fallback_tag

~~~cpp
const std::string & Localization::get_fallback_tag() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Gets the fallback localization tag.

**Parameters:** None.

---

### has_key

~~~cpp
bool Localization::has_key(const std::string &key) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether a key exists in the current or fallback tag.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### has_tag

~~~cpp
bool Localization::has_tag(const std::string &tag) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether a tag exists.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### load

~~~cpp
bool Localization::load(const std::string &tag, const std::string &path)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Loads a localization JSON file and stores it under a tag.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Localization

~~~cpp
Localization::Localization() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### Localization

~~~cpp
Localization::Localization(const Localization &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Localization value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Localization

~~~cpp
Localization::Localization(const std::string &default_tag, const std::string &fallback_tag, Logger *logger=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Localization instance with default and fallback tags.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Pointer to a Logger instance (optional). | — |


---

### operator=

~~~cpp
Localization & Localization::operator=(const Localization &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Localization &`

Constructs a Localization value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_current_tag

~~~cpp
bool Localization::set_current_tag(const std::string &tag)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Sets the currently active localization tag.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_fallback_tag

~~~cpp
void Localization::set_fallback_tag(const std::string &tag)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the fallback tag used when a key is missing in the current tag.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_logger

~~~cpp
void Localization::set_logger(Logger *logger)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the logger instance for logging missing keys and other messages.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Pointer to a Logger instance. | — |


