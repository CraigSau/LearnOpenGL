cmake_minimum_required(VERSION 3.10)

# Set the project name
project(LearnOpenGL)

# Specify the C standard
set(CMAKE_C_STANDARD 99)

# Add the glad library
add_library(glad glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

# Add the executable
add_executable(main src/main.c)

# Find GLFW and OpenGL
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

# Include directories for GLFW
include_directories(${GLFW_INCLUDE_DIRS})

# Link the libraries
target_link_libraries(main glad glfw OpenGL::GL)
