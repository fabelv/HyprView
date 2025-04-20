{ pkgs ? import <nixpkgs> { } }:

let
  qt = pkgs.qt6Packages;
in
pkgs.mkShell {
  nativeBuildInputs = [
    pkgs.cmake
    pkgs.ninja
    pkgs.clang
    pkgs.qtcreator
    qt.full
    pkgs.vscode-extensions.vadimcn.vscode-lldb
    pkgs.lldb_20
    pkgs.clang-tools
    pkgs.cppcheck
    pkgs.gcovr
    pkgs.clang-tools
    pkgs.sonar-scanner-cli
  ];

  buildInputs = [
    qt.full
    pkgs.wayland
    pkgs.nlohmann_json
    pkgs.gtest.dev
  ];

  shellHook = ''
    export QT_QPA_PLATFORM_PLUGIN_PATH=${qt.qtbase}/lib/qt-6/plugins/platforms
    export QML_IMPORT_PATH="${qt.qtdeclarative}/lib/qt-6/qml:$(pwd)/build/HyprView/HyprView"
    export CMAKE_PREFIX_PATH="${pkgs.gtest}/lib/cmake/GTest:$CMAKE_PREFIX_PATH"

    # DAP Environment Variables
    export LLDB_PATH="${pkgs.lldb_20}/bin/lldb-dap"
    export EXECUTABLE_PATH="./build/hyprview"
    export BUILD_COMMAND="make"
    export TEST_EXECUTABLE_PATH="./build/hyprview_tests"
    export TEST_COMMAND="make test"
  '';
}

