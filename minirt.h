/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:43:46 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/05 12:36:50 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "libft.h"
# include "keys.h"
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# define SPACE "\t\n\f\r\v "
# define MAX_SOLID 3
# define HEIGHT 500
# define WIDTH 500
# define CANV_MIN_X -1
# define CANV_MAX_X 1
# define CANV_MIN_Y -1
# define CAM_PACE 0.1

typedef enum e_err
{
	SUCCESS,
	MEM_FAIL,
	ARG_REQUIRED,
	FILE_EXTENSION,
	INVALID_FILE,
	INVALID_ELEMENT,
	INVALID_DUP,
}			t_err;

enum e_unique_el
{
	AMBIENT,
	CAMERA,
	LIGHT,
};

// typedef enum e_bool
// {
// 	FALSE,
// 	TRUE,
// }			t_bool;

typedef struct s_img
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		*name;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_point_3d
{
	double	x;
	double	y;
	double	z;
}			t_point_3d;

typedef t_point_3d	t_vector;

typedef struct s_pxl
{
	int	x;
	int	y;
	int	trgb;
}			t_pxl;

typedef struct s_point_2d
{
	double	x;
	double	y;
}			t_point_2d;

typedef struct s_ambient
{
	float	lighting_ratio;
	int		trgb;
}				t_ambient;

typedef struct s_camera
{
	t_point_3d		pos;
	t_vector		orientation;
	uint8_t			fov;
}					t_camera;

typedef struct s_light
{
	t_point_3d		pos;
	float			brightness;
	int				trgb;
}					t_light;

typedef struct s_sphere
{
	t_point_3d		pos;
	float			diameter;
	int				trgb;
}					t_sphere;

typedef struct s_plane
{
	t_point_3d		pos;
	t_vector		rotation;
	int				trgb;
}					t_plane;

typedef struct s_cylinder
{
	t_point_3d		center;
	t_vector		rotation;
	float			diameter;
	float			height;
	int				trgb;
}					t_cylinder;

/**
 * Possible struct for the scene:
 * one value for each unique element (A, C, L),
 * an array for each solid. Plus a pointer
 * to the image.
*/
typedef struct s_scene
{
	t_img		*img;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
}				t_scene;

/* PARSE */
int		parse_args(t_scene *scene, char *filename);
t_err	validate_ambient(t_scene *scene, char **el);
t_err	validate_camera(t_scene *scene, char **el);
t_err	validate_light(t_scene *scene, char **el);
int		validate_sphere(t_scene *scene, char **el);
int		validate_plane(t_scene *scene, char **el);
int		validate_cylinder(t_scene *scene, char **el);

/* PARSE UTILS */
int		validate_3d_range(t_point_3d point, float min, float max);
t_err	extract_xyz(char *xyz, t_point_3d *point);
t_err	extract_rgb(char *rgb, int *ret);

/* GRAPHIC */
int		create_trgb(int t, int r, int g, int b);
int		mlx_manage(t_scene *scene);
void	my_mlx_pixel_put_d(t_img *data, int x, int y, int color);
t_err	init_img(t_scene *scene);

/* RENDER */
t_err	render_scene(t_scene *scene);
void	draw(t_scene *scene);

/* ERROR HANDLING*/
t_err	ft_error(char *msg, char *arg, int err_code, t_scene *scene);
t_err	ft_warning(char *msg, char *arg, int err_code);

/* CLEANUP */
int		free_img(t_img *data);

#endif
