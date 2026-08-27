# Modding and AngelScript

`Potato::Modding` is a generic library. It discovers and orders mods, resolves safe content/script paths, calculates a shared hash, owns one client or server AngelScript runtime, and calls consumer-provided adapters. It does not define any game-specific content or behavior.

## Directory and manifest

Each direct child of the configured mods directory may contain `manifest.json`:

```text
mods/
  example_mod/
    manifest.json
    scripts/
      shared.as
      client.as
    content/
      example.json
```

```json
{
  "schema_version": 1,
  "id": "example_mod",
  "display_name": "Example Mod",
  "version": "1.0.0",
  "game_api_version": "example_api_1",
  "enabled": true,
  "side": "both",
  "dependencies": [],
  "load_after": [],
  "angel_script": {
    "shared": ["scripts/shared.as"],
    "client": ["scripts/client.as"],
    "server": []
  },
  "content": {
    "definitions": ["content/example.json"]
  },
  "exports": {
    "components": [
      "simple_component",
      { "id": "advanced_component", "script_prefix": "advanced" }
    ]
  }
}
```

Supported `side` values are `both`, `client`, and `server`. IDs, dependency names, content/export group names, export IDs, and script prefixes must be lowercase snake_case. Schema version must be supported, mod version must be non-empty, and `game_api_version` must exactly match the consumer configuration.

Every referenced path must be relative, exist, and stay inside its own mod directory after canonicalization. This applies to content, entry scripts, and AngelScript includes.

## Discovery and ordering

```cpp
using namespace potato::modding;

mod_service service;
mod_service_config config;
config.mods_path = "mods";
config.game_api_version = "example_api_1";
config.script_line_budget = 10000;

std::string error;
if (!service.discover(config, &error)) {
    report(error);
}
```

A missing mods directory is a successful empty discovery. A path that exists but is not a directory is an error. Disabled manifests are ignored.

Required `dependencies` must exist. `load_after` adds ordering only when the named mod exists. Self-dependencies, duplicate enabled IDs, and cycles fail discovery. Available nodes are ordered deterministically by mod ID, so identical inputs produce identical load order.

`mod_manager::content_paths(group, side)` collects resolved paths in mod order. `script_paths(manifest, side)` combines shared scripts with the selected side's scripts. `exports(manifest, group)` returns the consumer-defined export entries. `qualified_id(mod_id, local_id)` and `canonical_name()` help games build stable namespaced registries.

`shared_mod_hash()` fingerprints the discovered shared mod definition/content for compatibility checks. Use it as one input to multiplayer or cache validation; the game remains responsible for defining its compatibility policy.

## Start a script side

One `mod_service` owns exactly one side-specific runtime. `start_scripts` requires `client` or `server`; `both` is rejected as ambiguous.

```cpp
bool ok = service.start_scripts(
    mod_side::client,
    [](script_log_level level,
       const std::string& category,
       const std::string& message) {
        forward_log(level, category, message);
    },
    [](asIScriptEngine* engine, std::string& error) {
        return register_safe_game_api(engine, error);
    },
    [](const mod_manifest& manifest,
       angel_script_runtime& runtime,
       std::string& error) {
        return register_manifest_exports(manifest, runtime, error);
    },
    &error
);
```

The API registrar runs once after VM initialization. Mods then compile and their optional `void on_mod_loaded()` functions run in dependency order. The export registrar runs for each applicable mod so the consumer can interpret its generic export groups.

After a failed startup, the service records a failed state. Call `shutdown_scripts()` before reuse. Discovery configuration cannot change after the service has already discovered mods unless the existing configuration is identical.

## AngelScript runtime

The runtime registers AngelScript's standard `string` and four log functions:

```angelscript
void log_debug(const string &in message);
void log_info(const string &in message);
void log_warning(const string &in message);
void log_error(const string &in message);
```

It defines `potato_client` or `potato_server` while building the selected side. Scripts may include only relative `.as` files inside their mod root. Pragmas, absolute includes, and directory escapes are rejected.

The base VM exposes no filesystem, process, network, native pointer, or game API. Unsafe references and global variables are disabled; nesting, stack, call stack, and executed-line budgets are limited. Security still depends on the consumer registering only narrow, validated functions and value types.

Use `find_function(mod_id, side, declaration)` to locate a compiled function and `execute(function, object_arguments, error)` to call it. Object arguments are passed to the prepared context in order and must match the declaration. The returned function pointer is borrowed from the VM and becomes invalid after shutdown.

`angel_script_runtime` can also be used directly through `initialize`, `build_mod`, `find_function`, `execute`, and `shutdown`, but `mod_service` is the recommended owner because it enforces discovery and side lifecycle.
