cmake_minimum_required(VERSION 3.10...3.20)

project(todolist VERSION 1.7.6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# List of required packages
set(Packages
    SQLiteCpp
    fmt
)

# Find and include required packages
foreach(PACKAGE IN LISTS Packages)
    find_package(${PACKAGE} CONFIG REQUIRED)
endforeach()

# List of libraries to link with the executable
set(Libraries
    SQLiteCpp
    fmt::fmt
)

# List of source files
file(GLOB Sources src/*)

# Define the executable target
add_executable(${PROJECT_NAME} ${Sources})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
# Link libraries to the executable target
target_link_libraries(${PROJECT_NAME} PRIVATE ${Libraries})

# Set the output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)
