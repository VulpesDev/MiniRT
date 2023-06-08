/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:41:01 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/08 09:07:18 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

/**
 * range_x / WIDTH = canvas size of 1 pxl on x axis
 * range_x / WIDTH * ratio = canvas size of 1 pxl on y axis
 * added - to flip the y axis
*/
t_point_2d	to_canvas(t_pxl pxl)
{
	t_point_2d	ret;
	float		range_x;
	float		ratio;

	range_x = CANV_MAX_X - CANV_MIN_X;
	ratio = WIDTH / HEIGHT;
	ret.x = -(range_x / WIDTH * pxl.x + CANV_MIN_X);
	ret.y = -(range_x / WIDTH * ratio * pxl.y + CANV_MIN_Y);
	return (ret);
}

int	apply_ligthing_ratio(int trgb, float lighting_ratio)
{
	return (create_trgb(0, \
			lighting_ratio * ((trgb >> 16) & 0xFF),
			lighting_ratio * ((trgb >> 8) & 0xFF),
			lighting_ratio * (trgb & 0xFF)));
}

int	intersect_element(t_scene *scene, t_vector ray_dir, int *color, float *min_t)
{
	int		i;
	int		ret;
	float	t;

	ret = 0;
	i = 0;
	while (scene->sp[i].diameter)
	{
		if (intersect_sphere(scene, ray_dir, &t, i) && t < *min_t)
		{
			*min_t = t;
			*color = apply_ligthing_ratio(scene->sp[i].trgb, sp_light_coeff(scene, t, ray_dir, i));
			ret = 1;
		}
		i++;
	}
	i = 0;
	while (scene->pl[i].valid)
	{
		if (intersect_plane(scene, ray_dir, &t, i) && t < *min_t)
		{
			*min_t = t;
			*color = apply_ligthing_ratio(scene->pl[i].trgb, scene->ambient.lighting_ratio);
			ret = 1;
		}
		i++;
	}
	// i = 0;
	// while (scene->cy + i * sizeof(t_cylinder))
	// {
	// 	i++;
	// }
	return (ret);
}

/**
 * @returns a color as int
 * @math
 * circle = (x^2 - a) + (y^2 - b) - r^2 = 0 (a and b are the coord)
 * ray = a + bt (a: origin b: direction t: distance)
 * a : ray origin (scene->camera.pos)
 * b : ray direction (scene->camera.orientation)
 * r : radius (scene->sphere.diameter / 2)
 * t : hit distance
 * Substitute ray into circle and solve for t
 * (bx^2 + by^2 + bz^2)t^2 + (2(axbx + ayby + azbz))t
 * + (ax^2 +ay^2 + az^2 - r^2) = 0
 * Quadratic formula: (-b +- sqrt(b^2 - 4ac))/2a
 * Discriminant: b^2 - 4ac
*/
int	per_pixel(t_pxl p, t_scene *scene)
{
	t_point_2d	coord;
	t_vector	ray_direction;
	float		t;
	int			color;

	t = RAY_LEN;
	coord = to_canvas(p);
	ray_direction = vect_norm((t_vector){coord.x, coord.y, -1.0f});
	if (intersect_element(scene, ray_direction, &color, &t))
	{
		return (color);
	}
	return (apply_ligthing_ratio(scene->ambient.trgb, \
								scene->ambient.lighting_ratio));
}

/**
 * The trgb value of a pxl not intersecting a solid is each 8bit color
 * multiplied by the lighting ratio
*/
void	draw(t_scene *scene)
{
	t_pxl	p;
	t_img	*data;

	data = scene->img;
	p.y = 0;
	while (p.y < HEIGHT)
	{
		p.x = 0;
		while (p.x < WIDTH)
		{
			my_mlx_pixel_put_d(scene->img, p.x, p.y, per_pixel(p, scene));
			p.x++;
		}
		p.y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
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
