/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:54:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/16 17:25:39 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include <stdio.h>

double	radians(double grades)
{
	return (grades * M_PI / 180);
};

void	cam_orientation(t_camera *c)
{
	t_point3	lookat;
	// t_vec3		w;
	// t_vec3		u;
	// t_vec3		v;

	lookat = cam_look_at(c->look_at, c->orientation);
	printf("LookAt: %f %f %f\n", lookat.x, lookat.y, lookat.z);
	// w = vec3_unit(vec3_sub(c->pos, c->lookat))
}

void	cam_setup(t_camera *c)
{
	double	ratio;
	t_vec3	half_hor;
	t_vec3	half_ver;
	t_vec3	temp;

	cam_orientation(c);
	ratio = WIDTH / (double)HEIGHT;
	c->viewport_width = 2.0f * (tan(radians(c->fov) / 2.0f));
	c->viewport_height = c->viewport_width / ratio;
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
 * @brief Given the forward vector and a vector with 3 rotation angles
 * in range [-1, 1], it gives the look_at point
*/
t_point3	cam_look_at(t_vec3 forward, t_vec3 rot)
{
	t_vec3	look_at;

	look_at.x = forward.x * cos(rot.x * M_PI) * cos(rot.y * M_PI);
	look_at.y = forward.y * sin(rot.x * M_PI) * cos(rot.y * M_PI);
	look_at.z = forward.z * sin(rot.y * M_PI);
	return (vec3_unit(look_at));
}

