cmake_minimum_required(VERSION 3.15)

project(todolist_benchmark VERSION 1.7.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SQLiteCpp CONFIG REQUIRED)
find_package(benchmark REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_executable(todolist_benchmark
    Benchmark.cpp
    ../src/Task.cpp
    ../src/TaskManager.cpp
    ../src/Database.cpp
)

target_link_libraries(todolist_benchmark PRIVATE
    SQLiteCpp
    fmt::fmt
    benchmark::benchmark_main
)

target_include_directories(todolist_benchmark PUBLIC
    ../include
)
