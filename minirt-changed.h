/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:43:46 by tfregni           #+#    #+#             */
/*   Updated: 2023/05/26 21:13:56 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# define SPACE "\t\n\f\r\v "

typedef enum e_err
{
	ARG_REQUIRED = 1,
	FILE_EXTENSION,
	INVALID_FILE,
	INVALID_ELEMENT,
}			t_err;

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

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}			t_point;

typedef t_point	t_vector;

typedef struct s_ambient
{
	float		lighting_ratio;
	t_point		trgb;
}				t_ambient;

typedef struct s_camera
{
	t_point		pos;//I think view is a bit confusing
	t_vector	orientation;
	uint8_t		fov;
}				t_camera;

typedef struct s_light
{
	t_point		pos;//Consistency would be good in my opinion
	float		brightness;
	t_point			trgb;
}				t_light;

typedef struct s_sphere
{
	t_point		pos;
	float		diameter;
	t_point			trgb;
}				t_sphere;

typedef struct s_plane
{
	t_point		pos;
	t_vector	rot;//I think that's menant by the subject by normalized vector for axis/it is weird that it's in range [-1,1] maybe its in radians and not degrees, which would still not make sense 
	int			trgb;
}				t_plane;

typedef struct s_cylinder
{
	t_point		pos;
	t_vector	axis;
	float		rot;
	float		diameter;
	float		height;
	t_point			trgb;
}				t_cylinder;


/* PARSE */
int		parse_args(char *filename);

/* GRAPHIC */
int		create_trgb(int t, int r, int g, int b);

/* ERROR HANDLING*/
t_err	ft_error(char *msg, char *arg, int err_code);

#endif
