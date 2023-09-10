/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_body.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:32:49 by tvasilev          #+#    #+#             */
/*   Updated: 2023/09/10 16:34:32 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

bool	cy_hit_record(double tm[][3], t_shape *s, t_hit_record *rec, t_ray ray)
{
	if (tm[0][0] > 0.000001f && tm[0][0] < rec->t)
	{
		rec->t = tm[0][0];
		rec->p = ray_at(ray, tm[0][0]);
		rec->normal = vec3_unit(vec3_sub(rec->p, vec3_sub
					(s->cy.center, vec3_mult(s->rotation, tm[1][0]))));
		rec->color = s->color;
		return (true);
	}
	return (false);
}

bool	cy_hit_body(t_shape *shape, t_ray r, t_hit_record *rec)
{
	const double	a = vec3_dot(vec3_cross(r.direction, shape->rotation),
			vec3_cross(r.direction, shape->rotation));
	const double	b = 2 * vec3_dot(vec3_cross(r.direction, shape->rotation),
			vec3_cross(vec3_sub(r.origin, shape->cy.center), shape->rotation));
	const double	c = vec3_dot(vec3_cross(
				vec3_sub(r.origin, shape->cy.center), shape->rotation),
			vec3_cross(vec3_sub(r.origin, shape->cy.center),
				shape->rotation)) - ((shape->cy.diameter / 2)
			* (shape->cy.diameter / 2));
	const double	discriminant = b * b - 4 * a * c;
	double			tm[2][3];

	if (discriminant < 0)
		return (false);
	calculate_t(tm[0], a, b, discriminant);
	calculate_m(tm, r.direction, shape->rotation,
		vec3_sub(r.origin, shape->cy.center));
	determine_t_m(tm[0], tm[1], shape->cy.height);
	if (!tm[0] && !tm[1])
		return (false);
	return (cy_hit_record(tm, shape, rec, r));
}

int	intersect_body(t_scene *scene, t_ray r, float *t, int i)
{
	const double	a = vec3_dot(vec3_cross(r.direction,
				scene->shape[i].rotation),
			vec3_cross(r.direction, scene->shape[i].rotation));
	const double	b = 2 * vec3_dot(vec3_cross(r.direction,
				scene->shape[i].rotation), vec3_cross(vec3_sub(r.origin,
					scene->shape[i].cy.center), scene->shape[i].rotation));
	const double	c = vec3_dot(vec3_cross(
				vec3_sub(r.origin, scene->shape[i].cy.center),
				scene->shape[i].rotation),
			vec3_cross(vec3_sub(r.origin, scene->shape[i].cy.center),
				scene->shape[i].rotation)) - ((scene->shape[i].cy.diameter / 2)
			* (scene->shape[i].cy.diameter / 2));
	const double	discriminant = b * b - 4 * a * c;
	double			tm[2][3];

	if (discriminant < 0)
		return (false);
	calculate_t(tm[0], a, b, discriminant);
	calculate_m(tm, r.direction, scene->shape[i].rotation,
		vec3_sub(r.origin, scene->shape[i].cy.center));
	determine_t_m(tm[0], tm[1], scene->shape[i].cy.height);
	if (!tm[0] && !tm[1])
		return (false);
	*t = tm[0][0];
	return (discriminant);
}