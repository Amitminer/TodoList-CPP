cmake_minimum_required(VERSION 3.15)

project(todolist VERSION 1.7.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SQLiteCpp CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Task.cpp
    src/TaskManager.cpp
    src/Database.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SQLiteCpp
    fmt::fmt
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)