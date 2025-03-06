cmake_minimum_required(VERSION 3.19)
project(HyprView VERSION "0.1")

# Use C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure correct include paths when generating compile_commands.json
if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES
        ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

# Find and link Qt5
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(hyprview src/main.cpp)

target_link_libraries(hyprview PRIVATE Qt5::Widgets)

