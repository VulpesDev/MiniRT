/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_disk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:50:00 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/12 18:51:09 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "vec3.h"
#include "minirt.h"

/**
 * @brief Checks if the ray hits the top or bottom disk of the cylinder
*/
bool	cy_hit_disk(t_shape *shape, t_ray ray, t_hit_record *rec)
{
	const double	t3 = vec3_dot(vec3_sub(shape->cy.top, ray.origin),
			shape->cy.vec) / vec3_dot(ray.direction, shape->cy.vec);
	const double	t4 = vec3_dot(vec3_sub(shape->cy.bot, ray.origin),
			shape->cy.vec) / vec3_dot(ray.direction, shape->cy.vec);
	const t_vec3	v3 = vec3_sub(ray_at(ray, t3), shape->cy.top);
	const t_vec3	v4 = vec3_sub(ray_at(ray, t4), shape->cy.bot);
	bool			hit_disk;

	hit_disk = false;
	if (vec3_dot(v3, v3) <= pow(shape->cy.diameter / 2, 2)
		&& cy_hit_disk_record(t3, shape, rec, ray))
	{
		rec->normal = shape->cy.rotation;
		hit_disk = true;
	}
	if (vec3_dot(v4, v4) <= pow(shape->cy.diameter / 2, 2)
		&& cy_hit_disk_record(t4, shape, rec, ray))
	{
		rec->normal = shape->cy.vec;
		hit_disk = true;
	}
	return (hit_disk);
}


bool	cy_hit_disk_record(double t, t_shape *shape,
		t_hit_record *rec, t_ray ray)
{
	if (t > EPSILON && t < rec->t)
	{
		rec->t = t;
		rec->shape = shape;
		rec->p = ray_at(ray, t);
		rec->color = shape->color;
		rec->trgb = shape->trgb;
		return (true);
	}
	return (false);
}

