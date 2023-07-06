#!/bin/bash

# Remove build directory and create an empty one
rm -rf build &> /dev/null
mkdir build && cd build

# Build Project
cmake .. && make

# Run Project
./GraphicsEngine