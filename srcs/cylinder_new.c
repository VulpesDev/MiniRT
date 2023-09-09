/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:21:29 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/09 23:24:36 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "vec3.h"
#include "minirt.h"

float	cy_calc_discriminant(t_scene *scene, t_ray ray, float *t, int i)
{
	const t_vec3	oc = vec3_sub(ray.origin, scene->shape[i].cy.top);
	const float		a = vec3_dot(ray.direction, ray.direction)
		- pow(vec3_dot(ray.direction, scene->shape[i].cy.vec), 2);
	const float		b = 2 * (vec3_dot(ray.direction, oc)
			- vec3_dot(ray.direction, scene->shape[i].cy.vec)
			* vec3_dot(oc, scene->shape[i].cy.vec));
	const float		c = vec3_dot(oc, oc) - pow(vec3_dot(oc,
				scene->shape[i].cy.vec), 2)
		- pow(scene->shape[i].cy.height / 2, 2);
	const float		discriminant = b * b - (4.0f * a * c);

	if (discriminant >= 0)
		*t = (-b - sqrt(discriminant)) / (2.0f * a);
	return (discriminant);
}

bool	cy_hit_cap_record(double t, t_shape *shape, t_hit_record *rec, t_ray ray)
{
	if (t > EPSILON && t < rec->t)
	{
		rec->t = t;
		rec->p = ray_at(ray, t);
		rec->color = shape->color;
		rec->shape = shape;
		rec->normal = shape->rotation;
		return (true);
	}
	return (false);
}


bool	cy_hit_cap(t_shape *shape, t_ray ray, t_hit_record *rec)
{
	t_shape			cap_top;
	t_shape			cap_bot;
	t_hit_record	to_plane;
	double			radius;
	t_point_3d		t;

	to_plane = *rec;
	cap_top.pl.pos = shape->cy.top;
	cap_top.rotation = shape->rotation;
	cap_bot.pl.pos = shape->cy.bot;
	cap_bot.rotation = shape->cy.vec;
	if (!pl_hit(&cap_top, ray, &to_plane) && !pl_hit(&cap_bot, ray, &to_plane))
		return (false);
	t = ray_at(ray, to_plane.t);
	radius = vec3_len(vec3_sub(shape->cy.top, t));
	if (!(radius <= shape->cy.diameter / 2))
		return (false);
	return (cy_hit_cap_record(to_plane.t, shape, rec, ray));
}

bool	cy_hit_record(double t, t_shape *shape, t_hit_record *rec, t_ray ray)
{
	t_vec3	hit_vec;

	hit_vec = vec3_sub(ray_at(ray, t), shape->cy.top);
	if (t > EPSILON && t < rec->t && vec3_dot(hit_vec, shape->cy.vec) >= 0
		&& (vec3_dot(hit_vec, shape->cy.vec) <= shape->cy.height))
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

bool	cy_hit_body(t_shape *shape, t_ray ray, t_hit_record *rec)
{
	const t_vec3	oc = vec3_sub(ray.origin, shape->cy.top);
	const float		a = vec3_dot(ray.direction, ray.direction)
		- pow(vec3_dot(ray.direction, shape->cy.vec), 2);
	const float		b = 2 * (vec3_dot(ray.direction, oc)
			- vec3_dot(ray.direction, shape->cy.vec)
			* vec3_dot(oc, shape->cy.vec));
	const float		c = vec3_dot(oc, oc) - pow(vec3_dot(oc,
				shape->cy.vec), 2)
		- pow(shape->cy.height / 2, 2);
	const float		discriminant = b * b - (4.0f * a * c);

	if (discriminant < 0)
		return (false);
	return (cy_hit_record((-b - sqrt(discriminant)) / (2.0f * a), shape, rec,
			ray));
}

bool	cy_hit(t_shape *shape, t_ray ray, t_hit_record *rec)
{
	if (cy_hit_body(shape, ray, rec) || cy_hit_cap(shape, ray, rec))
		return (true);
	return (false);
}

void	cylinder_setup(t_shape *cy)
{
	t_vec3	vec1;
	t_vec3	vec2;

	cy->rotation = vec3_unit(cy->rotation);
	vec1 = vec3_mult(cy->rotation, cy->cy.height / 2);
	cy->cy.vec = vec3_inv(cy->rotation);
	vec2 = vec3_mult(cy->cy.vec, cy->cy.height);

	cy->cy.top = (t_point_3d){cy->cy.center.x + vec1.x,
		cy->cy.center.y + vec1.y,
		cy->cy.center.z + vec1.z};
	cy->cy.bot = (t_point_3d){cy->cy.top.x + vec2.x,
		cy->cy.top.y + vec2.y,
		cy->cy.top.z + vec2.z};
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
