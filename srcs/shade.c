/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:45:15 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/30 20:29:49 by tfregni          ###   ########.fr       */
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
 * - n_dot_l < 0 to get the solid to cast a shadow
 * onto itself, effectively having a dark side.
 * To scale the light intensity I multiply the light by the dot product
 * and not the dot product in range [0, 1]
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
	if ((cast_shadow(scene, (t_ray){vec3_sum(p, vec3_mult(l, EPSILON)), l}, rec)
		&& len_l > rec->t) || n_dot_l < 0)
		return (diff_shade / 2);
	light = ((scene->light.brightness * n_dot_l) + diff_shade) / 2;
	if (light < 0 || light > 1)
		printf("light: %f\n", light);
	return (light);
}

/**
 * Former intersect_element function
 * @brief Checks if the ray hits any element in the scene
 * In the scene->shape[i].hit(&scene->shape[i], ray, rec) call
 * the ray is updated with hit distance, hit point, normal and color
*/
bool	hit_element(t_scene *scene, t_ray ray, t_hit_record *rec)
{
	bool	hit_anything;
	int		i;

	hit_anything = false;
	rec->t = RAY_LEN;
	i = scene->shape_count - 1;
	while (i >= 0)
	{
		if (scene->shape[i].hit(&scene->shape[i], ray, rec) && rec->t > EPSILON)
			hit_anything = true;
		i--;
	}
	return (hit_anything);
}

/**
 * @brief Creates a hit record that gets updated if the ray hits an element
 * @returns the color of the hit element
*/
t_color	ray_color(t_scene *scene, t_ray r)
{
	double			light;
	t_hit_record	rec;

	if (hit_element(scene, r, &rec))
	{
		light = light_coeff(scene, &rec);
		return (apply_light_to_color(rec.color, light));
	}
	return (convert_color(scene->ambient.trgb));
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
