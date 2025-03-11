{ pkgs ? import <nixpkgs> {} }:

let
  qt5 = pkgs.libsForQt5;
in pkgs.stdenv.mkDerivation {
  pname = "hyprview";
  version = "1.0";
  src = ./.;

  nativeBuildInputs = [
    pkgs.cmake
    pkgs.ninja
    qt5.full
  ];

  buildInputs = [
    qt5.full
    pkgs.wayland
    pkgs.nlohmann_json
  ];
  
  configurePhase = ''
    cmake -GNinja $src
  '';

  buildPhase = ''
    cmake --build .
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp hyprview $out/bin/
  '';

  env = {
    QT_QPA_PLATFORM_PLUGIN_PATH = "${qt5.qtbase}/lib/qt-5/plugins/platforms";
  };
}

