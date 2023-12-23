# indoorjson-cpp

indoorjson serialization and desrialization library

# build
Install conan first https://conan.io/downloads

Use conan to prepare the dependencies and generate cmake files in "build" directory.
```bash
conan install . --output-folder=build --build=missing
```
Then use cmake to configure.
```bash
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
```
Finally trigger build using make.
```bash
make -j16
```
