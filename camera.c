/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:54:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/16 00:22:28 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include <stdio.h>

void	cam_setup(t_camera *c)
{
	double	ratio;
	t_vec3	half_hor;
	t_vec3	half_ver;
	t_vec3	temp;

	ratio = WIDTH / (double)HEIGHT;
	c->viewport_width = 2.0;
	c->viewport_height = c->viewport_width / ratio;
	c->focal_length = 1.0f;
	c->horizontal = vec3(c->viewport_width, 0, 0);
	c->vertical = vec3(0, c->viewport_height, 0);
	half_hor = vec3_div(c->horizontal, 2);
	half_ver = vec3_div(c->vertical, 2);
	temp = vec3_sub(c->pos, half_hor);
	temp = vec3_sub(temp, half_ver);
	c->lower_left_corner = vec3_sub(temp, vec3(0, 0, c->focal_length));
	printf("Camera: vp_w: %f, vp_h: %f, lower_left: %f %f %f\n", c->viewport_width, c->viewport_height, c->lower_left_corner.x, c->lower_left_corner.y, c->lower_left_corner.z);
}

/**
 * @brief Given the forward vector and a vector with 3 rotation angles,
 * it gives the look_at point
*/
t_point3	look_at(t_vec3 forward, t_vec3 rot)
{
	t_point3	look_at;

	look_at.x = forward.x + cos(rot.x) * cos(rot.y);
	look_at.y = forward.y + sin(rot.x);
	look_at.z = forward.z + cos(rot.x) * sin(rot.y);
	return (look_at);
}
