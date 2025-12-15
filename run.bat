@echo off
cd /d "%~dp0"
echo === Potato Engine Build System ===
echo.

if not exist "build\CMakeCache.txt" (
    echo Configuring CMake...
    cmake -G "MinGW Makefiles" -S . -B build
    if errorlevel 1 goto error
) else (
    echo Reconfiguring CMake...
    cmake -S . -B build
    if errorlevel 1 goto error
)

echo Building project...
cmake --build build
if errorlevel 1 goto error

echo.
echo === Build successful! ===

REM ======================================================
REM ============= HLSL -> SPIR-V SHADER COMPILE ==========
REM ======================================================

echo.
echo === Compiling shaders (HLSL -> SPIR-V) ===

REM forras:   assets\shaders\*.hlsl
REM kimenet:  build\assets\shaders\*.spv

set "SHADER_SRC_DIR=%cd%\assets\shaders"
set "SHADER_OUT_DIR=%cd%\build\assets\shaders"

if not exist "%SHADER_SRC_DIR%" (
    echo [WARN] Shader source dir not found: %SHADER_SRC_DIR%
    echo        Skipping shader compilation.
    goto launch
)

if not exist "%SHADER_OUT_DIR%" (
    mkdir "%SHADER_OUT_DIR%"
)

REM ha dxc.exe a PATH-ban van, ez megtalálja
REM ha nincs, tedd a dxc.exe-t a run.bat melletti mappába ÉS add hozzá a PATH-hoz,
REM vagy írd át lentebb a teljes elérési útra (pl. C:\VulkanSDK\...\dxc.exe)

where dxc >nul 2>nul
if errorlevel 1 (
    echo [WARN] dxc.exe not found in PATH.
    echo        Skipping shader compilation.
    goto launch
)

echo Compiling default_color_vs.hlsl ...
dxc "%SHADER_SRC_DIR%\default_color_vs.hlsl" -T vs_6_0 -E main -spirv -Fo "%SHADER_OUT_DIR%\default_color_vs.spv"
if errorlevel 1 (
    echo [ERROR] Vertex shader compile failed.
    goto error
)

echo Compiling default_color_ps.hlsl ...
dxc "%SHADER_SRC_DIR%\default_color_ps.hlsl" -T ps_6_0 -E main -spirv -Fo "%SHADER_OUT_DIR%\default_color_ps.spv"
if errorlevel 1 (
    echo [ERROR] Pixel shader compile failed.
    goto error
)

echo Shaders compiled to: %SHADER_OUT_DIR%
echo.

:launch
echo === Launching Potato Engine... ===
echo.
build\potato_engine.exe
goto end

:error
echo.
echo === Build failed! ===
pause
goto end

:end