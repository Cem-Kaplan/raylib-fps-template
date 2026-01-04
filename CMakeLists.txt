cmake_minimum_required(VERSION 3.10)
project(raylib_fps_template)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(raylib_fps
    src/main.cpp
    src/Player.cpp
)

target_link_libraries(raylib_fps
    raylib
    GL
    m
    pthread
    dl
    X11
)
