# indoorjson-cpp

indoorjson serialization and desrialization library

# Depedencies

## geos/3.12.0
We use [libgeos](https://github.com/libgeos/geos) to represent the Geometry of CellSpace and CellBoundary.

## json-schema-validator/2.2.0
We use [json-schema-validator](https://github.com/pboettch/json-schema-validator) to define and validate the json string.

Which use [nlohmann/json](https://github.com/nlohmann/json)

## glog/0.6.0
for log.

## gtest/1.14.0
for unit test.

# Build
1. Install conan first https://conan.io/downloads

2. Use conan to prepare the dependencies and generate cmake files in "build" directory.
```bash
conan install . --output-folder=build --build=missing
```
3. Then use cmake to configure.
```bash
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
```
4. Finally trigger build using make.
```bash
make -j16
```
