cmake_minimum_required(VERSION 3.12)
project(GraphicsEngine)

# Set C++ version
set(CMAKE_CXX_STANDARD 14)

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Include directories
include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} "deps")
include_directories("deps/glad")
include_directories("deps/KHR")
include_directories("includes")

# Add source files
set(SOURCES
        src/frame.cpp
        src/glad.c
        # Add more source files here if necessary
        includes/frame.h)

# Add GLAD library
add_library(glad src/glad.c)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw ${CMAKE_DL_LIBS})
