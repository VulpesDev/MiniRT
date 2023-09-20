/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:45:15 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/20 18:49:10 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	cast_shadow(t_scene *scene, t_ray ray, t_hit_record *rec)
{
	int		i;
	int		hit_any;
	t_color	color;

	hit_any = 0;
	i = scene->shape_count - 1;
	while (i >= 0)
	{
		if (rec->shape != &scene->shape[i])
		{
			color = rec->color;
			if (scene->shape[i].hit(&scene->shape[i], ray, rec)
				&& rec->t > EPSILON && rec->t < RAY_LEN)
			{
				rec->color = color;
				hit_any = 1;
			}
		}
		i--;
	}
	return (hit_any);
}

/**
 * @param n: normal vector
 * @param p: hit point
 * @returns	a double expressing the light intensity on the point
 * @brief if the light hits at an angle it's more diffused and
 * less intense
 * @param l: light ray (from the hit point to the light source)
 * @param n_dot_l: angle between the light ray and the normal
 * @param light: intensity of the light. If it's negative it's
 * set to 0
 * @explanation: n_dot_l is a value between -1 and 1 if l is normalized
 * diff_shade is a value between 0 and 1: [-1,1] is a range of 2,
 * I split it in half and displace it by 0.5 to get a range of 1.
 * Since brightness is in range [0,1], it would make the product
 * smaller, so I add 1. At this point the range is [0,2], so I divide
 * it by 2 to get a range of 1 and I do the same for the light
 * returned by the shadow to keep the proportion.
 * The conditions to cast the shadow are:
 * - cast_shadow function: hit an object with a ray with positive length
 * - len_l > rec->t: the light is farther than the object
 * - vec3_dot(rec->normal, l) < 0: the normal is facing the light
*/
double	diffuse_shade(t_scene *scene, t_vector n, t_vector p, t_hit_record *rec)
{
	t_vector	l;
	double		n_dot_l;
	double		light;
	double		len_l;
	double		diff_shade;

	l = vec3_sub(scene->light.pos, p);
	len_l = vec3_len(l);
	l = vec3_unit(l);
	n_dot_l = vec3_dot(n, l);
	diff_shade = n_dot_l / 2 + 0.5f;
	if (cast_shadow(scene, (t_ray){p, l}, rec)
		&& len_l > rec->t)
		return (diff_shade / 2);
	light = ((1 + scene->light.brightness) * diff_shade) / 2;
	return (light);
}

/**
 * @param hit: hit record
 * @brief: calculates the light intensity on the hit point
*/
double	light_coeff(t_scene *scene, t_hit_record *hit)
{
	t_vector	hit_pos;
	t_vector	normal;

	hit_pos = hit->p;
	normal = hit->normal;
	return (diffuse_shade(scene, normal, hit_pos, hit));
}
