{
  description = "Fractol - cross platform flake";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }: 
    let
      systems = [ "x86_64-linux" "aarch64-darwin" "x86_64-darwin" ];
      forAllSystems = f: nixpkgs.lib.genAttrs systems (system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
        in f system pkgs
      );
    in {
      packages = forAllSystems (system: pkgs:
        pkgs.stdenv.mkDerivation {
          pname = "miniRT";
          version = "1.0";
          src = ./.;

          buildInputs = if pkgs.stdenv.isDarwin then
            [ ]
          else
            with pkgs; [ minilibx xorg.libX11 xorg.libXext zlib libbsd ];

          CFLAGS = if pkgs.stdenv.isDarwin then "-Imlx" else "";
          LDFLAGS = if pkgs.stdenv.isDarwin then
            "-Lmlx -lmlx -lbsd -framework OpenGL -framework AppKit"
          else
            "";

          buildPhase = "make miniRT";
          installPhase = ''
            mkdir -p $out/bin
            cp miniRT $out/bin/
          '';
        }
      );

      apps = forAllSystems (system: pkgs: {
        default = {
          type = "app";
          program = "${self.packages.${system}}/bin/miniRT";
        };
      });
    };
}

