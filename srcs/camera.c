/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:54:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/23 17:48:58 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ray.h"
#include "minirt.h"
#include <stdio.h>

double	radians(double grades)
{
	return (grades * M_PI / 180);
}

/**
 * @brief: we found unclear what's required in the subject
 * @options:
 * - the orientation is relative to the camera position
 * (orient (0, 0, -1) means that the camera is looking in front of it,
 * so if the position is (2, 4, 6) the camera is looking at (2, 4, 5))
 * - the orientation vector gives the coordinates of the point the camera
 * is looking at (orient (0, 0, 0) means that the camera is looking at (0, 0, 0))
 * wherever the camera is.
 * We chose the first option. Here in comment the implementation of the second.
 * // c->look_at = vec3_unit(vec3_sub(c->orientation, c->pos));
 * - calculate the look_at vector as direction between position and orient
 * @explanation:
 * - check that the orientation vector is not 0, 0, 0 before trying to normalize
 * - translate the orientation vector to the camera position
 * - compute the direction from position to translated orientation
 * - find the right vector through the cross product with the vertical up
 * - if the right vector is 0 (camera along y axis) calculate it with another
 * arbitrary vector (0, 0, -1)
 * - normalize the right vector
 * - find the up vector through the cross product with the right vector
*/
void	cam_orientation(t_camera *c)
{
	if (vec3_len_squared(c->orientation) == 0)
		c->orientation = vec3(0, 0, -1);
	c->orientation = vec3_unit(c->orientation);
	c->look_at = vec3_sum(c->pos, c->orientation);
	c->look_at = vec3_sub(c->look_at, c->pos);
	c->right = vec3_cross(c->look_at, c->vert_up);
	if (vec3_len_squared(c->right) < EPSILON)
		c->right = vec3_cross(c->look_at, vec3(0, 0, -1));
	c->right = vec3_unit(c->right);
	c->up = vec3_unit(vec3_cross(c->right, c->look_at));
}

void	cam_setup(t_camera *c)
{
	cam_orientation(c);
	c->aspect_ratio = WIDTH / (double)HEIGHT;
	c->viewport_width = 2.0f * (tan(radians(c->fov) / 2.0f));
	c->viewport_height = c->viewport_width / c->aspect_ratio;
	c->horizontal = vec3(c->viewport_width, 0, 0);
	c->vertical = vec3(0, -c->viewport_height, 0);
	c->viewport_top_left = ray_at(ray(c->pos, c->look_at), c->focal_length);
	c->viewport_top_left = vec3_sub(c->viewport_top_left, \
		vec3_mult(c->right, c->viewport_width / 2));
	c->viewport_top_left = vec3_sum(c->viewport_top_left, \
		vec3_mult(c->up, c->viewport_height / 2));
	c->pxl_size_hor = vec3_div(c->horizontal, WIDTH);
	c->pxl_size_ver = vec3_div(c->vertical, HEIGHT);
}
