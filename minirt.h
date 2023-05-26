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
	float	lighting_ratio;
	int		trgb;
}				t_ambient;

typedef struct s_camera
{
	t_point		view;
	t_vector	orientation;
	uint8_t		fov;
}				t_camera;

typedef struct s_light
{
	t_point		point;
	float		brightness;
	int			trgb;
}				t_light;

typedef struct s_sphere
{
	t_point		center;
	float		diameter;
	int			trgb;
}				t_sphere;

typedef struct s_plane
{
	t_point		point;
	t_vector	vector;
	int			trgb;
}				t_plane;

typedef struct s_cylinder
{
	t_point		center;
	t_vector	axis;
	float		diameter;
	float		height;
	int			trgb;
}				t_cylinder;


/* PARSE */
int		parse_args(char *filename);

/* GRAPHIC */
int		create_trgb(int t, int r, int g, int b);

/* ERROR HANDLING*/
t_err	ft_error(char *msg, char *arg, int err_code);

#endif
