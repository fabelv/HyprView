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

# Find and link nlohmann_json
find_package(nlohmann_json REQUIRED)

# Automatically collect all source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Ensure Qt MOC runs for QObject-derived classes
set(CMAKE_AUTOMOC ON)

# Add executable
add_executable(hyprview ${SRC_FILES})

# Link Qt libraries
target_link_libraries(hyprview PRIVATE Qt5::Widgets)

# Include directories for headers
target_include_directories(hyprview PRIVATE src models services utils)
target_include_directories(hyprview PRIVATE ${nlohmann_json_INCLUDE_DIRS})

