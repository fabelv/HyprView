cmake_minimum_required(VERSION 3.19)
project(HyprView VERSION "0.1")

# Use C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: Keep compile_commands.json include paths correct
if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES
        ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

# Find Qt6 QML & Quick
find_package(Qt6 COMPONENTS Qml Quick QuickControls2 REQUIRED)

# include nlohmann_json 
find_package(nlohmann_json REQUIRED)

# include gtest
find_package(GTest REQUIRED)

# Enable Qt codegen (for Q_OBJECT, resources)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Gather C++ source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE TEST_FIELS test/*.cpp)

# Define executable
add_executable(hyprview
    ${SRC_FILES}
)

add_executable(hyprview_tests
    ${TEST_FIELS}
)


# Add QML resources (must be after add_executable)
qt6_add_resources(QML_RESOURCES src/qml/qml.qrc)
target_sources(hyprview PRIVATE ${QML_RESOURCES})

# Link against Qt libraries
target_link_libraries(hyprview PRIVATE
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    nlohmann_json::nlohmann_json
)

target_link_libraries(hyprview_tests PRIVATE GTest::gtest GTest::gtest_main)
add_test(NAME hyprview_tests COMMAND hyprview_tests)

target_include_directories(hyprview PRIVATE ${CMAKE_BINARY_DIR}/hyprview_autogen/include)
