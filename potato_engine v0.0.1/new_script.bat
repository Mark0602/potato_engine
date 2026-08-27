@echo off
setlocal
pushd "%~dp0"

set /p NAME="Script name (for example camera): "
if "%NAME%"=="" (
  echo ERROR: No name provided.
  popd
  exit /b 1
)

set /p SCENE_ID="Scene ID (-1 means global): "
if "%SCENE_ID%"=="" set "SCENE_ID=-1"

set "FILE=scripts\%NAME%.cpp"
if exist "%FILE%" (
  echo ERROR: %FILE% already exists.
  popd
  exit /b 1
)

(
echo #include "engine.h"
echo #include "src/script-registry.h"
echo.
echo class %NAME%_script final : public script {
echo     SCRIPT_ORDER^(0^)
echo     SCRIPT_SCENE^(%SCENE_ID%^)
echo.
echo public:
echo.
echo     // Runs on game start, incase of an attached_script, it runs when the object initates.
echo     void on_start^(^) override {
echo.
echo     }
echo.
echo     // Runs every frame - guess what...
echo     void on_update^(float delta_time^) override { 
echo.
echo     }
echo.
echo     // Runs every fram on the global render call, but you likely won't use it much, as auto_submit handles it already
echo     void on_render^(^) override {}
echo     // Runs when an SDL_Event occurs, but you likely won't use it much, as every important event can be accessed throught the update with states like Input::
echo     void on_event^(const SDL_Event^& event^) override {}
echo.
echo     // Runs when the script is destroyed, for example the game closed, or the object got deleted.
echo     void on_destroy^(^) override {
echo.
echo     }
echo };
echo.
echo REGISTER_SCRIPT^(%NAME%_script^)
) > "%FILE%"

echo Created: %FILE%
echo CMake will detect it on the next build.
popd
endlocal
