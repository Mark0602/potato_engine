# 🥔 Potato Engine

Egy egyszerű    játékmotor SDL3 alapokra építve.

## 🎮 Új Játék Létrehozása

```cmd
create_new_game.bat my_awesome_game
cd ..\my_awesome_game
configure.bat
build.bat
```

## 📁 Projekt Struktúra

```
potato_engine/
├── configure.bat          # ⚙️ Konfiguráció (futtasd először!)
├── build.bat             # 🔨 Build script
├── create_new_game.bat   # 🎮 Új játék létrehozó
├── CMakeLists.txt        # 📄 CMake config (relatív útvonalak)
├── src/                  # 💻 Forráskód
│   ├── main.cpp
│   └── engine/
├── SDL/                  # 📦 SDL3 forrás
└── build/                # 🏗️ Build könyvtár (ne commitold!)
```

## 🔧 Követelmények

- CMake 3.16+
- MinGW-w64 (MSYS2 ajánlott)

**MSYS2 telepítés:**
```bash
# MSYS2 UCRT64 terminálban:
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-make
```

Aztán add hozzá a PATH-hoz: `C:\msys64\ucrt64\bin`

## 📖 Részletes Dokumentáció

Lásd: `README_BUILD.md`

## 💡 Fontos!

- **Mindig futtasd először** a `configure.bat`-ot új gépen/átnevezés után
- **Ne commitold** a `build/` könyvtárat
- A `CMakeLists.txt` **már tartalmazza** az összes szükséges beállítást

---

Happy coding! 🥔✨
