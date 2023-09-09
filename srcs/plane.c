/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:25:30 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/09 23:29:36 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"

/*returns 0 or not depending if the ray hits the plane
!!! important !!! pass in normalized vectors*/
int	intersect_plane(t_scene *scene, t_ray ray, float *t, int i)
{
	const t_vector	p0 = scene->shape[i].pl.pos;
	const t_vector	n = scene->shape[i].pl.rotation;
	const t_vector	l0 = ray.origin;
	const t_vector	l = ray.direction;
	float			denom;

	denom = vec3_dot(n, l);
	if (denom > EPSILON)
	{
		*t = vec3_dot(vec3_sub(p0, l0), n) / denom;
		return (*t >= EPSILON);
	}
	return (0);
}

/**
 * @param valid: 1 if the normal is pointing towards the camera, -1 otherwise
 * @returns the normal vector of the plane. It multiplies by the valid param
 * so that the normal is negative if the camera is in the back of the plane
*/
t_vec3	pl_normal(t_shape *pl, t_point3 hit)
{
	(void) hit;
	return (vec3_mult(pl->pl.rotation, -pl->pl.valid));
}

bool	pl_hit_record(double t, t_shape *shape, t_hit_record *rec, t_ray ray)
{
	if (t > EPSILON && t < rec->t)
	{
		rec->t = t;
		rec->p = ray_at(ray, t);
		rec->normal = pl_normal(shape, rec->p);
		rec->color = shape->color;
		return (true);
	}
	return (false);
}

double	ft_abs_double(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

/**
 * The absolute value of the denom allows to render alse the dark side
 * of the plane. If the denom is negative we're in the back of the plane
*/
bool	pl_hit(t_shape *shape, t_ray r, t_hit_record *rec)
{
	t_vector		n;
	float			denom;
	const t_vector	p0 = shape->pl.pos;
	const t_vector	l0 = r.origin;
	const t_vector	l = vec3_unit(r.direction);

	if (vec3_len_squared(shape->pl.rotation) == 0)
		n = vec3(0, 0, -1);
	else
		n = vec3_unit(shape->pl.rotation);
	denom = vec3_dot(n, l);
	if (ft_abs_double(denom) > EPSILON)
	{
		if (denom > 0)
			shape->pl.valid = 1;
		else
			shape->pl.valid = -1;
		return (pl_hit_record(((vec3_dot(vec3_sub(p0, l0), n)) / denom), \
		shape, rec, r));
	}
	return (false);
}

