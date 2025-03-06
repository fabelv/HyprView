{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  nativeBuildInputs = [
    pkgs.cmake
    pkgs.ninja
    pkgs.clang
  ];
}

