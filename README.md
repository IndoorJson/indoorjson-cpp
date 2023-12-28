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
We use [json-schema-validator](https://github.com/pboettch/json-schema-validator) to define and validate the json string which uses [nlohmann/json](https://github.com/nlohmann/json)

## geos/3.12.0
We use [libgeos](https://github.com/libgeos/geos) to represent the Geometry of CellSpace and CellBoundary.

## glog/0.6.0
for logging

## gtest/1.14.0
for unit tests.

# Build
## install dependencies manually (Ubuntu 22.04)
1. install using apt
```bash
sudo apt install libglog
sudo apt install libgoogle-glog-dev
sudo apt install libgtest-dev
sudo apt install nlohmann-json3-dev
```
2. install from source code
    1. json-schema-validator

    No apt sources are available for it, so we need to build it from source code
    ```bash
    git clone https://github.com/pboettch/json-schema-validator.git
    cd json-schema-validator
    mkdir build
    cd build
    cmake ..
    make -j16
    make install
    ```

    2. libgeos

    The default libgeos version of Ubuntu 22.04 is libgeos 3.10.2 which is not stable enough so we better build if from the source code.
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


## install dependencies using conan (Ubuntu 22.04)
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

## install dependencies using conan (Windows Visual Studio Community)
1. Install conan first https://conan.io/downloads

2. Use conan to prepare the dependencies and generate cmake files in "out/build" directory.
```bash
conan install . --output-folder=out/build --build=missing
```

3. Open indoorjson-cpp directory using Visual Studio

4. Set CMakeSettings.json
```json
  "installRoot": "${projectDir}\\out\\install\\${name}",
  "cmakeCommandArgs": "-DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release",
```
5. Finally trigger configuration and building using VS GUI.

# example
 *---b3-----*---b7-----*
 |          |          |
 |          |          |
b4  space1  b2 space2  b6
 |          |          |
 |          |          |
 *---b1-----*---b5-----*
 
```json
{
  "connections": [
    {
      "comment": "this is a inter layer connection connect layer1 and layer2",
      "layers": [
        "layer1",
        "layer2"
      ],
      "nodes": [
        "n1",
        "node_2nd"
      ],
      "spaces": [
        "space1",
        "space_2nd"
      ]
    }
  ],
  "layers": [
    {
      "id": "layer1",
      "theme": "Topographic",
      "dual_space": {
        "edges": [
          {
            "boundary": "b2",
            "geom": "LINESTRING (0.5 0.5, 1.5 0.5)",
            "id": "e",
            "nodes": [
              "n1",
              "n2"
            ],
            "weight": 0.0
          }
        ],
        "nodes": [
          {
            "edges": [
              "e"
            ],
            "geom": "POINT (0.5 0.5)",
            "id": "n1",
            "space": "space1"
          },
          {
            "edges": [
              "e"
            ],
            "geom": "POINT (1.5 0.5)",
            "id": "n2",
            "space": "space2"
          }
        ]
      },
      "primal_space": {
        "boundaries": [
          {
            "edge": null,
            "geom": "LINESTRING (0 0, 1 0)",
            "id": "b1",
            "spaces": [
              "space1"
            ]
          },
          {
            "edge": "e",
            "geom": "LINESTRING (1 0, 1 1)",
            "id": "b2",
            "spaces": [
              "space1",
              "space2"
            ]
          },
          {
            "edge": null,
            "geom": "LINESTRING (1 1, 0 1)",
            "id": "b3",
            "spaces": [
              "space1"
            ]
          },
          {
            "edge": null,
            "geom": "LINESTRING (0 1, 0 0)",
            "id": "b4",
            "spaces": [
              "space1"
            ]
          },
          {
            "edge": null,
            "geom": "LINESTRING (1 0, 2 0)",
            "id": "b5",
            "spaces": [
              "space2"
            ]
          },
          {
            "edge": null,
            "geom": "LINESTRING (2 0, 2 1)",
            "id": "b6",
            "spaces": [
              "space2"
            ]
          },
          {
            "edge": null,
            "geom": "LINESTRING (2 1, 1 1)",
            "id": "b7",
            "spaces": [
              "space2"
            ]
          }
        ],
        "spaces": [
          {
            "boundaries": [
              "b1",
              "b2",
              "b3",
              "b4"
            ],
            "geom": "POLYGON ((0 0, 1 0, 1 1, 0 1, 0 0))",
            "id": "space1",
            "node": "n1"
          },
          {
            "boundaries": [
              "b2",
              "b5",
              "b6",
              "b7"
            ],
            "geom": "POLYGON ((1 0, 2 0, 2 1, 1 1, 1 0))",
            "id": "space2",
            "node": "n2"
          },
          {
            "boundaries": [],
            "geom": "POLYGON ((-1 0, 0 0, 0 1, -1 1, -1 0))",
            "id": "space_2nd",
            "node": null
          }
        ]
      }
    },
    {
      "id": "layer2",
      "theme": "Topographic",
      "dual_space": {
        "edges": [],
        "nodes": [
          {
            "edges": [],
            "geom": "POINT (-0.5 0.5)",
            "id": "node_2nd",
            "space": null
          }
        ]
      },
      "primal_space": {
        "boundaries": [
          {
            "edge": null,
            "geom": "LINESTRING (-1 0, 0 0)",
            "id": "b_2nd1",
            "spaces": []
          },
          {
            "edge": null,
            "geom": "LINESTRING (0 0, 0 1)",
            "id": "b_2nd2",
            "spaces": []
          },
          {
            "edge": null,
            "geom": "LINESTRING (0 1, -1 1)",
            "id": "b_2nd3",
            "spaces": []
          },
          {
            "edge": null,
            "geom": "LINESTRING (-1 1, -1 0)",
            "id": "b_2nd4",
            "spaces": []
          }
        ],
        "spaces": [
          {
            "boundaries": [],
            "geom": "POLYGON ((-1 0, 0 0, 0 1, -1 1, -1 0))",
            "id": "space_2nd",
            "node": null
          }
        ]
      }
    }
  ]
}
```
