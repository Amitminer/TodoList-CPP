@echo off
setlocal enabledelayedexpansion

REM Clean the build directory if it exists
if exist build (
    echo Cleaning existing build directory...
    rd /s /q build
    if errorlevel 1 (
        echo Failed to clean build directory.
        goto :error
    )
)

REM Create build directory and install dependencies using Conan
echo Creating build directory and installing dependencies...
conan install . --output-folder=build --build=missing
if %errorlevel% neq 0 (
    echo Conan install failed.
    goto :error
)

REM Define the generator variable
REM Visual Studio 17 2022 or MinGW Makefiles
set "generator=MinGW Makefiles"

REM Run CMake configuration
echo Running CMake configuration...
cd build

REM choose desired generators
cmake .. -DCMAKE_TOOLCHAIN_FILE="%cd%\conan_toolchain.cmake" -G "%generator%" -DCMAKE_BUILD_TYPE=Release
if %errorlevel% neq 0 (
    echo CMake configuration failed.
    cd ..
    goto :error
)
cd ..

REM Build the project using CMake
echo Building the project...
cmake --build build --config Release
if %errorlevel% neq 0 (
    echo Build failed.
    goto :error
)

echo Checking for todolist.exe ...
if exist build\Release\todolist.exe (
    echo Moving todolist.exe to the root directory...
    copy build\Release\todolist.exe .
    if errorlevel 1 (
        echo Failed to move todolist.exe.
       goto :error
    )
) else (
    echo todolist.exe not found in build directory.
    goto :error
)

echo Script completed successfully
goto :end

:error
echo An error occurred during script execution
:end
endlocal
