/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:22:05 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/07 14:33:27 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

float	sp_calc_hit_point(float discriminant, float a, float b)
{
	return ((-b - sqrt(discriminant)) / (2.0f * a));
}

/**
 * It returns the discriminant. If it's >=0 it assigns to t the value of
 * the closest hit point
*/
float	sp_calc_discriminant(t_scene *scene, t_vector ray_direction, \
							float *t, int i)
{
	float			a;
	float			b;
	float			c;
	t_point_3d		transl;
	float			discriminant;

	a = vect_dot(ray_direction, ray_direction);
	transl = vect_sub(scene->camera.pos, scene->sp[i].pos);
	b = 2.0f * vect_dot(transl, ray_direction);
	c = vect_dot(transl, transl) - pow((scene->sp[i].diameter / 2), 2);
	discriminant = b * b - (4.0f * a * c);
	if (discriminant >= 0)
		*t = sp_calc_hit_point(discriminant, a, b);
	return (discriminant);
}

float	sp_light_coeff(t_scene *scene, float t, t_vector ray_direction, int i)
{
	t_vector	hit_pos;
	t_vector	normal;
	float		light;

	hit_pos = vect_sum(scene->camera.pos, vect_mult(ray_direction, t));
	normal = vect_norm(vect_sub(hit_pos, scene->sp[i].pos));
	light = ft_fmax(\
		vect_dot(normal, vect_inverse((vect_norm(scene->light.pos)))), 0.0f);
	return (light);
}

int	intersect_sphere(t_scene *scene, t_vector ray_direction, float *t, int i)
{
	if (sp_calc_discriminant(scene, ray_direction, t, i) < 0)
		return (0);
	return (1);
}

