# Potato Engine - Build Instructions

## Projekt Klónozása / Átnevezése

Ha új játékot hozol létre vagy át akarod nevezni a projektet:

1. **Másold át a teljes projektet egy új könyvtárba**
   ```
   xcopy /E /I potato_engine my_new_game
   ```

2. **Törölj minden build artifactot** (ha van)
   ```
   cd my_new_game
   rmdir /S /Q build
   ```

3. **Futtasd a configure scriptet**
   ```
   configure.bat
   ```

4. **Build-eld a projektet**
   ```
   build.bat
   ```

## Első Használat

### Windows (MinGW)

1. Győződj meg róla, hogy telepítve van:
   - CMake (https://cmake.org/)
   - MinGW-w64 (MSYS2 ajánlott: https://www.msys2.org/)

2. Futtasd a konfigurációs scriptet:
   ```
   configure.bat
   ```

3. Build-eld a projektet:
   ```
   build.bat
   ```

4. Futtasd a játékot:
   ```
   build\potato_engine.exe
   ```

## Projekt Struktúra

```
potato_engine/
├── CMakeLists.txt          # CMake konfiguráció
├── configure.bat           # Konfiguráló script (új!)
├── build.bat              # Build script (új!)
├── .gitignore             # Git ignore fájl (új!)
├── src/                   # Forráskód
│   ├── main.cpp
│   └── engine/            # Engine kód
├── SDL/                   # SDL3 forrás
└── build/                 # Build könyvtár (git ignore-olt)
```

## Miért Hordozható?

- ✅ A CMake **relatív útvonalakat** használ (`CMAKE_BINARY_DIR`, `CMAKE_SOURCE_DIR`)
- ✅ A build könyvtár **nem verziókezelt** (.gitignore-ban van)
- ✅ A **configure.bat mindig törli** a régi cache-t
- ✅ **Bármilyen könyvtárnévvel** működik
- ✅ **Bármilyen gépen** működik (ahol van CMake + MinGW)

## Új Játék Létrehozása

1. Másold le a projektet új néven:
   ```
   cd C:\Users\markr\Desktop
   xcopy /E /I potato_engine\potato_engine my_awesome_game
   ```

2. Lépj be az új projektbe:
   ```
   cd my_awesome_game
   ```

3. Frissítsd a `CMakeLists.txt`-ben a projekt nevet:
   ```cmake
   project(my_awesome_game VERSION 0.0.1)
   ```

4. Futtasd a configure-t:
   ```
   configure.bat
   ```

5. Build-elj:
   ```
   build.bat
   ```

Kész! Az új játékod teljesen független a régi projekttől!

## Hibaelhárítás

### "CMake not found"
- Telepítsd a CMake-t és add hozzá a PATH-hoz

### "mingw32-make not found"
- Telepítsd a MinGW-t (MSYS2 ajánlott) és add hozzá a PATH-hoz

### Build hibák
- Futtasd újra a `configure.bat`-ot
- Ellenőrizd, hogy az SDL forrás megvan-e az `SDL/` könyvtárban
