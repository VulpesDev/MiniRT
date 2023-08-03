/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:18:37 by tvasilev          #+#    #+#             */
/*   Updated: 2023/08/03 11:48:03 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

int	intersect_cylinder(t_scene *scene, t_ray ray, float *t, int i)
{
	double	a;
	double	b;
	double	c;
	double discriminant;
	t_vector	X;

	printf("IN HERE !!!\n");
	X = vect_sub(ray.origin, scene->shape[i].cy.center);
	a = vect_dot(ray.direction, ray.direction) - (vect_dot(ray.direction, scene->shape[i].rotation)*vect_dot(ray.direction, scene->shape[i].rotation));
	b = 2*(vect_dot(ray.direction, X) - (vect_dot(ray.direction, scene->shape[i].rotation))*(vect_dot(X, scene->shape[i].rotation)));
	c = vect_dot(X, X) - (vect_dot(X, scene->shape[i].rotation)*vect_dot(X, scene->shape[i].rotation)) - scene->shape[i].cy.diameter;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	*t = (-b - sqrt(discriminant)) / (2.0 * a);
	return (t >= 0);
}

bool	cy_hit_record(double t, t_shape *shape, t_hit_record *rec, t_ray ray)
{
	if (t > 0.000001f && t < rec->t)
	{
		rec->t = t;
		rec->p = ray_at(ray, t);
		rec->normal = shape->rotation;
		rec->color = shape->color;
		return (true);
	}
	return (false);
}

bool	cy_hit(t_shape *shape, t_ray r, t_hit_record *rec)
{
	double	a;
	double	b;
	double	c;
	double t1,t2,t;
	double discriminant;
	t_vector	X;

	r.direction = vect_cross(r.direction, shape->rotation);
	X = vect_sub(r.origin, shape->cy.center);
	a = vect_dot(r.direction, r.direction);
	b = 2 * vect_dot(r.direction, vect_cross(X, shape->rotation));
	c = vect_dot(vect_cross(X, shape->rotation), vect_cross(X, shape->rotation)) - ((shape->cy.diameter / 2) * (shape->cy.diameter / 2));
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t2 < 0)
		return (false);
	t = t1 > 0 ? t1 : t2;
	return (cy_hit_record(t, shape, rec, r));
}