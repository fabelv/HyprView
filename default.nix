{ pkgs ? import <nixpkgs> {} }:

let
  qt = pkgs.qt6Packages;
in pkgs.stdenv.mkDerivation {
  pname = "hyprview";
  version = "1.0";
  src = ./.;

  nativeBuildInputs = [
    pkgs.cmake
    pkgs.ninja
    qt.full
  ];

  buildInputs = [
    qt.full
    pkgs.wayland
    pkgs.nlohmann_json
    pkgs.gtest
  ];
  
  configurePhase = ''
    cmake -GNinja $src -DGTest_DIR=${pkgs.gtest}/lib/cmake/GTest
  '';

  buildPhase = ''
    cmake --build .
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp hyprview $out/bin/
  '';

  env = {
    QT_QPA_PLATFORM_PLUGIN_PATH = "${qt.qtbase}/lib/qt-6/plugins/platforms";
  };
}

