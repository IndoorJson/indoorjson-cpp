# CMakeLists.txt
# Copyright (c) 2023 IndoorJson
# Author: Kunlin Yu <yukunlin@syriusrobotics.com>
# Create Date: 2023/12/20

cmake_minimum_required(VERSION 3.12)
project(indoorjson-cpp)

### standard

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


### include

include_directories(${CMAKE_SOURCE_DIR}/include)


### dependencies

# nlohmann/json
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(dependencies/nlohmann_json)


### executable

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)
