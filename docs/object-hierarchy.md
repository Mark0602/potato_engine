# Object hierarchy

Potato Engine objects can form an optional, non-owning parent/child hierarchy. The hierarchy affects transforms only: it does not imply ownership, visibility inheritance, update propagation, or automatic child deletion.

## Local and world transforms

For a root object, the public `transform` field is its world transform. Once the object has a parent, that same field becomes local to the parent. The explicit accessors make intent clear:

| API | Meaning |
| --- | --- |
| `get_transform()` / `get_local_transform()` | Local transform; world transform for a root |
| `set_transform()` / `set_local_transform()` | Replace the local transform |
| `get_world_transform()` | Compose every ancestor and return world space |
| `set_world_transform(world)` | Convert a world value back into current parent space |

Transform composition rotates the child position around the parent's top-left origin, adds the parent's position and angle, and combines SDL flip flags. Child size is unchanged because `Transform::size` represents dimensions, not scale. A parent's flip changes the child's resulting flip flags but does not mirror its positional offset.

`get_world_transform()` computes through the parent chain on demand. Keep hierarchies reasonably shallow when querying many objects per frame.

## Creating and changing relationships

```cpp
Object player(Transform{{100.0f, 80.0f}, {32.0f, 32.0f}});
Object weapon(Transform{{24.0f, 12.0f}, {16.0f, 8.0f}});

// Keep weapon.transform as a local offset from the player.
weapon.set_parent(&player, false);

player.transform.pos += velocity * dt;
player.transform.rotation.x += 30.0f * dt;

Transform weapon_world = weapon.get_world_transform();
```

`set_parent(parent, keep_world_transform)` is the central operation. `add_child()` is the parent-side convenience wrapper, while `remove_child()` and `clear_children()` detach relationships.

- The default `keep_world_transform=true` prevents a visible jump during reparenting. The engine rewrites the local transform to preserve the old world result.
- Pass `false` when the existing `transform` already represents the desired offset relative to the new parent.
- Passing `nullptr` makes the object a root.
- Self-parenting and relationships that would create a cycle return `false` without changing the hierarchy.

Use `get_parent()`, `get_children()`, `has_parent()`, and `is_ancestor_of()` to inspect the tree. Returned pointers are borrowed.

## Lifetime and ownership

Neither side owns the other. Destroying a child unregisters it from its parent. Destroying a parent detaches all direct children, preserves their current world transforms, and leaves them alive. A hierarchy therefore does not replace the game's normal RAII or entity ownership model.

`Object` is non-copyable, and its address is its hierarchy identity. Keep objects at stable addresses while registries or game code hold their pointers. Heap allocation through `std::unique_ptr` is the usual choice for dynamic collections.

## Engine integration

- Texture drawing, draw commands, Y sorting, and pointer hit tests use the composed world transform.
- `Camera::follow()` follows the target's world transform.
- Attached physics bodies collide and move in world space. `Collision_Body::transform()` remains the owner-local reference for compatibility; `collision_transform()` returns effective world geometry.
- Save snapshots store world transforms, not parent pointers. Loading into an already parented object converts the saved world transform into its current local space. Rebuild hierarchy links in game-specific load code.
- Direct animation writes to `object.transform` animate local space for a parented object and world space for a root.

Pointer hit testing remains an axis-aligned rectangle test and does not rotate the bounds with `rotation.x`. Parent visibility and input transparency do not automatically propagate to children; set them explicitly when group behavior is required.
