cmake_minimum_required(VERSION 3.10)

project(LearnOpenGLTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS true)
set(CMAKE_CXX_FLAGS "$CMAKE_CXX_FLAGS -Werror")

include_directories("include" "/usr/local/include" "src")

add_library(GLAD STATIC
    "libs/glad/glad.c"
)

find_library(GLFW NAME glfw REQUIRED)

add_executable(a.out
    src/main.cpp
    src/util/Window.cpp
)
target_link_libraries(a.out ${GLFW} GLAD)