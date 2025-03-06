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
}
