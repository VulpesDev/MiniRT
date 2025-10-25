{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  pname = "tvasielv_ft_miniRT";
  version = "1.0";

  src = ./.;

  buildInputs = with pkgs; [
    minilibx
    xorg.libX11
    xorg.libXext
    zlib
    libbsd
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
}
