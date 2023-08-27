/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:26:52 by tfregni           #+#    #+#             */
/*   Updated: 2023/08/27 18:40:22 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H
# include <stdbool.h>
# include "vec3.h"
# include "ray.h"

typedef struct s_scene	t_scene;
typedef struct s_shape	t_shape;
typedef struct s_sphere
{
	t_point_3d		pos;
	float			diameter;
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

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		t;
	int			trgb;
	t_color		color;
}				t_hit_record;

/* SPHERE */
int		intersect_sphere(t_scene *scene, t_ray ray, float *t, int i);
float	sp_light_coeff(t_scene *scene, float t, t_ray ray, int i);
float	sp_calc_discriminant(t_scene *scene, t_ray ray, \
							float *t, int i);
float	sp_calc_hit_point(float discriminant, float a, float b);
bool	sp_hit(t_shape *shape, t_ray r, t_hit_record *rec);
t_vec3	sp_normal(t_shape *sp, t_point3 hit);

/* PLANE */
int		intersect_plane(t_scene *scene, t_ray ray, float *t, int i);
bool	pl_hit(t_shape *shape, t_ray r, t_hit_record *rec);
t_vec3	pl_normal(t_shape *pl, t_point3 hit);

/* CYLINDER */
int		intersect_cylinder(t_scene *scene, t_ray ray, float *t, int i);
bool	cy_hit(t_shape *shape, t_ray r, t_hit_record *rec);

#endif
