{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }: flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs { inherit system; };
    in {
      packages.hyprview = pkgs.callPackage ./default.nix {};

      devShells.default = pkgs.callPackage ./shell.nix {};

      apps.default = flake-utils.lib.mkApp {
        drv = pkgs.callPackage ./default.nix {};
        name = "hyprview";
      };
    }
  );
}

