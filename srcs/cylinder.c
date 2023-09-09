/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:18:37 by tvasilev          #+#    #+#             */
/*   Updated: 2023/09/09 20:20:51 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	cy_hit_record(double t, t_shape *shape, t_hit_record *rec, t_ray ray, double m)
{
	if (t > 0.000001f && t < rec->t)
	{
		rec->t = t;
		rec->p = ray_at(ray, t);
		rec->normal = vec3_unit(vec3_sub(rec->p, vec3_sub(shape->cy.center, vec3_mult(shape->rotation, m))));
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
		//rec->normal = vec3_unit();
		rec->color = shape->color;
		return (true);
	}
	return (false);
}

//make so it only takes the first t
bool	cap(t_shape *shape, double t, t_ray ray, t_vector Ce, t_hit_record *rec)
{
	t_vector v;
	t_vector p;

	p = ray_at(ray, t);
	v = vec3_sub(p, Ce);
	if (vec3_len(v) <= shape->cy.diameter / 2)
		return (cy_hit_cap_record(t, shape, rec, ray));
	return (false);
}

/**
 * @brief Checks if the ray hits the top cap of the cylinder
 * @param p0: top cap center
 * @param n: top cap normal
 * @param l0: ray origin
 * @param l: ray direction
 * @param p0l0: vector from ray origin to top cap center
*/
bool	hit_plane_top(t_shape *shape, t_ray r, t_hit_record *rec)
{
	const t_vector	p0 = vec3_sum(shape->cy.center, \
		vec3_mult(shape->rotation, shape->cy.height));
	const t_vector	n = vec3_inv(vec3_unit(shape->rotation));
	const t_vector	l0 = r.origin;
	const t_vector	l = vec3_unit(r.direction);
	const float		denom = vec3_dot(n, l);

	if (denom > 1e-6)
	{
		t_vector p0l0 = vec3_sub(p0, l0);
		return (cap(shape, vec3_dot(p0l0, n) / denom, r, p0, rec));
	}
	return (false);
}


bool	hit_plane_bot(t_shape *shape, t_ray r, t_hit_record *rec)
{
	const t_vector	p0 = shape->cy.center;
	const t_vector	n = vec3_unit(shape->rotation);
	const t_vector	l0 = r.origin;
	const t_vector	l = vec3_unit(r.direction);
	const float		denom = vec3_dot(n, l);

	if (denom > 1e-6)
	{
		t_vector p0l0 = vec3_sub(p0, l0);
		return (cap(shape, vec3_dot(p0l0, n) / denom, r, p0, rec));
	}
	return (false);
}



//make so it only takes the first t
bool	cap_inter(t_shape *shape, double t, t_ray ray, t_vector Ce, float *tt)
{
	t_vector	v;
	t_vector	p;

	p = ray_at(ray, t);
	v = vec3_sub(p, Ce);
	if (vec3_len(v) <= shape->cy.diameter / 2)
	{
		*tt = t;
		return (true);
	}
	return (false);
}

bool	hit_plane_top_inter(t_shape *shape, t_ray r, float *t)
{
	t_vector p0 = vec3_sum(shape->cy.center, vec3_mult(shape->rotation, shape->cy.height));
	t_vector n = vec3_inv(vec3_unit(shape->rotation));
	t_vector l0 = r.origin;
	t_vector l = vec3_unit(r.direction);
	float denom = vec3_dot(n, l);
	if (denom > 1e-6)
	{
		t_vector p0l0 = vec3_sub(p0, l0);
		return (cap_inter(shape, vec3_dot(p0l0, n) / denom, r, p0, t));
	}
	return (false);
}


bool	hit_plane_bot_inter(t_shape *shape, t_ray r, float *t)
{
	t_vector p0 = shape->cy.center;
	t_vector n = vec3_unit(shape->rotation);
	t_vector l0 = r.origin;
	t_vector l = vec3_unit(r.direction);
	float denom = vec3_dot(n, l);
	if (denom > 1e-6)
	{
		t_vector p0l0 = vec3_sub(p0, l0);
		return (cap_inter(shape, vec3_dot(p0l0, n) / denom, r, p0, t));
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
	t_hit_record rec;
	t_vector	olddir;
	t_vector	X;

	*t = 0;
	// rec = NULL;
	rec.t = RAY_LEN;
	scene->shape[i].rotation = vec3_unit(scene->shape[i].rotation);
	// if (hit_plane_top_inter(&(scene->shape[i]), r, t) || hit_plane_bot_inter(&(scene->shape[i]), r, t))
	// 	 ;
	// 	//return (1);
	olddir = r.direction;
	r.direction = vec3_cross(r.direction, scene->shape[i].rotation);
	X = vec3_sub(r.origin, scene->shape[i].cy.center);
	a = vec3_dot(r.direction, r.direction);
	b = 2 * vec3_dot(r.direction, vec3_cross(X, scene->shape[i].rotation));
	c = vec3_dot(vec3_cross(X, scene->shape[i].rotation), vec3_cross(X, scene->shape[i].rotation)) - ((scene->shape[i].cy.diameter / 2) * (scene->shape[i].cy.diameter / 2));
	//? maybe normalize the r direction first
	discriminant = b * b - 4 * a * c;
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	m1 = vec3_dot(olddir, scene->shape[i].rotation) * t1 + vec3_dot(X, scene->shape[i].rotation);
	m2 = vec3_dot(olddir, scene->shape[i].rotation) * t2 + vec3_dot(X, scene->shape[i].rotation);

	if (t1 > 0 && m1 >= 0 && m1 <= scene->shape[i].cy.height)
		*t = t1;
	else if (t2 > 0 && m2 >= 0 && m2 <= scene->shape[i].cy.height)
		*t = t2;
	return (discriminant);
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
	if (vec3_len_squared(shape->rotation) == 0)
		shape->rotation = vec3(0, 1, 0);
	shape->rotation = vec3_unit(shape->rotation);
	if (hit_plane_top(shape, r, rec) || hit_plane_bot(shape, r, rec))
		return (true);
	olddir = r.direction;
	r.direction = vec3_cross(r.direction, shape->rotation);
	X = vec3_sub(r.origin, shape->cy.center);
	a = vec3_dot(r.direction, r.direction);
	b = 2 * vec3_dot(r.direction, vec3_cross(X, shape->rotation));
	c = vec3_dot(vec3_cross(X, shape->rotation), vec3_cross(X, shape->rotation)) - ((shape->cy.diameter / 2) * (shape->cy.diameter / 2));
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	m1 = vec3_dot(olddir, shape->rotation) * t1 + vec3_dot(X, shape->rotation);
	m2 = vec3_dot(olddir, shape->rotation) * t2 + vec3_dot(X, shape->rotation);

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

