{ pkgs ? import <nixpkgs> {} }:

let
  qt5 = pkgs.libsForQt5;
in pkgs.mkShell {
  nativeBuildInputs = [
    pkgs.cmake
    pkgs.ninja
    pkgs.clang
    pkgs.qtcreator
    qt5.full
    pkgs.vscode-extensions.vadimcn.vscode-lldb
    pkgs.lldb_20
  ];

  buildInputs = [
    qt5.full
    pkgs.wayland
    pkgs.nlohmann_json
  ];

  shellHook = ''
    export QT_QPA_PLATFORM_PLUGIN_PATH=${qt5.qtbase}/lib/qt-5/plugins/platforms
    export LLDB_PATH="${pkgs.lldb_20}/bin/lldb-dap"
  '';
}

