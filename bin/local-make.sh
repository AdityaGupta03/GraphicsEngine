#!/bin/bash

echo
# Remove build directory and create an empty one
cd build 2> /dev/null
if [ $? -ne 0 ]; then
  mkdir build && cd build
  first_time=true
else
  rm -f ./UnitTests ./GraphicsEngine &> /dev/null
  first_time=false
fi

> cmake_log
> make_log

# Build Project
#read -p "Do you want to use manually set glfw3 path (in \"CMakeLists.txt\")? (y/n): " optional_cmake
#
#if [[ optional_cmake == "y" || optional_cmake == "Y" ]]; then
#  cmake -DENABLE_OPTIONAL_COMMAND=ON .. &> cmake_log
#else
#  cmake .. &> cmake_log
#fi

echo -en "Building executable(s)...\t--> "
if [[ $first_time == true ]]; then
  cmake .. &> cmake_log
  if [ $? -ne 0 ]; then
    echo -e "Failed to build with cmake. Check build log (\"cmake_log\")\n"
    echo
    exit
  fi

  make &> make_log
  if [ $? -ne 0 ]; then
    echo -e "Failed to build with cmake. Check build log (\"make_log\")\n"
    echo
    exit
  fi
else
  if [ $# -lt 1 ]; then
    cmake --build . --target GraphicsEngine &> cmake_log
    if [ $? -ne 0 ]; then
      echo -e "Failed to build with cmake. Check build log (\"cmake_log\")\n"
      echo
      exit
    fi
  else
    if [[ $1 == "tests" ]]; then
          cmake --build . --target UnitTests &> cmake_log
          if [ $? -ne 0 ]; then
              echo -e "Failed to build with cmake. Check build log (\"cmake_log\")\n"
              echo
              exit
            fi
        else
          echo "Invaild flags passed."
          echo "Usage: local-make.sh [tests]"
          echo
          exit
        fi
  fi
fi

echo "Built."

# Run Project
if [[ $1 == "tests" ]]; then
  echo -e "Running executable...\t --> UnitTests\n"
  ./UnitTests
else
  echo -e "Running executable...\t --> GraphicsEngine\n"
  ./GraphicsEngine
fi