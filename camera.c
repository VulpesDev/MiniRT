/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:54:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/07/02 14:19:48 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "vector_math.h"
#include <stdio.h>

double	radians(double grades)
{
	return (grades * M_PI / 180);
};

t_vec3	point_in_dir(t_vec3 origin, t_vec3 orientation)
{
	t_vec3	temp;

	temp = vect_mult(orientation, 1.0f); // 1 is just random distance
	return (vect_sum(origin, temp));
}

void	cam_setup(t_camera *c)
{
	t_vec3	half_hor;
	t_vec3	half_ver;
	t_vec3	temp;
	t_point3	lookat;
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;

	c->vup = vec3(0, 1, 0);
	lookat = point_in_dir(c->pos, c->orientation);
	printf("LookAt: %f %f %f\n", lookat.x, lookat.y, lookat.z);
	w = vec3_unit(vec3_sub(c->pos, lookat));
	u = vec3_unit(vect_cross(c->vup, w));
	v = vect_cross(w, u);
	
	c->viewport_width = 2.0f * (tan(radians(c->fov) / 2.0f));
	c->viewport_height = c->viewport_width / (WIDTH / (double)HEIGHT);
	c->horizontal = vect_mult(u, c->viewport_width);
	c->vertical = vect_mult(v, c->viewport_height);
	half_hor = vec3_div(c->horizontal, 2);
	half_ver = vec3_div(c->vertical, 2);
	temp = vec3_sub(c->pos, half_hor);
	temp = vec3_sub(temp, half_ver);
	c->lower_left_corner = vec3_sub(temp, w);
	printf("Camera: vp_w: %f, vp_h: %f, lower_left: %f %f %f\n", c->viewport_width, c->viewport_height, c->lower_left_corner.x, c->lower_left_corner.y, c->lower_left_corner.z);
}

