# indoorjson-cpp
indoorjson serialization and desrialization library writen in c++14

# Introduction
IndoorGML 1.0 was been published in 2014 and 1.1 was been published in 2020.

https://www.ogc.org/standard/indoorgml/

https://docs.ogc.org/is/19-011r4/19-011r4.html

http://indoorgml.net/


Recently, the IndoorGML standard working group has been developing IndoorGML 2.0.
As an extension of GML, IndoorGML 1 supports GML and XML natively.
However, considering embedded systems (e.g., robots) and certain web-based applications, XML proves to be too heavy.
In light of this, JSON emerges as a more suitable serialization solution for these conceptual models.

Presently, the SWG (Standard Working Group) is in the process of defining a JSON schema to serve as an appendix to IndoorGML 2.0.
This schema is referred to as "indoorjson".
It's essential to note that indoorjson is not a standalone standard but rather a serialization format for IndoorGML 2.0.

https://github.com/opengeospatial/IndoorGML-SWG/tree/master/IndoorGML2

IndoorGML 2.0 is currently in a draft stage and has not been officially published.
The project you're referring to is an experimental initiative aiming to implement an encoder and decoder for IndoorGML 2.0.
It's important to note that details, such as field names, are subject to change as the project evolves.
Therefore, it is advised not to use this library in a production environment.

# Depedencies

## json-schema-validator/2.2.0
We use [json-schema-validator](https://github.com/pboettch/json-schema-validator) to define and validate the json string.

Which use [nlohmann/json](https://github.com/nlohmann/json)

## geos/3.12.0
We use [libgeos](https://github.com/libgeos/geos) to represent the Geometry of CellSpace and CellBoundary.

## glog/0.6.0
for log.

## gtest/1.14.0
for unit test.

# Build
## install dependencies manually
1. install using apt
```bash
sudo apt install libgeos++-dev
sudo apt install libglog
sudo apt install libgoogle-glog-dev
sudo apt install libgtest-dev
sudo apt install nlohmann-json3-dev
```
2. install from source code
2.1. json-schema-validator
No apt sources is aavailable for it, so we build it from source code
```bash
git clone https://github.com/pboettch/json-schema-validator.git
cd json-schema-validator
mkdir build
cd build
cmake ..
make -j16
make install
```
2.2 libgeos
The default libgeos version of Ubuntu is 3.10.2 which is not stable enough so we build the source code
```bash
git clone https://github.com/libgeos/geos.git
cd geos
git checkout 3.12.0
mkdir build
cd build
cmake ..  -DBUILD_TESTING=OFF
make -j16
sudo make install
```

3. build indoorjson-cpp
```bash
cd indoorjson-cpp
mkdir build
cd build
cmake ..
make -j16
```


## install dependencies using conan
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
