cmake_minimum_required(VERSION 3.12)
project(GraphicsEngine)

option(ENABLE_OPTIONAL_COMMAND "Enable Optional Command" OFF)

if (ENABLE_OPTIONAL_COMMAND)
    set(glfw3_DIR "/path/to/directory/containing/config/file")
endif ()

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
include_directories("shaders")

# Add source files for main application
set(SOURCES
        src/frame.cpp
        src/glad.c
        src/vertex.cpp
        src/VBO.cpp
        src/EBO.cpp
        src/VAO.cpp
        src/shader.cpp
        src/camera.cpp
        # Add more source files here if necessary
        includes/frame.h 
        includes/matrix.h 
        src/matrix.cpp 
        src/model.cpp 
        includes/model.h 
        includes/VBO.h
        includes/EBO.h
        includes/VAO.h
        includes/shader.h
        includes/camera.h
        src/color.cpp
        includes/color.h
        src/modelUtils.cpp
        includes/modelUtils.h)

# Add GLAD library
add_library(glad src/glad.c)

# Create executable for main application
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries for main application
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw ${CMAKE_DL_LIBS})

# Create executable for unit tests
add_executable(UnitTests
        tests/src/master_test.cpp
        tests/src/vertex_tests.cpp
        tests/src/shader_tests.cpp
        tests/src/utils.cpp
        tests/includes/shader_tests.h
        tests/includes/shader_tests.h
        tests/includes/utils.h
        src/shader.cpp
        src/vertex.cpp
        src/glad.c
        shaders/static.vert
        shaders/static.frag
        src/color.cpp
)

# Include directories for unit tests
target_include_directories(UnitTests PRIVATE "includes")
target_include_directories(UnitTests PRIVATE "tests/includes")

# Link libraries for unit tests
target_link_libraries(UnitTests ${OPENGL_LIBRARIES} glfw ${CMAKE_DL_LIBS})

# Add tests
enable_testing()

# Run unit tests as part of the test suite
add_test(NAME MyUnitTests COMMAND UnitTests)

# Custom target for running only unit tests
add_custom_target(runUnitTests
        COMMAND ${CMAKE_CTEST_COMMAND} -R MyUnitTests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running unit tests"
        VERBATIM)