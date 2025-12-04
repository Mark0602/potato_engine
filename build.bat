@echo off
REM Script to build the potato engine

echo Building potato_engine...

REM Check if build directory exists
if not exist build (
    echo Build directory not found! Run configure.bat first.
    pause
    exit /b 1
)

REM Check if CMakeCache.txt exists
if not exist build\CMakeCache.txt (
    echo CMake cache not found! Run configure.bat first.
    pause
    exit /b 1
)

REM Build the project
cd build
mingw32-make

if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    cd ..
    pause
    exit /b 1
)

cd ..
echo.
echo Build successful! Executable location:
dir /B build\*.exe 2>nul | findstr /V /I "cmake"
echo.
pause
