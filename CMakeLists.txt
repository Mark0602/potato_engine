cmake_minimum_required(VERSION 3.16)

# =============================================================================
# PROJECT CONFIGURATION
# =============================================================================
# FONTOS: Ha új játékot hozol létre, változtasd meg a projekt nevet itt!
# Például: project(my_awesome_game VERSION 1.0.0)
project(potato_engine VERSION 0.0.1)

# =============================================================================
# BUILD DIRECTORIES
# =============================================================================
# Ezek a változók relatív útvonalakat használnak, így a projekt hordozható
# CMAKE_BINARY_DIR: a build könyvtár (ahol a CMake fut)
# CMAKE_SOURCE_DIR: a projekt gyökérkönyvtára (ahol ez a CMakeLists.txt van)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# =============================================================================
# SDL3 DEPENDENCY
# =============================================================================
# Az SDL3 forráskódja a projekt SDL/ könyvtárában található
# EXCLUDE_FROM_ALL: nem installáljuk az SDL-t, csak használjuk
add_subdirectory(SDL EXCLUDE_FROM_ALL)

# Find SDL3_image - próbáljunk különböző módokat
find_package(SDL3_image QUIET)

if(NOT SDL3_image_FOUND)
    # Próbáljuk meg pkg-config-kal
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(SDL3_image QUIET SDL3_image)
    endif()
endif()

# Ha még mindig nem találtuk meg, próbáljuk meg manuálisan
if(NOT SDL3_image_FOUND)
    # First prefer a bundled copy inside the project's SDL directory (if user placed it there)
    set(_PROJECT_SDL3_IMAGE_ROOT "${CMAKE_SOURCE_DIR}/SDL/SDL3_image-3.2.4/x86_64-w64-mingw32")

    find_path(SDL3_IMAGE_INCLUDE_DIR SDL3_image/SDL_image.h PATHS
        ${_PROJECT_SDL3_IMAGE_ROOT}/include
        C:/msys64/ucrt64/include
        /usr/include
        /usr/local/include
    )

    # Try common library filenames/locations (static import libs on MinGW use libSDL3_image.dll.a)
    find_library(SDL3_IMAGE_LIBRARY NAMES SDL3_image SDL3_image-3 libSDL3_image libSDL3_image.dll.a PATHS
        ${_PROJECT_SDL3_IMAGE_ROOT}/lib
        C:/msys64/ucrt64/lib
        /usr/lib
        /usr/local/lib
    )

    if(SDL3_IMAGE_INCLUDE_DIR AND SDL3_IMAGE_LIBRARY)
        message(STATUS "Found SDL3_image manually at include=${SDL3_IMAGE_INCLUDE_DIR} lib=${SDL3_IMAGE_LIBRARY}")
        set(SDL3_image_FOUND TRUE)
    endif()
endif()

if(SDL3_image_FOUND)
    message(STATUS "SDL3_image found - image loading will be enabled")
else()
    message(STATUS "WARNING: SDL3_image not found - image loading will be disabled")
    message(STATUS "To enable image loading, install SDL3_image:")
    message(STATUS "  Windows/MSYS2: pacman -S mingw-w64-ucrt-x86_64-SDL3_image")
    message(STATUS "  Linux: sudo apt install libsdl3-image-dev")
    message(STATUS "  macOS: brew install sdl3-image")
endif()

# =============================================================================
# SOURCE FILES
# =============================================================================
# Automatikusan gyűjtjük össze az összes .cpp fájlt
# Engine kód: src/engine/ és alkönyvtáraiban
file(GLOB_RECURSE ENGINE_SOURCES "src/engine/*.cpp")
# Játék-specifikus kód: src/ könyvtárban (közvetlenül)
file(GLOB SCRIPT_SOURCES "src/*.cpp")

# =============================================================================
# EXECUTABLE TARGET
# =============================================================================
# FONTOS: A target nevének meg kell egyeznie a project() névvel (fentebb)
add_executable(${PROJECT_NAME} 
    ${ENGINE_SOURCES}
    ${SCRIPT_SOURCES}
)

# =============================================================================
# INCLUDE DIRECTORIES
# =============================================================================
# A src/ könyvtár elérhető #include direktívákban
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Add SDL3_image include directories
if(SDL3_image_FOUND)
    if(SDL3_image_INCLUDE_DIRS)
        target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_image_INCLUDE_DIRS})
    elseif(SDL3_IMAGE_INCLUDE_DIR)
        target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_IMAGE_INCLUDE_DIR})
    endif()
endif()

# =============================================================================
# LINKING
# =============================================================================
# Link SDL3 könyvtárral
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

# Link SDL3_image if found
if(SDL3_image_FOUND)
    if(SDL3_image_LIBRARIES)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_image_LIBRARIES})
    elseif(SDL3_IMAGE_LIBRARY)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_IMAGE_LIBRARY})
    elseif(TARGET SDL3_image::SDL3_image)
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_image::SDL3_image)
    endif()
endif()
