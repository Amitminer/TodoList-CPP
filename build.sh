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

# Change to the build directory
cd build

# Run CMake configuration
cmake .. -DCMAKE_TOOLCHAIN_FILE=$(pwd)/conan_toolchain.cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
if [ $? -ne 0 ]; then
    echo "CMake configuration failed."
    exit 1
fi

# Build the project using CMake
cmake --build .
if [ $? -ne 0 ]; then
    echo "Build failed."
    exit 1
fi

# Move the built executable to the root directory
echo "Moving todolist to the root directory..."
cp todolist ..

echo "Build and move completed successfully."
