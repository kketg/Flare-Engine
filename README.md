# Flare-Engine
A thing we're trying to do

## Setup to build
* Have a cpp compiler. Tested w/ GNU Make 4.2.1, GCC 9.3.0 on Ubuntu 20.04 (Soon also on MinGW Windows 10)
* Cmake in path (optionally have GUI too)
* GLFW should be built with the app, per `CmakeLists.txt`, so no work there
* `cmake .` (in repo root)
* `make` (or equivalent command based on your compiler. (Think Windows has `make` too with MinGW ?))
* `./Test` or `Test.exe`