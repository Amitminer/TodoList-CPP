#!/bin/bash

set -e

# Check if the build directory exists and clean it if it does
if [ -d "build" ]; then
    echo "Cleaning existing build directory..."
    rm -rf build
fi

# Create build directory and install dependencies using Conan
echo "Creating build directory and installing dependencies..."
conan install . --output-folder=build --build=missing

# Run CMake configuration
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$(pwd)/build/conan_toolchain.cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
if [ $? -ne 0 ]; then
    echo "CMake configuration failed."
    exit 1
fi

# Build the project using CMake
cmake --build build
if [ $? -ne 0 ]; then
    echo "Build failed."
    exit 1
fi

# Check for the executable in both the build and root directories
if [ -f "./todolist" ]; then
    EXECUTABLE="./todolist"
elif [ -f "build/todolist" ]; then
    EXECUTABLE="build/todolist"
else
    echo "Executable not found."
    exit 1
fi

# Move the built executable to the root directory
if [ "$EXECUTABLE" != "./todolist" ]; then
    echo "Moving $EXECUTABLE to the root directory..."
    mv "$EXECUTABLE" .
fi

echo "Build and move completed successfully."
