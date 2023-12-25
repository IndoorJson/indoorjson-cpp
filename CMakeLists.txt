# CMakeLists.txt
# Copyright (c) 2023 IndoorJson
# Author: Kunlin Yu <yukunlin@syriusrobotics.com>
# Create Date: 2023/12/20

cmake_minimum_required(VERSION 3.12)
project(indoorjson-cpp)

### C++ standard

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# json-schema-validator
find_package(nlohmann_json_schema_validator REQUIRED)

# libgeos
find_package(GEOS REQUIRED)
add_compile_definitions(USE_UNSTABLE_GEOS_CPP_API)

# gtest
find_package(GTest REQUIRED)

# glog
find_package(glog REQUIRED)
if(WIN32)
    add_compile_definitions(GLOG_NO_ABBREVIATED_SEVERITIES)
endif()

### include

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_INCLUDE_PATH})

### source code
set(SOURCE_CODE
  src/serialization/feature.cpp
  src/serialization/cell_space.cpp
  src/serialization/cell_boundary.cpp
  src/serialization/node.cpp
  src/serialization/edge.cpp
  src/serialization/geometry.cpp
  src/serialization/thematic_layer.cpp
  src/serialization/dual_space_layer.cpp
  src/serialization/primal_space_layer.cpp
  src/serialization/connection.cpp
  src/serialization/indoor_features.cpp
)

### library

add_library(${PROJECT_NAME} ${SOURCE_CODE})

### executable

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE
  ${PROJECT_NAME}
  GEOS::geos
  nlohmann_json::nlohmann_json
  nlohmann_json_schema_validator
  glog::glog
  )

### tests
enable_testing()

set(TEST_CASES
  test_feature
  test_node
  test_edge
  test_thematic_layer
)

foreach(CASE ${TEST_CASES})
  add_executable(${CASE} tests/${CASE}.cpp)
  add_test(NAME ${CASE} COMMAND ${CASE})
  target_link_libraries(${CASE}
    ${PROJECT_NAME}
    GEOS::geos
    nlohmann_json::nlohmann_json
    nlohmann_json_schema_validator
    glog::glog
    GTest::GTest
  )
endforeach()