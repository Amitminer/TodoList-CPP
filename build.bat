@echo off
setlocal enabledelayedexpansion

REM Install vcpkg if not already installed
if not exist vcpkg (
    echo Installing vcpkg...
    git clone https://github.com/microsoft/vcpkg.git
    cd vcpkg
    ./bootstrap-vcpkg.bat
    if errorlevel 1 (
        echo Failed to install vcpkg.
        cd ..
        goto :error
    )
    cd ..
)

REM Install SQLiteCpp using vcpkg
echo Installing SQLiteCpp...
vcpkg\vcpkg.exe integrate install
vcpkg\vcpkg.exe install sqlitecpp
if errorlevel 1 (
    echo Failed to install SQLiteCpp.
    goto :error
)

REM Clean the build directory if it exists
if exist build (
    echo Cleaning existing build directory...
    rd /s /q build
    if errorlevel 1 (
        echo Failed to clean build directory.
        goto :error
    )
)

REM Create build directory
mkdir build
cd build

REM Define the generator variable
set "generator=Visual Studio 17 2022"

REM Run CMake configuration
echo Running CMake configuration...
cmake .. -G "%generator%" -DCMAKE_BUILD_TYPE=Release
if errorlevel 1 (
    echo CMake configuration failed.
    cd ..
    goto :error
)
cd ..

REM Build the project using CMake
echo Building the project...
cmake --build build --config Release
if errorlevel 1 (
    echo Build failed.
    goto :error
)

echo Checking for build\Release\todolist.exe...
if exist build\Release\todolist.exe (
    echo Moving todolist.exe to the root directory...
    copy build\Release\todolist.exe . 
    if errorlevel 1 (
        echo Failed to move todolist.exe.
        goto :error
    )
) else (
    echo todolist.exe not found in build\Release directory.
    goto :error
)

echo Script completed successfully
goto :end

:error
echo An error occurred during script execution
exit /b 1

:end
endlocal
