/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:25:30 by tfregni           #+#    #+#             */
/*   Updated: 2023/07/31 20:20:05 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

/**
 * ray: p = a + bt
 * 	p: a point on the ray
 * 	a: the origin (camera.pos)
 *	b: direction
 *	t: distance along the ray
 * plane: (p - p0)·n = 0
 * 	p0: given point on the plane (pl.pos)
 * 	p: an arbitrary point on the plane
 * 	n: the normal vector
 * The vector between p and p0 is the difference between them
 * This vector lies on the plane and therefore it's perpendicular
 * to the normal. The dot product of perpendicular vectors is 0.
 * If I substitute the ray equation into the plane equation to
 * look for a point that belongs to both
 * (a + bt - p0)·n = 0 which solved for t is
 * ((p0 - a) · n) / b · n
*/
// int	intersect_plane(t_scene *scene, t_ray ray, float *t, int i)
// {
// 	float	denominator;
// 	float	numerator;

// 	denominator = vect_dot(ray.direction, vect_norm(scene->shape[i].pl.rotation));
// 	if (denominator > 1e-6)
// 	{
// 		numerator = vect_dot(vect_sub(scene->shape[i].pl.pos, scene->camera.pos), vect_norm(scene->shape[i].pl.rotation));
// 		*t = numerator / denominator;
// 		return (1);
// 	}
// 	return (0);
// }

/*returns 0 or not depending if the ray hits the plane
!!! important !!! pass in normalized vectors*/
int	intersect_plane(t_scene *scene, t_ray ray, float *t, int i)
{
	t_vector p0 = scene->shape[i].pl.pos;
	t_vector n = scene->shape[i].pl.rotation;
	t_vector l0 = ray.origin;
	t_vector l = ray.direction;
	float denom = vect_dot(n, l);
	printf("Hello\n");
	if (denom > 1e-6)
	{
		t_vector p0l0 = vect_sub(p0, l0);
		*t = vect_dot(p0l0, n) / denom;
		printf("Plane intersect\n");
		return (*t >= 0);
	}
	return (0);
}

t_vec3	pl_normal(t_point3 hit, t_point3 center)
{
	t_vec3	normal;

	normal = vec3_unit(vec3_sub(hit, center));
	return (normal);
}

bool	pl_hit_record(double t, t_shape *shape, t_hit_record *rec, t_ray ray)
{
	if (t > 0.000001f && t < rec->t)
	{
		rec->t = t;
		rec->p = ray_at(ray, t);
		rec->normal = shape->rotation; //? maybe this should just be pl.rotation
		rec->color = shape->color;
		return (true);
	}
	return (false);
}

bool	pl_hit(t_shape *shape, t_ray r, t_hit_record *rec)
{
	t_vector p0 = shape->pl.pos;
	t_vector n = vect_norm(shape->rotation);
	t_vector l0 = r.origin;
	t_vector l = vect_norm(r.direction);
	float denom = vect_dot(n, l);
	if (denom > 1e-6)
	{
		t_vector p0l0 = vect_sub(p0, l0);
		return (pl_hit_record((vect_dot(p0l0, n) / denom), shape, rec, r));
	}
	return (false);
}
