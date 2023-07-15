#!/bin/bash

echo "Making GraphicsEngine project and running..."
echo

# Remove build directory and create an empty one
rm -rf build &> /dev/null
mkdir build && cd build

> cmake_log
> make_log

# Build Project
cmake .. &> cmake_log
if [ $? -ne 0 ]; then
  echo
  echo "Failed to build with cmake. Check build log (\"cmake_log\")..."
  echo
  exit
fi

make &> make_log
if [ $? -ne 0 ]; then
  echo
  echo "Failed to build with make. Check build log (\"make_log\")..."
  echo
  exit
fi

echo
echo "Built. Running project..."
echo

# Run Project
./GraphicsEngine