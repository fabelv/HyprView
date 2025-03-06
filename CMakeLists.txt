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

# Add source files
add_executable(hyprview 
    src/main.cpp
    src/models/monitor.cpp
)

# Link Qt5 libraries
target_link_libraries(hyprview PRIVATE Qt5::Widgets)

# Include directories for headers
target_include_directories(hyprview PRIVATE src/models)

# Manually include nlohmann_json
find_package(nlohmann_json REQUIRED)
target_include_directories(hyprview PRIVATE ${nlohmann_json_INCLUDE_DIRS})

