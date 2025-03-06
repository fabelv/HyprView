
cmake_minimum_required(VERSION 3.16)
project(HyprView)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(hyprview src/main.cpp)

target_link_libraries(hyprview PRIVATE Qt5::Widgets)

