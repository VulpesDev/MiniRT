/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:54:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/08/29 13:39:57 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include <stdio.h>

double	radians(double grades)
{
	return (grades * M_PI / 180);
};

// void	cam_scratch_orientation(t_camera *c)
// {
// 	t_matrix	cam_to_world;
// 	t_matrix	*m;

// 	m = &cam_to_world;
// 	c->look_at = vec3_unit(vec3_sub(c->pos, c->orientation));
// 	c->right = vec3_unit(vec3_cross(c->vup, c->look_at));
// 	c->up = vec3_cross(c->look_at, c->right);
// 	m->size = 16;
// 	m->matrix[0][0] = c->right.x;
// 	m->matrix[0][1] = c->right.y;
// 	m->matrix[0][2] = c->right.z;
// 	m->matrix[0][3] = 0;
// 	m->matrix[1][0] = c->up.x;
// 	m->matrix[1][1] = c->up.y;
// 	m->matrix[1][2] = c->up.z;
// 	m->matrix[1][3] = 0;
// 	m->matrix[2][0] = c->look_at.x;
// 	m->matrix[2][1] = c->look_at.y;
// 	m->matrix[2][2] = c->look_at.z;
// 	m->matrix[2][3] = 0;
// 	m->matrix[3][0] = c->pos.x;
// 	m->matrix[3][1] = c->pos.y;
// 	m->matrix[3][2] = c->pos.z;
// 	m->matrix[3][3] = 1;
// 	c->m = mx_cross(c->m, cam_to_world);
// }

/**
 * Remember that cross product is anticommutative, so a x b = -b x a
*/
void	cam_orientation(t_camera *c)
{
	// cam_scratch_orientation(c);
	c->right = vec3_unit(vec3_cross(c->orientation, c->vert_up));
	c->up = vec3_unit(vec3_cross(c->right, c->orientation));
	c->look_at = vec3_unit(c->orientation);
	c->m.size = 16;
	c->m.matrix[0][0] = c->right.x;
	c->m.matrix[0][1] = c->right.y;
	c->m.matrix[0][2] = c->right.z;
	c->m.matrix[0][3] = 0;
	c->m.matrix[1][0] = c->up.x;
	c->m.matrix[1][1] = c->up.y;
	c->m.matrix[1][2] = c->up.z;
	c->m.matrix[1][3] = 0;
	c->m.matrix[2][0] = c->vert_up.x;
	c->m.matrix[2][1] = c->vert_up.y;
	c->m.matrix[2][2] = c->vert_up.z;
	c->m.matrix[2][3] = 0;
	c->m.matrix[3][0] = c->pos.x;
	c->m.matrix[3][1] = c->pos.y;
	c->m.matrix[3][2] = c->pos.z;
	c->m.matrix[3][3] = 1;
}

void	cam_setup(t_camera *c)
{
	t_vec3	half_hor;
	t_vec3	half_ver;
	t_vec3	temp;

	c->m = mx_get_identity();
	cam_orientation(c);
	c->aspect_ratio = WIDTH / (double)HEIGHT;
	c->viewport_width = 2.0f * (tan(radians(c->fov) / 2.0f));
	c->viewport_height = c->viewport_width / c->aspect_ratio;
	c->horizontal = vec3(c->viewport_width, 0, 0);
	c->vertical = vec3(0, -c->viewport_height, 0);
	// c->horizontal = vec3_mult(c->right, c->viewport_width);
	// c->vertical = vec3_mult(c->up, -c->viewport_height);
	half_hor = vec3_div(c->horizontal, 2);
	half_ver = vec3_div(c->vertical, 2);
	temp = vec3_sub(c->pos, vec3(0, 0, c->focal_length));
	temp = vec3_sub(c->pos, half_hor);
	temp = vec3_sub(temp, half_ver);
	c->viewport_top_left = vec3_sub(temp, vec3(0, 0, c->focal_length));
	c->pxl_size_hor = vec3_div(c->horizontal, WIDTH);
	c->pxl_size_ver = vec3_div(c->vertical, HEIGHT);
	printf("Camera: vp_w: %f, vp_h: %f, ratio: %f, top_left: %f %f %f\n", c->viewport_width, c->viewport_height, c->aspect_ratio, c->viewport_top_left.x, c->viewport_top_left.y, c->viewport_top_left.z);
	printf("Horizontal: ");
	vec3_print(c->horizontal);
	printf(" Half_hor: ");
	vec3_print(half_hor);
	printf("\nVertical: ");
	vec3_print(c->vertical);
	printf(" Half_ver: ");
	vec3_print(half_ver);
	printf("\n");
}


