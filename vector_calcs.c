/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:48:28 by tvasilev          #+#    #+#             */
/*   Updated: 2023/06/14 11:05:38 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	vect_mult(t_vector v, float a)
{
	t_vector	result;

	result.x = v.x * a;
	result.y = v.y * a;
	result.z = v.z * a;
	return (result);
}

float	vect_mag(t_vector v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

t_vector	vect_norm(t_vector v)
{
	t_vector	result;
	float		m;

	m = vect_mag(v);
	result.x = v.x / m;
	result.y = v.y / m;
	result.z = v.z / m;
	return (result);
}

t_vector	vect_sum(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector	vect_sub(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

float	vect_dot(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return (result.x + result.y + result.z);
}

t_vector	vect_cross(t_vector u, t_vector v)
{
	return ((t_vector){
		u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x
	});
}

t_vector	vect_inverse(t_vector a)
{
	return ((t_vector){-a.x, -a.y, -a.z});
}

