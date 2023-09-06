/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:18:37 by tvasilev          #+#    #+#             */
/*   Updated: 2023/09/06 17:34:24 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

//already included
// t_vec3	cy_normal(t_shape *cy, t_point3 hit)
// {
// 	t_ray	normal;
// 	const t_vector N = vec3_unit(cy->rotation);
// 	const t_vector X = vec3_sub(hit, N);
// 	const t_vector V = vec3_inv(N);
// 	double t;

// 	normal = ray(cy->cy.center, vec3_unit(cy->rotation));
// 	t = vec3_dot(N, V);
// 	if (t != 0)
// 	{
// 		t = vec3_dot(vec3_inv(X), V) / t;
// 	}
// 	normal = ray(ray_at(ray(cy->cy.center, N), t), hit);
// 	return (vec3_unit(normal.direction));
// }

bool	cy_hit_record(double t, t_shape *shape, t_hit_record *rec, t_ray ray, double m)
{
	//m = 2;
	if (t > 0.000001f && t < rec->t)
	{
		rec->t = t;
		rec->p = ray_at(ray, t);
		//rec->normal = cy_normal(shape, rec->p);
		rec->normal = vect_norm(vect_sub( rec->p, vect_sub(shape->cy.center, vect_mult(shape->rotation, m))));
		rec->color = shape->color;
		return (true);
	}
	return (false);
}

bool	cy_hit_cap_record(double t, t_shape *shape, t_hit_record *rec, t_ray ray)
{
	if (t > 0.000001f && t < rec->t)
	{
		rec->t = t;
		rec->p = ray_at(ray, t);
		//rec->normal = vect_norm();
		rec->color = shape->color;
		return (true);
	}
	return (false);
}

//make so it only takes the first t
bool	cap(t_shape *shape, double t, t_ray ray, t_vector Ce, t_hit_record *rec)
{
	t_vector V;
	t_vector p;

	p = ray_at(ray, t);
	V = vect_sub(p, Ce);
	if (vect_mag(V) <= shape->cy.diameter/2)
		return (cy_hit_cap_record(t, shape, rec, ray));
	return (false);
}


bool	hit_plane_top(t_shape *shape, t_ray r, t_hit_record *rec)
{
	t_vector p0 = vect_sum(shape->cy.center, vect_mult(shape->rotation, shape->cy.height));
	t_vector n = vect_inverse(vect_norm(shape->rotation));
	t_vector l0 = r.origin;
	t_vector l = vect_norm(r.direction);
	float denom = vect_dot(n, l);
	if (denom > 1e-6)
	{
		t_vector p0l0 = vect_sub(p0, l0);
		return (cap(shape, vect_dot(p0l0, n) / denom, r, p0, rec));
	}
	return (false);
}


bool	hit_plane_bot(t_shape *shape, t_ray r, t_hit_record *rec)
{
	t_vector p0 = shape->cy.center;
	t_vector n = vect_norm(shape->rotation);
	t_vector l0 = r.origin;
	t_vector l = vect_norm(r.direction);
	float denom = vect_dot(n, l);
	if (denom > 1e-6)
	{
		t_vector p0l0 = vect_sub(p0, l0);
		return (cap(shape, vect_dot(p0l0, n) / denom, r, p0, rec));
	}
	return (false);
}

//first check if it hits a plane
//limit the plane with the top_cap function
bool	cy_hit(t_shape *shape, t_ray r, t_hit_record *rec)
{
	double	a;
	double	b;
	double	c;
	double t1,t2,t, m1, m2, m;
	double discriminant;
	t_vector	olddir;
	t_vector	X;

	t = m = 0;
	shape->rotation = vect_norm(shape->rotation);
	if (hit_plane_top(shape, r, rec) || hit_plane_bot(shape, r, rec))
		return (true);
	olddir = r.direction;
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
	m1 = vect_dot(olddir, shape->rotation) * t1 + vect_dot(X, shape->rotation);
	m2 = vect_dot(olddir, shape->rotation) * t2 + vect_dot(X, shape->rotation);

	if (t1 > 0 && m1 >= 0 && m1 <= shape->cy.height)
	{
		t = t1;
		m = m1;
	}
	else if (t2 > 0 && m2 >= 0 && m2 <= shape->cy.height)
	{
		t = t2;
		m = m2;
	}
	else
		return (false);
	return (cy_hit_record(t, shape, rec, r, m));
}