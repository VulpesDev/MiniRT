/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:56:18 by tvasilev          #+#    #+#             */
/*   Updated: 2023/09/10 15:25:00 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

bool	intersect_cap(t_shape *shape, double t, t_ray ray, float *tt)
{
	const t_vector	p0 = vec3_sum(shape->cy.center, \
		vec3_mult(shape->rotation, shape->cy.height));
	const t_vector	p = ray_at(ray, t);
	const t_vector	v = vec3_sub(p, p0);

	if (vec3_len(v) <= shape->cy.diameter / 2 && t > 0.000001f)
	{
		*tt = t;
		return (true);
	}
	return (false);
}

bool	hit_cap(t_shape *shape, double t, t_ray ray, t_hit_record *rec)
{
	const t_vector	p0 = vec3_sum(shape->cy.center, \
		vec3_mult(shape->rotation, shape->cy.height));
	const t_vector	p = ray_at(ray, t);
	const t_vector	v = vec3_sub(p, p0);

	if (vec3_len(v) <= shape->cy.diameter / 2 &&
		t > 0.000001f && t < rec->t)
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

/**
 * @brief Checks if the ray hits the top cap of the cylinder
 * @param p0: top cap center
 * @param n: top cap normal
 * @param l0: ray origin
 * @param l: ray direction
 * @param p0l0: vector from ray origin to top cap center
*/
bool	hit_plane_cap(t_shape *shape, t_ray r, t_hit_record *rec, bool top)
{
	t_vector		p0;
	const t_vector	n = vec3_inv(vec3_unit(shape->rotation));
	const t_vector	l0 = r.origin;
	const t_vector	l = vec3_unit(r.direction);
	const float		denom = vec3_dot(n, l);

	if (top)
		p0 = vec3_sum(shape->cy.center, \
			vec3_mult(shape->rotation, shape->cy.height));
	else
		p0 = shape->cy.center;
	if (denom > 1e-6)
		return (hit_cap(shape, vec3_dot(vec3_sub(p0, l0), n) / denom,
				r, rec));
	return (false);
}

bool	intersect_plane_cap(t_shape *shape, t_ray r, float *t, bool top)
{
	t_vector		p0;
	const t_vector	n = vec3_inv(vec3_unit(shape->rotation));
	const t_vector	l0 = r.origin;
	const t_vector	l = vec3_unit(r.direction);
	const float		denom = vec3_dot(n, l);

	if (top)
		p0 = vec3_sum(shape->cy.center, \
			vec3_mult(shape->rotation, shape->cy.height));
	else
		p0 = shape->cy.center;
	if (denom > 1e-6)
		return (intersect_cap(shape,
				vec3_dot(vec3_sub(p0, l0), n) / denom, r, t));
	return (false);
}