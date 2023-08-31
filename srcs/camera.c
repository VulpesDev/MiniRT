/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:54:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/08/31 17:44:42 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ray.h"
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

// void	cam_setup(t_camera *c)
// {
// 	t_vec3	half_hor;
// 	t_vec3	half_ver;
// 	t_vec3	temp;

// 	c->m = mx_get_identity();
// 	cam_orientation(c);
// 	c->aspect_ratio = WIDTH / (double)HEIGHT;
// 	c->viewport_width = 2.0f * (tan(radians(c->fov) / 2.0f));
// 	c->viewport_height = c->viewport_width / c->aspect_ratio;
// 	c->horizontal = vec3(c->viewport_width, 0, 0);
// 	c->vertical = vec3(0, -c->viewport_height, 0);
// 	// c->horizontal = vec3_mult(c->right, c->viewport_width);
// 	// c->vertical = vec3_mult(c->up, -c->viewport_height);
// 	half_hor = vec3_div(c->horizontal, 2);
// 	half_ver = vec3_div(c->vertical, 2);
// 	temp = vec3_sub(c->pos, vec3(0, 0, c->focal_length));
// 	temp = vec3_sub(c->pos, half_hor);
// 	temp = vec3_sub(temp, half_ver);
// 	c->viewport_top_left = vec3_sub(temp, vec3(0, 0, c->focal_length));
// 	c->pxl_size_hor = vec3_div(c->horizontal, WIDTH);
// 	c->pxl_size_ver = vec3_div(c->vertical, HEIGHT);
// 	printf("Camera: vp_w: %f, vp_h: %f, ratio: %f, top_left: %f %f %f\n", c->viewport_width, c->viewport_height, c->aspect_ratio, c->viewport_top_left.x, c->viewport_top_left.y, c->viewport_top_left.z);
// 	printf("Horizontal: ");
// 	vec3_print(c->horizontal);
// 	printf(" Half_hor: ");
// 	vec3_print(half_hor);
// 	printf("\nVertical: ");
// 	vec3_print(c->vertical);
// 	printf(" Half_ver: ");
// 	vec3_print(half_ver);
// 	printf("\n");
// }

void	cam_setup(t_camera *c)
{
	c->m = mx_get_identity();
	cam_orientation(c);
	c->aspect_ratio = WIDTH / (double)HEIGHT;
	c->viewport_width = 2.0f * (tan(radians(c->fov) / 2.0f));
	c->viewport_height = c->viewport_width / c->aspect_ratio;
	c->half_hor = c->viewport_width/2;
	c->half_ver = c->viewport_height/2;
	c->horizontal = vec3(c->viewport_width, 0, 0);
	c->vertical = vec3(0, -c->viewport_height, 0);
	// c->horizontal = vec3_mult(c->right, c->viewport_width);
	// c->vertical = vec3_mult(c->up, -c->viewport_height);
	c->viewport_top_left = ray_at(ray(c->pos, c->orientation), c->focal_length);
	c->viewport_top_left = vec3_sub(c->viewport_top_left, vec3_mult(c->right, c->viewport_width/2));
	c->viewport_top_left = vec3_sum(c->viewport_top_left, vec3_mult(c->up, c->viewport_height/2));
	/*1. calculate point at t of direction
		2. move horizontally and vertiacally to the top left*/
	c->pxl_size_hor = vec3_div(c->horizontal, WIDTH);
	c->pxl_size_ver = vec3_div(c->vertical, HEIGHT);
	printf("Camera: vp_w: %f, vp_h: %f, ratio: %f, top_left: %f %f %f\n", c->viewport_width, c->viewport_height, c->aspect_ratio, c->viewport_top_left.x, c->viewport_top_left.y, c->viewport_top_left.z);
	printf("Horizontal: ");
	vec3_print(c->horizontal);
}

// void	cam_setup(t_camera *c)
// {
// 	t_vec3	half_hor;
// 	t_vec3	half_ver;
// 	t_vec3	temp;

// 	t_vec3	vup = vec3(0, 1, 0);
// 	c->m = mx_get_identity();
// 	cam_orientation(c);
// 	c->focal_length = vec3_len(vec3_sub(c->pos, c->look_at));
// 	c->aspect_ratio = (double)WIDTH / (double)HEIGHT;
// 	c->viewport_height = 2.0f * (tan(radians(c->fov) / 2.0f)) * c->focal_length;
// 	c->viewport_width = c->viewport_height * c->aspect_ratio;
// 	t_vec3	w,u,v;

// 	w = vec3_unit(vec3_sub(c->pos, c->look_at));
// 	u = vec3_unit(vec3_cross(vup, w));
// 	v = vec3_cross(w, u);
// 	c->horizontal = vec3_mult(u, c->viewport_width);
// 	c->vertical = vec3_mult(vec3_inv(v), c->viewport_height);
// 	half_hor = vec3_div(c->horizontal, 2);
// 	half_ver = vec3_div(c->vertical, 2);
// 	temp = vec3_mult(w, c->focal_length);
// 	temp = vec3_sub(temp, half_hor);
// 	temp = vec3_sub(temp, half_ver);
// 	c->viewport_top_left = vec3_sub(c->pos, temp);
// 	c->pxl_size_hor = vec3_div(c->horizontal, WIDTH);
// 	c->pxl_size_ver = vec3_div(c->vertical, HEIGHT);

// 	printf("Camera: vp_w: %f, vp_h: %f, ratio: %f, top_left: %f %f %f\n", c->viewport_width, c->viewport_height, c->aspect_ratio, c->viewport_top_left.x, c->viewport_top_left.y, c->viewport_top_left.z);
// 	printf("Horizontal: ");
// 	vec3_print(c->horizontal);
// 	printf(" Half_hor: ");
// 	vec3_print(half_hor);
// 	printf("\nVertical: ");
// 	vec3_print(c->vertical);
// 	printf(" Half_ver: ");
// 	vec3_print(half_ver);
// 	printf("\n");
// }


