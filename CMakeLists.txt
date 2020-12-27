# cmake -B bin
# cmake --build bin
cmake_minimum_required(VERSION 3.19)
project(maze)

# use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# compiler warnings
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# executable and include dir
add_executable(main
    src/main.cpp
    src/maze/maze.cpp
)
target_include_directories(main PRIVATE include/)
