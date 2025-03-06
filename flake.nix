
{
  inputs = { nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable"; };

  outputs = { self, nixpkgs }: let
    systems = [ "x86_64-linux" "aarch64-linux" ];
    forAllSystems = f: nixpkgs.lib.genAttrs systems (system: f system (import nixpkgs { inherit system; }));
  in {
    packages = forAllSystems (system: pkgs: let
      qt5 = pkgs.libsForQt5;
    in {
      hyprview = pkgs.stdenv.mkDerivation {
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
      };
    });

    devShells = forAllSystems (system: pkgs: let
      qt5 = pkgs.libsForQt5;
    in {
      default = pkgs.mkShell {
        nativeBuildInputs = [
          pkgs.cmake 
          pkgs.ninja
          qt5.full
          pkgs.clang
        ];
        buildInputs = [
          qt5.full
          pkgs.wayland
        ];
      };
    });
  };
}

