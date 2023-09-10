/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:56:18 by tvasilev          #+#    #+#             */
/*   Updated: 2023/09/10 14:57:46 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

bool	cy_hit_cap_record(double t, t_shape *shape,
	t_hit_record *rec, t_ray ray)
{
	if (t > 0.000001f && t < rec->t)
	{
		rec->t = t;
		rec->p = ray_at(ray, t);
		rec->normal = vec3_unit(vec3_sub(rec->p, shape->cy.center));
		rec->normal = vec3_cross(shape->rotation, rec->normal);
		rec->color = shape->color;
		return (true);
	}
	return (false);
}

bool	cap(t_shape *shape, double t, t_ray ray, t_vector Ce, t_hit_record *rec)
{
	t_vector	v;
	t_vector	p;

	p = ray_at(ray, t);
	v = vec3_sub(p, Ce);
	if (vec3_len(v) <= shape->cy.diameter / 2)
		return (cy_hit_cap_record(t, shape, rec, ray));
	return (false);
}

/**
 * @brief Checks if the ray hits the top cap of the cylinder
 * @param p0: top cap center
 * @param n: top cap normal
 * @param l0: ray origin
 * @param l: ray direction
 * @param p0l0: vector from ray origin to top cap center
*/
bool	hit_plane_top(t_shape *shape, t_ray r, t_hit_record *rec)
{
	const t_vector	p0 = vec3_sum(shape->cy.center, \
		vec3_mult(shape->rotation, shape->cy.height));
	const t_vector	n = vec3_inv(vec3_unit(shape->rotation));
	const t_vector	l0 = r.origin;
	const t_vector	l = vec3_unit(r.direction);
	const float		denom = vec3_dot(n, l);

	if (denom > 1e-6)
		return (cap(shape, vec3_dot(vec3_sub(p0, l0), n) / denom, r, p0, rec));
	return (false);
}

bool	hit_plane_bot(t_shape *shape, t_ray r, t_hit_record *rec)
{
	const t_vector	p0 = shape->cy.center;
	const t_vector	n = vec3_unit(shape->rotation);
	const t_vector	l0 = r.origin;
	const t_vector	l = vec3_unit(r.direction);
	const float		denom = vec3_dot(n, l);

	if (denom > 1e-6)
		return (cap(shape, vec3_dot(vec3_sub(p0, l0), n) / denom, r, p0, rec));
	return (false);
}