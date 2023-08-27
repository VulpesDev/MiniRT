/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:41:01 by tfregni           #+#    #+#             */
/*   Updated: 2023/08/27 13:32:46 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "matrix_math.h"

// void	print_4x4(t_matrix_trans m)
// {
// 	for (int i = 0; i < 4; i++)
// 	{
// 		for (int j = 0; j < 4; j++)
// 			printf("%f\t", m[i][j]);
// 		printf("\n");
// 	}
// 	printf("\n");
// }

int	apply_lighting_ratio(int trgb, float lighting_ratio)
{
	return (create_trgb(0, \
			lighting_ratio * ((trgb >> 16) & 0xFF),
			lighting_ratio * ((trgb >> 8) & 0xFF),
			lighting_ratio * (trgb & 0xFF)));
}

t_color	apply_light_to_color(t_color c, double light)
{
	// printf("color: %f %f %f\n", c.r, c.g, c.b);
	return (color(0.0, c.r * light, c.g * light, c.b * light));
}

int	intersect_element(t_scene *scene, t_ray ray, int *color, float *min_t)
{
	int		i;
	int		ret;
	float	t;

	ret = 0;
	i = scene->shape_count - 1;
	while (i >= 0)
	{
		// printf("shape[%d] i: %d\n", scene->shape_count, i);
		if (scene->shape[i].intersect(scene, ray, &t, i) && t < *min_t && t > 0)
		{
			*min_t = t;
			*color = apply_lighting_ratio(scene->shape[i].trgb, \
											sp_light_coeff(scene, t, ray, i));
			ret = 1;
		}
		i--;
	}
	return (ret);
}

/**
 * @brief converts an int in trgb format to a color struct with double values
 * in range [0, 1]
 * @param trgb int in trgb format
 * @return color struct
*/
t_color	convert_color(int trgb)
{
	t_color	c;

	c.t = ((trgb >> 24) & 0xFF) / 255.999;
	c.r = ((trgb >> 16) & 0xFF) / 255.999;
	c.g = ((trgb >> 8) & 0xFF) / 255.999;
	c.b = (trgb & 0xFF) / 255.999;
	return (c);
}

/**
 * @brief converts a color struct with double values in range [0, 1]
 * to an int in trgb format
 * @param c color struct
 * @return int in trgb format
*/
int	convert_trgb(t_color c)
{
	int		t;
	int		r;
	int		g;
	int		b;

	t = (int)(c.t * 255.999);
	r = (int)(c.r * 255.999);
	g = (int)(c.g * 255.999);
	b = (int)(c.b * 255.999);
	return (t << 24 | r << 16 | g << 8 | b);
}

bool	hit_element(t_scene *scene, t_ray ray, t_hit_record *rec)
{
	bool	hit_anything;
	int		i;

	hit_anything = false;
	rec->t = RAY_LEN;
	i = scene->shape_count - 1;
	while (i >= 0)
	{
		if (scene->shape[i].hit(&scene->shape[i], ray, rec) && rec->t > 0.001f)
		{
			hit_anything = true;
		}
		i--;
	}
	return (hit_anything);
}

/**
 * A lerp is always of the form
 * blendedValue=(1−t)⋅startValue+t⋅endValue,
*/
t_color	ray_color(t_scene *scene, t_ray r)
{
	t_vec3			unit_direction;
	double			t;
	t_vec3			blend;
	t_hit_record	rec;

	// return (color(0.5, (normal.x + 1) * 0.5, (normal.y + 1) * 0.5, (normal.z + 1) * 0.5));
	if (hit_element(scene, r, &rec))
	{
		double light = ft_fmax((vec3_dot(rec.normal, vec3_inv(vec3_unit(scene->light.pos)))), 0.0f);
		// rec.trgb = ft_fmax(rec.trgb * light, 0.0f);
		return (apply_light_to_color(rec.color, light));
	}
	unit_direction = vec3_unit(r.direction);
	t = 0.5 * (unit_direction.y + 1.0);
	blend = vec3_sum(vec3_mult(vec3(1, 1, 1), 1.0 - t), vec3_mult(vec3(0.5, 0.7, 1.0), t));
	return (color(0, blend.x, blend.y, blend.z));
}

t_err	render_scene(t_scene *scene)
{
	if (!init_img(scene))
	{
		draw(scene);
		mlx_manage(scene);
		return (SUCCESS);
	}
	return (ft_error("render", "couldn't init image", MEM_FAIL, scene));
}
