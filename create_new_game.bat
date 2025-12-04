@echo off
REM Script to create a new game project from the potato_engine template

echo ============================================
echo Potato Engine - New Game Project Creator
echo ============================================
echo.

REM Check if a project name was provided
if "%~1"=="" (
    echo Usage: create_new_game.bat [project_name]
    echo.
    echo Example: create_new_game.bat my_awesome_game
    echo.
    pause
    exit /b 1
)

set PROJECT_NAME=%~1
set CURRENT_DIR=%CD%
set TARGET_DIR=%CURRENT_DIR%\..\%PROJECT_NAME%

echo Project name: %PROJECT_NAME%
echo Target directory: %TARGET_DIR%
echo.

REM Check if target directory already exists
if exist "%TARGET_DIR%" (
    echo ERROR: Directory "%TARGET_DIR%" already exists!
    echo Please choose a different name or delete the existing directory.
    echo.
    pause
    exit /b 1
)

echo Creating new project...
echo.

REM Copy the entire project
xcopy /E /I /Q "%CURRENT_DIR%" "%TARGET_DIR%"

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to copy project files!
    pause
    exit /b 1
)

REM Delete the build directory in the new project
if exist "%TARGET_DIR%\build" (
    echo Cleaning build directory...
    rmdir /S /Q "%TARGET_DIR%\build"
)

REM Update CMakeLists.txt with the new project name
echo Updating CMakeLists.txt...
powershell -Command "(Get-Content '%TARGET_DIR%\CMakeLists.txt') -replace 'project\(potato_engine VERSION', 'project(%PROJECT_NAME% VERSION' | Set-Content '%TARGET_DIR%\CMakeLists.txt'"

if %ERRORLEVEL% NEQ 0 (
    echo WARNING: Failed to update CMakeLists.txt automatically.
    echo Please manually change the project name in CMakeLists.txt
)

echo.
echo ============================================
echo Project created successfully!
echo ============================================
echo.
echo Location: %TARGET_DIR%
echo.
echo Next steps:
echo 1. cd ..\%PROJECT_NAME%
echo 2. configure.bat
echo 3. build.bat
echo.
echo Happy coding!
echo.
pause
