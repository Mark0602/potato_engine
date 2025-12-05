# SDL_image Telepítési Útmutató

## Windows (MSYS2) - Ajánlott

1. Nyisd meg az MSYS2 UCRT64 terminált

2. Telepítsd az SDL3_image-t:
```bash
pacman -S mingw-w64-ucrt-x86_64-SDL3_image
```

3. Ha még nincs telepítve az SDL3:
```bash
pacman -S mingw-w64-ucrt-x86_64-SDL3
```

4. Futtasd újra a configure scriptet:
```cmd
configure.bat
```

5. Build-eld a projektet:
```cmd
build.bat
```

## Ellenőrzés

Ellenőrizd, hogy az SDL_image telepítve van:
```bash
# MSYS2 terminálban:
pacman -Qs SDL3_image
```

## Hibaelhárítás

### "SDL3_image not found"

Ha a CMake nem találja az SDL3_image-t:

1. Győződj meg róla, hogy az MSYS2 bin könyvtára a PATH-ban van:
   ```
   C:\msys64\ucrt64\bin
   ```

2. Próbáld meg manuálisan megkeresni:
   ```bash
   # MSYS2 terminálban:
   pkg-config --modversion SDL3_image
   ```

3. Ha továbbra sem működik, telepítsd újra:
   ```bash
   pacman -S --reinstall mingw-w64-ucrt-x86_64-SDL3_image
   ```

## Alternatíva: SDL_image letöltése manuálisan

Ha nem használsz MSYS2-t:

1. Töltsd le az SDL3_image-t: https://github.com/libsdl-org/SDL_image
2. Build-eld CMake-kel
3. Másold a library fájlokat a projekt könyvtárába
4. Frissítsd a CMakeLists.txt-t az egyedi útvonalakkal

## Támogatott Képformátumok

Az SDL_image támogatja:
- PNG
- JPEG
- BMP
- GIF
- TGA
- és még sok mást...
