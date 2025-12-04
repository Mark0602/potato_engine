@echo off
REM Script to configure and build the potato engine
REM This ensures the CMake cache is always regenerated with correct paths

echo Configuring potato_engine...

REM Delete old CMake cache to ensure clean configuration
if exist build\CMakeCache.txt (
    echo Cleaning old CMake cache...
    del /Q build\CMakeCache.txt
    rmdir /S /Q build\CMakeFiles 2>nul
)

REM Create build directory if it doesn't exist
if not exist build mkdir build

REM Configure with CMake
echo Running CMake configuration...
cmake -G "MinGW Makefiles" -B build -S .

if %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

echo.
echo Configuration successful!
echo To build the project, run: build.bat
echo.
pause
