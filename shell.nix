{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
	gcc
	gnumake
	clang
	minilibx
	xorg.libX11
	xorg.libXext
	zlib
	libbsd
  ];

  shellHook = ''
	mkdir -p mlx_linux
	ln -sf ${pkgs.minilibx}/lib/libmlx.a mlx_linux/libmlx_Linux.a
	lb -sf ${pkgs.minilibx}/include/mlx.h mlx_linux/
      '';
}
