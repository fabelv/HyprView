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

# ======================
# 🔍 Dependencies
# ======================

# Qt6
find_package(Qt6 COMPONENTS Qml Quick QuickControls2 REQUIRED)

# JSON
find_package(nlohmann_json REQUIRED)

# GTest and GMock via CMake config mode
find_package(GTest REQUIRED CONFIG)

# Enable Qt codegen (for Q_OBJECT, resources)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# ======================
# 📦 Core library
# ======================

file(GLOB_RECURSE HYPRVIEW_CORE_SOURCES lib/hyprview_core/**/*.cpp)

add_library(hyprview_core ${HYPRVIEW_CORE_SOURCES})

target_include_directories(hyprview_core
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(hyprview_core
    nlohmann_json::nlohmann_json
)

# ======================
# 🚀 Main executable
# ======================

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(hyprview ${SRC_FILES})

qt6_add_resources(QML_RESOURCES src/ui/qml/qml.qrc)
target_sources(hyprview PRIVATE ${QML_RESOURCES})

target_link_libraries(hyprview
    PRIVATE
    hyprview_core
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
)

target_include_directories(hyprview PRIVATE ${CMAKE_BINARY_DIR}/hyprview_autogen/include)

# ======================
# 🧪 Tests
# ======================

#TODO fix tests build

# file(GLOB_RECURSE TEST_FILES test/**/*.cpp)
# file(GLOB_RECURSE SERVICE_SRC_FILES src/services/*.cpp)
#
# add_executable(hyprview_tests ${TEST_FILES} ${SERVICE_SRC_FILES})
#
# target_link_options(hyprview_tests PRIVATE "-Wl,--wrap=system")
# target_link_libraries(hyprview_tests
#     PRIVATE
#     hyprview_core
#     GTest::gtest
#     GTest::gtest_main
#     GTest::gmock
#     GTest::gmock_main
# )
#
# add_test(NAME hyprview_tests COMMAND hyprview_tests)

