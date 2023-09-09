/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:54:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/09 09:33:19 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ray.h"
#include <stdio.h>

double	radians(double grades)
{
	return (grades * M_PI / 180);
}

void	cam_orientation(t_camera *c)
{
	c->look_at = vec3_unit(c->orientation);
	c->right = vec3_unit(vec3_cross(c->look_at, c->vert_up));
	c->up = vec3_unit(vec3_cross(c->right, c->look_at));
}

void	cam_setup(t_camera *c)
{
	cam_orientation(c);
	c->aspect_ratio = WIDTH / (double)HEIGHT;
	c->viewport_width = 2.0f * (tan(radians(c->fov) / 2.0f));
	c->viewport_height = c->viewport_width / c->aspect_ratio;
	c->half_hor = c->viewport_width / 2;
	c->half_ver = c->viewport_height / 2;
	c->horizontal = vec3(c->viewport_width, 0, 0);
	c->vertical = vec3(0, -c->viewport_height, 0);
	c->orientation = vec3_unit(c->orientation);
	c->viewport_top_left = ray_at(ray(c->pos, c->orientation), c->focal_length);
	c->viewport_top_left = vec3_sub(c->viewport_top_left, \
		vec3_mult(c->right, c->viewport_width / 2));
	c->viewport_top_left = vec3_sum(c->viewport_top_left, \
		vec3_mult(c->up, c->viewport_height / 2));
	c->pxl_size_hor = vec3_div(c->horizontal, WIDTH);
	c->pxl_size_ver = vec3_div(c->vertical, HEIGHT);
	printf("Cam_pos: (%f, %f, %f)\n", c->pos.x, c->pos.y, c->pos.z);
	printf("Cam_orient: (%f, %f, %f)\n", c->orientation.x, c->orientation.y, c->orientation.z);
	printf("\n\n");
}
