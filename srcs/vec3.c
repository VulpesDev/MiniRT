/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:42:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/07 11:54:02 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"

t_vec3	vec3(double x, double y, double z)
{
	t_vec3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_color	color(double t, double r, double g, double b)
{
	t_color	result;

	result.t = t;
	result.r = r;
	result.g = g;
	result.b = b;
	return (result);
}

t_point3	point(double x, double y, double z)
{
	t_point3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_vec3	vec3_sum(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vec3	vec3_mult(t_vec3 a, double b)
{
	t_vec3	result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	return (result);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vec3	vec3_div(t_vec3 a, double b)
{
	return (vec3_mult(a, 1 / b));
}

double	vec3_len_squared(t_vec3 a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

double	vec3_len(t_vec3 a)
{
	return (sqrt(vec3_len_squared(a)));
}

t_vec3	vec3_unit(t_vec3 a)
{
	return (vec3_div(a, vec3_len(a)));
}

t_vec3	vec3_inv(t_vec3 a)
{
	return (vec3_mult(a, -1));
}

void	vec3_print(t_vec3 a)
{
	printf("x: %f, y: %f, z: %f\n", a.x, a.y, a.z);
}

/**
 * @brief Reflects a vector
 * @param l: light vector to reflect
 * @param n: normal vector
*/
t_vec3	vec3_reflect(t_vec3 l, t_vec3 n)
{
	return (vec3_sub(l, vec3_mult(n, 2 * vec3_dot(l, n))));
}
