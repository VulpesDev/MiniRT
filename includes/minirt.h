/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:43:46 by tfregni           #+#    #+#             */
/*   Updated: 2023/08/27 16:15:03 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"
# include "keys.h"
# include "matrix_math.h"
# include "camera.h"
# include "hittable.h"
# define SPACE "\t\n\f\r\v "
# define MAX_SOLID 5
# define CANV_MIN_X -1.0f
# define CANV_MAX_X 1.0f
# define CANV_MIN_Y -1.0f
# define CANV_DIST 1.0f
# define CAM_PACE 0.1
# define LIGHT_PACE 0.3
# define ORIENT_PACE 0.01
# define RAY_LEN 50
# define BOUNCES 2
# define ZNEAR CANV_DIST
# define ZFAR RAY_LEN
# define EPSILON 1e-6

typedef struct s_ray	t_ray;
typedef int				(*t_hit_func)(t_scene *scene, t_ray ray, \
							float *t, int i);
typedef bool			(*t_hit)(t_shape *shape, t_ray ray, t_hit_record *rec);
typedef t_vec3			(*t_normal)(t_shape *shape, t_point3 hit);

typedef enum e_err
{
	SUCCESS,
	MEM_FAIL,
	ARG_REQUIRED,
	FILE_EXTENSION,
	INVALID_FILE,
	INVALID_ELEMENT,
	INVALID_DUP,
	MISS_UNIQUE,
}			t_err;

enum e_unique_el
{
	AMBIENT,
	CAMERA,
	LIGHT,
};

typedef enum e_bool
{
	FALSE,
	TRUE,
}			t_bool;

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

typedef struct s_light
{
	t_point_3d		pos;
	float			brightness;
	int				trgb;
}					t_light;

typedef struct s_shape
{
	union {
		t_sphere	sp;
		t_plane		pl;
		t_cylinder	cy;
	};
	char			*type;
	t_vector		rotation;
	t_hit_func		intersect;
	t_hit			hit;
	t_normal		normal;
	t_matrix_trans	transform;
	int				trgb;
	t_color			color;
}			t_shape;

typedef struct s_scene
{
	t_img		*img;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_shape		*shape;
	int			shape_count;
}				t_scene;

/* PARSE */
int		parse_args(t_scene *scene, char *filename);
t_err	validate_ambient(t_scene *scene, char **el);
t_err	validate_camera(t_scene *scene, char **el);
t_err	validate_light(t_scene *scene, char **el);
int		validate_sphere(t_scene *scene, char **el);
int		validate_plane(t_scene *scene, char **el);
int		validate_cylinder(t_scene *scene, char **el);
void	set_camera_canvas(t_camera *c);
void	set_transform_mx(t_camera *c);

/* PARSE UTILS */
int		validate_3d_range(t_point_3d point, float min, float max);
t_err	extract_xyz(char *xyz, t_point_3d *point);
t_err	extract_rgb(char *rgb, int *ret);

/* GRAPHIC */
int		create_trgb(int t, int r, int g, int b);
t_color	convert_color(int trgb);
int		mlx_manage(t_scene *scene);
void	my_mlx_pixel_put_d(t_img *data, int x, int y, int color);
t_err	init_img(t_scene *scene);

/* RENDER */
t_err	render_scene(t_scene *scene);
void	draw(t_scene *scene);
int		intersect_element(t_scene *scene, t_ray ray, int *color, float *min_t);

/* SHADE */
float	diffuse_reflection(t_scene *scene, t_vector n, t_vector p);
int		cast_shadow(t_scene *scene, t_ray ray);

/* ERROR HANDLING*/
t_err	ft_error(char *msg, char *arg, int err_code, t_scene *scene);
t_err	ft_warning(char *msg, char *arg, int err_code);

/* CLEANUP */
int		free_img(t_img *data);
void	free_scene(t_scene **scene);

/* DEBUG */
void	print_4x4(t_matrix_trans m);

#endif
