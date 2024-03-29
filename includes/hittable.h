/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:26:52 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/12 18:52:46 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H
# include <stdbool.h>
# include "vec3.h"
# include "ray.h"

typedef struct s_scene		t_scene;
typedef struct s_shape		t_shape;
typedef struct s_hit_record	t_hit_record;
typedef int					(*t_hit_func)(t_scene *scene, t_ray ray, \
								double *t, int i);
typedef bool				(*t_hit)(t_shape *shape, t_ray ray, \
								t_hit_record *rec);
typedef bool				(*t_inside)(t_shape *shape, t_point3 cam);
typedef t_vec3				(*t_normal)(t_shape *shape, t_point3 hit);

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
	t_point_3d		top;
	t_point_3d		bot;
	t_vector		rotation;
	t_vector		vec;
	float			diameter;
	float			height;
	int				trgb;
}					t_cylinder;

typedef struct s_shape
{
	union {
		t_sphere	sp;
		t_plane		pl;
		t_cylinder	cy;
	};
	t_hit			hit;
	t_normal		normal;
	t_inside		is_inside;
	int				trgb;
	t_color			color;
}			t_shape;

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		t;
	t_shape		*shape;
	int			trgb;
	t_color		color;
}				t_hit_record;

t_shape	*check_inside(t_scene *s);

/* SPHERE */
double	sp_calc_discriminant(t_scene *scene, t_ray ray, \
							double *t, int i);
bool	sp_hit(t_shape *shape, t_ray r, t_hit_record *rec);
t_vec3	sp_normal(t_shape *sp, t_point3 hit);
bool	sp_is_inside(t_shape *s, t_point_3d cam);

/* PLANE */
bool	pl_hit(t_shape *shape, t_ray r, t_hit_record *rec);
t_vec3	pl_normal(t_shape *pl, t_point3 hit);
bool	pl_is_inside(t_shape *s, t_point_3d cam);

/* CYLINDER */
void	cylinder_setup(t_shape *cy);
bool	cy_hit(t_shape *shape, t_ray r, t_hit_record *rec);
bool	cy_hit_disk(t_shape *shape, t_ray ray, t_hit_record *rec);
bool	cy_hit_record(double t, t_shape *shape, t_hit_record *rec, t_ray ray);
bool	cy_hit_disk_record(double t, t_shape *shape,
			t_hit_record *rec, t_ray ray);
bool	cy_is_inside(t_shape *s, t_point_3d cam);

#endif
