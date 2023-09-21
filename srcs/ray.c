/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:14:47 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/21 10:30:40 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

/**
 * @brief Create a ray object
*/
t_ray	ray(t_point3 origin, t_vec3 direction)
{
	t_ray	result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}

/**
 * @brief Calculate the point on the ray at distance t (hit point)
 * @param ray The ray
 * @param t The distance
 * @return t_point3 The point on the ray at distance t
*/
t_point3	ray_at(t_ray ray, double t)
{
	t_point3	result;

	result = vec3_sum(ray.origin, vec3_mult(ray.direction, t));
	return (result);
}
