/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:43:46 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/13 09:39:50 by tfregni          ###   ########.fr       */
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
# define WIDTH 1024
# define HEIGHT 768
# define CANV_MIN_X -1.0f
# define CANV_MAX_X 1.0f
# define CANV_MIN_Y -1.0f
# define CANV_DIST 1
# define CAM_PACE 0.1
# define LIGHT_PACE 0.3
# define RAY_LEN 50
# define BOUNCES 2
# define ZNEAR CANV_DIST
# define ZFAR RAY_LEN

typedef float			t_matrix_trans[4][4];
typedef struct s_scene	t_scene;
typedef struct s_ray	t_ray;
typedef int				(*t_hit_func)(t_scene *scene, t_ray ray, \
							float *t, int i);
typedef struct s_camera	t_camera;

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
}	t_bool;

typedef struct s_matrix
{
	double	matrix[4][4];
	size_t	size;
}	t_matrix;

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

typedef t_point_3d		t_vector;

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
	t_point_2d		top_right;
	t_point_2d		bot_left;
	float			pixel_size;
	t_matrix_trans	m_proj;
	t_matrix		transform;
	t_matrix		inverse;
	t_matrix		transpose;
}					t_camera;

/**
 * @brief The structure of type t_camera contains the necessary information for
 *        camera configuration, rendering and transformation.
 * @param hsize Stores the horizontal size (in pixels).
 * @param vsize Stores the vertical size (in pixels).
 * @param field_of_view This field stores angle that describes how much the
 *                      camera can see. When the field of view is small, the
 *                      view will be "zoomed in", magnifying a smaller area of
 *                      the scene.
 * @param half_width Stores the camera's half hsize value.
 * @param half_height Stores the camera's half vsize value.
 * @param pixel_size Stores the camera's pixel size calculated from half_width
 *                   and hsize values.
 * @param transform Stores the transformation matrix for the camera.
 * @param inverse Stores the inverse matrix for the camera.
 * @param transpose Stores the transpose matrix for the camera.
 */
// typedef struct s_camera
// {
// 	float		hsize;
// 	float		vsize;
// 	float		field_of_view;
// 	float		half_width;
// 	float		half_height;
// 	float		pixel_size;
// 	t_matrix	transform;
// 	t_matrix	inverse;
// 	t_matrix	transpose;
// }	t_camera;

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
	int				valid;
}					t_plane;

typedef struct s_cylinder
{
	t_point_3d		center;
	t_vector		rotation;
	float			diameter;
	float			height;
	int				trgb;
}					t_cylinder;

typedef struct s_ray
{
	t_point_3d	origin;
	t_vector	direction;
}			t_ray;

typedef struct s_shape
{
	union {
		t_sphere	sp;
		t_plane		pl;
		t_cylinder	cy;
	};
	t_vector		rotation;
	t_hit_func		intersect;
	t_matrix_trans	transform;
	int				trgb;
}			t_shape;

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
int		intersect_element(t_scene *scene, t_ray ray, int *color, float *min_t);

/* SPHERE */
int		intersect_sphere(t_scene *scene, t_ray ray, float *t, int i);
float	sp_light_coeff(t_scene *scene, float t, t_ray ray, int i);
float	sp_calc_discriminant(t_scene *scene, t_ray ray, \
							float *t, int i);
float	sp_calc_hit_point(float discriminant, float a, float b);

/* PLANE */
int		intersect_plane(t_scene *scene, t_ray ray, \
						float *t, int i);

/* ERROR HANDLING*/
t_err	ft_error(char *msg, char *arg, int err_code, t_scene *scene);
t_err	ft_warning(char *msg, char *arg, int err_code);

/* CLEANUP */
int		free_img(t_img *data);
void	free_scene(t_scene **scene);

#endif
