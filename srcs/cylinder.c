/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:21:29 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/17 13:52:18 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "vec3.h"
#include "minirt.h"

/**
 * @brief Calculates the discriminant of the quadratic equation
 * @param oc: vector from the center of the top cap to the ray origin
*/
double	cy_calc_discriminant(t_scene *scene, t_ray ray, double *t, int i)
{
	const t_vec3	oc = vec3_sub(ray.origin, scene->shape[i].cy.top);
	const double	a = vec3_dot(ray.direction, ray.direction)
		- pow(vec3_dot(ray.direction, scene->shape[i].cy.vec), 2);
	const double	b = 2 * (vec3_dot(ray.direction, oc)
			- vec3_dot(ray.direction, scene->shape[i].cy.vec)
			* vec3_dot(oc, scene->shape[i].cy.vec));
	const double	c = vec3_dot(oc, oc) - pow(vec3_dot(oc,
				scene->shape[i].cy.vec), 2)
		- pow(scene->shape[i].cy.diameter / 2, 2);
	const double	discriminant = b * b - (4.0f * a * c);

	if (discriminant >= 0)
		*t = (-b - sqrt(discriminant)) / (2.0f * a);
	return (discriminant);
}

/**
 * @explanation: to find the normal I find the distance along the center vector at the
 * level of the hit point: double center_t = vec3_dot(hit_vec, shape->cy.vec);
 * Then the coordinate of the point on the center vector is:
 * rec->normal = vec3_sum(shape->cy.top, vec3_mult(shape->cy.vec, center_t));
 * Finally, the normal is the normalized vector from the hit point to the point I found
 * along the center vector.
*/
bool	cy_hit_record(double t, t_shape *shape, t_hit_record *rec, t_ray ray)
{
	t_vec3	hit_vec;
	double	center_t;

	hit_vec = vec3_sub(ray_at(ray, t), shape->cy.top);
	if (t > EPSILON && t < rec->t && vec3_dot(hit_vec, shape->cy.vec) >= 0
		&& (vec3_dot(hit_vec, shape->cy.vec) <= shape->cy.height))
	{
		rec->t = t;
		rec->p = ray_at(ray, t);
		rec->shape = shape;
		center_t = vec3_dot(hit_vec, shape->cy.vec);
		rec->normal = vec3_sum(shape->cy.top, \
			vec3_mult(shape->cy.vec, center_t));
		rec->normal = vec3_unit(vec3_sub(rec->p, rec->normal));
		// rec->normal = vec3_sub(shape->cy.center, rec->p);
		// rec->normal = vec3_unit(vec3_cross(rec->normal, shape->cy.rotation));
		rec->color = shape->color;
		return (true);
	}
	return (false);
}

bool	cy_hit_body(t_shape *shape, t_ray ray, t_hit_record *rec)
{
	const t_vec3	oc = vec3_sub(ray.origin, shape->cy.top);
	const double	a = vec3_dot(ray.direction, ray.direction)
		- pow(vec3_dot(ray.direction, shape->cy.vec), 2);
	const double	b = 2 * (vec3_dot(ray.direction, oc)
			- vec3_dot(ray.direction, shape->cy.vec)
			* vec3_dot(oc, shape->cy.vec));
	const double	c = vec3_dot(oc, oc) - pow(vec3_dot(oc,
				shape->cy.vec), 2)
		- pow(shape->cy.diameter / 2, 2);
	const double	discriminant = b * b - (4.0f * a * c);

	if (discriminant < 0)
		return (false);
	return (cy_hit_record((-b - sqrt(discriminant)) / (2.0f * a), shape, rec,
			ray));
}

bool	cy_hit(t_shape *shape, t_ray ray, t_hit_record *rec)
{
	if (cy_hit_body(shape, ray, rec)
		|| cy_hit_disk(shape, ray, rec))
		return (true);
	return (false);
}

void	cylinder_setup(t_shape *cy)
{
	t_vec3	vec1;
	t_vec3	vec2;

	if (vec3_len_squared(cy->cy.rotation) == 0)
		cy->cy.rotation = vec3(0, 1, 0);
	cy->cy.rotation = vec3_unit(cy->cy.rotation);
	cy->cy.vec = vec3_inv(cy->cy.rotation);
	vec1 = vec3_mult(cy->cy.rotation, cy->cy.height / 2);
	vec2 = vec3_mult(cy->cy.vec, cy->cy.height);
	cy->cy.top = vec3_sum(cy->cy.center, vec1);
	cy->cy.bot = vec3_sum(cy->cy.top, vec2);
	// printf("cyl_top: ");
	// vec3_print(cy->cy.top);
	// printf("cyl_bot: ");
	// vec3_print(cy->cy.bot);
}
