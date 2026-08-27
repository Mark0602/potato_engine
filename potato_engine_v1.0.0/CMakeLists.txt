cmake_minimum_required(VERSION 3.24)
project(potato_engine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(POTATO_BUILD_SANDBOX "Build the minimal Potato Engine sandbox" ON)

set(SDL_ARCH "x86_64-w64-mingw32")
set(SDL_PACKAGES
    SDL3-3.4.8
    SDL3_image-3.4.4
    SDL3_ttf-3.1.0
    SDL3_mixer-3.2.4
)

set(SDL_IMPORT_LIBRARIES
    "${CMAKE_SOURCE_DIR}/src/include/SDL3-3.4.8/${SDL_ARCH}/lib/libSDL3.dll.a"
    "${CMAKE_SOURCE_DIR}/src/include/SDL3_image-3.4.4/${SDL_ARCH}/lib/libSDL3_image.dll.a"
    "${CMAKE_SOURCE_DIR}/src/include/SDL3_ttf-3.1.0/${SDL_ARCH}/lib/libSDL3_ttf.dll.a"
    "${CMAKE_SOURCE_DIR}/src/include/SDL3_mixer-3.2.4/${SDL_ARCH}/lib/libSDL3_mixer.dll.a"
)

set(SDL_RUNTIME_DLLS
    "${CMAKE_SOURCE_DIR}/src/include/SDL3-3.4.8/${SDL_ARCH}/bin/SDL3.dll"
    "${CMAKE_SOURCE_DIR}/src/bin/SDL3_image.dll"
    "${CMAKE_SOURCE_DIR}/src/include/SDL3_ttf-3.1.0/${SDL_ARCH}/bin/SDL3_ttf.dll"
    "${CMAKE_SOURCE_DIR}/src/include/SDL3_mixer-3.2.4/${SDL_ARCH}/bin/SDL3_mixer.dll"
)

function(potato_add_sdl_includes target visibility)
    foreach(SDL_PACKAGE IN LISTS SDL_PACKAGES)
        target_include_directories(${target} ${visibility}
            "${CMAKE_SOURCE_DIR}/src/include/${SDL_PACKAGE}/${SDL_ARCH}/include"
        )
    endforeach()
endfunction()

# FlatBuffers is used only by the generic object snapshot helper.
set(FLATBUFFERS_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(FLATBUFFERS_BUILD_FLATLIB OFF CACHE BOOL "" FORCE)
set(FLATBUFFERS_BUILD_FLATC ON CACHE BOOL "" FORCE)
set(FLATBUFFERS_INSTALL OFF CACHE BOOL "" FORCE)
set(FLATBUFFERS_BUILD_SHAREDLIB OFF CACHE BOOL "" FORCE)
set(FLATBUFFERS_BUILD_FLATHASH OFF CACHE BOOL "" FORCE)
set(FLATBUFFERS_BUILD_BENCHMARKS OFF CACHE BOOL "" FORCE)
set(FLATBUFFERS_BUILD_GRPCTEST OFF CACHE BOOL "" FORCE)
add_subdirectory(flatbuffers EXCLUDE_FROM_ALL)

set(GENERATED_DIR "${CMAKE_BINARY_DIR}/generated")
set(SAVE_SCHEMA "${CMAKE_SOURCE_DIR}/saves/templates/save_game.fbs")
set(SAVE_GENERATED_HEADER "${GENERATED_DIR}/save_game_generated.h")

add_custom_command(
    OUTPUT "${SAVE_GENERATED_HEADER}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${GENERATED_DIR}"
    COMMAND flatc --cpp --gen-object-api --scoped-enums
            -o "${GENERATED_DIR}" "${SAVE_SCHEMA}"
    DEPENDS flatc "${SAVE_SCHEMA}"
    COMMENT "Generating Potato Engine save schema"
    VERBATIM
)
add_custom_target(generate_potato_schema DEPENDS "${SAVE_GENERATED_HEADER}")

# One simdjson implementation is shared by localization and mod manifests.
add_library(potato_json STATIC "${CMAKE_SOURCE_DIR}/src/simdjson.cpp")
add_library(Potato::Json ALIAS potato_json)
target_include_directories(potato_json PUBLIC "${CMAKE_SOURCE_DIR}/src")

# The reviewed AngelScript VM ships with the engine and links statically.
file(GLOB ANGELSCRIPT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/third_party/angelscript/source/*.cpp"
)
add_library(potato_angelscript STATIC
    ${ANGELSCRIPT_SOURCES}
    "${CMAKE_SOURCE_DIR}/third_party/angelscript/add_on/scriptbuilder/scriptbuilder.cpp"
    "${CMAKE_SOURCE_DIR}/third_party/angelscript/add_on/scriptstdstring/scriptstdstring.cpp"
)
add_library(Potato::AngelScript ALIAS potato_angelscript)
target_include_directories(potato_angelscript PUBLIC
    "${CMAKE_SOURCE_DIR}/third_party/angelscript/include"
    "${CMAKE_SOURCE_DIR}/third_party/angelscript/add_on"
)

file(GLOB MODDING_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/modding/*.cpp"
)
add_library(potato_modding STATIC ${MODDING_SOURCES})
add_library(Potato::Modding ALIAS potato_modding)
target_include_directories(potato_modding PUBLIC "${CMAKE_SOURCE_DIR}/src")
target_link_libraries(potato_modding PUBLIC Potato::AngelScript Potato::Json)

add_library(potato_functionality_trigger STATIC
    "${CMAKE_SOURCE_DIR}/src/functionality_trigger.cpp"
)
add_library(Potato::FunctionalityTrigger ALIAS potato_functionality_trigger)
target_include_directories(potato_functionality_trigger PUBLIC
    "${CMAKE_SOURCE_DIR}/src"
)

set(POTATO_ENGINE_SOURCES
    "${CMAKE_SOURCE_DIR}/engine.cpp"
    "${CMAKE_SOURCE_DIR}/src/animations.cpp"
    "${CMAKE_SOURCE_DIR}/src/asset_pool.cpp"
    "${CMAKE_SOURCE_DIR}/src/audio.cpp"
    "${CMAKE_SOURCE_DIR}/src/camera.cpp"
    "${CMAKE_SOURCE_DIR}/src/debug.cpp"
    "${CMAKE_SOURCE_DIR}/src/entity.cpp"
    "${CMAKE_SOURCE_DIR}/src/fonts.cpp"
    "${CMAKE_SOURCE_DIR}/src/game_console.cpp"
    "${CMAKE_SOURCE_DIR}/src/input.cpp"
    "${CMAKE_SOURCE_DIR}/src/label.cpp"
    "${CMAKE_SOURCE_DIR}/src/light.cpp"
    "${CMAKE_SOURCE_DIR}/src/loading_screen.cpp"
    "${CMAKE_SOURCE_DIR}/src/localization.cpp"
    "${CMAKE_SOURCE_DIR}/src/object.cpp"
    "${CMAKE_SOURCE_DIR}/src/particle.cpp"
    "${CMAKE_SOURCE_DIR}/src/physics.cpp"
    "${CMAKE_SOURCE_DIR}/src/render.cpp"
    "${CMAKE_SOURCE_DIR}/src/save_game.cpp"
    "${CMAKE_SOURCE_DIR}/src/texture.cpp"
    "${CMAKE_SOURCE_DIR}/src/tileset.cpp"
    "${SAVE_GENERATED_HEADER}"
)

add_library(potato_engine STATIC ${POTATO_ENGINE_SOURCES})
add_library(Potato::Engine ALIAS potato_engine)
add_dependencies(potato_engine generate_potato_schema)
target_include_directories(potato_engine PUBLIC
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/src"
    "${GENERATED_DIR}"
)
potato_add_sdl_includes(potato_engine PUBLIC)
target_link_libraries(potato_engine PUBLIC
    FlatBuffers::FlatBuffers
    Potato::Json
    ${SDL_IMPORT_LIBRARIES}
)

if(POTATO_BUILD_SANDBOX)
    file(GLOB SANDBOX_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/examples/*.cpp"
    )
    add_executable(potato_sandbox WIN32
        "${CMAKE_SOURCE_DIR}/main.cpp"
        ${SANDBOX_SOURCES}
    )
    set_target_properties(potato_sandbox PROPERTIES OUTPUT_NAME "potato")
    target_link_libraries(potato_sandbox PRIVATE Potato::Engine)
    add_custom_command(TARGET potato_sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SDL_RUNTIME_DLLS}
            $<TARGET_FILE_DIR:potato_sandbox>
        COMMENT "Copying SDL runtime libraries"
    )
endif()

include(CTest)
if(BUILD_TESTING)
    add_executable(potato_modding_tests
        "${CMAKE_SOURCE_DIR}/tests/potato_modding_tests.cpp"
    )
    target_link_libraries(potato_modding_tests PRIVATE Potato::Modding)
    add_test(NAME potato_modding_core COMMAND potato_modding_tests)
    set_tests_properties(potato_modding_core PROPERTIES
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )

    add_executable(functionality_trigger_tests
        "${CMAKE_SOURCE_DIR}/tests/functionality_trigger_tests.cpp"
    )
    target_link_libraries(functionality_trigger_tests PRIVATE
        Potato::FunctionalityTrigger
    )
    add_test(NAME functionality_trigger_core COMMAND functionality_trigger_tests)

    add_executable(engine_helpers_tests
        "${CMAKE_SOURCE_DIR}/tests/engine_helpers_tests.cpp"
    )
    target_link_libraries(engine_helpers_tests PRIVATE Potato::Engine)
    add_test(NAME potato_engine_helpers COMMAND engine_helpers_tests)
endif()
