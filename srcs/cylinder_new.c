/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:21:29 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/09 20:34:18 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "vec3.h"
#include "minirt.h"

float	cy_calc_discriminant(t_scene *scene, t_ray ray, float *t, int i)
{
	const t_vec3	oc = vec3_sub(ray.origin, scene->shape[i].cy.top);
	const float		a = vec3_dot(ray.direction, ray.direction);
	const float		b = 2 * (vec3_dot(ray.direction, oc)
			- vec3_dot(ray.direction, scene->shape[i].rotation)
			* vec3_dot(oc, scene->shape[i].rotation));
	const float		c = vec3_dot(oc, oc) - pow(vec3_dot(oc,
				scene->shape[i].rotation), 2)
		- pow(scene->shape[i].cy.height / 2, 2);
	const float		discriminant = b * b - (4.0f * a * c);

	if (discriminant >= 0)
		*t = (-b - sqrt(discriminant)) / (2.0f * a);
	return (discriminant);
}

bool	cy_hit_record(double t, t_shape *shape, t_hit_record *rec, t_ray ray)
{
	if (t > EPSILON && t < rec->t)
	{
		rec->t = t;
		rec->p = ray_at(ray, t);
		rec->shape = shape;
		rec->normal = vec3_unit(vec3_sub(rec->p, vec3_sub(shape->cy.center,
						vec3_mult(shape->rotation, shape->cy.height / 2))));
		rec->color = shape->color;
		return (true);
	}
	return (false);
}

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

bool	cy_hit(t_shape *shape, t_ray r, t_hit_record *rec)
{
	const t_vec3	oc = vec3_sub(ray.origin, scene->shape[i].cy.top);
	const float		a = vec3_dot(ray.direction, ray.direction);
	const float		b = 2 * (vec3_dot(ray.direction, oc)
			- vec3_dot(ray.direction, scene->shape[i].rotation)
			* vec3_dot(oc, scene->shape[i].rotation));
	const float		c = vec3_dot(oc, oc) - pow(vec3_dot(oc,
				scene->shape[i].rotation), 2)
		- pow(scene->shape[i].cy.height / 2, 2);
	const float		discriminant = b * b - (4.0f * a * c);

	if (discriminant < 0)
		return (false);
	return (cy_hit_record((-b - sqrt(discriminant)) / (2.0f * a), shape, rec,
			ray));
}

void	cylinder_setup(t_shape *cy)
{
	t_vec3	up_vec;
	t_vec3	down_vec;

	up_vec = vec3_div(vec3_mult(cy->cy.rotation, cy->cy.height), 2);
	down_vec = vec3_inv(up_vec);
	cy->cy.top = (t_point_3d){cy->cy.center.x + up_vec.x,
		cy->cy.center.y + up_vec.y,
		cy->cy.center.z + up_vec.z};
	cy->cy.top = (t_point_3d){cy->cy.center.x + down_vec.x,
		cy->cy.center.y + down_vec.y,
		cy->cy.center.z + down_vec.z};
	printf("cyl_top: ");
	vec3_print(cy->cy.top);
	printf("cyl_bot: ");
	vec3_print(cy->cy.bot);
}

/* Step 1: Transform the ray and cylinder to a local coordinate system
You will need to apply a transformation matrix based on the cylinder's
center and rotation. This transforms the ray and cylinder into a local
space where the cylinder's axis aligns with the z-axis.
Step 2: Solve for ray-cylinder intersection in local coordinates
You can use the simplified cylinder equation (circular cross-section):
(x^2 + y^2 - r^2) = 0, where r is the radius (diameter / 2). */
int	intersect_cylinder(t_scene *scene, t_ray ray, float *t, int i)
{
	if (cy_calc_discriminant(scene, ray, t, i) < 0)
		return (0);
	return (1);
}
