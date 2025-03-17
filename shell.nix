{ pkgs ? import <nixpkgs> {} }:

let
  qt = pkgs.qt6Packages;
in pkgs.mkShell {
  nativeBuildInputs = [
    pkgs.cmake
    pkgs.ninja
    pkgs.clang
    pkgs.qtcreator
    qt.full
    pkgs.vscode-extensions.vadimcn.vscode-lldb
    pkgs.lldb_20
  ];

  buildInputs = [
    qt.full
    pkgs.wayland
    pkgs.nlohmann_json
  ];

  shellHook = ''
    export QT_QPA_PLATFORM_PLUGIN_PATH=${qt.qtbase}/lib/qt-6/plugins/platforms
    export LLDB_PATH="${pkgs.lldb_20}/bin/lldb-dap"
  '';
}

