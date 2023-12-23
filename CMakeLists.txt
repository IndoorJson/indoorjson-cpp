# CMakeLists.txt
# Copyright (c) 2023 IndoorJson
# Author: Kunlin Yu <yukunlin@syriusrobotics.com>
# Create Date: 2023/12/20

cmake_minimum_required(VERSION 3.12)
project(indoorjson-cpp)

### C++ standard

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


find_package(GEOS REQUIRED)
find_package(glog REQUIRED)
find_package(gtest REQUIRED)
find_package(nlohmann_json_schema_validator REQUIRED)

### include

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_INCLUDE_PATH})

### source code
set(SOURCE_CODE
  src/serialization/feature.cpp
  src/serialization/node.cpp
  src/serialization/cell_space.cpp
)


### executable

add_executable(main src/main.cpp ${SOURCE_CODE})
target_link_libraries(main PRIVATE
  GEOS::geos
  nlohmann_json::nlohmann_json
  nlohmann_json_schema_validator
  )