cmake_minimum_required(VERSION 3.20)

project(parquet_inspector)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Arrow REQUIRED)
find_package(Parquet REQUIRED)

add_executable(parquet_inspector src/main.cpp src/parser.cpp)

target_include_directories(parquet_inspector PRIVATE include)
target_link_libraries(
    parquet_inspector
    PRIVATE
    Parquet::parquet_shared
    Arrow::arrow_shared
)
