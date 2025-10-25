{
  description = "Flake for miniRT";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      packages.${system}.miniRT = pkgs.stdenv.mkDerivation {
        pname = "miniRT";
        version = "1.0";

        src = ./.;

        buildInputs = with pkgs; [
          minilibx
          xorg.libX11
          xorg.libXext
          zlib
          libbsd
	  makeWrapper
        ];

        preBuild = ''
          mkdir -p mlx_linux
          ln -sf ${pkgs.minilibx}/lib/libmlx.a mlx_linux/libmlx_Linux.a
          ln -sf ${pkgs.minilibx}/include/mlx.h mlx_linux/
        '';

        buildPhase = ''
          make miniRT
        '';

        installPhase = ''
          mkdir -p $out/bin
          cp miniRT $out/bin/
	
	# Wrap the binary to include all library paths
          wrapProgram $out/bin/miniRT \
            --set LD_LIBRARY_PATH "${pkgs.libbsd}/lib:${pkgs.xorg.libX11}/lib:${pkgs.xorg.libXext}/lib:${pkgs.zlib}/lib"
        '';
      };

      devShells.${system}.default = pkgs.mkShell {
        buildInputs = with pkgs; [
          minilibx
          xorg.libX11
          xorg.libXext
          zlib
          libbsd
	  makeWrapper
        ];

        shellHook = ''
          mkdir -p mlx_linux
          ln -sf ${pkgs.minilibx}/lib/libmlx.a mlx_linux/libmlx_Linux.a
          ln -sf ${pkgs.minilibx}/include/mlx.h mlx_linux/
        '';
      };

      apps.${system}.miniRT = {
        type = "app";
        program = "${self.packages.${system}.miniRT}/bin/miniRT";
      };

      # Set defaults so 'nix build' and 'nix run' work
      defaultPackage.${system} = self.packages.${system}.miniRT;
      defaultApp.${system} = self.apps.${system}.miniRT;
    };
}

