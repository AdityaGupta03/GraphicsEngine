#!/bin/bash

echo "Making GraphicsEngine project and running..."
echo

# Remove build directory and create an empty one
rm -rf build &> /dev/null
mkdir build && cd build

> cmake_log
> make_log

# Build Project
read -p "Do you want to use manually set glfw3 path (in \"CMakeLists.txt\")? (y/n): " optional_cmake

if [[ optional_cmake == "y" || optional_cmake == "Y" ]]; then
  cmake -DENABLE_OPTIONAL_COMMAND=ON .. &> cmake_log
else
  cmake .. &> cmake_log
fi

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