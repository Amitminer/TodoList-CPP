@echo off
setlocal enabledelayedexpansion

REM Function to display usage instructions
:usage
echo Usage: build.bat --vcpkg^|--conan
exit /b 1

REM Check if an argument is passed for the package manager
if "%1"=="" goto :usage
set "PACKAGE_MANAGER=%1"

REM Determine which package manager to use based on the argument
if /I "%PACKAGE_MANAGER%"=="--vcpkg" (
    where vcpkg >nul 2>nul
    if %errorlevel% neq 0 (
        echo vcpkg not found in PATH. Exiting...
        exit /b 1
    )
    set "USE_VCPKG=1"
    set "USE_CONAN=0"
) else if /I "%PACKAGE_MANAGER%"=="--conan" (
    where conan >nul 2>nul
    if %errorlevel% neq 0 (
        echo Conan not found in PATH. Exiting...
        exit /b 1
    )
    set "USE_CONAN=1"
    set "USE_VCPKG=0"
) else (
    echo Invalid package manager specified. Use "--vcpkg" or "--conan".
    exit /b 1
)

REM Create and navigate to the build directory
if exist build (
    rd /s /q build
)
mkdir build
cd build

REM Install dependencies using the specified package manager
if %USE_VCPKG%==1 (
    echo Installing dependencies with vcpkg...
    vcpkg install
    if %errorlevel% neq 0 (
        echo Failed to install dependencies with vcpkg. Exiting...
        exit /b 1
    )
) else (
    echo Installing dependencies with conan...
    conan install .. --install-folder=build --build=missing
    if %errorlevel% neq 0 (
        echo Failed to install dependencies with conan. Exiting...
        exit /b 1
    )
)

REM Configure the build system
if %USE_VCPKG%==1 (
    echo Configuring the build system with Visual Studio generator...
    cmake -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE="P:\AppData\Roaming\ProgrammingTools\vcpkg\scripts\buildsystems\vcpkg.cmake" ..
) else (
    echo Configuring the build system with MinGW Makefiles generator...
    REM Replace <path_to_conan_toolchain> with the actual path to your Conan toolchain file if you have one
    cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE="%cd%\conan_toolchain.cmake" ..
)
if %errorlevel% neq 0 (
    echo Failed to configure the build system. Exiting...
    exit /b 1
)

REM Build the project
echo Building the project...
cmake --build .
if %errorlevel% neq 0 (
    echo Build failed. Exiting...
    exit /b 1
)

REM Move entire Debug folder to another location
set "DESTINATION_FOLDER=P:\Programming\CPP\TodoList-CPP\Debug"
if not exist "%DESTINATION_FOLDER%" (
    mkdir "%DESTINATION_FOLDER%"
)
move /y Debug "%DESTINATION_FOLDER%" > nul

REM Check if move was successful
if %errorlevel% neq 0 (
    echo Failed to move Debug folder. Exiting...
    exit /b 1
)

echo Build successful.
endlocal
exit /b 0
