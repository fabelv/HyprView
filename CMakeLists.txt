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

# Find and link Qt6
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Find and link nlohmann_json
find_package(nlohmann_json REQUIRED)

# Ensure Qt MOC, UIC, and RCC run for QObject-derived classes
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Define UI files location
set(CMAKE_AUTOUIC_SEARCH_PATHS src/ui)  

# Automatically collect all source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Add executable
add_executable(hyprview ${SRC_FILES})

# Link Qt libraries
target_link_libraries(hyprview PRIVATE Qt6::Widgets)

# Ensure auto-generated UI headers are found
target_include_directories(hyprview PRIVATE ${CMAKE_BINARY_DIR}/hyprview_autogen/include)

