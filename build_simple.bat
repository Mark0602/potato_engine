@echo off
echo Building potato_engine...
cd /d C:\Users\markr\Desktop\potato_engine\potato_engine
echo.
echo Cleaning old build...
if exist build\CMakeCache.txt del /Q build\CMakeCache.txt
if exist build\CMakeFiles rmdir /S /Q build\CMakeFiles

echo.
echo Running CMake...
cd build
cmake .. -G "MinGW Makefiles"

if %ERRORLEVEL% NEQ 0 (
    echo CMake failed!
    pause
    exit /b 1
)

echo.
echo Running make...
mingw32-make

if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo Build successful!
echo Output: build\potato_engine.exe
pause
