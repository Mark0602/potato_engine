@echo off
cd /d %~dp0
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
echo Launching Potato Engine...
echo.
build\potato_engine.exe
goto end

:error
echo.
echo === Build failed! ===
pause
goto end

:end
