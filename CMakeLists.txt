cmake_minimum_required(VERSION 3.12)
project(GraphicsEngine)

option(ENABLE_OPTIONAL_COMMAND "Enable Optional Command" OFF)

# Set C++ version
set(CMAKE_CXX_STANDARD 14)

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# If flag set get glfw3 from path
if (ENABLE_OPTIONAL_COMMAND)
    set(glfw3_DIR "/path/to/directory/containing/config/file")
endif ()

# Include directories
include_directories(
        ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} "deps"
        "deps/glad"
        "deps/KHR"
        "includes"
)

# Dynamically add source files
set(SOURCE_DIR "src")
file(GLOB CPP_SOURCES "${SOURCE_DIR}/*.cpp")

# Create executable for main application
add_executable(${PROJECT_NAME} ${CPP_SOURCES} "src/glad.c")

# Set test sources
set(TEST_SOURCE_DIR "tests/src")
file(GLOB TEST_SOURCES "${TEST_SOURCE_DIR}/*.cpp")

# Create executable for unit tests
add_executable(UnitTests
        ${TEST_SOURCES}
        src/vertex.cpp
)

# Include directories for unit tests
target_include_directories(UnitTests PRIVATE "tests/includes")

# Link libraries
target_link_libraries(UnitTests ${OPENGL_LIBRARIES} glfw ${CMAKE_DL_LIBS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw ${CMAKE_DL_LIBS})