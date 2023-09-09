/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:22:05 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/09 10:36:20 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"

/**
 * It returns the discriminant. If it's >=0 it assigns to t the value of
 * the closest hit point
*/
float	sp_calc_discriminant(t_scene *scene, t_ray ray, \
							float *t, int i)
{
	float			a;
	float			b;
	float			c;
	t_point_3d		transl;
	float			discriminant;

	a = vec3_dot(ray.direction, ray.direction);
	transl = vec3_sub(ray.origin, scene->shape[i].sp.pos);
	b = 2.0f * vec3_dot(transl, ray.direction);
	c = vec3_dot(transl, transl) - pow((scene->shape[i].sp.diameter / 2), 2);
	discriminant = b * b - (4.0f * a * c);
	if (discriminant >= 0)
		*t = (-b - sqrt(discriminant)) / (2.0f * a);
	return (discriminant);
}

/**
 * @returns 1 if the ray hits the sphere, 0 otherwise
*/
int	intersect_sphere(t_scene *scene, t_ray ray, float *t, int i)
{
	if (sp_calc_discriminant(scene, ray, t, i) < 0)
		return (0);
	return (1);
}

/**
 * @param hit: hit point
 * @param center: center of the sphere
 * @returns a normalized vector perpendicular to the surface of the sphere
 * Since the direction is hit - center which is always radius long,
 * we can get the normalized by dividing by radius. This saves an expensive
 * sqrt.
 * t_vec3			(*t_normal)(t_shape *shape, t_point3 hit);
*/
t_vec3	sp_normal(t_shape *sp, t_point3 hit)
{
	t_vec3		normal;
	t_point3	center;

	center = sp->sp.pos;
	normal = vec3_div(vec3_sub(hit, center), sp->sp.diameter / 2);
	return (normal);
}

/**
 * @param t: hit distance
 * @param rec: t_hit_record if there's a hit the value gets updated
 * @returns true if there's a hit, false otherwise
*/
bool	sp_hit_record(double t, t_shape *shape, t_hit_record *rec, t_ray ray)
{
	if (t > EPSILON && t < rec->t)
	{
		rec->t = t;
		rec->p = ray_at(ray, t);
		rec->shape = shape;
		rec->normal = sp_normal(shape, rec->p);
		rec->color = shape->color;
		return (true);
	}
	return (false);
}

/**
 * typedef bool			(*t_hit)(t_shape *shape, t_ray ray, t_hit_record *rec);
*/
bool	sp_hit(t_shape *shape, t_ray r, t_hit_record *rec)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_sub(r.origin, shape->sp.pos);
	a = vec3_dot(r.direction, r.direction);
	b = 2.0 * vec3_dot(oc, r.direction);
	c = vec3_dot(oc, oc) - pow(shape->sp.diameter / 2, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	return (sp_hit_record((-b - \
		sqrt(discriminant)) / (2.0 * a), shape, rec, r));
}
