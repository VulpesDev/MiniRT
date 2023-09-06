/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:38:19 by tvasilev          #+#    #+#             */
/*   Updated: 2023/09/06 14:53:35 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

bool intersect_cap_top(t_shape *shape, t_ray r, float *tt)
{
	t_vector p0 = vect_sum(shape->cy.center, vect_mult(shape->rotation, shape->cy.height));
	t_vector n = vect_inverse(vect_norm(shape->rotation));
	t_vector l0 = r.origin;
	t_vector l = vect_norm(r.direction);
	float denom = vect_dot(n, l);
	if (denom > 1e-6)
	{
		t_vector p0l0 = vect_sub(p0, l0);
		*tt = vect_dot(p0l0, n) / denom;
		return true;
		if (vect_mag(vect_sub(ray_at(r, *tt), p0)) <= shape->cy.diameter/2)
		{
			if (*tt > 0.000001f)
			{
				return (true);
			}
		}
	}
	return (false);
}

bool intersect_cap_bot(t_shape *shape, t_ray r, float *tt)
{
	t_vector p0 = shape->cy.center;
	t_vector n = vect_norm(shape->rotation);
	t_vector l0 = r.origin;
	t_vector l = vect_norm(r.direction);
	float denom = vect_dot(n, l);
	if (denom > 1e-6)
	{
		t_vector p0l0 = vect_sub(p0, l0);
		*tt = vect_dot(p0l0, n) / denom;
		return true;
		if (vect_mag(vect_sub(ray_at(r, *tt), p0)) <= shape->cy.diameter/2)
		{
			if (*tt > EPSILON)
			{
				return (true);
			}
		}
	}
	return (false);
}

//! not really needed I think
//* Edit * needed for the shadow casting
//! Caps dont cast shadows
int	intersect_cylinder(t_scene *scene, t_ray r, float *t, int i)
{
	double	a;
	double	b;
	double	c;
	double discriminant;
	double t1,t2, m1, m2;
	t_vector	olddir;
	t_vector	X;

	*t = 0;
	scene->shape[i].rotation = vect_norm(scene->shape[i].rotation);
	// discriminant = vect_dot(scene->shape[i].rotation, vect_norm(r.direction));
	// if (intersect_cap_bot(&scene->shape[i], r, t) || intersect_cap_top(&scene->shape[i], r, t))
	// {
	// 	// printf("t: %f\n", *t);
	// 	return (true);
	// }
	olddir = r.direction;
	r.direction = vect_cross(r.direction, scene->shape[i].rotation);
	X = vect_sub(r.origin, scene->shape[i].cy.center);
	a = vect_dot(r.direction, r.direction);
	b = 2 * vect_dot(r.direction, vect_cross(X, scene->shape[i].rotation));
	c = vect_dot(vect_cross(X, scene->shape[i].rotation), vect_cross(X, scene->shape[i].rotation)) - ((scene->shape[i].cy.diameter / 2) * (scene->shape[i].cy.diameter / 2));
	discriminant = b * b - 4 * a * c;
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	m1 = vect_dot(olddir, scene->shape[i].rotation) * t1 + vect_dot(X, scene->shape[i].rotation);
	m2 = vect_dot(olddir, scene->shape[i].rotation) * t2 + vect_dot(X, scene->shape[i].rotation);

	if (t1 > 0 && m1 >= 0 && m1 <= scene->shape[i].cy.height)
		*t = t1;
	else if (t2 > 0 && m2 >= 0 && m2 <= scene->shape[i].cy.height)
		*t = t2;
	return (discriminant);
}