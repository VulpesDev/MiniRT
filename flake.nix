{
  description = "A project from 42Berlin's core curriculum. Exploring fractals and complex numbers. Written in C, also using our own ft_printf.";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      packages.${system}.default = pkgs.stdenv.mkDerivation {
        pname = "miniRT";
        version = "1.0";
        
        src = ./.;
        
        buildInputs = with pkgs; [
          minilibx
          xorg.libX11
          xorg.libXext
          zlib
        ];
        
        preBuild = ''
          mkdir -p mlx_linux
          ln -sf ${pkgs.minilibx}/lib/libmlx.a mlx_linux/libmlx_Linux.a
          ln -sf ${pkgs.minilibx}/include/mlx.h mlx_linux/
        '';
        
        installPhase = ''
          mkdir -p $out/bin
          cp miniRT $out/bin/
        '';
      };

      devShells.${system}.default = pkgs.mkShell {
        buildInputs = with pkgs; [
          minilibx
          xorg.libX11
          xorg.libXext
          zlib
          libbsd
        ];
        
        shellHook = ''
          mkdir -p mlx_linux
          ln -sf ${pkgs.minilibx}/lib/libmlx.a mlx_linux/libmlx_Linux.a
          ln -sf ${pkgs.minilibx}/include/mlx.h mlx_linux/
        '';
      };

      apps.${system}.default = {
        type = "app";
        program = "${self.packages.${system}.default}/bin/miniRT";
      };
    };
}
