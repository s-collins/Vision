# Vision

Vision system for UA's NASA Robotic Mining Competition Team 

## Prerequisites

This project depends on the following external libraries:
- GoogleTest ( <https://github.com/google/googletest> )
- OpenCV ( <https://opencv.org/> )

```
TODO: Installation instructions for GoogleTest
```

```
TODO: Installation instructions for OpenCV
```

## Build Instructions

The build system for this project is generated with CMake. The "scripts" 
directory contains a simple bash script for out-of-source building. It
places the archives into a directory called "lib", and it places the
executables into a directory called "bin".

To use,make sure that you have CMake installed, then run the following from the 
"Vision" directory:

```
$ bash scripts/build.sh
```

There is also a script for cleaning up the build:

```
$ bash scripts/clean.sh
```
