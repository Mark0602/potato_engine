@echo off
setlocal
pushd "%~dp0"

where dxc >nul 2>nul
if errorlevel 1 (
  echo ERROR: dxc.exe is not available on PATH.
  echo Install the DirectX Shader Compiler, then run this file again.
  popd
  exit /b 1
)

dxc -E main -T ps_6_0 -O3 -Fo day_night_light.frag.dxil day_night_light.frag.hlsl
if errorlevel 1 goto :failed

dxc -spirv -fspv-target-env=vulkan1.1 -fvk-use-dx-layout -E main -T ps_6_0 -O3 -Fo day_night_light.frag.spv day_night_light.frag.hlsl
if errorlevel 1 goto :failed

echo Shader build succeeded.
popd
endlocal
exit /b 0

:failed
echo Shader build failed.
popd
endlocal
exit /b 1
