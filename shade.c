/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:45:15 by tfregni           #+#    #+#             */
/*   Updated: 2023/08/27 15:49:12 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	cast_shadow(t_scene *scene, t_ray ray)
{
	int		i;
	float	t;

	i = scene->shape_count - 1;
	while (i >= 0)
	{
		if (scene->shape[i].intersect(scene, ray, &t, i)
			&& t > EPSILON && t < 1)
			return (1);
		i--;
	}
	return (0);
}

/**
 * @param n: normal vector
 * @param p: hit point
 * @returns	a float expressing the light intensity on the point
 * @brief if the light hits at an angle it's more diffused and
 * less intense
 * @param l: light ray
 * @param n_dot_l: angle between the light ray and the normal
 * @param light: intensity of the light. If it's negative it's
 * set to 0
*/
float	diffuse_reflection(t_scene *scene, t_vector n, t_vector p)
{
	t_vector	l;
	float		n_dot_l;
	float		light;
	float		len_l;
	t_ray		ray;

	l = vec3_sub(p, scene->light.pos);
	ray = (t_ray){p, vec3_inv(l)};
	if (cast_shadow(scene, ray))
		return (0.1f);
	n_dot_l = vec3_dot(n, l);
	len_l = vec3_len(l);
	if (len_l < EPSILON)
		return (1.0f);
	light = ft_fmax((scene->light.brightness * n_dot_l / len_l), 0.0f);
	return (light);
}
