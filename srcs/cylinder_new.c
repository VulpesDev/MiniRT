/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:21:29 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/12 16:01:37 by tfregni          ###   ########.fr       */
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

	if (discriminant >= EPSILON)
		*t = (-b - sqrt(discriminant)) / (2.0f * a);
	return (discriminant);
}

bool	cy_hit_disk_record(double t, t_shape *shape,
		t_hit_record *rec, t_ray ray)
{
	if (t >= EPSILON && t < rec->t)
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
		rec->normal = shape->rotation;
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
		rec->normal = vec3_unit(vec3_sub(shape->cy.center, rec->p));
		rec->normal = vec3_cross(rec->normal, shape->rotation);
		rec->color = shape->color;
		return (true);
	}
	return (false);
}

bool	cy_hit_body(t_shape *shape, t_ray ray, t_hit_record *rec)
{
	const t_vec3	oc = vec3_sub(ray.origin, shape->cy.top);
	const double		a = vec3_dot(ray.direction, ray.direction)
		- pow(vec3_dot(ray.direction, shape->cy.vec), 2);
	const double		b = 2 * (vec3_dot(ray.direction, oc)
			- vec3_dot(ray.direction, shape->cy.vec)
			* vec3_dot(oc, shape->cy.vec));
	const double		c = vec3_dot(oc, oc) - pow(vec3_dot(oc,
				shape->cy.vec), 2)
		- pow(shape->cy.diameter / 2, 2);
	const double		discriminant = b * b - (4.0f * a * c);

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

	if (vec3_len_squared(cy->rotation) == 0)
		cy->rotation = vec3(0, 1, 0);
	cy->rotation = vec3_unit(cy->rotation);
	cy->cy.vec = vec3_inv(cy->rotation);
	vec1 = vec3_mult(cy->rotation, cy->cy.height / 2);
	vec2 = vec3_mult(cy->cy.vec, cy->cy.height);

	cy->cy.top = vec3_sum(cy->cy.center, vec1);
	cy->cy.bot = vec3_sum(cy->cy.top, vec2);
	printf("cyl_top: ");
	vec3_print(cy->cy.top);
	printf("cyl_bot: ");
	vec3_print(cy->cy.bot);
}

int	intersect_cylinder_cap(t_scene *scene, t_ray ray, double *t, int i)
{
	const double	t3 = vec3_dot(vec3_sub(scene->shape[i].cy.top, ray.origin),
			scene->shape[i].cy.vec) / vec3_dot(ray.direction, \
				scene->shape[i].cy.vec);
	const double	t4 = vec3_dot(vec3_sub(scene->shape[i].cy.bot, ray.origin),
			scene->shape[i].cy.vec) / vec3_dot(ray.direction, \
				scene->shape[i].cy.vec);
	const t_vec3	v3 = vec3_sub(ray_at(ray, t3), scene->shape[i].cy.top);
	const t_vec3	v4 = vec3_sub(ray_at(ray, t4), scene->shape[i].cy.bot);
	double			old_t;

	old_t = *t;
	if (vec3_dot(v3, v3) <= pow(scene->shape[i].cy.diameter / 2, 2)
		&& t3 >= EPSILON && t3 < *t)
		*t = t3;
	if (vec3_dot(v4, v4) <= pow(scene->shape[i].cy.diameter / 2, 2)
		&& t4 >= EPSILON && t4 < *t)
		*t = t4;
	return (*t != old_t);
}

int	intersect_cylinder(t_scene *scene, t_ray ray, double *t, int i)
{
	int		hit;
	t_vec3	hit_vec;

	hit = 0;
	hit_vec = vec3_sub(ray_at(ray, *t), scene->shape[i].cy.top);
	if (cy_calc_discriminant(scene, ray, t, i) >= EPSILON)
	{
		if (vec3_dot(hit_vec, scene->shape[i].cy.vec) >= 0
			&& (vec3_dot(hit_vec, scene->shape[i].cy.vec)
				<= scene->shape[i].cy.height))
			hit = 1;
	}
	if (intersect_cylinder_cap(scene, ray, t, i))
		hit = 1;
	return (hit);
}
