/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:26:42 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/09 10:34:37 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <stdio.h> // @todo delete

t_vec3	vec3_inv(t_vec3 a)
{
	return (vec3_mult(a, -1));
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

void	vec3_print(t_vec3 a)
{
	printf("x: %f, y: %f, z: %f\n", a.x, a.y, a.z);
}
