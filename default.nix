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
    pkgs.gtest.dev
  ];

  configurePhase = ''
    cmake -GNinja $src -DGTest_DIR=${pkgs.gtest}/lib/cmake/GTest
  '';

  buildPhase = ''
    cmake --build .
  '';

  installPhase = ''
    # Install binary
    mkdir -p $out/bin
    cp hyprview $out/bin/

    # Install QML resources
    mkdir -p $out/share/hyprview/qml
    cp -r src/ui/qml/* $out/share/hyprview/qml

    # Install .desktop file for Wofi/app launchers
    mkdir -p $out/share/applications
    cat > $out/share/applications/hyprview.desktop <<EOF
[Desktop Entry]
Name=HyprView
Comment=Monitor layout tool for Hyprland
Exec=hyprview
Icon=display
Terminal=false
Type=Application
Categories=Utility;
EOF

    # Optional: install icon
    # mkdir -p $out/share/icons/hicolor/256x256/apps
    # cp res/icon.png $out/share/icons/hicolor/256x256/apps/hyprview.png
  '';

  env = {
    QT_QPA_PLATFORM_PLUGIN_PATH = "${qt.qtbase}/lib/qt-6/plugins/platforms";
  };
}

