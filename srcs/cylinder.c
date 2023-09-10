/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:18:37 by tvasilev          #+#    #+#             */
/*   Updated: 2023/09/10 16:33:21 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

void	calculate_t(double t[], double a, double b, double discriminant)
{
	t[0] = 0;
	t[1] = (-b - sqrt(discriminant)) / (2.0 * a);
	t[2] = (-b + sqrt(discriminant)) / (2.0 * a);
}

void	calculate_m(double tm[][3], t_vec3 dir, t_vec3 rot, t_vec3 X)
{
	tm[1][0] = 0;
	tm[1][1] = vec3_dot(dir, rot) * tm[0][1] + vec3_dot(X, rot);
	tm[1][2] = vec3_dot(dir, rot) * tm[0][2] + vec3_dot(X, rot);
}

void	determine_t_m(double t[], double m[], double height)
{
	if (t[1] > 0 && m[1] >= 0 && m[1] <= height)
	{
		t[0] = t[1];
		m[0] = m[1];
	}
	else if (t[2] > 0 && m[2] >= 0 && m[2] <= height)
	{
		t[0] = t[2];
		m[0] = m[2];
	}
}

int	intersect_cylinder(t_scene *scene, t_ray r, float *t, int i)
{
	scene->shape[i].rotation = vec3_unit(scene->shape[i].rotation);
	if (intersect_plane_cap(&scene->shape[i], r, t, true)
		|| intersect_plane_cap(&scene->shape[i], r, t, false))
		return (true);
	else
		return (intersect_body(scene, r, t, i));
}

//first check if it hits a plane
//limit the plane with the top_cap function
bool	cy_hit(t_shape *shape, t_ray r, t_hit_record *rec)
{
	shape->rotation = vec3_unit(shape->rotation);
	if (hit_plane_cap(shape, r, rec, true)
		|| hit_plane_cap(shape, r, rec, false))
		return (true);
	else
		return (cy_hit_body(shape, r, rec));
}
