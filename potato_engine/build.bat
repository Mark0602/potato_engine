@echo off
setlocal
pushd "%~dp0"

where cmake >nul 2>nul
if errorlevel 1 (
  echo ERROR: CMake is not available on PATH.
  popd
  exit /b 1
)

where g++ >nul 2>nul
if errorlevel 1 (
  echo ERROR: The MinGW g++ compiler is not available on PATH.
  popd
  exit /b 1
)

echo Configuring project...
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++
if errorlevel 1 (
  echo Existing CMake cache is invalid, retrying with a fresh cache...
  cmake -S . -B build --fresh -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++
  if errorlevel 1 (
    echo CMake configuration failed.
    popd
    exit /b 1
  )
)

echo Building...
cmake --build build --parallel
if errorlevel 1 (
  echo Build failed.
  popd
  exit /b 1
)

echo Build succeeded.
popd
endlocal
exit /b 0
