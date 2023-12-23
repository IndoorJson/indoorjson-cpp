# CMakeLists.txt
# Copyright (c) 2023 IndoorJson
# Author: Kunlin Yu <yukunlin@syriusrobotics.com>
# Create Date: 2023/12/20

cmake_minimum_required(VERSION 3.12)
project(indoorjson-cpp)

### C++ standard

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


### include

include_directories(${CMAKE_SOURCE_DIR}/include)


### dependencies

# nlohmann/json
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(dependencies/nlohmann_json)

# json-schema-validator
set(nlohmann_json_VERSION v3.10.5 CACHE INTERNAL "")
add_subdirectory(dependencies/json-schema-validator)

# libgeos
add_subdirectory(dependencies/geos)


### source code
set(SOURCE_CODE
  src/serialization/feature.cpp
  src/serialization/node.cpp
  src/serialization/cell_space.cpp
)


### executable

add_executable(main src/main.cpp ${SOURCE_CODE})
target_link_libraries(main PRIVATE
  nlohmann_json::nlohmann_json
  nlohmann_json_schema_validator
  geos
  )
