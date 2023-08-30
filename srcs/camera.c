/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:54:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/08/31 00:22:28 by tfregni          ###   ########.fr       */
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
	t_vec3	new;

	printf("viewport_width: %f\tviewport_height: %f\n", c->viewport_width, c->viewport_height);
	c->look_at = vec3_unit(vec3_sub(vec3_unit(c->orientation), c->pos));
	c->right = vec3_unit(vec3_cross(c->look_at, c->vert_up));
	c->up = vec3_unit(vec3_cross(c->right, c->look_at));
	if (vec3_len(c->up) == 0)
	{
		new = vec3(0, 0, 1);
		c->right = vec3_unit(vec3_cross(c->look_at, new));
		c->up = vec3_unit(vec3_cross(c->right, c->look_at));
	}
	printf("look_at: "); vec3_print(c->look_at);
	printf("\nright: "); vec3_print(c->right);
	printf("\nup: "); vec3_print(c->up); printf("\n");
	c->m = mx_lookat(c->right, c->up, c->look_at, c->pos);
}

/**
 * Through testing with pos 0,0,5 and orient 0,0,0 I got that
 * right = cross(look_at, vert_up) = 1,0,0
 * up = cross(right, look_at) = 0,1,0
 * Can change the sign by reversing the factors in cross
 * x -> y
 * y -> x
*/
void	cam_setup(t_camera *c)
{
	c->aspect_ratio = (double)WIDTH / (double)HEIGHT;
	c->viewport_width = tan(radians(c->fov / 2.0f)) * 2.0f;
	c->viewport_height = c->viewport_width / c->aspect_ratio;
}


