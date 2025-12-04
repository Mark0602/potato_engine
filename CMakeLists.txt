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

# =============================================================================
# LINKING
# =============================================================================
# Link SDL3 könyvtárral
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)