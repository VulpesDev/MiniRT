/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:22:05 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/17 16:18:43 by tfregni          ###   ########.fr       */
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

int	cast_shadow(t_scene *scene, t_ray ray)
{
	int		i;
	float	t;

	i = scene->shape_count - 1;
	while (i >= 0)
	{
		if (scene->shape[i].intersect(scene, ray, &t, i) && t > 0.000001f && t < 1)
			return (1);
		i--;
	}
	return (0);
}

/**
 * @param n: normal vector
 * @param p: hit point
 * @returns	a float expressing the light intensity on the point
*/
float	diffuse_reflection(t_scene *scene, t_vector n, t_vector p)
{
	t_vector	l;
	float		n_dot_l;
	float		light;
	float		len_l;
	t_ray		ray;

	l = vect_sub(p, scene->light.pos);
	ray = (t_ray){p, vect_inverse(l)};
	if (cast_shadow(scene, ray))
		return (0.1f);
	n_dot_l = vect_dot(n, l);
	len_l = vect_mag(l);
	if (len_l == 0)
		return (1.0f);
	light = ft_fmax((scene->light.brightness * n_dot_l / len_l), 0.0f);
	return (light);
}

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
*/
t_vec3	sp_normal(t_point3 hit, t_point3 center)
{
	t_vec3	normal;

	normal = vec3_unit(vec3_sub(hit, center));
	return (normal);
}

bool	sp_hit_record(double t, t_shape *shape, t_hit_record *rec, t_ray ray)
{
	if (t > 0.000001f && t < rec->t)
	{
		rec->t = t;
		rec->p = ray_at(ray, t);
		rec->normal = sp_normal(rec->p, shape->sp.pos);
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

	(void) rec;
	oc = vec3_sub(r.origin, shape->sp.pos);
	a = vec3_dot(r.direction, r.direction);
	b = 2.0 * vec3_dot(oc, r.direction);
	c = vec3_dot(oc, oc) - pow(shape->sp.diameter / 2, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	return (sp_hit_record((-b - sqrt(discriminant)) / (2.0 * a), shape, rec, r));
}

