/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:41:01 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/03 22:22:50 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Can check interception with just the discriminant of the quadratic formula
 * b^2 - 4ac. If < 0 no intersection, 0 tan, > 0 2 intersections
 *
*/
// int	intersect_sphere(t_sphere sp, t_pxl p)
// {

// }

int	apply_ligthing_ratio(int trgb, float lighting_ratio)
{
	return (create_trgb(0, \
			lighting_ratio * ((trgb >> 16) & 0xFF),
			lighting_ratio * ((trgb >> 8) & 0xFF),
			lighting_ratio * (trgb & 0xFF)));
}

/**
 * The trgb value of a pxl not intersecting a solid is each 8bit color
 * multiplied by the
*/
void	draw(t_scene *scene)
{
	t_pxl	p;
	t_img	*data;

	printf("LR: %f\n", scene->ambient.lighting_ratio);
	data = scene->img;
	p.y = 0;
	p.trgb = apply_ligthing_ratio(scene->ambient.trgb, \
								scene->ambient.lighting_ratio);
	while (p.y < WIDTH)
	{
		p.x = 0;
		while (p.x < HEIGHT)
		{
			my_mlx_pixel_put_d(scene->img, p.x, p.y, p.trgb);
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
	}
	return (SUCCESS);
}
