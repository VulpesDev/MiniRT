/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:22:05 by tfregni           #+#    #+#             */
/*   Updated: 2023/08/27 18:10:31 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

float	sp_calc_hit_point(float discriminant, float a, float b)
{
	return ((-b - sqrt(discriminant)) / (2.0f * a));
}

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

	a = vect_dot(ray.direction, ray.direction);
	transl = vect_sub(ray.origin, scene->shape[i].sp.pos);
	b = 2.0f * vect_dot(transl, ray.direction);
	c = vect_dot(transl, transl) - pow((scene->shape[i].sp.diameter / 2), 2);
	discriminant = b * b - (4.0f * a * c);
	if (discriminant >= 0)
		*t = sp_calc_hit_point(discriminant, a, b);
	return (discriminant);
}

/**
 * @param t: hit distance
 * @brief: calculates the light intensity on the hit point
*/
float	sp_light_coeff(t_scene *scene, float t, t_ray ray, int i)
{
	t_vector	hit_pos;
	t_vector	normal;
	float		light;

	hit_pos = vect_sum((t_vector)ray.origin, vect_mult(ray.direction, t));
	normal = vect_norm(vect_sub(scene->shape[i].sp.pos, hit_pos));
	light = diffuse_reflection(scene, normal, hit_pos);
	// light = ft_fmax(\
	// 	vect_dot(normal, vect_inverse((vect_norm(scene->light.pos)))), 0.0f);
	return (light);
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
 * @todo	- could be calculated with (hit_point - center) / radius
 * avoiding the sqrt
 * @param hit: hit point
 * @param center: center of the sphere
 * @returns a normalized vector perpendicular to the surface of the sphere
 * t_vec3			(*t_normal)(t_shape *shape, t_point3 hit);
*/
t_vec3	sp_normal(t_shape *sp, t_point3 hit)
{
	t_vec3		normal;
	t_point3	center;

	center = sp->sp.pos;
	normal = vec3_unit(vec3_sub(hit, center));
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
	return (sp_hit_record((-b - sqrt(discriminant)) / (2.0 * a), shape, rec, r));
}

