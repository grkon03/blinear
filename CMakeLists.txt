# cmake version
cmake_minimum_required(VERSION 3.21)

# project
project(blinear CXX)

# C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TARGET_source_file
./src/main.cpp
./src/header/cube.cpp
./src/header/ball.cpp
./src/header/util/error.cpp
./src/header/util/util.cpp
)

# executable
add_executable(blinear ${TARGET_source_file})