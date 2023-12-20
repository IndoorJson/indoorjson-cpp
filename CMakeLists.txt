# CMakeLists.txt
# Copyright (c) 2023 IndoorJson
# Author: Kunlin Yu <yukunlin@syriusrobotics.com>
# Create Date: 2023/12/20

cmake_minimum_required(VERSION 3.12)
project(indoorjson-cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(main src/main.cpp)

