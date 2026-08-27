@echo off
setlocal
pushd "%~dp0"

call "%~dp0build.bat"
if errorlevel 1 (
  echo ERROR: Potato Engine build failed.
  popd
  exit /b 1
)

if not exist "%~dp0build\potato.exe" (
  echo ERROR: build\potato.exe was not created.
  popd
  exit /b 1
)

"%~dp0build\potato.exe" %*
set "POTATO_EXIT_CODE=%ERRORLEVEL%"
popd
endlocal & exit /b %POTATO_EXIT_CODE%
