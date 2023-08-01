/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:18:37 by tvasilev          #+#    #+#             */
/*   Updated: 2023/08/01 16:47:03 by tvasilev         ###   ########.fr       */
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
		printf("It HIT !!!\n");
		return (true);
	}
	printf("It did not ???\n");
	return (false);
}

bool	cy_hit(t_shape *shape, t_ray r, t_hit_record *rec)
{
	double	a;
	double	b;
	double	c;
	double discriminant;
	t_vector	X;

	X = vect_sub(r.origin, shape->cy.center);
	a = vect_dot(r.direction, r.direction) - (vect_dot(r.direction, shape->rotation)*vect_dot(r.direction, shape->cy.rotation));
	b = 2*(vect_dot(r.direction, X) - (vect_dot(r.direction, shape->rotation))*(vect_dot(X, shape->rotation)));
	c = vect_dot(X, X) - (vect_dot(X, shape->rotation)*vect_dot(X, shape->rotation)) - shape->cy.diameter;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	return (cy_hit_record((-b - sqrt(discriminant)) / (2.0 * a), shape, rec, r));
}